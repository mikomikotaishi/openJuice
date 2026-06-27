/**
 * @file GlobalSettings.cppm
 * @module openjuice.engine.managers:GlobalSettings
 * @brief Implementation of the GlobalSettings class.
 *
 * This file contains the implementation of the GlobalSettings class, which manages global settings for the application.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.managers:GlobalSettings;

import stdx;

import openjuice.engine.util;

using stdx::collections::Vector;
using stdx::time::Milliseconds;

using openjuice::engine::util::Constants;
using openjuice::engine::util::Language;

BEGIN_MODULE_NAMESPACE(openjuice::engine::managers);

/**
 * @class GlobalSettings
 * @brief Class to manage global settings.
 *
 * The GlobalSettings class is a singleton class that manages global settings for the application.
 */
export class GlobalSettings {
public:
    static constexpr StringView PATH_DEBUGFILE = Constants::PATH_DEBUGFILE; ///< The debug file path.
    static constexpr StringView USERDATA_DIR = Constants::USERDATA_DIR; ///< The user data directory path.
private:
    Vector<StringView> programArgs; ///< The program command line arguments.
    String programName; ///< The name of the executable.
    Milliseconds deltaTime{0}; ///< The delta-time associated with the frame rate (1/frame rate), in seconds
    Language language = Language::ENGLISH; ///< The current language setting.

    /**
     * @brief Private constructor to prevent instantiation.
     */
    GlobalSettings() = default;

    /**
     * @brief Private destructor to prevent destruction.
     */
    ~GlobalSettings() = default;
public:
    GlobalSettings(const GlobalSettings&) = delete("Copy construction is disabled.");
    GlobalSettings& operator=(const GlobalSettings&) = delete("Copy assignment is disabled.");

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

    [[nodiscard]]
    String getProgramName() const noexcept {
        return programName;
    }

    [[nodiscard]]
    Vector<StringView> getProgramArgs() const noexcept {
        return programArgs;
    }

    [[nodiscard]]
    Language getLanguage() const noexcept {
        return language;
    }

    [[nodiscard]]
    Milliseconds getDeltaTime() const noexcept {
        return deltaTime;
    }

    /**
     * @brief Get the singleton instance of GlobalSettings.
     *
     * @return The singleton instance.
     */
    [[nodiscard]]
    static String languageToCode(Language lang) noexcept {
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
                Ops::unreachable();
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
     * @brief Set the program arguments.
     *
     * @param args The arguments of the program to set.
     * @return A reference to the object itself.
     */
    GlobalSettings& setProgramArgs(Span<StringView> args) noexcept {
        programArgs = Vector<StringView>(args.begin(), args.end());
        return *this;
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
     * @brief Set the frame rate.
     *
     * @param lang The frame rate to set. If frameRate is 0, it sets deltaTime to 0.0f
     * @return A reference to the object itself.
     */
    GlobalSettings& setFrameRate(u16 frameRate) noexcept {
        deltaTime = (frameRate == 0) ? Milliseconds{0} : Milliseconds{1000 / frameRate};
        return *this;
    }
};

END_MODULE_NAMESPACE();
