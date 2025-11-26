/**
 * @file ChatClient.cppm
 * @module openjuice.chat.ChatClient
 * @brief Implementation of the ChatClient class.
 *
 * This file contains the implementation of the ChatClient class, which is used to manage chat client connections.
 */

module;

#include "Macros.hpp"

export module openjuice.chat.ChatClient;

import std;

import openjuice.engine.managers.GlobalSettings;
import openjuice.engine.util.Logging;

import boost.asio;
import boost.system;

#if 0

using std::concurrent::JoiningThread;
using std::io::Cin;
using std::io::Cout;
using std::io::InputStream;
using std::io::Stderr;

namespace io = std::io;
namespace string = std::text::string;

using namespace openjuice::engine::util::logging;

using IOContext = boost::asio::io_context;
using Resolver = boost::asio::ip::tcp::resolver;
using ResultsType = boost::asio::ip::tcp::resolver::results_type;
using Socket = boost::asio::ip::tcp::socket;
using StreamBuffer = boost::asio::streambuf;

using namespace boost::asio;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatClient
 * @brief Class for managing chat client connections.
 * 
 * The ChatClient class manages chat client connections and handles communication with the chat server.
 */
export class ChatClient {
private:
    Socket clientSocket; ///< Socket for the chat client.
    JoiningThread listenerThread; ///< Listener thread for the chat client.

    /**
     * @brief Start the chat client.
     */
    void startChat() {
        Logger::getInstance().log(LogLevel::INFO, "Starting chat");
        String message;
        while (io::getline(Cin, message)) {
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
                    io::getline(is, message);
                    io::print("\n[CHAT] {}\n> ", message);
                    Cout.flush();
                }
            } catch (...) {
                io::println(Stderr, "Disconnected from server.");
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
        ResultsType endpoints = resolver.resolve(host, string::to_string(port));
        boost::asio::connect(clientSocket, endpoints);
        startListening();
        startChat();
    }
};

END_MODULE_NAMESPACE();

#endif
