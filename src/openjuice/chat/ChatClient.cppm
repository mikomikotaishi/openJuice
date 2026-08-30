/**
 * @file ChatClient.cppm
 * @module openjuice.chat.ChatClient
 * @brief Implementation of the ChatClient class.
 *
 * This file contains the implementation of the ChatClient class, which is used to manage chat client connections.
 */

module;

#include "Macros.hpp"

export module openjuice.chat:ChatClient;

import stdx;

using stdx::collections::Vector;
using stdx::mem::SharedPointer;
using stdx::net::BindException;
using stdx::net::Endpoint;
using stdx::net::Resolver;
using stdx::net::SocketException;
using stdx::net::TcpStream;
using stdx::net::UnknownHostException;
using stdx::sync::Atomic;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;
using stdx::thread::Thread;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatClient
 * @brief A connection to a chat server, owned by whatever is displaying the chat.
 *
 * The client connects and returns; it does not own the terminal and does not run a chat loop. One
 * thread blocks on the socket and parks whatever arrives in a queue, and the owner drains that queue
 * whenever it is ready to draw. Delivering messages by queue rather than by calling back on the
 * network thread is what lets a UI consume them without being thread-safe itself.
 */
export class ChatClient {
public:
    static constexpr usize MAX_MESSAGE_LENGTH = 4096; ///< Longest single message accepted from the server.
private:
    static constexpr usize RECEIVE_CHUNK = 1024; ///< How much is taken off the socket per read.

    SharedPointer<Logger> logger; ///< The logger instance.
    Optional<TcpStream> stream; ///< The connection to the chat server.
    Atomic<bool> connected{false}; ///< Whether the connection is still usable.
    mutable Mutex inboxMutex; ///< Guards inbox, which the listener fills and the owner drains.
    Vector<String> inbox; ///< Messages received but not yet collected.
    Function<void()> onMessage; ///< Called on the listener thread when a message lands. May be empty.
    Thread listenerThread; ///< Receives from the server. Joined by the destructor.

    /**
     * @brief Receive from the server until the connection ends.
     *
     * The socket is left blocking, so this parks in the kernel rather than polling. The destructor
     * shuts the connection down to wake it.
     */
    void listen() {
        Array<char, RECEIVE_CHUNK> buffer;
        String messageBuffer;

        try {
            while (connected.load()) {
                const usize received = stream->receive(as_writable_bytes(Span<char>(buffer)));

                if (received == 0) {
                    break;
                }

                messageBuffer.append(buffer.data(), received);

                usize pos;
                Vector<String> complete;
                while ((pos = messageBuffer.find('\n')) != String::npos) {
                    complete.push_back(messageBuffer.substr(0, pos));
                    messageBuffer.erase(0, pos + 1);
                }

                if (messageBuffer.length() > MAX_MESSAGE_LENGTH) {
                    logger->error("Server exceeded the maximum message length");
                    break;
                }

                if (complete.empty()) {
                    continue;
                }

                {
                    ScopedLock lock{inboxMutex};
                    for (String& message: complete) {
                        inbox.push_back(Ops::move(message));
                    }
                }

                if (onMessage) {
                    onMessage();
                }
            }
        } catch (const SocketException& e) {
            if (connected.load()) {
                logger->error("Disconnected from server: {}", e.what());
            }
        }

        connected.store(false);
    }
public:
    /**
     * @brief Connect to a chat server.
     * @param host The host to connect to.
     * @param port The port to connect to.
     * @param loggerFactory Shared logger factory used to create this client's logger.
     * @param onMessage Called on the listener thread once messages are waiting; keep it cheap and
     * do not touch the UI from it. Use it to wake the owner, which then calls @ref collect.
     * @throws BindException if the client fails to connect
     * @throws UnknownHostException if the host is unknown
     */
    ChatClient(StringView host, u16 port, SharedPointer<LoggerFactory> loggerFactory, Function<void()> onMessage = nullptr) throws (BindException, UnknownHostException):
        logger{loggerFactory->of("ChatClient")},
        onMessage{Ops::move(onMessage)} {
        Optional<Endpoint> serverEndpoint;

        try {
            serverEndpoint = Resolver().resolve_one(host, port);
        } catch (const UnknownHostException& e) {
            logger->error("Unknown host {}: {}", host, e.what());
            throw;
        }

        if (!serverEndpoint) {
            logger->error("Unknown host: {}", host);
            throw UnknownHostException("Failed to resolve host");
        }

        try {
            stream.emplace(TcpStream::connect(*serverEndpoint));
        } catch (const SocketException& e) {
            logger->error("Failed to connect to server at {}:{}: {}", host, port, e.what());
            throw BindException("Failed to connect to chat server");
        }

        logger->info("Connected to server at {}:{}", host, port);
        connected.store(true);

        listenerThread = Thread([this] -> void {
            listen();
        });
    }

    /**
     * @brief Whether the connection is still usable.
     * @return true until the server closes or an error ends the connection
     */
    [[nodiscard]]
    bool isConnected() const noexcept {
        return connected.load();
    }

    /**
     * @brief Send a message to the server.
     * @param message The message to send, without a trailing newline.
     * @return true if the message was sent
     */
    bool send(StringView message) noexcept {
        if (!connected.load() || !stream) {
            return false;
        }

        String line{message};
        line += '\n';

        try {
            stream->send_all(as_bytes(Span<const char>(line.data(), line.size())));
            return true;
        } catch (const SocketException& e) {
            logger->error("Failed to send message: {}", e.what());
            connected.store(false);
            return false;
        }
    }

    /**
     * @brief Take everything received since the last call.
     * @return The messages, oldest first, with their newlines removed.
     */
    [[nodiscard]]
    Vector<String> collect() {
        ScopedLock lock{inboxMutex};
        Vector<String> taken = Ops::move(inbox);
        inbox.clear();
        return taken;
    }

    /**
     * @brief Destructor to clean up resources.
     */
    ~ChatClient() {
        connected.store(false);

        if (stream) {
            try {
                stream->shutdown();
            } catch (const Exception& _) {
                // Stream already down
            }
        }

        if (listenerThread.joinable()) {
            listenerThread.join();
        }
    }
};

END_MODULE_NAMESPACE();
