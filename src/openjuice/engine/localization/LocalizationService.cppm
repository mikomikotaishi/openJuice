/**
 * @file LocalizationService.cppm
 * @module openjuice.engine.localization:LocalizationService
 * @brief Module file for managing parsing text from files.
 *
 * This file contains the implementation of the LocalizationService class.
 */
module;

#include "Macros.hpp"

export module openjuice.engine.localization:LocalizationService;

import stdx;

import openjuice.engine.localization.Language;
import openjuice.engine.settings;
import openjuice.engine.util;

using stdx::collections::HashMap;
using stdx::collections::Vector;
using stdx::fs::Path;
using stdx::inject::Inject;
using stdx::inject::Named;
using stdx::inject::Singleton;
using stdx::io::IOException;
using stdx::io::InputFileStream;
using stdx::io::Scanner;
using stdx::mem::SharedPointer;
using stdx::meta::reflect::Class;
using stdx::net::Uri;
using stdx::util::logging::Logger;

using openjuice::engine::settings::SettingsService;

BEGIN_MODULE_NAMESPACE(openjuice::engine::localization);

/**
 * @class LocalizationService
 * @brief Service class for loading localization and game initialization.
 */
export class [[=Singleton]] LocalizationService final {
public:
    static constexpr StringView PATH_ABILITIES_FILE = "./assets/define/{}/abilities.txt"; ///< File containing ability localization.
    static constexpr StringView PATH_CARDARTISTS_FILE = "./assets/define/{}/cardartists.txt"; ///< File containing card artist localization.
    static constexpr StringView PATH_CARDS_FILE = "./assets/define/{}/cards.txt"; ///< File containing main cards localization.
    static constexpr StringView PATH_CARDS_2_FILE = "./assets/define/{}/cards_2.txt"; ///< File containing secondary cards localization.
    static constexpr StringView PATH_CARDS_BOUNTY_FILE = "./assets/define/{}/cards_bounty.txt"; ///< File containing bounty mode card localization.
    static constexpr StringView PATH_CARDS_COOP_FILE = "./assets/define/{}/cards_coop.txt"; ///< File containing co-op mode card localization.
    static constexpr StringView PATH_CARDS_EFFECT_COOP_FILE = "./assets/define/{}/cards_effect_coop.txt"; ///< File containing co-op mode card effect localization.
    static constexpr StringView PATH_CARDS_EFFECT_FILE = "./assets/define/{}/cards_effect.txt"; ///< File containing general card effect localization.
    static constexpr StringView PATH_CARDS_MISC_FILE = "./assets/define/{}/cards_misc.txt"; ///< File containing miscellaneous cards localization.
    static constexpr StringView PATH_CARDS_MUSHROOM_FILE = "./assets/define/{}/cards_mushroom.txt"; ///< File containing mushroom cards localization.
    static constexpr StringView PATH_CHALLENGES_FILE = "./assets/define/{}/challenges.txt"; ///< File containing challenge localization.
    static constexpr StringView PATH_CHAOS_MUTATORS_FILE = "./assets/define/{}/chaos_mutators.txt"; ///< File containing chaos mutator localization.
    static constexpr StringView PATH_CHARACTERSELECT_FILE = "./assets/define/{}/characterselect.txt"; ///< File containing character selection localization.
    static constexpr StringView PATH_CODEX_FILE = "./assets/define/{}/codex.txt"; ///< File containing codex/lore localization.
    static constexpr StringView PATH_COMMENT_FILE = "./assets/define/{}/comment.txt"; ///< File containing UI comments and messages.
    static constexpr StringView PATH_CONFIG_FILE = "./assets/define/{}/config.txt"; ///< File containing configuration settings localization.
    static constexpr StringView PATH_CONSUMABLES_FILE = "./assets/define/{}/consumables.txt"; ///< File containing consumable item localization.
    static constexpr StringView PATH_ERROR_FILE = "./assets/define/{}/error.txt"; ///< File containing error messages.
    static constexpr StringView PATH_EVENTNAMES_FILE = "./assets/define/{}/eventnames.txt"; ///< File containing event name localization.
    static constexpr StringView PATH_FIELDEVENTS_FILE = "./assets/define/{}/fieldevents.txt"; ///< File containing field event localization.
    static constexpr StringView PATH_FIELDNAMES_FILE = "./assets/define/{}/fieldnames.txt"; ///< File containing field name localization.
    static constexpr StringView PATH_GAME_MESSAGE_FILE = "./assets/define/{}/game_message.txt"; ///< File containing game message localization.
    static constexpr StringView PATH_GAME_NORMA_FILE = "./assets/define/{}/game_norma.txt"; ///< File containing norma level localization.
    static constexpr StringView PATH_GAME_SYSTEM_FILE = "./assets/define/{}/game_system.txt"; ///< File containing game system messages.
    static constexpr StringView PATH_GAME_TUTORIAL_FILE = "./assets/define/{}/game_tutorial.txt"; ///< File containing tutorial messages.
    static constexpr StringView PATH_LAUNCHER_FILE = "./assets/define/{}/launcher.txt"; ///< File containing launcher localization.
    static constexpr StringView PATH_MENUSCREENS_FILE = "./assets/define/{}/menuscreens.txt"; ///< File containing menu screen localization.
    static constexpr StringView PATH_MIXERS_FILE = "./assets/define/{}/mixers.txt"; ///< File containing mixer localization.
    static constexpr StringView PATH_MULTIPLAYER_FILE = "./assets/define/{}/multiplayer.txt"; ///< File containing multiplayer localization.
    static constexpr StringView PATH_PETS_FILE = "./assets/define/{}/pets.txt"; ///< File containing pet localization.
    static constexpr StringView PATH_PINS_FILE = "./assets/define/{}/pins.txt"; ///< File containing pin localization.
    static constexpr StringView PATH_PROFILE_FILE = "./assets/define/{}/profile.txt"; ///< File containing profile localization.
    static constexpr StringView PATH_RESULT_FILE = "./assets/define/{}/result.txt"; ///< File containing result screen localization.
    static constexpr StringView PATH_SHOP_FILE = "./assets/define/{}/shop.txt"; ///< File containing shop localization.
    static constexpr StringView PATH_UNIT_GAMES_FILE = "./assets/define/{}/unitgames.txt"; ///< File containing unit game localization.
    static constexpr StringView PATH_UNITS_FILE = "./assets/define/{}/units.txt"; ///< File containing unit localization.
    static constexpr StringView PATH_VOICEACTORS_FILE = "./assets/define/{}/voiceactors.txt"; ///< File containing voice actor localization.

