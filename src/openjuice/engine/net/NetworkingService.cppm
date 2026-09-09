/**
 * @file NetworkingService.cppm
 * @module openjuice.engine.net:NetworkingService
 * @brief Implementation of the NetworkingService class.
 *
 * This file contains the implementation of the NetworkingService class, the single central point
 * through which all online connectivity (lobby setup, chat, matchmaking) is routed.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.net:NetworkingService;

import stdx;

import openjuice.chat;

using stdx::collections::Vector;
using stdx::inject::Inject;
using stdx::inject::Named;
using stdx::inject::Singleton;
using stdx::mem::SharedPointer;
using stdx::meta::reflect::Class;
using stdx::net::BindException;
using stdx::net::Endpoint;
using stdx::net::IPAddress;
using stdx::net::IPv4Address;
using stdx::net::SocketException;
using stdx::net::UdpSocket;
using stdx::net::UnknownHostException;
using stdx::sync::Atomic;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;
using stdx::thread::Thread;
using stdx::thread::StopToken;
using stdx::util::logging::Logger;

using openjuice::chat::ChatClient;
using openjuice::chat::ChatConnectionFactory;
using openjuice::chat::ChatServer;

BEGIN_MODULE_NAMESPACE(openjuice::engine::net);

/**
 * @class NetworkingService
 * @brief Central service for all online connectivity in the engine.
 *
 * Owned by Engine and injected into the online screens. It is the single entry point for setting up
 * lobbies, chat, and matchmaking connections, so that networking is not scattered across the parts
 * that use it. The public surface is thread-safe: it is reached from the UI thread (via screens)
 * and from the service's own I/O work, so all mutable state is guarded.
 */
export class [[=Singleton]] NetworkingService final {
public:
    static constexpr u16 DEFAULT_LOBBY_PORT = 49152; ///< Default TCP port a host binds and a joiner reaches, absent an override.
    static constexpr u16 DISCOVERY_PORT = 49153; ///< UDP port hosts listen on for discovery probes and reply with a beacon.
    static constexpr usize DISCOVERY_BUFFER_SIZE = 2048; ///< Largest discovery datagram accepted.
    static constexpr StringView DISCOVERY_PROBE = "OPENJUICE_LOBBY_QUERY"; ///< The probe a searching client broadcasts.
    static constexpr StringView BEACON_PREFIX = "OPENJUICE_LOBBY"; ///< The tag a host's beacon reply starts with.

    /**
     * @struct DiscoveredLobby
     * @brief A game lobby found on the local network, as reported by a host's discovery beacon.
     */
    struct DiscoveredLobby {
        String name; ///< The lobby's display name.
        String host; ///< The host's address, as text, used to join.
        u16 port = DEFAULT_LOBBY_PORT; ///< The port the host is listening on.
        bool passwordProtected = false; ///< True for a private (password-protected) lobby.
        u8 players = 0; ///< Current player count.
        u8 maxPlayers = 0; ///< Maximum player count.
        String timer; ///< The configured game timer, as text.
        String events; ///< The configured events, as text.
        String fieldName; ///< The board/field name.
    };

    /**
     * @enum Status
     * @brief The connection state of the networking service.
     */
    enum class Status: u8 {
        OFFLINE, ///< Not connected and not attempting to connect.
        CONNECTING, ///< A connection attempt is in progress.
        ONLINE, ///< Connected and able to service lobby/chat/matchmaking requests.
    };
private:
    SharedPointer<Logger> logger; ///< The logger instance.
    SharedPointer<ChatConnectionFactory> chatConnectionFactory; ///< Builds ChatServer/ChatClient instances on demand, so this service depends on no LoggerFactory of its own.

    mutable Mutex connectionMutex; ///< Guards mutable connection state touched from multiple threads.
    Atomic<Status> status = Status::OFFLINE; ///< Current connection state, read without the lock.
    bool initialized = false; ///< Whether init() has run.

    SharedPointer<ChatServer> chatServer; ///< The chat server, present only while this player is hosting.
    SharedPointer<ChatClient> chatConnection; ///< This player's connection to the game's chat, host included.

    mutable Mutex discoveryMutex; ///< Guards the discovered-lobby list, filled by the listener thread and drained by the UI thread.
    Vector<DiscoveredLobby> discovered; ///< Lobbies heard from since discovery started.
    Thread discoveryThread; ///< Listens for beacon replies. Joined by stopDiscovery()/the destructor.
    Atomic<bool> discovering = false; ///< Whether the discovery listener is running.
    Atomic<bool> reprobeRequested = false; ///< Set by refreshDiscovery() so the discovery thread re-broadcasts on its next turn.
    Function<void()> onDiscovery; ///< Woken on the listener thread when a lobby is found. Keep it cheap and off the UI. May be empty.

