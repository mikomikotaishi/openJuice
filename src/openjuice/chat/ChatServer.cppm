/**
 * @file ChatServer.cppm
 * @module openjuice.chat.ChatServer
 * @brief Implementation of the ChatServer class.
 *
 * This file contains the implementation of the ChatServer class, which is used to manage chat server connections.
 */

module;

#include "Macros.hpp"

export module openjuice.chat.ChatServer;

import openjuice.chat.ChatSession;

import std;

import boost.asio;
import boost.system;

#if 0

using std::collections::Vector;
using std::mem::SharedPointer;

using boost::asio::ip::tcp::Acceptor;
using boost::asio::ip::tcp::Socket;
using boost::system::ErrorCode;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatServer
 * @brief Class for managing chat server connections.
 * 
 * The ChatServer class manages chat server connections and handles incoming client connections.
 */
export class ChatServer {
private:
    Acceptor serverAcceptor; ///< Acceptor for incoming connections.
    Vector<SharedPointer<ChatSession>> clients; ///< List of connected clients.

    /**
     * @brief Accept an incoming connection.
     */
    void acceptConnection() {
        serverAcceptor.async_accept(
            [this](ErrorCode ec, Socket socket) -> void {
                if (!ec) {
                    std::mem::make_shared<ChatSession>(std::util::move(socket), clients)->start();
                }
                acceptConnection();
            }
        );
    }
public:
    /**
     * @brief Constructor to initialise a ChatServer object.
     *
     * @param ioContext The IO context to use.
     * @param port The port to listen on.
     */
    ChatServer(IOContext& ioContext, i16 port):
        serverAcceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), static_cast<u16>(port))) {
        acceptConnection();
    }
};

END_MODULE_NAMESPACE();

#endif
