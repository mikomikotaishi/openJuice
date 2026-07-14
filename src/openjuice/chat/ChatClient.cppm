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

import openjuice.engine.services;

using stdx::mem::SharedPointer;
using stdx::net::BindException;
using stdx::net::Endpoint;
using stdx::net::Resolver;
using stdx::net::SocketException;
using stdx::net::TcpStream;
using stdx::net::UnknownHostException;
using stdx::thread::Thread;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatClient
 * @brief Class for managing chat client connections.
 * 
 * The ChatClient class manages chat client connections and handles communication with the chat server.
 */
export class ChatClient {
private:
    SharedPointer<Logger> logger; ///< The logger instance.
    Optional<TcpStream> clientStream; ///< The connection to the chat server, held while connected.
    Thread listenerThread; ///< Listener thread for the chat client.
    bool connected = false; ///< Connection status.

    /**
     * @brief Start the chat client.
     */
    void startChat() {
        logger->info("Starting chat");
        String message;
        while (connected) {
            message = System::in.readln();
            if (message.empty()) {
                break;
            }
            message += "\n";

            try {
                clientStream->send_all(as_bytes(Span<const char>(message.data(), message.size())));
            } catch (const SocketException& e) {
                logger->error("Failed to send message: {}", e.what());
                connected = false;
                break;
            }
        }
    }

    /**
     * @brief Start listening for messages from the server.
     */
    void startListening() {
        listenerThread = Thread([this] -> void {
            try {
                char buffer[1024];
                String messageBuffer;
                while (connected) {
                    const Optional<usize> received = clientStream->try_receive(as_writable_bytes(Span<char>(buffer)));

                    // An empty Optional is "nothing has arrived yet"; a zero count is the server closing.
                    if (!received) {
                        continue;
                    }

                    if (*received == 0) {
                        connected = false;
                        break;
                    }

                    messageBuffer.append(buffer, *received);

                    usize pos;
                    while ((pos = messageBuffer.find('\n')) != String::npos) {
                        String message = messageBuffer.substr(0, pos);
                        System::out.print("\n[CHAT] {}\n> ", message);
                        System::out.flush();
                        messageBuffer.erase(0, pos + 1);
                    }
                }
            } catch (const Exception& e) {
                logger->error("Exception in listener thread: {}", e.what());
                connected = false;
                logger->error("Disconnected from server.");
            }
        });
    }

    /**
     * @brief Stop listening for messages from the server.
     */
    void stopListening() {
        connected = false;
        if (clientStream) {
            clientStream->close();
        }
        listenerThread.request_stop();
    }
public:
    /**
     * @brief Constructor to initialize a ChatClient object.
     * @param host The host to connect to.
     * @param port The port to connect to.
     * @param loggerFactory Shared logger factory used to create this client's logger.
     * @throws BindException if the client fails to connect
     * @throws UnknownHostException if the host is unknown
     */
    ChatClient(StringView host, u16 port, SharedPointer<LoggerFactory> loggerFactory) throws (BindException, UnknownHostException):
        logger{loggerFactory->of("ChatClient")} {
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
            clientStream.emplace(TcpStream::connect(*serverEndpoint));
        } catch (const SocketException& e) {
            logger->error("Failed to connect to server at {}:{}: {}", host, port, e.what());
            throw BindException("Failed to connect to chat server");
        }
        
        logger->info("Connected to server at {}:{}", host, port);
        connected = true;
        clientStream->socket().set_blocking(false); // Non-blocking for listener thread
        startListening();
        clientStream->socket().set_blocking(true); // Blocking for main chat
        startChat();
    }
    
    /**
     * @brief Destructor to clean up resources.
     */
    ~ChatClient() {
        stopListening();
    }
};

END_MODULE_NAMESPACE();