    /**
     * @brief Encode a lobby as a single-line, tab-separated beacon payload.
     * @param lobby The lobby to advertise.
     * @return The line a host sends in reply to a probe.
     *
     * A deliberately simple line format rather than JSON: both ends live here, the chat layer
     * already speaks newline-delimited text, and a fixed field order keeps parsing of untrusted
     * network input trivial to bound. The name/timer/events/field are assumed free of tabs.
     */
    [[nodiscard]]
    static String encodeBeacon(const DiscoveredLobby& lobby) {
        return Ops::fmt(
            "{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}",
            BEACON_PREFIX,
            lobby.name,
            lobby.passwordProtected ? 1 : 0,
            lobby.players,
            lobby.maxPlayers,
            lobby.timer,
            lobby.events,
            lobby.fieldName
        );
    }

    /**
     * @brief Parse a beacon payload into a lobby, filling in the sender's address.
     * @param payload The received datagram text.
     * @param from The endpoint the datagram came from, used for the host address/port.
     * @return The lobby, or an empty Optional if the payload is not a well-formed beacon.
     *
     * Treats the payload as untrusted: anything not matching the expected prefix and field count is
     * rejected rather than trusted.
     */
    [[nodiscard]]
    static Optional<DiscoveredLobby> decodeBeacon(StringView payload, const Endpoint& from) {
        Vector<String> fields;
        usize start = 0;
        while (true) {
            const usize tab = payload.find('\t', start);
            if (tab == StringView::npos) {
                fields.emplace_back(payload.substr(start));
                break;
            }
            fields.emplace_back(payload.substr(start, tab - start));
            start = tab + 1;
        }

        if (fields.size() != 8 || fields[0] != BEACON_PREFIX) {
            return nullopt;
        }

        return DiscoveredLobby {
            .name = fields[1],
            .host = Ops::fmt("{}", from.address()),
            .port = from.port(),
            .passwordProtected = Boolean::parse_or(fields[2], false),
            .players = Byte::parse_or(fields[3], 0),
            .maxPlayers = Byte::parse_or(fields[4], 0),
            .timer = fields[5],
            .events = fields[6],
            .fieldName = fields[7],
        };
    }

    /**
     * @brief Tear down the chat server and client without taking the lock.
     */
    void teardownChat() noexcept {
        if (chatConnection != nullptr) {
            chatConnection.reset();
        }

        if (chatServer != nullptr) {
            chatServer.reset();
        }
    }

    /**
     * @brief Send one discovery probe to the LAN broadcast address.
     *
     * Opens a short-lived broadcast socket, sends the probe to DISCOVERY_PORT, and closes it. Kept
     * self-contained so it can be driven both from thread start and from a refresh request.
     */
    void broadcastProbe() noexcept {
        try {
            UdpSocket socket = UdpSocket::unbound(IPAddress::Family::IPV4);
            socket.set_broadcast(true);

            const String probe = String(DISCOVERY_PROBE);
            const Endpoint target(IPv4Address::BROADCAST, DISCOVERY_PORT);
            static_cast<void>(socket.send_to(as_bytes(Span<const char>(probe.data(), probe.size())), target));
        } catch (const SocketException& e) {
            logger->warn("Failed to broadcast lobby discovery probe: {}!", e.what());
        }
    }

    /**
     * @brief The discovery loop: probe, then collect beacon replies until asked to stop.
     * @param token Cooperative cancellation from stopDiscovery().
     *
     * Runs on the discovery thread. The receive socket is non-blocking and polled so the loop stays
     * responsive to the stop token and to refresh requests, rather than parking in a blocking read.
     */
    void runDiscovery(StopToken token) noexcept {
        Optional<UdpSocket> socket;

        try {
            socket.emplace(UdpSocket::bind(Endpoint(IPv4Address::ANY, 0)));
            socket->socket().set_blocking(false);
        } catch (const SocketException& e) {
            logger->error("Failed to open lobby discovery socket: {}!", e.what());
            discovering.store(false);
            return;
        }

        broadcastProbe();

        Array<byte, DISCOVERY_BUFFER_SIZE> buffer;

        while (!token.stop_requested() && discovering.load()) {
            if (reprobeRequested.exchange(false)) {
                broadcastProbe();
            }

            Optional<UdpSocket::Received> received;
            try {
                received = socket->try_receive_from(Span<byte>(buffer));
            } catch (const SocketException& e) {
                logger->warn("Lobby discovery receive failed: {}!", e.what());
                Thread::sleep_for(100ms);
                continue;
            }

            if (!received.has_value()) {
                Thread::sleep_for(50ms);
                continue;
            }

            const StringView payload(reinterpret_cast<const char*>(buffer.data()), received->length);

            if (payload == DISCOVERY_PROBE) {
                continue;
            }

            Optional<DiscoveredLobby> lobby = decodeBeacon(payload, received->from);
            if (!lobby.has_value()) {
                continue;
            }

            recordLobby(Ops::move(*lobby));
        }
    }

