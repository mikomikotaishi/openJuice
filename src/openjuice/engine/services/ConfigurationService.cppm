/**
 * @file ConfigurationService.cppm
 * @module openjuice.engine.services:ConfigurationService
 * @brief Implementation of the ConfigurationService class.
 *
 * This file contains the implementation of the ConfigurationService class, which manages persisted,
 * user-configurable settings for the application (language, frame rate, and future options such as
 * volume control).
 */

module;

#include "Macros.hpp"

export module openjuice.engine.services:ConfigurationService;

import stdx;

import openjuice.engine.util;

import marzer.toml;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::fs::FileSystemException;
using stdx::fs::Path;
using stdx::io::IOException;
using stdx::io::IOState;
using stdx::io::OutputFileStream;
using stdx::mem::SharedPointer;
using stdx::time::Milliseconds;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::util::Constants;
using openjuice::engine::util::Language;

using marzer::toml::NodeView;
using marzer::toml::TomlNode;
using marzer::toml::TomlParseException;
using marzer::toml::TomlTable;

BEGIN_MODULE_NAMESPACE(openjuice::engine::services);

/**
 * @class ConfigurationService
 * @brief Service class that manages persisted, user-configurable settings.
 *
 * The ConfigurationService owns the settings a player can configure and persists them
 * to a TOML file so they survive across sessions. It is injected wherever these settings
 * are read or written.
 */
export class ConfigurationService final {
public:
    static constexpr StringView USERDATA_DIR = Constants::USERDATA_DIR; ///< The user data directory path.
    static constexpr StringView PATH_SETTINGS_FILE = Constants::PATH_SETTINGS_FILE; ///< The settings file path.
    static constexpr u16 DEFAULT_FRAME_RATE = 60; ///< The default frame rate (fps) used when none is configured.

    /**
     * @enum Error
     * @brief Enumeration of errors occuring in ConfigurationService operations
     */
    enum class Error: u8 {
        DESERIALIZATION_FAILED, ///< Deserialization of settings data failed
        CORRUPTED_SETTINGS_TOML, ///< The TOML file storing the settings is corrupted or has invalid data
        SETTINGS_LOAD_FAILED, ///< Loading settings data failed
        SETTINGS_SAVE_LOCATION_INVALID, ///< The settings save location is invalid
        SETTINGS_SAVE_WRITE_FAILED, ///< Writing settings data to file failed
        SETTINGS_SAVE_FAILED, ///< Saving settings data failed
    };

    /**
     * @brief Converts a language to its persisted, human-readable code.
     * @param lang The language to convert.
     * @return The language code (e.g. "en").
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
        }
        Ops::unreachable();
    }

    /**
     * @brief Converts a persisted language code back into a language.
     * @param code The language code (e.g. "en").
     * @return The matching language, or an empty optional if the code is unknown.
     */
    [[nodiscard]]
    static Optional<Language> languageFromCode(StringView code) noexcept {
        switch (util::hashString(code)) {
            case "en"_hash:
                return Language::ENGLISH;
            case "sp"_hash:
                return Language::SPANISH;
            case "fr"_hash:
                return Language::FRENCH;
            case "ptbr"_hash:
                return Language::PORTUGUESE_BR;
            case "ru"_hash:
                return Language::RUSSIAN;
            case "jp"_hash:
                return Language::JAPANESE;
            case "chs"_hash:
                return Language::CHINESE_SIMPLIFIED;
            case "cht"_hash:
                return Language::CHINESE_TRADITIONAL;
            case "ko"_hash:
                return Language::KOREAN;
        }
        return nullopt;
    }
private:
    SharedPointer<Logger> logger; ///< The logger instance.

    Language language = Language::ENGLISH; ///< The currently configured language.
    u16 frameRate = DEFAULT_FRAME_RATE; ///< The currently configured frame rate, in frames per second.

    /**
     * @brief Deserializes a TOML into this instance's settings.
     * @param table The TOML table to deserialize from.
     * @return Expected<void, ConfigurationService::Error> indicating success or failure.
     */
    [[nodiscard]]
    Expected<void, Error> deserialize(const TomlTable& table) noexcept {
        try {
            if (NodeView<const TomlNode> languageNode = table["language"]; languageNode) {
                if (Optional<String> languageValue = languageNode.value<String>()) {
                    if (Optional<Language> parsed = languageFromCode(*languageValue)) {
                        language = *parsed;
                    } else {
                        logger->warn("Unknown language code '{}', using default", *languageValue);
                        language = Language::ENGLISH;
                    }
                } else {
                    logger->warn("language field is not a string");
                    return Unexpected(Error::DESERIALIZATION_FAILED);
                }
            } else {
                logger->debug("language field not found, using default");
                language = Language::ENGLISH;
            }

            if (NodeView<const TomlNode> frameRateNode = table["frameRate"]; frameRateNode) {
                if (Optional<i64> frameRateValue = frameRateNode.value<i64>()) {
                    if (*frameRateValue >= 1 && *frameRateValue <= 600) {
                        frameRate = static_cast<u16>(*frameRateValue);
                    } else {
                        logger->warn("frameRate {} out of range (1-600), using default", *frameRateValue);
                        frameRate = DEFAULT_FRAME_RATE;
                    }
                } else {
                    logger->warn("frameRate field is not a valid integer");
                    return Unexpected(Error::DESERIALIZATION_FAILED);
                }
            } else {
                logger->debug("frameRate field not found, using default");
                frameRate = DEFAULT_FRAME_RATE;
            }

            return {};
        } catch (const TomlParseException& e) {
            logger->error("Failed to parse TOML file: {}", e.what());
            return Unexpected(Error::CORRUPTED_SETTINGS_TOML);
        } catch (const IOException& e) {
            if (!stdx::fs::exists(PATH_SETTINGS_FILE)) {
                logger->warn("Failed to load settings, file/directory does not exist: {}", e.what());
                return Unexpected(Error::SETTINGS_SAVE_LOCATION_INVALID);
            } else {
                logger->warn("Failed to load settings, read operation failed: {}", e.what());
                return Unexpected(Error::SETTINGS_LOAD_FAILED);
            }
        } catch (const Exception& e) {
            logger->error("Exception during deserialization: {}", e.what());
            return Unexpected(Error::DESERIALIZATION_FAILED);
        }
    }
public:
    /**
     * @brief Constructs a new ConfigurationService object.
     * @param loggerFactory The injected logger factory.
     */
    explicit ConfigurationService(SharedPointer<LoggerFactory> loggerFactory):
        logger{loggerFactory->of("ConfigurationService")} {
        try {
            stdx::fs::create_directories(USERDATA_DIR);
            if (Expected<void, Error> result = load(); !result) {
                logger->warn("Failed to load settings during initialization");
            }
        } catch (const FileSystemException& e) {
            logger->warn("Failed to create directory {}: {}", USERDATA_DIR, e.what());
        }
    }

