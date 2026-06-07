/**
 * @file Censor.cppm
 * @module openjuice.chat.Censor
 * @brief Implementation of the Censor class.
 *
 * This file contains the implementation of the Censor class, which is used to censor inappropriate words in chat messages.
 */

module;

#include "Macros.hpp"

export module openjuice.chat:Censor;

import stdx;
import google.re2;

import openjuice.engine.managers;
import openjuice.engine.util;

using stdx::collections::Vector;
using stdx::io::Scanner;
using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::managers::GlobalSettings;
using openjuice::engine::util::Constants;
using openjuice::engine::util::Language;

using google::re2::RE2;
using google::re2::StringPiece;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class Censor
 * @brief Class for censoring inappropriate words in chat messages.
 * 
 * The Censor class is a singleton class that censors inappropriate words in chat messages based on a blacklist.
 */
export class Censor {
public:
    static constexpr StringView PATH_BLACKLIST_FILE = Constants::PATH_BLACKLIST_FILE; ///< The blacklist file path.
private:
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("Censor"); ///< The logger instance.
    Vector<String> blacklist; ///< List of inappropriate words to censor.
    const String gameLanguageCode; ///< The language code currently being used by the game.
    char censorChar; ///< Character used for censoring.

    /**
     * @brief Private constructor to prevent instantiation.
     */
    Censor():
        gameLanguageCode{GlobalSettings::languageToCode(GlobalSettings::getInstance().getLanguage())} {
        Language gameLanguage = GlobalSettings::getInstance().getLanguage();
        switch (gameLanguage) {
            case Language::ENGLISH:
            case Language::RUSSIAN:
            case Language::SPANISH:
            case Language::PORTUGUESE_BR:
                censorChar = '*';
                break;
            case Language::JAPANESE:
            case Language::CHINESE_SIMPLIFIED:
            case Language::CHINESE_TRADITIONAL:
            case Language::KOREAN:
                censorChar = '#';
                break;
            default:
                Ops::unreachable();
        }
        loadBlacklist(gameLanguage);
    }

    /**
     * @brief Load the blacklist for the specified language.
     * 
     * @param language The language for which to load the blacklist.
     * @throws InvalidLanguageException if no valid language is found
     */
    void loadBlacklist(Language language) throws (InvalidLanguageException) {
        LOGGER->info("Loading blacklist for language of value {}", static_cast<u8>(language));
        String filename = stdx::fmt::format(PATH_BLACKLIST_FILE, gameLanguageCode);
        blacklist.clear();
        Scanner file(filename);
        
        while (file.has_next()) {
            Optional<String> word = file.next();
            if (word.has_value() && !word.value().empty()) {
                blacklist.push_back(*word);
            }
        }
    }
public:
    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    Censor(const Censor&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying.
     */
    Censor& operator=(const Censor&) = delete;

    /**
     * @brief Get the singleton instance of Censor.
     * 
     * @return The singleton instance.
     */
    static Censor& getInstance() {
        static Censor instance;
        return instance;
    }

    /**
     * @brief Censor inappropriate words in a message.
     * 
     * @param message The message to censor.
     * @return The censored message.
     */
    [[nodiscard]]
    String censorMessage(const String& message) const {
        static RE2::Options options;
        options.set_case_sensitive(false);
        String censoredMessage = message;
        for (const String& word: blacklist) {
            String pattern = stdx::fmt::format("\\b{}\\b", word);
            RE2 regex(pattern, options);
            String replacement(word.length(), censorChar);
            RE2::GlobalReplace(&censoredMessage, regex, replacement);
        }
        return censoredMessage;
    }
};

END_MODULE_NAMESPACE();