    static inline const Uri ORANGE_JUICE_WIKI_URL = "https://orangejuice.wiki"_uri; ///< The URL for the 100% Orange Juice! wiki

    /**
     * @enum Error
     * @brief Enumeration of errors occuring in LocalizationService operations
     */
    enum class Error: u8 {
        EMPTY_KEY, ///< The key was empty
        INVALID_KEY, ///< The key did not map anywhere
        FILE_NOT_FOUND, ///< No such file was found
        FILE_OPEN_FAILURE, ///< The file could not be opened
        FILE_READ_FAILURE, ///< The file failed to parse
    };
private:
    static constexpr StringView EMPTY_STRING = ""; ///< The empty string.
    static constexpr StringView COMMENT_PREFIX = "//"; ///< A comment prefix used in the localization files.
    static constexpr StringView EOF_MARKER = "[EOF]"; ///< A marker used to denote the end of the file in the localization files.

    SharedPointer<Logger> logger; ///< The logger instance.

    HashMap<String, String> cardNames; ///< A dictionary of all card names.
    HashMap<String, String> cardDescriptions; ///< A dictionary of all card descriptions.
    HashMap<String, String> cardFlavours; ///< A dictionary of all card flavour texts.
    HashMap<String, String> cardArtistNames; ///< A dictionary of all card artist names.
    HashMap<String, String> commentTexts; ///< A dictionary of all comment texts.
    HashMap<String, String> configTexts; ///< A dictionary of all config menu texts.
    HashMap<String, String> fieldNames; ///< A dictionary of all field names.
    HashMap<String, String> gameMessages; ///< A dictionary of all game messages.
    HashMap<String, String> gameNormaTexts; ///< A dictionary of all messages issued during norma.
    HashMap<String, String> gameSystemTexts; ///< A dictionary of all game system texts.
    HashMap<String, String> menuScreenTexts; ///< A dictionary of all menu screen texts.
    HashMap<String, String> resultTexts; ///< A dictionary of all result screen texts.
    HashMap<String, String> unitNames; ///< A dictionary of all unit names.
    HashMap<String, String> unitDescriptions; ///< A dictionary of all unit descriptions.
    HashMap<String, String> voiceActorNames; ///< A dictionary of all voice actor names.

