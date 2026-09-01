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
using stdx::net::Socket;
using stdx::net::SocketException;
using stdx::net::TcpStream;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class ChatSession
 * @brief One connected client, owned and driven by the ChatServer.
 *
 * A session holds a connection and the bytes that have arrived on it so far, and does nothing on
 * its own: the server's reactor decides when it is worth reading, and the server decides who a
 * message reaches. There is no thread here and no reference back to the other clients, which is
 * what keeps every session reachable from exactly one thread.
 */
export class ChatSession {
public:
    static constexpr usize MAX_MESSAGE_LENGTH = 4096; ///< Longest single message accepted from a client.
private:
    static constexpr usize RECEIVE_CHUNK = 1024; ///< How much is taken off the socket per read.

    TcpStream stream; ///< The connection to this session's client.
    String peerName; ///< How this client is named in the log.
    String inputBuffer; ///< Bytes received but not yet forming a complete message.
public:
    /**
     * @brief Constructor to initialize a ChatSession object.
     * @param stream The connection to the session's client.
     * @param peerName How to name this client in the log.
     */
    ChatSession(TcpStream stream, String peerName) noexcept:
        stream{Ops::move(stream)}, peerName{Ops::move(peerName)} {}

    /**
     * @brief How this client is named in the log.
     * @return The peer's address, or a placeholder if it could not be read.
     */
    [[nodiscard]]
    StringView peer() const noexcept {
        return peerName;
    }

    /**
     * @brief The descriptor this session is reachable by.
     * @return The connection's native handle.
     */
    [[nodiscard]]
    Socket::NativeHandle handle() const noexcept {
        return stream.native_handle();
    }

    /**
     * @brief Reads everything that has arrived and splits off the complete messages.
     * @param messages Receives each complete message, newline included.
     * @return false once the peer has closed its writing half.
     * @throws SocketException if the receive fails, or the peer overruns MAX_MESSAGE_LENGTH.
     */
    [[nodiscard]]
    THROWS(SocketException)
    bool drain(Vector<String>& messages) {
        Array<char, RECEIVE_CHUNK> buffer;

        while (true) {
            const Optional<usize> received = stream.try_receive(as_writable_bytes(Span<char>(buffer)));
            if (!received.has_value()) {
                break;
            }

            if (*received == 0) {
                return false;
            }

            inputBuffer.append(buffer.data(), *received);
        }

        usize pos;
        while ((pos = inputBuffer.find('\n')) != String::npos) {
            messages.push_back(inputBuffer.substr(0, pos + 1));
            inputBuffer.erase(0, pos + 1);
        }

        if (inputBuffer.length() > MAX_MESSAGE_LENGTH) {
            throw SocketException("Client exceeded the maximum message length");
        }

        return true;
    }

    /**
     * @brief Deliver a message to the client.
     * @param msg The message to deliver.
     * @throws SocketException if the send fails.
     */
    THROWS(SocketException)
    void deliver(StringView msg) {
        stream.send_all(as_bytes(Span<const char>(msg.data(), msg.size())));
    }
};

END_MODULE_NAMESPACE();
