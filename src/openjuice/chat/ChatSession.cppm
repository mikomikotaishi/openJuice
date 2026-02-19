/**
 * @file ChatSession.cppm
 * @module openjuice.chat.ChatSession
 * @brief Implementation of the ChatSession class.
 *
 * This file contains the implementation of the ChatSession class, which is used to manage individual chat sessions.
 */

module;

#include "Macros.hpp"

export module openjuice.chat:ChatSession;

import stdx;
import sfml;

using stdx::collections::Vector;
using stdx::linq::Query;
using stdx::mem::EnableSharedFromThis;
using stdx::mem::SharedPointer;
using stdx::mem::UniquePointer;
using stdx::thread::JoiningThread;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using sfml::net::Socket;
using sfml::net::TcpSocket;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatSession
 * @brief Class for managing individual chat sessions.
 * 
 * The ChatSession class manages individual chat sessions and handles communication with clients.
 */
export class ChatSession: public EnableSharedFromThis<ChatSession> {
private:
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("ChatSession"); ///< The logger instance.
    UniquePointer<TcpSocket> sessionSocket; ///< Socket for the chat session.
    String inputBuffer; ///< Buffer for incoming messages.
    Vector<SharedPointer<ChatSession>>& clients; ///< List of connected clients.
    JoiningThread sessionThread; ///< Thread for handling this session.
    bool isActive = false; ///< Session active status.

    /**
     * @brief Broadcast a message to all clients.
     *
     * @param msg The message to broadcast.
     */
    void broadcast(const String& msg) {
        for (SharedPointer<ChatSession>& client: clients) {
            if (client.get() != this) {
                client->deliver(msg);
            }
        }
    }

    /**
     * @brief Remove the client from the list of connected clients.
     */
    void removeClient() {
        clients = Query(clients)
            .where([this](const auto& c) -> bool { return c.get() != this; })
            .to<Vector>();
    }

    /**
     * @brief Read messages from the client.
     */
    void readMessages() {
        char buffer[1024];
        
        while (isActive) {
            usize received = 0;
            Socket::Status status = sessionSocket->receive(buffer, sizeof(buffer), received);
            
            if (status == Socket::Status::Done && received > 0) {
                inputBuffer.append(buffer, received);
                
                // Process complete messages (delimited by newline)
                usize pos;
                while ((pos = inputBuffer.find('\n')) != String::npos) {
                    String message = inputBuffer.substr(0, pos + 1);
                    inputBuffer.erase(0, pos + 1);
                    LOGGER->info("Received: {}", message);
                    broadcast(message);
                }
            } else if (status == Socket::Status::Disconnected) {
                LOGGER->info("Client disconnected");
                isActive = false;
                removeClient();
                break;
            } else if (status == Socket::Status::Error) {
                LOGGER->error("Socket error occurred");
                isActive = false;
                removeClient();
                break;
            }
        }
    }
public:
    /**
     * @brief Constructor to initialise a ChatSession object.
     *
     * @param socket The socket for the chat session.
     * @param clients The list of connected clients.
     */
    ChatSession(UniquePointer<TcpSocket> socket, Vector<SharedPointer<ChatSession>>& clients):
        sessionSocket{stdx::util::move(socket)}, clients{clients} {
        if (sessionSocket) {
            sessionSocket->setBlocking(false);
        }
    }
    
    /**
     * @brief Start the chat session.
     */
    void start() {
        isActive = true;
        
        // Start reading messages in a separate thread
        sessionThread = JoiningThread([this]() -> void {
            readMessages();
        });
    }

    /**
     * @brief Deliver a message to the client.
     *
     * @param msg The message to deliver.
     */
    void deliver(StringView msg) {
        if (sessionSocket && isActive) {
            if (sessionSocket->send(msg.data(), msg.size()) != Socket::Status::Done) {
                LOGGER->error("Failed to send message to client");
            }
        }
    }
    
    /**
     * @brief Destructor to clean up resources.
     */
    ~ChatSession() {
        isActive = false;
        if (sessionSocket) {
            sessionSocket->disconnect();
        }
        sessionThread.request_stop();
    }
};

END_MODULE_NAMESPACE();
