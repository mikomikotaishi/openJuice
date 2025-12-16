/**
 * @file ChatSession.cppm
 * @module openjuice.chat.ChatSession
 * @brief Implementation of the ChatSession class.
 *
 * This file contains the implementation of the ChatSession class, which is used to manage individual chat sessions.
 */

module;

#include "Macros.hpp"

export module openjuice.chat.ChatSession;

import std;
import stdx;

import boost.asio;
import boost.system;

#if 0

using std::collections::Vector;
using std::mem::EnableSharedFromThis;
using std::mem::SharedPointer;
using stdx::linq::Query;

using boost::asio::ip::tcp::Socket;
using boost::system::ErrorCode;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatSession
 * @brief Class for managing individual chat sessions.
 * 
 * The ChatSession class manages individual chat sessions and handles communication with clients.
 */
export class ChatSession: public EnableSharedFromThis<ChatSession> {
private:
    Socket sessionSocket; ///< Socket for the chat session.
    String inputBuffer; ///< Buffer for incoming messages.
    Vector<SharedPointer<ChatSession>>& clients; ///< List of connected clients.

    /**
     * @brief Broadcast a message to all clients.
     *
     * @param msg The message to broadcast.
     */
    void broadcast(const String& msg) {
        for (SharedPointer<ChatSession>& client: clients) {
            if (client != boost::asio::shared_from_this()) {
                client->deliver(msg);
            }
        }
    }

    /**
     * @brief Remove the client from the list of connected clients.
     */
    void removeClient() {
        clients = Query::from(clients)
            .where([self = boost::asio::shared_from_this()](const auto& c) -> bool { return c != self; })
            .to<Vector>();
    }

    /**
     * @brief Read a message from the client.
     */
    void readMessage() {
        SharedPointer<ChatSession> self(shared_from_this());
        boost::asio::async_read_until(sessionSocket, boost::asio::dynamic_buffer(inputBuffer), '\n',
            [this, self](ErrorCode ec, usize length) -> void {
                if (!ec) {
                    String message = inputBuffer.substr(0, length);
                    inputBuffer.erase(0, length);
                    std::io::print("Received: {}", message);
                    broadcast(message);
                    readMessage();
                } else {
                    removeClient();
                }
            }
        );
    }
public:
    /**
     * @brief Constructor to initialise a ChatSession object.
     *
     * @param socket The socket for the chat session.
     * @param clients The list of connected clients.
     */
    ChatSession(Socket socket, Vector<SharedPointer<ChatSession>>& clients):
        sessionSocket{std::util::move(socket)}, clients{clients} {}
    
    /**
     * @brief Start the chat session.
     */
    void start() {
        clients.push_back(boost::asio::shared_from_this());
        readMessage();
    }

    /**
     * @brief Deliver a message to the client.
     *
     * @param msg The message to deliver.
     */
    void deliver(StringView msg) {
        boost::asio::async_write(sessionSocket, boost::asio::buffer(msg),
            [](ErrorCode, usize) -> void {}
        );
    }
};

END_MODULE_NAMESPACE();

#endif