    /**
     * @brief Store a freshly discovered lobby and wake the owner.
     * @param lobby The lobby to record.
     *
     * De-duplicates on host+port so repeated beacons refresh a single row rather than piling up.
     */
    void recordLobby(DiscoveredLobby lobby) noexcept {
        Function<void()> notify;

        {
            ScopedLock<Mutex> lock(discoveryMutex);

            bool replaced = false;
            for (DiscoveredLobby& other: discovered) {
                if (other.host == lobby.host && other.port == lobby.port) {
                    other = Ops::move(lobby);
                    replaced = true;
                    break;
                }
            }

            if (!replaced) {
                discovered.push_back(Ops::move(lobby));
            }

            notify = onDiscovery;
        }

        if (notify != nullptr) {
            notify();
        }
    }
public:
    /**
     * @brief Constructor of the NetworkingService.
     * @param logger The injected logger.
     * @param chatConnectionFactory The injected factory used to build chat connections on demand.
     */
    [[=Inject]]
    NetworkingService(
        [[=Named(*Class<NetworkingService>().name())]] SharedPointer<Logger> logger,
        SharedPointer<ChatConnectionFactory> chatConnectionFactory
    ):
        logger{Ops::move(logger)},
        chatConnectionFactory{Ops::move(chatConnectionFactory)} {}

    /**
     * @brief Destructor of the NetworkingService.
     *
     * Ensures any live connection is torn down so no I/O outlives the service.
     */
    ~NetworkingService() {
        stopDiscovery();
        disconnect();
    }

    /**
     * @brief Initialize the networking service.
     * @return True if initialization succeeded.
     *
     * Prepares the transport but does not open a connection.
     */
    [[nodiscard]]
    bool init() {
        ScopedLock<Mutex> lock(connectionMutex);

        if (initialized) {
            logger->warn("Networking already initialized; ignoring repeat call.");
            return true;
        }

        initialized = true;
        logger->info("Networking service initialized!");
        return true;
    }

    /**
     * @brief Get the current connection status.
     * @return The current Status.
     */
    [[nodiscard]]
    Status getStatus() const noexcept {
        return status.load();
    }

    /**
     * @brief Whether the service currently has a live online connection.
     * @return True when the status is ONLINE.
     */
    [[nodiscard]]
    bool isOnline() const noexcept {
        return status.load() == Status::ONLINE;
    }

    /**
     * @brief Open a connection to the online backend.
     *
     * The single place a connection is established, so lobby/chat/matchmaking all share one
     * transport rather than each opening their own.
     */
    void connect() {
        ScopedLock<Mutex> lock(connectionMutex);

        if (!initialized) {
            logger->warn("connect() called before init(); ignoring.");
            return;
        }

        if (status.load() != Status::OFFLINE) {
            logger->debug("connect() called while already connecting or online; ignoring.");
            return;
        }

        status.store(Status::CONNECTING);
        logger->info("Opening online connection...");
    }

    /**
     * @brief Tear down the current connection, if any.
     */
    void disconnect() noexcept {
        ScopedLock<Mutex> lock(connectionMutex);

        teardownChat();

        if (status.load() == Status::OFFLINE) {
            return;
        }

        status.store(Status::OFFLINE);
        logger->info("Closed online connection.");
    }

    /**
     * @brief Begin searching the local network for game lobbies.
     * @param onFound Woken on the discovery thread each time a lobby is found. Keep it cheap and do
     * not touch the UI from it: use it only to wake the owner, which then calls collectLobbies().
     * @return True if discovery started (or was already running).
     *
     * Broadcasts a probe and listens for host beacons on a background thread. Results accumulate
     * until stopDiscovery() or refreshDiscovery(). Safe to call again while running (a no-op).
     */
    [[nodiscard]]
    bool startDiscovery(Function<void()> onFound = nullptr) {
        if (discovering.exchange(true)) {
            return true;
        }

        {
            ScopedLock<Mutex> lock(discoveryMutex);
            discovered.clear();
            onDiscovery = Ops::move(onFound);
        }

        try {
            discoveryThread = Thread([this](StopToken token) -> void {
                runDiscovery(token);
            });
        } catch (const Exception& e) {
            discovering.store(false);
            logger->error("Failed to start lobby discovery: {}!", e.what());
            return false;
        }

        logger->info("Started lobby discovery.");
        return true;
    }

