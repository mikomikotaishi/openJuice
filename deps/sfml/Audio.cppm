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

#include <SFML/Audio.hpp>

export module sfml:audio;

export import :system;

import stdx;

using stdx::collections::Vector;

export namespace sfml::audio {
    using sf::InputSoundFile;
    
    class Listener final {
    public:
        Listener() = delete;

        using Cone = sf::Listener::Cone;

        static void setGlobalVolume(f32 volume) {
            sf::Listener::setGlobalVolume(volume);
        }

        [[nodiscard]]
        static f32 getGlobalVolume() {
            return sf::Listener::getGlobalVolume();
        }

        static void setPosition(const sf::Vector3f& position) {
            sf::Listener::setPosition(position);
        }

        [[nodiscard]]
        static sf::Vector3f getPosition() {
            return sf::Listener::getPosition();
        }

        static void setDirection(const sf::Vector3f& direction) {
            sf::Listener::setDirection(direction);
        }

        [[nodiscard]]
        static sf::Vector3f getDirection() {
            return sf::Listener::getDirection();
        }

        static void setVelocity(const sf::Vector3f& velocity) {
            sf::Listener::setVelocity(velocity);
        }

        [[nodiscard]]
        static sf::Vector3f getVelocity() {
            return sf::Listener::getVelocity();
        }

        static void setCone(const Cone& cone) {
            sf::Listener::setCone(cone);
        }

        [[nodiscard]]
        static Cone getCone() {
            return sf::Listener::getCone();
        }

        static void setUpVector(const sf::Vector3f& upVector) {
            sf::Listener::setUpVector(upVector);
        }

        [[nodiscard]]
        static sf::Vector3f getUpVector() {
            return sf::Listener::getUpVector();
        }
    };

    using sf::Music;
    using sf::OutputSoundFile;

    class PlaybackDevice final {
    public:
        PlaybackDevice() = delete;

        using Notification = sf::PlaybackDevice::Notification;
        using NotificationCallback = sf::PlaybackDevice::NotificationCallback;

        [[nodiscard]]
        static Vector<stdx::core::String> getAvailableDevices() {
            return sf::PlaybackDevice::getAvailableDevices();
        }

        [[nodiscard]]
        static Optional<stdx::core::String> getDefaultDevice() {
            return sf::PlaybackDevice::getDefaultDevice();
        }

        [[nodiscard]]
        static bool setDevice(const stdx::core::String& name) {
            return sf::PlaybackDevice::setDevice(name);
        }

        [[nodiscard]]
        static Optional<stdx::core::String> getDevice() {
            return sf::PlaybackDevice::getDevice();
        }
    };

    using sf::Sound;
    using sf::SoundBuffer;
    using sf::SoundBufferRecorder;
    using sf::SoundChannel;
    using sf::SoundFileFactory;
    using sf::SoundFileReader;
    using sf::SoundFileWriter;
    using sf::SoundRecorder;
    using sf::SoundSource;
    using sf::SoundStream;
}
