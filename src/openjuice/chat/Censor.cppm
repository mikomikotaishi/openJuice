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

import openjuice.engine.localization;
import openjuice.engine.settings;

using stdx::collections::Vector;
using stdx::inject::Inject;
using stdx::inject::Named;
using stdx::io::Scanner;
using stdx::mem::SharedPointer;
using stdx::meta::reflect::Class;
using stdx::util::logging::Logger;

using openjuice::engine::localization::Language;
using openjuice::engine::settings::SettingsService;

using google::re2::RE2;
using google::re2::StringPiece;

BEGIN_MODULE_NAMESPACE(openjuice::chat);

/**
 * @class Censor
 * @brief Class for censoring inappropriate words in chat messages.
 * 
 * The Censor class censors inappropriate words in chat messages based on a blacklist.
 */
export class Censor {
private:
    static constexpr StringView PATH_BLACKLIST_FILE = "./blacklist/blacklist_{}.txt"; ///< The blacklist file path.

    SharedPointer<Logger> logger; ///< The logger instance.
    Vector<String> blacklist; ///< List of inappropriate words to censor.
    Language language; ///< The language code currently being used by the game.
    char censorChar; ///< Character used for censoring.

    /**
     * @brief Load the blacklist for the specified language.
     * @param language The language for which to load the blacklist.
     */
    void loadBlacklist() {
        logger->info("Loading blacklist for language {}...", language);
        String filename = Ops::fmt(PATH_BLACKLIST_FILE, SettingsService::languageToCode(language));
        blacklist.clear();
        Scanner file(filename);
        
        while (file.has_next()) {
            if (Expected<String, Scanner::Error> word = file.next(); word.has_value() && !word.value().empty()) {
                blacklist.push_back(*word);
            }
        }
        logger->info("Blacklist for language {} successfully loaded!", language);
    }
public:
    /**
     * @brief Constructs a new Censor object.
     * @param logger The injected logger.
     * @param settings The language of the censor.
     */
    [[=Inject]]
    Censor([[=Named(*Class<Censor>().name())]] SharedPointer<Logger> logger, Language language):
        logger{Ops::move(logger)},
        language{language} {
        switch (language) {
            case Language::ENGLISH:
            case Language::SPANISH:
            case Language::FRENCH:
            case Language::PORTUGUESE_BR:
            case Language::RUSSIAN:
                censorChar = '*';
                break;
            case Language::JAPANESE:
            case Language::CHINESE_SIMPLIFIED:
            case Language::CHINESE_TRADITIONAL:
            case Language::KOREAN:
                censorChar = '#';
                break;
        }
        loadBlacklist();
    }

    /**
     * @brief Censor inappropriate words in a message.
     * @param message The message to censor.
     * @return The censored message.
     */
    [[nodiscard]]
    String censorMessage(StringView message) const {
        static RE2::Options options;
        options.set_case_sensitive(false);
        String censoredMessage = String(message);
        for (const String& word: blacklist) {
            String pattern = Ops::fmt("\\b{}\\b", word);
            RE2 regex(pattern, options);
            String replacement(word.length(), censorChar);
            RE2::GlobalReplace(&censoredMessage, regex, replacement);
        }
        return censoredMessage;
    }
};

END_MODULE_NAMESPACE();
