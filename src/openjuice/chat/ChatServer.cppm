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
import sfml;

import :ChatSession;

using stdx::collections::Vector;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::mem::UniquePointer;
using stdx::net::BindException;
using stdx::thread::Thread;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using sfml::net::Socket;
using sfml::net::TcpListener;
using sfml::net::TcpSocket;

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
    TcpListener serverListener; ///< Listener for incoming connections.
    Vector<SharedPointer<ChatSession>> clients; ///< List of connected clients.
    Thread acceptThread; ///< Thread for accepting connections.
    bool running = false; ///< Server running status.

    /**
     * @brief Accept incoming connections.
     */
    void acceptConnections() {
        while (running) {
            UniquePointer<TcpSocket> clientSocket = Pointers::unique<TcpSocket>();
            
            if (serverListener.accept(*clientSocket) == Socket::Status::Done) {
                logger->info("Client connected from {}", clientSocket->getRemoteAddress()->toString());
                SharedPointer<ChatSession> session = Pointers::shared<ChatSession>(Ops::move(clientSocket), clients, loggerFactory);
                session->start();
            }
        }
    }

public:
    /**
     * @brief Constructor to initialize a ChatServer object.
     *
     * @param port The port to listen on.
     * @throws BindException if the server fails to start
     */
    ChatServer(u16 port, SharedPointer<LoggerFactory> loggerFactory) throws (BindException):
        loggerFactory{loggerFactory},
        logger{loggerFactory->of("ChatServer")} {
        if (serverListener.listen(port) != Socket::Status::Done) {
            logger->error("Failed to bind server to port {}", port);
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
        serverListener.close();
        acceptThread.request_stop();
    }
};

END_MODULE_NAMESPACE();