    Language language; ///< The language code currently being used by the game.

    /**
     * @brief Parses a simple format file where values follow directly after keys.
     * @param filePath Path to the file.
     * @param targetMap The map to populate with key-value pairs.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseSimpleFormatFile(const Path& filePath, HashMap<String, String>& targetMap) noexcept {
        if (!stdx::fs::exists(filePath)) {
            return Unexpected<ErrorDescription<Error>>(
                Tags::IN_PLACE,
                Error::FILE_NOT_FOUND, 
                Ops::fmt("Failed to find file {}!", filePath)
            );
        }
        InputFileStream file(filePath);
        if (!file.is_open()) {
            return Unexpected<ErrorDescription<Error>>(
                Tags::IN_PLACE,
                Error::FILE_OPEN_FAILURE,
                Ops::fmt("Failed to open file {}!", filePath)
            );
        }

        String currentKey;
        bool expectingValue = false;

        Scanner scanner(file);
        while (Expected<String, Scanner::Error> lineResult = scanner.next_line()) {
            const String& line = *lineResult;
            if (line.empty() || line.starts_with(COMMENT_PREFIX) || line == EOF_MARKER) {
                continue;
            }

            if (line[0] == '<' && line[line.length() - 1] == '>') {
                currentKey = util::trimString(line.substr(1, line.length() - 2));
                expectingValue = true;
            } else if (expectingValue) {
                targetMap[currentKey] = util::unescapeText(line);
                expectingValue = false;
            }
        }

        return {};
    }

    /**
     * @brief Parses the cards file and populates card-related maps.
     * @param filePath Path to the cards file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseCardsFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing cards file: {}...", filePath);
        #endif

        if (!stdx::fs::exists(filePath)) {
            return Unexpected<ErrorDescription<Error>>(
                Tags::IN_PLACE,
                Error::FILE_NOT_FOUND, 
                Ops::fmt("Failed to find file {}!", filePath)
            );
        }
        InputFileStream file(filePath);
        if (!file.is_open()) {
            return Unexpected<ErrorDescription<Error>>(
                Tags::IN_PLACE,
                Error::FILE_OPEN_FAILURE,
                Ops::fmt("Failed to open file {}!", filePath)
            );
        }

        String currentKey;
        String currentName;
        String currentDescription;
        String currentFlavor;

        Scanner scanner(file);
        while (Expected<String, Scanner::Error> lineResult = scanner.next_line()) {
            const String& line = *lineResult;
            if (line.empty() || line.starts_with(COMMENT_PREFIX) || line == EOF_MARKER) {
                continue;
            }

            if (line[0] == '<' && line[line.length() - 1] == '>') {
                if (!currentKey.empty()) {
                    cardNames[currentKey] = currentName;
                    cardDescriptions[currentKey] = currentDescription;
                    cardFlavours[currentKey] = currentFlavor;
                }
                currentKey = util::trimString(line.substr(1, line.length() - 2));
                currentName = "";
                currentDescription = "";
                currentFlavor = "";
            } else if (line.starts_with("name=")) {
                currentName = util::unescapeText(line.substr(5));
            } else if (line.starts_with("descr=")) {
                currentDescription = util::unescapeText(line.substr(6));
            } else if (line.starts_with("flavor=")) {
                currentFlavor = util::unescapeText(line.substr(7));
            }
        }

        if (!currentKey.empty()) {
            cardNames[currentKey] = currentName;
            cardDescriptions[currentKey] = currentDescription;
            cardFlavours[currentKey] = currentFlavor;
        }

        return {};
    }

    /**
     * @brief Parses the card artist names file and populates the cardArtistNames map.
     * @param filePath Path to the card artist names file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseCardArtistNamesFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing card artist names file: {}...", filePath);
        #endif

        return parseSimpleFormatFile(filePath, cardArtistNames);
    }

    /**
     * @brief Parses the card artist names file and populates the commentTexts map.
     * @param filePath Path to the comments file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseCommentsFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing comments file: {}...", filePath);
        #endif

        return parseSimpleFormatFile(filePath, commentTexts);
    }

    /**
     * @brief Parses the card artist names file and populates the configTexts map.
     * @note It is NOT used for parsing user config files.
     * @param filePath Path to the config texts file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseConfigFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing config texts file: {}...", filePath);
        #endif

        return parseSimpleFormatFile(filePath, configTexts);
    }

    /**
     * @brief Parses the field names file and populates the fieldNames map.
     * @param filePath Path to the field names file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseFieldNamesFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing field names file: {}...", filePath);
        #endif

        return parseSimpleFormatFile(filePath, fieldNames);
    }

    /**
     * @brief Parses the game messages file and populates the gameMessages map.
     * @param filePath Path to the game messages file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseGameMessagesFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing game messages file: {}...", filePath);
        #endif

        return parseSimpleFormatFile(filePath, gameMessages);
    }

    /**
     * @brief Parses the game norma file and populates the gameNormaTexts map.
     * @param filePath Path to the game norma file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseGameNormaFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing game norma texts file: {}...", filePath);
        #endif

        return parseSimpleFormatFile(filePath, gameNormaTexts);
    }

    /**
     * @brief Parses the game system file and populates the gameSystemTexts map.
     * @param filePath Path to the game system file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseGameSystemFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing game system texts file: {}...", filePath);
        #endif

        return parseSimpleFormatFile(filePath, gameSystemTexts);
    }

    /**
     * @brief Parses the menu screens file and populates the menuScreenTexts map.
     * @param filePath Path to the menu screens file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseMenuScreensFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing menu screens texts file: {}...", filePath);
        #endif

        return parseSimpleFormatFile(filePath, menuScreenTexts);
    }

    /**
     * @brief Parses the result file and populates the resultTexts map.
     *
     * @param filePath Path to the result file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseResultFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing result texts file: {}...", filePath);
        #endif

        return parseSimpleFormatFile(filePath, resultTexts);
    }

    /**
     * @brief Parses the units file and populates the unitNames map.
     * @param filePath Path to the units file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseUnitsFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing units file: {}...", filePath);
        #endif

        if (!stdx::fs::exists(filePath)) {
            return Unexpected<ErrorDescription<Error>>(
                Tags::IN_PLACE,
                Error::FILE_NOT_FOUND, 
                Ops::fmt("Failed to find file {}!", filePath)
            );
        }
        InputFileStream file(filePath);
        if (!file.is_open()) {
            return Unexpected<ErrorDescription<Error>>(
                Tags::IN_PLACE,
                Error::FILE_OPEN_FAILURE,
                Ops::fmt("Failed to open file {}!", filePath)
            );
        }

        String currentKey;
        String currentName;
        String currentDescription;

        Scanner scanner(file);
        while (Expected<String, Scanner::Error> lineResult = scanner.next_line()) {
            const String& line = *lineResult;
            if (line.empty() || line.substr(0, 2) == COMMENT_PREFIX || line == EOF_MARKER) {
                continue;
            }

            if (line[0] == '<' && line[line.length() - 1] == '>') {
                if (!currentKey.empty() && !currentName.empty()) {
                    unitNames[currentKey] = currentName;
                    unitDescriptions[currentKey] = currentDescription;
                }
                currentKey = util::trimString(line.substr(1, line.length() - 2));
                currentName = "";
                currentDescription = "";
            } else if (line.starts_with("name=")) {
                currentName = util::unescapeText(line.substr(5));
            } else if (line.starts_with("descr=")) {
                currentDescription = util::unescapeText(line.substr(6));
            }
        }

        if (!currentKey.empty() && !currentName.empty()) {
            unitNames[currentKey] = currentName;
            unitDescriptions[currentKey] = currentDescription;
        }

        return {};
    }

    /**
     * @brief Parses the voice actor names file and populates the voiceActorNames map.
     * @param filePath Path to the voice actor names file.
     * @return A Error representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> parseVoiceActorNamesFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        logger->debug("Parsing voice actor names file: {}...", filePath);
        #endif

        return parseSimpleFormatFile(filePath, voiceActorNames);
    }

    /**
     * @brief Initializes all text maps by parsing their respective files.
     */
    [[nodiscard]]
    bool init() noexcept {
        #ifndef NDEBUG
        logger->debug("Now loading localization contents...");
        #endif

        bool successful = true;

        Path cardsFile(Ops::fmt(PATH_CARDS_FILE, SettingsService::languageToCode(language)));
        Path cards2File(Ops::fmt(PATH_CARDS_2_FILE, SettingsService::languageToCode(language)));
        Path cardArtistsFile(Ops::fmt(PATH_CARDARTISTS_FILE, SettingsService::languageToCode(language)));
        Path commentsFile(Ops::fmt(PATH_COMMENT_FILE, SettingsService::languageToCode(language)));
        Path configFile(Ops::fmt(PATH_CONFIG_FILE, SettingsService::languageToCode(language)));
        Path fieldNamesFile(Ops::fmt(PATH_FIELDNAMES_FILE, SettingsService::languageToCode(language)));
        Path gameMessagesFile(Ops::fmt(PATH_GAME_MESSAGE_FILE, SettingsService::languageToCode(language)));
        Path gameNormaFile(Ops::fmt(PATH_GAME_NORMA_FILE, SettingsService::languageToCode(language)));
        Path gameSystemFile(Ops::fmt(PATH_GAME_SYSTEM_FILE, SettingsService::languageToCode(language)));
        Path menuScreensFile(Ops::fmt(PATH_MENUSCREENS_FILE, SettingsService::languageToCode(language)));
        Path resultFile(Ops::fmt(PATH_RESULT_FILE, SettingsService::languageToCode(language)));
        Path unitsFile(Ops::fmt(PATH_UNITS_FILE, SettingsService::languageToCode(language)));
        Path voiceActorsFile(Ops::fmt(PATH_VOICEACTORS_FILE, SettingsService::languageToCode(language)));

        Vector<Expected<void, ErrorDescription<Error>>> results = {
            parseCardsFile(cardsFile),
            parseCardsFile(cards2File),
            parseCardArtistNamesFile(cardArtistsFile),
            parseCommentsFile(commentsFile),
            parseConfigFile(configFile),
            parseFieldNamesFile(fieldNamesFile),
            parseGameMessagesFile(gameMessagesFile),
            parseGameNormaFile(gameNormaFile),
            parseGameSystemFile(gameSystemFile),
            parseMenuScreensFile(menuScreensFile),
            parseResultFile(resultFile),
            parseUnitsFile(unitsFile),
            parseVoiceActorNamesFile(voiceActorsFile)
        };

        for (const Expected<void, ErrorDescription<Error>>& result: results) {
            if (!result.has_value()) {
                logger->warn(
                    "Failed to load file, error {}!",
                    result.error().message()
                );
                successful = false;
            }
        }

        #ifndef NDEBUG
        logger->debug("Loading localization complete!");
        #endif

        return successful;
    }

