/**
 * @file ChatConnectionFactory.cppm
 * @module openjuice.chat:ChatConnectionFactory
 * @brief Implementation of the ChatConnectionFactory class.
 *
 * This file contains the ChatConnectionFactory, which constructs ChatServer and ChatClient
 * instances on demand. It exists because those types mix a dependency they always need (their
 * logger) with runtime arguments the caller supplies (host, port, the message callback): the
 * factory holds the logger-minting capability and takes the runtime part per call, so that callers
 * such as NetworkingService depend on this factory rather than on a LoggerFactory of their own.
 */

module;

#include "Macros.hpp"

export module openjuice.chat:ChatConnectionFactory;

import :ChatClient;
import :ChatServer;

import stdx;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::net::BindException;
using stdx::net::UnknownHostException;
using stdx::util::logging::LoggerFactory;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatConnectionFactory
 * @brief Constructs ChatServer and ChatClient instances on demand.
 *
 * The one place that holds a LoggerFactory in the chat/networking area. It mints a fresh, correctly
 * named logger for each connection it builds.
 */
export class ChatConnectionFactory final {
private:
    SharedPointer<LoggerFactory> loggerFactory; ///< Retained to mint a per-instance logger for each connection built.
public:
    /**
     * @brief Constructs a new ChatConnectionFactory object.
     * @param loggerFactory The injected logger factory, used to name each connection's logger.
     */
    explicit ChatConnectionFactory(SharedPointer<LoggerFactory> loggerFactory):
        loggerFactory{Ops::move(loggerFactory)} {}

    /**
     * @brief Build a chat server bound to a port.
     * @param port The port to listen on.
     * @return The constructed server. Heap-allocated: ChatServer pins its own address via the
     * reactor thread, so it is not movable and must not be returned by value.
     * @throws BindException if the server fails to bind.
     */
    [[nodiscard]]
    THROWS(BindException)
    SharedPointer<ChatServer> createServer(u16 port) const {
        return Pointers::shared<ChatServer>(loggerFactory->of("ChatServer"), port);
    }

    /**
     * @brief Build a chat client connected to a host.
     * @param host The host to connect to.
     * @param port The port to connect to.
     * @param onMessage Woken on the client's listener thread when messages arrive.
     * @return The constructed client.
     * @throws BindException if the client fails to connect.
     * @throws UnknownHostException if the host is unknown.
     */
    [[nodiscard]]
    THROWS(BindException, UnknownHostException)
    SharedPointer<ChatClient> createClient(StringView host, u16 port, Function<void()> onMessage = nullptr) const {
        return Pointers::shared<ChatClient>(loggerFactory->of("ChatClient"), host, port, Ops::move(onMessage));
    }
};

END_MODULE_NAMESPACE();
