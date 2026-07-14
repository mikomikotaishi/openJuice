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

using stdx::collections::Vector;
using stdx::linq::Query;
using stdx::mem::EnableSharedFromThis;
using stdx::mem::SharedPointer;
using stdx::net::SocketException;
using stdx::net::TcpStream;
using stdx::thread::Thread;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatSession
 * @brief Class for managing individual chat sessions.
 * 
 * The ChatSession class manages individual chat sessions and handles communication with clients.
 */
export class ChatSession: public EnableSharedFromThis<ChatSession> {
private:
    SharedPointer<Logger> logger; ///< The logger instance.
    TcpStream sessionStream; ///< The connection to this session's client.
    String inputBuffer; ///< Buffer for incoming messages.
    Vector<SharedPointer<ChatSession>>& clients; ///< List of connected clients.
    Thread sessionThread; ///< Thread for handling this session.
    bool active = false; ///< Session active status.

    /**
     * @brief Broadcast a message to all clients.
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
        clients = Query<>::from(clients)
            .where([this](const auto& c) -> bool { return c.get() != this; })
            .to<Vector>();
    }

    /**
     * @brief Read messages from the client.
     */
    void readMessages() {
        char buffer[1024];
        
        while (active) {
            Optional<usize> received;

            try {
                received = sessionStream.try_receive(as_writable_bytes(Span<char>(buffer)));
            } catch (const SocketException& e) {
                logger->error("Socket error occurred: {}", e.what());
                active = false;
                removeClient();
                break;
            }

            // An empty Optional is "nothing has arrived yet"; a zero count is the peer closing.
            if (!received) {
                continue;
            }

            if (*received == 0) {
                logger->info("Client disconnected");
                active = false;
                removeClient();
                break;
            }

            inputBuffer.append(buffer, *received);

            // Process complete messages (delimited by newline)
            usize pos;
            while ((pos = inputBuffer.find('\n')) != String::npos) {
                String message = inputBuffer.substr(0, pos + 1);
                inputBuffer.erase(0, pos + 1);
                logger->info("Received: {}", message);
                broadcast(message);
            }
        }
    }
public:
    /**
     * @brief Constructor to initialize a ChatSession object.
     * @param stream The connection to the session's client.
     * @param clients The list of connected clients.
     * @param loggerFactory Shared logger factory used to create this session's logger.
     */
    ChatSession(TcpStream stream, Vector<SharedPointer<ChatSession>>& clients, SharedPointer<LoggerFactory> loggerFactory):
        logger{loggerFactory->of("ChatSession")},
        sessionStream{Ops::move(stream)}, clients{clients} {
        sessionStream.socket().set_blocking(false);
    }
    
    /**
     * @brief Start the chat session.
     */
    void start() {
        active = true;
        
        // Start reading messages in a separate thread
        sessionThread = Thread([this] -> void {
            readMessages();
        });
    }

    /**
     * @brief Deliver a message to the client.
     * @param msg The message to deliver.
     */
    void deliver(StringView msg) {
        if (!active || !sessionStream.is_open()) {
            return;
        }

        try {
            sessionStream.send_all(as_bytes(Span<const char>(msg.data(), msg.size())));
        } catch (const SocketException& e) {
            logger->error("Failed to send message to client: {}", e.what());
        }
    }
    
    /**
     * @brief Destructor to clean up resources.
     */
    ~ChatSession() {
        active = false;
        sessionStream.close();
        sessionThread.request_stop();
    }
};

END_MODULE_NAMESPACE();