    /**
     * @brief Clears all localization dictionaries, to be performed at cleanup.
     */
    void cleanup() noexcept {
        #ifndef NDEBUG
        logger->debug("Now cleaning localization contents...");
        #endif

        cardNames.clear();
        cardDescriptions.clear();
        cardFlavours.clear();
        cardArtistNames.clear();
        commentTexts.clear();
        configTexts.clear();
        fieldNames.clear();
        gameMessages.clear();
        gameNormaTexts.clear();
        gameSystemTexts.clear();
        menuScreenTexts.clear();
        resultTexts.clear();
        unitNames.clear();
        unitDescriptions.clear();
        voiceActorNames.clear();

        #ifndef NDEBUG
        logger->debug("Cleaning localization complete!");
        #endif
    }
public:
    /**
     * @brief Constructs a new LocalizationService object.
     * @param logger The injected logger.
     * @param settings The injected settings service.
     */
    [[=Inject]]
    LocalizationService(
        [[=Named(*Class<LocalizationService>().name())]] SharedPointer<Logger> logger,
        SharedPointer<SettingsService> settings
    ):
        logger{Ops::move(logger)},
        language{settings->getLanguage()} {
        if (init()) {
            this->logger->info("Successfully loaded all text assets!");
        } else {
            this->logger->warn("Text assets were not successfully initialized!");
        }
    }

