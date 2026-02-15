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

import openjuice.engine.managers;

#if 0
using stdx::concurrent::JoiningThread;
using stdx::io::Cin;
using stdx::io::Cout;
using stdx::io::InputStream;
using stdx::io::Stderr;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using IOContext = boost::asio::io_context;
using Resolver = boost::asio::ip::tcp::resolver;
using ResultsType = boost::asio::ip::tcp::resolver::results_type;
using Socket = boost::asio::ip::tcp::socket;
using StreamBuffer = boost::asio::streambuf;

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
    Socket clientSocket; ///< Socket for the chat client.
    JoiningThread listenerThread; ///< Listener thread for the chat client.

    /**
     * @brief Start the chat client.
     */
    void startChat() {
        LOGGER->info("Starting chat");
        String message;
        while (stdx::io::getline(Cin, message)) {
            message += "\n";
            boost::asio::write(clientSocket, boost::asio::buffer(message));
        }
    }

    /**
     * @brief Start listening for messages from the server.
     */
    void startListening() {
        listenerThread = JoiningThread([this]() -> void {
            try {
                StreamBuffer buffer;
                while (true) {
                    boost::asio::read_until(clientSocket, buffer, '\n');
                    InputStream is(&buffer);
                    String message;
                    stdx::io::getline(is, message);
                    stdx::io::print("\n[CHAT] {}\n> ", message);
                    Cout.flush();
                }
            } catch (...) {
                stdx::io::println(Stderr, "Disconnected from server.");
            }
        });
    }

    /**
     * @brief Stop listening for messages from the server.
     */
    void stopListening() {
        listenerThread.request_stop();
    }
public:
    /**
     * @brief Constructor to initialise a ChatClient object.
     *
     * @param ioContext The IO context to use.
     * @param host The host to connect to.
     * @param port The port to connect to.
     */
    ChatClient(IOContext& ioContext, const String& host, i16 port):
        clientSocket(ioContext) {
        Resolver resolver(ioContext);
        ResultsType endpoints = resolver.resolve(host, stdx::text::string::to_string(port));
        boost::asio::connect(clientSocket, endpoints);
        startListening();
        startChat();
    }
};

END_MODULE_NAMESPACE();

#endif
