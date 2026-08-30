/**
 * @file ChatServer.cppm
 * @module openjuice.chat.ChatServer
 * @brief Implementation of the ChatServer class.
 *
 * This file contains the implementation of the ChatServer class, which is used to manage chat server connections.
 */

module;

#include "Macros.hpp"

export module openjuice.chat:ChatServer;

import stdx;

import :ChatSession;

using stdx::collections::TreeMap;
using stdx::collections::Vector;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::mem::UniquePointer;
using stdx::net::BindException;
using stdx::net::Endpoint;
using stdx::net::Event;
using stdx::net::Interest;
using stdx::net::Reactor;
using stdx::net::Socket;
using stdx::net::SocketException;
using stdx::net::TcpListener;
using stdx::net::TcpStream;
using stdx::thread::Thread;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatServer
 * @brief Class for managing chat server connections.
 *
 * The ChatServer class manages chat server connections and handles incoming client connections.
 *
 * Everything happens on one reactor thread: the listener and every session are registered with the
 * Reactor, which reports which descriptors are worth touching rather than having a thread block or
 * spin on each. That is what makes the session map safe to hold without a lock, since only that one
 * thread ever reaches it. The sole exception is Reactor::stop, which is documented as callable from
 * another thread and is how the destructor ends the loop.
 */
export class ChatServer {
private:
    using NativeHandle = Socket::NativeHandle; ///< The descriptor type sessions are keyed by.

    SharedPointer<Logger> logger; ///< The logger instance.
    Reactor reactor; ///< Readiness loop driving the listener and every session.
    Optional<TcpListener> listener; ///< Listener for incoming connections.
    TreeMap<NativeHandle, UniquePointer<ChatSession>> sessions; ///< Connected clients. Reactor thread only.
    Thread reactorThread; ///< Runs the reactor loop. Joined by the destructor before anything it touches.

    /**
     * @brief Take every connection that is already waiting.
     */
    void acceptPending() {
        while (true) {
            Optional<TcpStream> accepted;

            try {
                accepted = listener->try_accept();
            } catch (const SocketException& e) {
                logger->error("Failed to accept connection: {}", e.what());
                return;
            }

            if (!accepted) {
                return;
            }

            adopt(Ops::move(*accepted));
        }
    }

    /**
     * @brief Register a freshly accepted connection as a session.
     * @param stream The accepted connection.
     */
    void adopt(TcpStream stream) {
        const NativeHandle handle = stream.native_handle();
        String peerName = "unknown";

        try {
            stream.socket().set_blocking(false);

            if (const Optional<Endpoint> peer = stream.remote_endpoint(); peer) {
                peerName = Ops::fmt("{}", *peer);
            }
        } catch (const SocketException& e) {
            logger->error("Failed to set up accepted connection: {}", e.what());
            return;
        }

        sessions.emplace(handle, Pointers::unique<ChatSession>(Ops::move(stream), peerName));

        try {
            reactor.add(handle, Interest::READ, [this, handle](const Event& event) -> void {
                onSessionReady(handle, event);
            });
        } catch (const Exception& e) {
            logger->error("Failed to register client with the reactor: {}", e.what());
            sessions.erase(handle);
            return;
        }

        logger->info("[{}] connected", peerName);
    }

    /**
     * @brief Handle a session that the reactor reports as ready.
     * @param handle The session's descriptor.
     * @param event What the reactor reported.
     */
    void onSessionReady(NativeHandle handle, const Event& event) {
        const auto found = sessions.find(handle);
        if (found == sessions.end()) {
            return;
        }

        const StringView peer = found->second->peer();
        Vector<String> messages;
        bool open = true;

        try {
            open = found->second->drain(messages);
        } catch (const SocketException& e) {
            logger->error("[{}] dropped after a socket error: {}", peer, e.what());
            drop(handle);
            return;
        }

        for (const String& message: messages) {
            logger->info("[{}] {}", peer, message);
            broadcast(handle, message);
        }

        if (!open || event.error || event.hangup) {
            logger->info("[{}] disconnected", peer);
            drop(handle);
        }
    }

    /**
     * @brief Send a message to every client except the one it came from.
     * @param from The descriptor the message arrived on.
     * @param message The message to send, newline included.
     */
    void broadcast(NativeHandle from, StringView message) {
        Vector<NativeHandle> failed;

        for (const auto& [handle, session]: sessions) {
            if (handle == from) {
                continue;
            }

            try {
                session->deliver(message);
            } catch (const SocketException& e) {
                logger->error("[{}] failed to deliver a message: {}", session->peer(), e.what());
                failed.push_back(handle);
            }
        }

        // Collected rather than dropped in the loop above, which would invalidate its iterator.
        for (const NativeHandle handle: failed) {
            drop(handle);
        }
    }

    /**
     * @brief Deregister a session and close it.
     * @param handle The session's descriptor.
     *
     * Safe to call from inside that session's own handler: the Reactor drops the kernel
     * registration before returning and keeps the handler alive until the turn ends.
     */
    void drop(NativeHandle handle) {
        const auto found = sessions.find(handle);
        if (found == sessions.end()) {
            return;
        }

        try {
            reactor.remove(handle);
        } catch (const Exception& e) {
            logger->error("[{}] failed to deregister: {}", found->second->peer(), e.what());
        }

        sessions.erase(found);
    }
public:
    /**
     * @brief Constructor to initialize a ChatServer object.
     * @param port The port to listen on.
     * @param loggerFactory Shared logger factory used to create this server's logger.
     * @throws BindException if the server fails to start
     */
    ChatServer(u16 port, SharedPointer<LoggerFactory> loggerFactory) throws (BindException):
        logger{loggerFactory->of("ChatServer")} {
        try {
            listener.emplace(TcpListener::bind_dual_stack(port));
            listener->socket().set_blocking(false);
        } catch (const SocketException& e) {
            logger->error("Failed to bind server to port {}: {}", port, e.what());
            throw BindException("Failed to start chat server");
        }

        reactor.add(listener->native_handle(), Interest::READ, [this](const Event& event) -> void {
            if (event.error || event.hangup) {
                logger->error("Listening socket failed; the server is no longer accepting clients");
                reactor.stop();
                return;
            }

            acceptPending();
        });

        logger->info("Chat server listening on port {}", port);

        reactorThread = Thread([this] -> void {
            try {
                reactor.run();
            } catch (const Exception& e) {
                logger->error("Reactor loop ended: {}", e.what());
            }
        });
    }

    /**
     * @brief Destructor to clean up resources.
     */
    ~ChatServer() {
        try {
            reactor.stop();

            if (reactorThread.joinable()) {
                reactorThread.join();
            }
        } catch (const Exception& _) {
            // Nothing useful to do while unwinding.
        }
    }
};

END_MODULE_NAMESPACE();
