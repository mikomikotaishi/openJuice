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

#include <SFML/Window.hpp>

export module sfml:window;

export import :system;

export namespace sfml {
    using ::VkInstance;
    using ::VkSurfaceKHR;

    class Clipboard final {
    public:
        Clipboard() = delete;

        [[nodiscard]]
        static sf::String getString() {
            return sf::Clipboard::getString();
        }

        static void setString(const sf::String& text) {
            sf::Clipboard::setString(text);
        }
    };

    using sf::Context;
    using sf::GlFunctionPointer;
    using sf::ContextSettings;
    using sf::Cursor;
    using sf::Event;
    using sf::GlResource;
    using ContextDestroyCallback = void (*)(void*);

    class Joystick final {
    public:
        Joystick() = delete;
        using Identification = sf::Joystick::Identification;
        using Axis = sf::Joystick::Axis;

        [[nodiscard]]
        static bool isConnected(unsigned int joystick) {
            return sf::Joystick::isConnected(joystick);
        }

        [[nodiscard]]
        static unsigned int getButtonCount(unsigned int joystick) {
            return sf::Joystick::getButtonCount(joystick);
        }

        [[nodiscard]]
        static bool hasAxis(unsigned int joystick, Axis axis) {
            return sf::Joystick::hasAxis(joystick, axis);
        }

        [[nodiscard]]
        static bool isButtonPressed(unsigned int joystick, unsigned int button) {
            return sf::Joystick::isButtonPressed(joystick, button);
        }

        [[nodiscard]]
        static float getAxisPosition(unsigned int joystick, Axis axis) {
            return sf::Joystick::getAxisPosition(joystick, axis);
        }

        [[nodiscard]]
        static Identification getIdentification(unsigned int joystick) {
            return sf::Joystick::getIdentification(joystick);
        }

        static void update() {
            sf::Joystick::update();
        }
    };

    class Keyboard final {
    public:
        Keyboard() = delete;
        using Scancode = sf::Keyboard::Scancode;
        using Key = sf::Keyboard::Key;
        using Scan = sf::Keyboard::Scan;

        [[nodiscard]]
        static bool isKeyPressed(Key key) {
            return sf::Keyboard::isKeyPressed(key);
        }

        [[nodiscard]]
        static bool isKeyPressed(Scancode code) {
            return sf::Keyboard::isKeyPressed(code);
        }

        [[nodiscard]]
        static Key localize(Scancode code) {
            return sf::Keyboard::localize(code);
        }

        [[nodiscard]]
        static Scancode delocalize(Key key) {
            return sf::Keyboard::delocalize(key);
        }

        [[nodiscard]]
        static sf::String getDescription(Scancode code) {
            return sf::Keyboard::getDescription(code);
        }

        static void setVirtualKeyboardVisible(bool visible) {
            sf::Keyboard::setVirtualKeyboardVisible(visible);
        }
    };

    class Mouse final {
    public:
        Mouse() = delete;
        using Button = sf::Mouse::Button;
        using Wheel = sf::Mouse::Wheel;

        [[nodiscard]]
        static bool isButtonPressed(Button button) {
            return sf::Mouse::isButtonPressed(button);
        }

        [[nodiscard]]
        static sf::Vector2i getPosition() {
            return sf::Mouse::getPosition();
        }

        static void setPosition(sf::Vector2i position) {
            sf::Mouse::setPosition(position);
        }
    };

    class Sensor final {
    public:
        Sensor() = delete;
        using Type = sf::Sensor::Type;

        [[nodiscard]]
        static bool isAvailable(Type sensor) {
            return sf::Sensor::isAvailable(sensor);
        }

        static void setEnabled(Type sensor, bool enabled) {
            sf::Sensor::setEnabled(sensor, enabled);
        }

        [[nodiscard]]
        static sf::Vector3f getValue(Type sensor) {
            return sf::Sensor::getValue(sensor);
        }
    };

    class Touch final {
    public:
        Touch() = delete;

        [[deprecated("Use sf::Event::TouchBegan and sf::Event::TouchEnded")]]
        [[nodiscard]]
        static bool isDown(unsigned int finger) {
            return sf::Touch::isDown(finger);
        }

        [[deprecated("Use position member of sf::Event::TouchBegan, sf::Event::TouchEnded and sf::Event::TouchMoved")]]
        [[nodiscard]]
        static sf::Vector2i getPosition(unsigned int finger) {
            return sf::Touch::getPosition(finger);
        }

        [[deprecated("Use position member of sf::Event::TouchBegan, sf::Event::TouchEnded and sf::Event::TouchMoved")]]
        [[nodiscard]]
        static sf::Vector2i getPosition(unsigned int finger, const sf::WindowBase& relativeTo) {
            return sf::Touch::getPosition(finger, relativeTo);
        }
    };

    using sf::VideoMode;
    class Vulkan final {
    public:
        Vulkan() = delete;

        [[nodiscard]]
        static bool isAvailable() {
            return sf::Vulkan::isAvailable();
        }

        [[nodiscard]]
        static sf::VulkanFunctionPointer getFunction(const char* name) {
            return sf::Vulkan::getFunction(name);
        }

        [[nodiscard]]
        static const std::vector<const char*>& getGraphicsRequiredInstanceExtensions() {
            return sf::Vulkan::getGraphicsRequiredInstanceExtensions();
        }
    };

    using sf::VulkanFunctionPointer;
    using sf::Window;
    using sf::WindowBase;

    class Style final {
    public:
        Style() = delete;
        using Self = decltype(sf::Style::Titlebar);

        static constexpr Self None = sf::Style::None;
        static constexpr Self Titlebar = sf::Style::Titlebar;
        static constexpr Self Resize = sf::Style::Resize;
        static constexpr Self Close = sf::Style::Close;
        static constexpr Self Default = sf::Style::Default;
    };

    using sf::State;
    using sf::WindowHandle;
}
