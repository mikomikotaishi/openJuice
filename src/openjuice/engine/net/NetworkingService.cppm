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
using stdx::net::UnknownHostException;
using stdx::sync::Atomic;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;
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

    mutable Mutex netMutex; ///< Guards mutable connection state touched from multiple threads.
    Atomic<Status> status = Status::OFFLINE; ///< Current connection state, read without the lock.
    bool initialized = false; ///< Whether init() has run. Guarded by netMutex.

    SharedPointer<ChatServer> chatServer; ///< The chat server, present only while this player is hosting. Guarded by netMutex.
    SharedPointer<ChatClient> chatConnection; ///< This player's connection to the game's chat, host included. Guarded by netMutex.

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
        ScopedLock<Mutex> lock(netMutex);

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
        ScopedLock<Mutex> lock(netMutex);

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
        ScopedLock<Mutex> lock(netMutex);

        teardownChat();

        if (status.load() == Status::OFFLINE) {
            return;
        }

        status.store(Status::OFFLINE);
        logger->info("Closed online connection.");
    }

    /**
     * @brief Start hosting the chat for a game this player is creating.
     * @param port The port to bind, defaulted to DEFAULT_LOBBY_PORT.
     * @return True if the server bound successfully.
     */
    [[nodiscard]]
    bool hostChat(u16 port = DEFAULT_LOBBY_PORT) {
        ScopedLock<Mutex> lock(netMutex);

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
        ScopedLock<Mutex> lock(netMutex);

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
        ScopedLock<Mutex> lock(netMutex);
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
        ScopedLock<Mutex> lock(netMutex);

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
        ScopedLock<Mutex> lock(netMutex);

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
        ScopedLock<Mutex> lock(netMutex);
        return chatConnection != nullptr && chatConnection->isConnected();
    }
};

END_MODULE_NAMESPACE();