    /**
     * @brief Re-broadcast a probe and clear results collected so far.
     *
     * Backs the "Refresh" action. Does nothing if discovery is not running.
     */
    void refreshDiscovery() noexcept {
        if (!discovering.load()) {
            return;
        }

        {
            ScopedLock<Mutex> lock(discoveryMutex);
            discovered.clear();
        }

        reprobeRequested.store(true);
    }

    /**
     * @brief Take a snapshot of the lobbies found so far.
     * @return The discovered lobbies. Called on the UI thread.
     */
    [[nodiscard]]
    Vector<DiscoveredLobby> collectLobbies() const {
        ScopedLock<Mutex> lock(discoveryMutex);
        return discovered;
    }

    /**
     * @brief Stop searching the local network and join the discovery thread.
     *
     * Safe to call when discovery is not running.
     */
    void stopDiscovery() noexcept {
        if (!discovering.exchange(false)) {
            return;
        }

        discoveryThread.request_stop();

        if (discoveryThread.joinable()) {
            discoveryThread.join();
        }

        {
            ScopedLock<Mutex> lock(discoveryMutex);
            onDiscovery = nullptr;
        }

        logger->info("Stopped lobby discovery.");
    }

    /**
     * @brief Start hosting the chat for a game this player is creating.
     * @param port The port to bind, defaulted to DEFAULT_LOBBY_PORT.
     * @return True if the server bound successfully.
     */
    [[nodiscard]]
    bool hostChat(u16 port = DEFAULT_LOBBY_PORT) {
        ScopedLock<Mutex> lock(connectionMutex);

        if (chatServer != nullptr) {
            logger->warn("Already hosting chat; ignoring repeat hostChat() call.");
            return true;
        }

        try {
            chatServer = chatConnectionFactory->createServer(port);
        } catch (const BindException& e) {
            logger->error("Failed to host chat on port {}: {}!", port, e.what());
            return false;
        }

        logger->info("Hosting chat on port {}.", port);
        return true;
    }

    /**
     * @brief Connect this player to a game's chat.
     * @param host The host address to connect to.
     * @param port The port the host is listening on, defaulted to DEFAULT_LOBBY_PORT.
     * @param onMessage Woken on the client's listener thread when messages arrive. Keep it cheap and
     * do not touch the UI from it: use it only to wake the owner, which then calls collectChat().
     * @return True if the connection was established.
     */
    [[nodiscard]]
    bool joinChat(StringView host, u16 port = DEFAULT_LOBBY_PORT, Function<void()> onMessage = nullptr) {
        ScopedLock<Mutex> lock(connectionMutex);

        if (chatConnection != nullptr) {
            logger->warn("Already connected to chat; ignoring repeat joinChat() call.");
            return true;
        }

        try {
            chatConnection = chatConnectionFactory->createClient(host, port, Ops::move(onMessage));
        } catch (const UnknownHostException& e) {
            logger->error("Failed to join chat at {}:{}: unknown host: {}!", host, port, e.what());
            return false;
        } catch (const BindException& e) {
            logger->error("Failed to join chat at {}:{}: {}!", host, port, e.what());
            return false;
        }

        logger->info("Joined chat at {}:{}.", host, port);
        return true;
    }

    /**
     * @brief Leave the current chat, closing this player's connection and stopping hosting.
     */
    void leaveChat() noexcept {
        ScopedLock<Mutex> lock(connectionMutex);
        teardownChat();
    }

    /**
     * @brief Send a message to the current chat.
     * @param message The message to send, without a trailing newline.
     * @return True if the message was handed to the connection.
     *
     * Does nothing and returns false when not connected to a chat.
     */
    bool sendChat(StringView message) noexcept {
        ScopedLock<Mutex> lock(connectionMutex);

        if (chatConnection == nullptr) {
            return false;
        }

        return chatConnection->send(message);
    }

    /**
     * @brief Take the chat messages received since the last call.
     * @return The messages, oldest first, or empty when not connected.
     *
     * Called on the UI thread after the onMessage callback wakes it.
     */
    [[nodiscard]]
    Vector<String> collectChat() {
        ScopedLock<Mutex> lock(connectionMutex);

        if (chatConnection == nullptr) {
            return {};
        }

        return chatConnection->collect();
    }

    /**
     * @brief Whether this player currently has a live chat connection.
     * @return True when a chat client exists and is still connected.
     */
    [[nodiscard]]
    bool inChat() const noexcept {
        ScopedLock<Mutex> lock(connectionMutex);
        return chatConnection != nullptr && chatConnection->isConnected();
    }
};

END_MODULE_NAMESPACE();
