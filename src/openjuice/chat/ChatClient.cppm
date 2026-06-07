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
import sfml;

import openjuice.engine.managers;

using stdx::io::Cin;
using stdx::io::Cout;
using stdx::io::File;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::net::BindException;
using stdx::net::UnknownHostException;
using stdx::thread::Thread;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using sfml::net::Dns;
using sfml::net::IpAddress;
using sfml::net::Socket;
using sfml::net::TcpSocket;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatClient
 * @brief Class for managing chat client connections.
 * 
 * The ChatClient class manages chat client connections and handles communication with the chat server.
 */
export class ChatClient {
private:
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("ChatClient"); ///< The logger instance.
    TcpSocket clientSocket; ///< Socket for the chat client.
    Thread listenerThread; ///< Listener thread for the chat client.
    bool isConnected = false; ///< Connection status.

    /**
     * @brief Start the chat client.
     */
    void startChat() {
        LOGGER->info("Starting chat");
        String message;
        while (isConnected) {
            message = System::in.readln();
            if (message.empty()) {
                break;
            }
            message += "\n";
            if (clientSocket.send(message.c_str(), message.size()) != Socket::Status::Done) {
                LOGGER->error("Failed to send message");
                isConnected = false;
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
                while (isConnected) {
                    usize received = 0;
                    Socket::Status status = clientSocket.receive(buffer, sizeof(buffer), received);
                    
                    if (status == Socket::Status::Done && received > 0) {
                        messageBuffer.append(buffer, received);

                        usize pos;
                        while ((pos = messageBuffer.find('\n')) != String::npos) {
                            String message = messageBuffer.substr(0, pos);
                            System::out.print("\n[CHAT] {}\n> ", message);
                            System::out.flush();
                            messageBuffer.erase(0, pos + 1);
                        }
                    } else if (status == Socket::Status::Disconnected) {
                        isConnected = false;
                        break;
                    }
                }
            } catch (...) {
                System::err.println("Disconnected from server.");
                isConnected = false;
            }
        });
    }

    /**
     * @brief Stop listening for messages from the server.
     */
    void stopListening() {
        isConnected = false;
        clientSocket.disconnect();
        listenerThread.request_stop();
    }
public:
    /**
     * @brief Constructor to initialise a ChatClient object.
     *
     * @param host The host to connect to.
     * @param port The port to connect to.
     * @throws BindException if the client fails to connect
     * @throws UnknownHostException if the host is unknown
     */
    ChatClient(StringView host, u16 port) throws (BindException, UnknownHostException) {
        try {
            const IpAddress serverAddress = Dns::resolve(host).value_or({IpAddress::Any}).at(0);
            if (serverAddress == IpAddress::Any) {
                LOGGER->error("Unknown host: {}", host);
                throw UnknownHostException("Failed to resolve host");
            }
            
            if (clientSocket.connect(serverAddress, port) != Socket::Status::Done) {
                LOGGER->error("Failed to connect to server at {}:{}", host, port);
                throw BindException("Failed to connect to chat server");
            }
        } catch (const OutOfRangeException& e) {
            LOGGER->error("Failed to resolve host: {}", e.what());
            throw UnknownHostException("Failed to resolve host");
        }
        
        LOGGER->info("Connected to server at {}:{}", host, port);
        isConnected = true;
        clientSocket.setBlocking(false); // Non-blocking for listener thread
        startListening();
        clientSocket.setBlocking(true); // Blocking for main chat
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
