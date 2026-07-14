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

using stdx::collections::Vector;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::net::BindException;
using stdx::net::Endpoint;
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
 */
export class ChatServer {
private:
    SharedPointer<LoggerFactory> loggerFactory; ///< The injected logger factory.
    SharedPointer<Logger> logger; ///< The logger instance.
    Optional<TcpListener> serverListener; ///< Listener for incoming connections, held until the server shuts down.
    Vector<SharedPointer<ChatSession>> clients; ///< List of connected clients.
    Thread acceptThread; ///< Thread for accepting connections.
    bool running = false; ///< Server running status.

    /**
     * @brief Accept incoming connections.
     */
    void acceptConnections() {
        while (running) {
            try {
                TcpStream accepted = serverListener->accept();
                const Optional<Endpoint> peer = accepted.remote_endpoint();

                if (peer) {
                    logger->info("Client connected from {}", *peer);
                } else {
                    logger->info("Client connected from an unknown address");
                }

                SharedPointer<ChatSession> session = Pointers::shared<ChatSession>(Ops::move(accepted), clients, loggerFactory);
                session->start();
            } catch (const SocketException& e) {
                // Closing the listener from the destructor fails the blocking accept, which is how
                // this loop is woken to notice that running has been cleared.
                if (running) {
                    logger->error("Failed to accept connection: {}", e.what());
                }
            }
        }
    }

public:
    /**
     * @brief Constructor to initialize a ChatServer object.
     * @param port The port to listen on.
     * @param loggerFactory Shared logger factory used to create this server's logger.
     * @throws BindException if the server fails to start
     */
    ChatServer(u16 port, SharedPointer<LoggerFactory> loggerFactory) throws (BindException):
        loggerFactory{loggerFactory},
        logger{loggerFactory->of("ChatServer")} {
        try {
            serverListener.emplace(TcpListener::bind_dual_stack(port));
        } catch (const SocketException& e) {
            logger->error("Failed to bind server to port {}: {}", port, e.what());
            throw BindException("Failed to start chat server");
        }
        
        logger->info("Chat server listening on port {}", port);
        running = true;
        
        // Start accepting connections in a separate thread
        acceptThread = Thread([this] -> void {
            acceptConnections();
        });
    }
    
    /**
     * @brief Destructor to clean up resources.
     */
    ~ChatServer() {
        running = false;
        if (serverListener) {
            serverListener->close();
        }
        acceptThread.request_stop();
    }
};

END_MODULE_NAMESPACE();