    /**
     * @brief Destroy the ConfigurationService object.
     */
    ~ConfigurationService() = default;

    /**
     * @brief Get the currently configured language.
     * @return The current language.
     */
    [[nodiscard]]
    Language getLanguage() const noexcept {
        return language;
    }

    /**
     * @brief Get the currently configured frame rate.
     * @return The current frame rate, in frames per second.
     */
    [[nodiscard]]
    u16 getFrameRate() const noexcept {
        return frameRate;
    }

    /**
     * @brief Get the delta-time derived from the configured frame rate.
     * @return The delta-time (1 / frame rate). If the frame rate is 0, this is 0.
     */
    [[nodiscard]]
    Milliseconds getDeltaTime() const noexcept {
        return (frameRate == 0) ? Milliseconds{0} : Milliseconds{1000 / frameRate};
    }

    /**
     * @brief Set the configured language.
     * @param lang The language to set.
     */
    void setLanguage(Language lang) noexcept {
        language = lang;
    }

    /**
     * @brief Set the configured frame rate.
     * @param rate The frame rate to set, in frames per second.
     */
    void setFrameRate(u16 rate) noexcept {
        frameRate = rate;
    }

    /**
     * @brief Load settings data from file.
     * @return Expected<void, ConfigurationService::Error> indicating success or failure.
     */
    [[nodiscard]]
    Expected<void, Error> load() noexcept {
        if (!stdx::fs::exists(PATH_SETTINGS_FILE)) {
            logger->info("Settings file not found, creating with defaults");
            return save();
        }

        try {
            TomlTable data = marzer::toml::parse_file(PATH_SETTINGS_FILE);

            if (!deserialize(data).has_value()) {
                logger->error("Failed to deserialize settings data");
                return Unexpected(Error::DESERIALIZATION_FAILED);
            }

            logger->info("Settings loaded successfully (language {}, {} fps)", language, frameRate);
            return {};
        } catch (const TomlParseException& e) {
            logger->error("Failed to parse TOML file: {}", e.what());
            return Unexpected(Error::CORRUPTED_SETTINGS_TOML);
        } catch (const Exception& e) {
            logger->error("Error loading settings: {}", e.what());
            return Unexpected(Error::SETTINGS_LOAD_FAILED);
        }
    }

    /**
     * @brief Save settings data to file.
     * @return Expected<void, ConfigurationService::Error> indicating success or failure.
     */
    [[nodiscard]]
    Expected<void, Error> save() noexcept {
        try {
            TomlTable data;
            data.insert("language", languageToCode(language));
            data.insert("frameRate", static_cast<i64>(frameRate));

            OutputFileStream file{Path(PATH_SETTINGS_FILE)};
            file.exceptions(IOState::STREAM_ERROR | IOState::IO_OPERATION_FAIL);

            file << data;
            file.close();

            logger->info("Settings saved successfully (language {}, {} fps)", language, frameRate);
            return {};
        } catch (const IOException& e) {
            if (!stdx::fs::exists(PATH_SETTINGS_FILE)) {
                logger->warn("Failed to save settings, file/directory does not exist: {}", e.what());
                return Unexpected(Error::SETTINGS_SAVE_LOCATION_INVALID);
            } else {
                logger->warn("Failed to save settings, write operation failed: {}", e.what());
                return Unexpected(Error::SETTINGS_SAVE_WRITE_FAILED);
            }
        } catch (const Exception& e) {
            logger->warn("Error saving settings: {}", e.what());
            return Unexpected(Error::SETTINGS_SAVE_FAILED);
        }
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::services::ConfigurationService;

template <>
struct Formatter<ConfigurationService::Error> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(ConfigurationService::Error err, FormatContext& ctx) {
        StringView name;
        switch (err) {
            case ConfigurationService::Error::DESERIALIZATION_FAILED:
                name = "Deserialization failed";
                break;
            case ConfigurationService::Error::CORRUPTED_SETTINGS_TOML:
                name = "Corrupted settings TOML";
                break;
            case ConfigurationService::Error::SETTINGS_LOAD_FAILED:
                name = "Settings load failed";
                break;
            case ConfigurationService::Error::SETTINGS_SAVE_LOCATION_INVALID:
                name = "Settings save location invalid";
                break;
            case ConfigurationService::Error::SETTINGS_SAVE_WRITE_FAILED:
                name = "Settings save write failed";
                break;
            case ConfigurationService::Error::SETTINGS_SAVE_FAILED:
                name = "Settings save failed";
                break;
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALIZE_FORMATTER(ConfigurationService::Error);
