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
using stdx::thread::JoiningThread;
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
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("ChatServer"); ///< The logger instance.
    TcpListener serverListener; ///< Listener for incoming connections.
    Vector<SharedPointer<ChatSession>> clients; ///< List of connected clients.
    JoiningThread acceptThread; ///< Thread for accepting connections.
    bool isRunning = false; ///< Server running status.

    /**
     * @brief Accept incoming connections.
     */
    void acceptConnections() {
        while (isRunning) {
            UniquePointer<TcpSocket> clientSocket = Pointers::unique<TcpSocket>();
            
            if (serverListener.accept(*clientSocket) == Socket::Status::Done) {
                LOGGER->info("Client connected from {}", clientSocket->getRemoteAddress()->toString());
                SharedPointer<ChatSession> session = Pointers::shared<ChatSession>(System::move(clientSocket), clients);
                session->start();
            }
        }
    }

public:
    /**
     * @brief Constructor to initialise a ChatServer object.
     *
     * @param port The port to listen on.
     * @throws BindException if the server fails to start
     */
    explicit ChatServer(u16 port) throws (BindException) {
        if (serverListener.listen(port) != Socket::Status::Done) {
            LOGGER->error("Failed to bind server to port {}", port);
            throw BindException("Failed to start chat server");
        }
        
        LOGGER->info("Chat server listening on port {}", port);
        isRunning = true;
        
        // Start accepting connections in a separate thread
        acceptThread = JoiningThread([this]() -> void {
            acceptConnections();
        });
    }
    
    /**
     * @brief Destructor to clean up resources.
     */
    ~ChatServer() {
        isRunning = false;
        serverListener.close();
        acceptThread.request_stop();
    }
};

END_MODULE_NAMESPACE();
