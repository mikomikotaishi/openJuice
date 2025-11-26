/**
 * @file GlobalSettings.cppm
 * @module openjuice.engine.managers.GlobalSettings
 * @brief Implementation of the GlobalSettings class.
 *
 * This file contains the implementation of the GlobalSettings class, which manages global settings for the application.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.managers.GlobalSettings;

import std;

import openjuice.engine.util.Language;

using std::collections::Vector;

namespace sys = std::sys;

using openjuice::engine::util::Language;

BEGIN_MODULE_NAMESPACE(openjuice::engine::managers);

/**
 * @class GlobalSettings
 * @brief Class to manage global settings.
 *
 * The GlobalSettings class is a singleton class that manages global settings for the application.
 */
export class GlobalSettings {
private:
    String programName; ///< The name of the executable.
    Vector<String> programArgs; ///< The program command line arguments.
    Language language = Language::ENGLISH; ///< The current language setting.
    f32 deltaTime = 0.0f; ///< The delta-time associated with the frame rate (1/frame rate), in seconds

    /**
     * @brief Private constructor to prevent instantiation.
     */
    GlobalSettings() = default;

    /**
     * @brief Private destructor to prevent destruction.
     */
    ~GlobalSettings() = default;
public:
    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    GlobalSettings(const GlobalSettings&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying.
     */
    GlobalSettings& operator=(const GlobalSettings&) = delete;

    /**
     * @brief Get the singleton instance of GlobalSettings.
     *
     * @return The singleton instance.
     */
    [[nodiscard]]
    static GlobalSettings& getInstance() noexcept {
        static GlobalSettings instance;
        return instance;
    }

    /**
     * @brief Get the singleton instance of GlobalSettings.
     *
     * @return The singleton instance.
     */
    [[nodiscard]]
    static String languageToString(Language lang) noexcept {
        switch (lang) {
            case Language::ENGLISH:
                return "en";
            case Language::SPANISH:
                return "sp";
            case Language::FRENCH:
                return "fr";
            case Language::PORTUGUESE_BR:
                return "ptbr";
            case Language::RUSSIAN:
                return "ru";
            case Language::JAPANESE:
                return "jp";
            case Language::CHINESE_SIMPLIFIED:
                return "chs";
            case Language::CHINESE_TRADITIONAL:
                return "cht";
            case Language::KOREAN:
                return "ko";
            default:
                sys::unreachable();
        }
    }

    /**
     * @brief Set the program name.
     *
     * @param name The name to set.
     * @return A reference to the object itself
     */
    GlobalSettings& setProgramName(StringView name) noexcept {
        programName = name;
        return *this;
    }

    /**
     * @brief Get the program name.
     *
     * @return The program name.
     */
    [[nodiscard]]
    String getProgramName() const noexcept {
        return programName;
    }

    /**
     * @brief Set the program arguments.
     *
     * @param args The arguments of the program to set.
     * @return A reference to the object itself.
     */
    GlobalSettings& setProgramArgs(const Vector<String>& args) noexcept {
        programArgs = args;
        return *this;
    }

    /**
     * @brief Get the program arguments.
     *
     * @return The program arguments.
     */
    [[nodiscard]]
    Vector<String> getProgramArgs() const noexcept {
        return programArgs;
    }

    /**
     * @brief Set the language.
     *
     * @param lang The language to set.
     * @return A reference to the object itself.
     */
    GlobalSettings& setLanguage(Language lang) noexcept {
        language = lang;
        return *this;
    }

    /**
     * @brief Get the current language.
     *
     * @return The current language.
     */
    [[nodiscard]]
    Language getLanguage() const noexcept {
        return language;
    }

    /**
     * @brief Set the frame rate.
     *
     * @param lang The frame rate to set. If frameRate is 0, it sets deltaTime to 0.0f
     * @return A reference to the object itself.
     */
    GlobalSettings& setFrameRate(u16 frameRate) noexcept {
        deltaTime = (frameRate == 0) ? 0.0f : 1.0f / static_cast<f32>(frameRate);
        return *this;
    }

    /**
     * @brief Get the current deltaTime (1/frame rate).
     * @return The current deltaTime.
     */
    [[nodiscard]]
    f32 getDeltaTime() const noexcept {
        return deltaTime;
    }
};

END_MODULE_NAMESPACE();
