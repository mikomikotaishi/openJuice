/**
 * @file Censor.cppm
 * @module openjuice.chat.Censor
 * @brief Implementation of the Censor class.
 *
 * This file contains the implementation of the Censor class, which is used to censor inappropriate words in chat messages.
 */

module;

#include "Macros.hpp"

export module openjuice.chat.Censor;

import std;
import stdx;

import openjuice.engine.managers.GlobalSettings;
import openjuice.engine.util.Constants;
import openjuice.engine.util.Exceptions;
import openjuice.engine.util.Language;

import boost.regex;

#if 0

using std::collections::Vector;
using std::io::InputFileStream;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::managers::GlobalSettings;
using openjuice::engine::util::Constants;
using openjuice::engine::util::Language;
using openjuice::engine::util::exceptions::InvalidLanguageException;

using boost::regex::Regex;

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
     * @throws InvalidLanguageException if no valid language is found
     */
    Censor():
        gameLanguageCode{GlobalSettings::languageToString(GlobalSettings::getInstance().getLanguage())} {
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
                throw InvalidLanguageException("Invalid language code");
        }
        loadBlacklist(gameLanguage);
    }

    /**
     * @brief Load the blacklist for the specified language.
     * @param language The language for which to load the blacklist.
     * @throws InvalidLanguageException if no valid language is found
     */
    void loadBlacklist(Language language) {
        LOGGER->info("Loading blacklist for language of value {}", static_cast<u8>(language));
        String filename = std::fmt::format(PATH_BLACKLIST_FILE, gameLanguageCode);
        blacklist.clear();
        String word;
        InputFileStream file(filename);
        while (std::io::getline(file, word)) {
            if (!word.empty()) {
                blacklist.push_back(word);
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
     * @return The singleton instance.
     */
    static Censor& getInstance() {
        static Censor instance;
        return instance;
    }

    /**
     * @brief Censor inappropriate words in a message.
     * @param message The message to censor.
     * @return The censored message.
     */
    [[nodiscard]]
    String censorMessage(const String& message) const {
        String censoredMessage = message;
        for (const String& word: blacklist) {
            Regex pattern(std::fmt::format("\\b{}\\b", word), boost::regex_constants::icase);
            String replacement(word.length(), censorChar);
            censoredMessage = boost::regex_replace(censoredMessage, pattern, replacement);
        }
        return censoredMessage;
    }
};

END_MODULE_NAMESPACE();

#endif