    /**
     * @brief Destroy the LocalizationService object
     */
    ~LocalizationService() {
        cleanup();
    }

    /**
     * @brief Gets a card name by key.
     * @param key The lookup key.
     * @return The name, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getCardName(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = cardNames.find(String(key)); it != cardNames.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a card description by key.
     * @param key The lookup key.
     * @return The description, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getCardDescription(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = cardDescriptions.find(String(key)); it != cardDescriptions.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a card flavour text by key.
     * @param key The lookup key.
     * @return The flavour text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getCardFlavour(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = cardFlavours.find(String(key)); it != cardFlavours.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a card artist name by key.
     * @param key The lookup key.
     * @return The card artist name, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getCardArtistName(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = cardArtistNames.find(String(key)); it != cardArtistNames.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a comment text by key.
     * @param key The lookup key.
     * @return The comment text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getCommentText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = commentTexts.find(String(key)); it != commentTexts.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a config text by key.
     * @param key The lookup key.
     * @return The config text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getConfigText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = configTexts.find(String(key)); it != configTexts.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a field name by key.
     * @param key The lookup key.
     * @return The field name, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getFieldName(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = fieldNames.find(String(key)); it != fieldNames.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a game message by key.
     * @param key The lookup key.
     * @return The game message, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getGameMessage(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = gameMessages.find(String(key)); it != gameMessages.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a norma text by key.
     * @param key The lookup key.
     * @return The norma text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getGameNormaText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = gameNormaTexts.find(String(key)); it != gameNormaTexts.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a game system text by key.
     * @param key The lookup key.
     * @return The game system text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getGameSystemText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = gameSystemTexts.find(String(key)); it != gameSystemTexts.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a menu screen text by key.
     * @param key The lookup key.
     * @return The menu screen text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getMenuScreenText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = menuScreenTexts.find(String(key)); it != menuScreenTexts.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a result text by key.
     * @param key The lookup key.
     * @return The result text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getResultText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = resultTexts.find(String(key)); it != resultTexts.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a unit name by key.
     * @param key The lookup key.
     * @return The unit name, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getUnitName(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = unitNames.find(String(key)); it != unitNames.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a unit description by key.
     * @param key The lookup key.
     * @return The unit description, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getUnitDescription(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = unitDescriptions.find(String(key)); it != unitDescriptions.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a voice actor name by key.
     * @param key The lookup key.
     * @return The voice actor name, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<String, Error> getVoiceActorName(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(Error::EMPTY_KEY);
        }

        if (auto it = voiceActorNames.find(String(key)); it != voiceActorNames.end()) {
            return it->second;
        } else {
            return Unexpected(Error::INVALID_KEY);
        }
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::localization::LocalizationService;

namespace stdx::fmt {
    template <>
    struct Formatter<LocalizationService::Error> {
        static constexpr const char* parse(FormatParseContext& ctx) noexcept {
            return ctx.begin();
        }

        static FormatContext::iterator format(LocalizationService::Error err, FormatContext& ctx) {
            StringView name;
            switch (err) {
                case LocalizationService::Error::EMPTY_KEY:
                    name = "Empty key"; 
                    break;
                case LocalizationService::Error::INVALID_KEY:
                    name = "Invalid key"; 
                    break;
                case LocalizationService::Error::FILE_NOT_FOUND:
                    name = "File not found"; 
                    break;
                case LocalizationService::Error::FILE_OPEN_FAILURE:
                    name = "File open failure"; 
                    break;
                case LocalizationService::Error::FILE_READ_FAILURE:
                    name = "File read failure"; 
                    break;
            }
            return format_to(ctx.out(), "{}", name);
        }
    };
}

SPECIALIZE_FORMATTER(LocalizationService::Error);
