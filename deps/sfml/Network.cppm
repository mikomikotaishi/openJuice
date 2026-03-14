////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2025 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Module preamble
////////////////////////////////////////////////////////////

module;

#include <SFML/Network.hpp>

#include "Macros.hpp"

export module sfml:network;

export import :system;

import stdx;

using stdx::collections::Vector;

export namespace sf {
    using sf::operator==;
    using sf::operator!=;
    using sf::operator<;
    using sf::operator>;
    using sf::operator<=;
    using sf::operator>=;
    using sf::operator>>;
    using sf::operator<<;
}

export namespace sfml::net {
    using sf::Ftp;
    using sf::Http;
    using sf::IpAddress;
    using sf::Packet;
    using sf::Sftp;
    using sf::Socket;
    using sf::SocketHandle;
    using sf::SocketSelector;
    using sf::TcpListener;
    using sf::TcpSocket;
    using sf::UdpSocket;

    class Dns final {
    public:
        Dns() = delete;

        using MxRecord = sf::Dns::MxRecord;
        using SrvRecord = sf::Dns::SrvRecord;

        [[nodiscard]]
        static Optional<Vector<sf::IpAddress>> resolve(
            const sf::String& hostname,
            const Vector<sf::IpAddress>& servers = {},
            Optional<sf::Time> timeout = sf::seconds(1)
        ) {
            return sf::Dns::resolve(hostname, servers, timeout);
        }

        [[nodiscard]]
        static Vector<String> queryNs(
            const sf::String& hostname,
            const Vector<sf::IpAddress>& servers = {},
            Optional<sf::Time> timeout = sf::seconds(1)
        ) {
            return sf::Dns::queryNs(hostname, servers, timeout);
        }

        [[nodiscard]]
        static Vector<MxRecord> queryMx(
            const sf::String& hostname,
            const Vector<sf::IpAddress>& servers = {},
            Optional<sf::Time> timeout = sf::seconds(1)
        ) {
            return sf::Dns::queryMx(hostname, servers, timeout);
        }

        [[nodiscard]]
        static Vector<SrvRecord> querySrv(
            const sf::String& hostname,
            const Vector<sf::IpAddress>& servers = {},
            Optional<sf::Time> timeout = sf::seconds(1)
        ) {
            return sf::Dns::querySrv(hostname, servers, timeout);
        }

        [[nodiscard]]
        static Vector<Vector<sf::String>> queryTxt(
            const sf::String& hostname,
            const Vector<sf::IpAddress>& servers = {},
            Optional<sf::Time> timeout = sf::seconds(1)
        ) {
            return sf::Dns::queryTxt(hostname, servers, timeout);
        }

        [[nodiscard]]
        static Optional<sf::IpAddress> getPublicAddress(
            Optional<Time> timeout = nullopt,
            sf::IpAddress::Type type = sf::IpAddress::Type::IpV4
        ) {
            return sf::Dns::getPublicAddress(timeout, type);
        }
    };

    using sf::operator==;
    using sf::operator!=;
    using sf::operator<;
    using sf::operator>;
    using sf::operator<=;
    using sf::operator>=;
    using sf::operator>>;
    using sf::operator<<;
}
