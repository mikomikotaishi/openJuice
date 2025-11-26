/**
 * @file TextManager.cppm
 * @module openjuice.engine.managers.TextManager
 * @brief Module file for managing parsing text from files.
 *
 * This file contains the implementation of the TextManager class.
 */
module;

// Standard library headers are necessary here - there is no workaround
#include <string>

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.managers.TextManager;

export import :TextManagerError;

import std;

import openjuice.engine.managers.GlobalSettings;
import openjuice.engine.util.Misc;
import openjuice.engine.util.Logging;

using std::collections::HashMap;
using std::collections::Vector;
using std::fs::Path;
using std::io::IOException;
using std::io::InputFileStream;
using std::util::InPlaceTag;

namespace io = std::io;
namespace fmt = std::fmt;
namespace fs = std::fs;

using namespace openjuice::engine::util::logging;

BEGIN_MODULE_NAMESPACE(openjuice::engine::managers);

/**
 * @class TextManager
 * @brief Class for loading localisation and game initialisation.
 */
export class TextManager {
public:
    static constexpr StringView PATH_ABILITIES_FILE = "./assets/define/{}/abilities.txt"; ///< File containing ability localisation.
    static constexpr StringView PATH_CARDARTISTS_FILE = "./assets/define/{}/cardartists.txt"; ///< File containing card artist localisation.
    static constexpr StringView PATH_CARDS_FILE = "./assets/define/{}/cards.txt"; ///< File containing main cards localisation.
    static constexpr StringView PATH_CARDS_2_FILE = "./assets/define/{}/cards_2.txt"; ///< File containing secondary cards localisation.
    static constexpr StringView PATH_CARDS_BOUNTY_FILE = "./assets/define/{}/cards_bounty.txt"; ///< File containing bounty mode card localisation.
    static constexpr StringView PATH_CARDS_COOP_FILE = "./assets/define/{}/cards_coop.txt"; ///< File containing co-op mode card localisation.
    static constexpr StringView PATH_CARDS_EFFECT_COOP_FILE = "./assets/define/{}/cards_effect_coop.txt"; ///< File containing co-op mode card effect localisation.
    static constexpr StringView PATH_CARDS_EFFECT_FILE = "./assets/define/{}/cards_effect.txt"; ///< File containing general card effect localisation.
    static constexpr StringView PATH_CARDS_MISC_FILE = "./assets/define/{}/cards_misc.txt"; ///< File containing miscellaneous cards localisation.
    static constexpr StringView PATH_CARDS_MUSHROOM_FILE = "./assets/define/{}/cards_mushroom.txt"; ///< File containing mushroom cards localisation.
    static constexpr StringView PATH_CHALLENGES_FILE = "./assets/define/{}/challenges.txt"; ///< File containing challenge localisation.
    static constexpr StringView PATH_CHAOS_MUTATORS_FILE = "./assets/define/{}/chaos_mutators.txt"; ///< File containing chaos mutator localisation.
    static constexpr StringView PATH_CHARACTERSELECT_FILE = "./assets/define/{}/characterselect.txt"; ///< File containing character selection localisation.
    static constexpr StringView PATH_CODEX_FILE = "./assets/define/{}/codex.txt"; ///< File containing codex/lore localisation.
    static constexpr StringView PATH_COMMENT_FILE = "./assets/define/{}/comment.txt"; ///< File containing UI comments and messages.
    static constexpr StringView PATH_CONFIG_FILE = "./assets/define/{}/config.txt"; ///< File containing configuration settings localisation.
    static constexpr StringView PATH_CONSUMABLES_FILE = "./assets/define/{}/consumables.txt"; ///< File containing consumable item localisation.
    static constexpr StringView PATH_ERROR_FILE = "./assets/define/{}/error.txt"; ///< File containing error messages.
    static constexpr StringView PATH_EVENTNAMES_FILE = "./assets/define/{}/eventnames.txt"; ///< File containing event name localisation.
    static constexpr StringView PATH_FIELDEVENTS_FILE = "./assets/define/{}/fieldevents.txt"; ///< File containing field event localisation.
    static constexpr StringView PATH_FIELDNAMES_FILE = "./assets/define/{}/fieldnames.txt"; ///< File containing field name localisation.
    static constexpr StringView PATH_GAME_MESSAGE_FILE = "./assets/define/{}/game_message.txt"; ///< File containing game message localisation.
    static constexpr StringView PATH_GAME_NORMA_FILE = "./assets/define/{}/game_norma.txt"; ///< File containing norma level localisation.
    static constexpr StringView PATH_GAME_SYSTEM_FILE = "./assets/define/{}/game_system.txt"; ///< File containing game system messages.
    static constexpr StringView PATH_GAME_TUTORIAL_FILE = "./assets/define/{}/game_tutorial.txt"; ///< File containing tutorial messages.
    static constexpr StringView PATH_LAUNCHER_FILE = "./assets/define/{}/launcher.txt"; ///< File containing launcher localisation.
    static constexpr StringView PATH_MENUSCREENS_FILE = "./assets/define/{}/menuscreens.txt"; ///< File containing menu screen localisation.
    static constexpr StringView PATH_MIXERS_FILE = "./assets/define/{}/mixers.txt"; ///< File containing mixer localisation.
    static constexpr StringView PATH_MULTIPLAYER_FILE = "./assets/define/{}/multiplayer.txt"; ///< File containing multiplayer localisation.
    static constexpr StringView PATH_PETS_FILE = "./assets/define/{}/pets.txt"; ///< File containing pet localisation.
    static constexpr StringView PATH_PINS_FILE = "./assets/define/{}/pins.txt"; ///< File containing pin localisation.
    static constexpr StringView PATH_PROFILE_FILE = "./assets/define/{}/profile.txt"; ///< File containing profile localisation.
    static constexpr StringView PATH_RESULT_FILE = "./assets/define/{}/result.txt"; ///< File containing result screen localisation.
    static constexpr StringView PATH_SHOP_FILE = "./assets/define/{}/shop.txt"; ///< File containing shop localisation.
    static constexpr StringView PATH_UNIT_GAMES_FILE = "./assets/define/{}/unitgames.txt"; ///< File containing unit game localisation.
    static constexpr StringView PATH_UNITS_FILE = "./assets/define/{}/units.txt"; ///< File containing unit localisation.
    static constexpr StringView PATH_VOICEACTORS_FILE = "./assets/define/{}/voiceactors.txt"; ///< File containing voice actor localisation.

    static constexpr StringView ORANGE_JUICE_WIKI_URL = "https://100orangejuice.fandom.com"; ///< The URL for the 100% Orange Juice! wiki
private:
    static inline const Logger& LOGGER = Logger::getInstance(); ///< The logger instance.

    static constexpr StringView EMPTY_STRING = ""; ///< The empty string.
    static constexpr StringView COMMENT_PREFIX = "//"; ///< A comment prefix used in the localisation files.
    static constexpr StringView EOF_MARKER = "[EOF]"; ///< A marker used to denote the end of the file in the localisation files.

    const String gameLanguageCode; ///< The language code currently being used by the game.

    HashMap<String, String> cardNames; ///< A dictionary of all card names.
    HashMap<String, String> cardDescriptions; ///< A dictionary of all card descriptions.
    HashMap<String, String> cardFlavours; ///< A dictionary of all card flavour texts.
    HashMap<String, String> cardArtistNames; ///< A dictionary of all card artist names.
    HashMap<String, String> commentTexts; ///< A dictionary of all comment texts.
    HashMap<String, String> fieldNames; ///< A dictionary of all field names.
    HashMap<String, String> gameMessages; ///< A dictionary of all game messages.
    HashMap<String, String> gameNormaTexts; ///< A dictionary of all messages issued during norma.
    HashMap<String, String> gameSystemTexts; ///< A dictionary of all game system texts.
    HashMap<String, String> menuScreenTexts; ///< A dictionary of all menu screen texts.
    HashMap<String, String> resultTexts; ///< A dictionary of all result screen texts.
    HashMap<String, String> unitNames; ///< A dictionary of all unit names.
    HashMap<String, String> unitDescriptions; ///< A dictionary of all unit descriptions.
    HashMap<String, String> voiceActorNames; ///< A dictionary of all voice actor names.

    /**
     * @brief Default constructor.
     */
    TextManager():
        gameLanguageCode{GlobalSettings::languageToString(GlobalSettings::getInstance().getLanguage())} {
        if (initialiseContents()) {
            LOGGER.log(LogLevel::INFO, "Successfully loaded all text assets!");
        } else {
            LOGGER.log(LogLevel::WARNING, "Text assets were not successfully initialised!");
        }
    }

    /**
     * @brief Destroy the TextManager object
     */
    ~TextManager() noexcept(noexcept(cleanup())) {
        cleanup();
    }

    /**
     * @brief Parses a simple format file where values follow directly after keys.
     *
     * @param filePath Path to the file.
     * @param targetMap The map to populate with key-value pairs.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseSimpleFormatFile(const Path& filePath, HashMap<String, String>& targetMap) noexcept {
        if (!fs::exists(filePath)) {
            return Unexpected<Error<TextManagerError>>(
                Tags::IN_PLACE,
                TextManagerError::FILE_NOT_FOUND, 
                fmt::format("Failed to find file {}", filePath.native())
            );
        }
        InputFileStream file(filePath);
        if (!file.is_open()) {
            return Unexpected<Error<TextManagerError>>(
                Tags::IN_PLACE,
                TextManagerError::FILE_OPEN_FAILURE,
                fmt::format("Failed to open file {}", filePath.native())
            );
        }

        String line;
        String currentKey;
        bool expectingValue = false;

        while (io::getline(file, line)) {
            if (line.empty() || line.starts_with(COMMENT_PREFIX) || line == EOF_MARKER) {
                continue;
            }

            if (line[0] == '<' && line[line.length() - 1] == '>') {
                currentKey = util::misc::trimString(line.substr(1, line.length() - 2));
                expectingValue = true;
            } else if (expectingValue) {
                targetMap[currentKey] = line;
                expectingValue = false;
            }
        }

        return {};
    }

    /**
     * @brief Parses the cards file and populates card-related maps.
     *
     * @param filePath Path to the cards file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseCardsFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing cards file: {}", filePath.native());
        #endif

        if (!fs::exists(filePath)) {
            return Unexpected<Error<TextManagerError>>(
                Tags::IN_PLACE,
                TextManagerError::FILE_NOT_FOUND, 
                fmt::format("Failed to find file {}", filePath.native())
            );
        }
        InputFileStream file(filePath);
        if (!file.is_open()) {
            return Unexpected<Error<TextManagerError>>(
                Tags::IN_PLACE,
                TextManagerError::FILE_OPEN_FAILURE,
                fmt::format("Failed to open file {}", filePath.native())
            );
        }

        String line;
        String currentKey;
        String currentName;
        String currentDescription;
        String currentFlavor;

        while (io::getline(file, line)) {
            if (line.empty() || line.starts_with(COMMENT_PREFIX) || line == EOF_MARKER) {
                continue;
            }

            if (line[0] == '<' && line[line.length() - 1] == '>') {
                if (!currentKey.empty()) {
                    cardDescriptions[currentKey] = currentDescription;
                    cardFlavours[currentKey] = currentFlavor;
                }
                currentKey = util::misc::trimString(line.substr(1, line.length() - 2));
                currentName = "";
                currentDescription = "";
                currentFlavor = "";
            } else if (line.starts_with("name=")) {
                currentName = line.substr(5);
            } else if (line.starts_with("descr=")) {
                currentDescription = line.substr(6);
            } else if (line.starts_with("flavor=")) {
                currentFlavor = line.substr(7);
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
     *
     * @param filePath Path to the card artist names file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseCardArtistNamesFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing card artist names file: {}", filePath.native());
        #endif

        return parseSimpleFormatFile(filePath, cardArtistNames);
    }

    /**
     * @brief Parses the card artist names file and populates the commentTexts map.
     *
     * @param filePath Path to the comments file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseCommentsFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing comments file: {}", filePath.native());
        #endif

        return parseSimpleFormatFile(filePath, commentTexts);
    }

    /**
     * @brief Parses the field names file and populates the fieldNames map.
     *
     * @param filePath Path to the field names file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseFieldNamesFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing field names file: {}", filePath.native());
        #endif

        return parseSimpleFormatFile(filePath, fieldNames);
    }

    /**
     * @brief Parses the game messages file and populates the gameMessages map.
     *
     * @param filePath Path to the game messages file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseGameMessagesFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing game messages file: {}", filePath.native());
        #endif

        return parseSimpleFormatFile(filePath, gameMessages);
    }

    /**
     * @brief Parses the game norma file and populates the gameNormaTexts map.
     *
     * @param filePath Path to the game norma file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseGameNormaFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing game norma texts file: {}", filePath.native());
        #endif

        return parseSimpleFormatFile(filePath, gameNormaTexts);
    }

    /**
     * @brief Parses the game system file and populates the gameSystemTexts map.
     *
     * @param filePath Path to the game system file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseGameSystemFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing game system texts file: {}", filePath.native());
        #endif

        return parseSimpleFormatFile(filePath, gameSystemTexts);
    }

    /**
     * @brief Parses the menu screens file and populates the menuScreenTexts map.
     *
     * @param filePath Path to the menu screens file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseMenuScreensFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing menu screens texts file: {}", filePath.native());
        #endif

        return parseSimpleFormatFile(filePath, menuScreenTexts);
    }

    /**
     * @brief Parses the result file and populates the resultTexts map.
     *
     * @param filePath Path to the result file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseResultFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing result texts file: {}", filePath.native());
        #endif

        return parseSimpleFormatFile(filePath, resultTexts);
    }

    /**
     * @brief Parses the units file and populates the unitNames map.
     *
     * @param filePath Path to the units file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseUnitsFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing units file: {}", filePath.native());
        #endif

        if (!fs::exists(filePath)) {
            return Unexpected<Error<TextManagerError>>(
                Tags::IN_PLACE,
                TextManagerError::FILE_NOT_FOUND, 
                fmt::format("Failed to find file {}", filePath.native())
            );
        }
        InputFileStream file(filePath);
        if (!file.is_open()) {
            return Unexpected<Error<TextManagerError>>(
                Tags::IN_PLACE,
                TextManagerError::FILE_OPEN_FAILURE,
                fmt::format("Failed to open file {}", filePath.native())
            );
        }

        String line;
        String currentKey;
        String currentName;
        String currentDescription;

        while (io::getline(file, line)) {
            if (line.empty() || line.substr(0, 2) == COMMENT_PREFIX || line == EOF_MARKER) {
                continue;
            }

            if (line[0] == '<' && line[line.length() - 1] == '>') {
                if (!currentKey.empty() && !currentName.empty()) {
                    unitNames[currentKey] = currentName;
                }
                currentKey = util::misc::trimString(line.substr(1, line.length() - 2));
                currentName = "";
                currentDescription = "";
            } else if (line.starts_with("name=")) {
                currentName = line.substr(5);
            } else if (line.starts_with("descr=")) {
                currentDescription = line.substr(6);
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
     *
     * @param filePath Path to the voice actor names file.
     * @return A TextManagerError representing the parsing failure, otherwise nothing.
     */
    [[nodiscard]]
    Expected<void, Error<TextManagerError>> parseVoiceActorNamesFile(const Path& filePath) noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Parsing voice actor names file: {}", filePath.native());
        #endif

        return parseSimpleFormatFile(filePath, voiceActorNames);
    }

    /**
     * @brief Initialises all text maps by parsing their respective files.
     */
    [[nodiscard]]
    bool initialiseContents() noexcept {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Now loading localisation contents");
        #endif

        bool successful = true;

        Path cardsFile(fmt::format(PATH_CARDS_FILE, gameLanguageCode));
        Path cards2File(fmt::format(PATH_CARDS_2_FILE, gameLanguageCode));
        Path cardArtistsFile(fmt::format(PATH_CARDARTISTS_FILE, gameLanguageCode));
        Path commentsFile(fmt::format(PATH_COMMENT_FILE, gameLanguageCode));
        Path fieldNamesFile(fmt::format(PATH_FIELDNAMES_FILE, gameLanguageCode));
        Path gameMessagesFile(fmt::format(PATH_GAME_MESSAGE_FILE, gameLanguageCode));
        Path gameNormaFile(fmt::format(PATH_GAME_NORMA_FILE, gameLanguageCode));
        Path gameSystemFile(fmt::format(PATH_GAME_SYSTEM_FILE, gameLanguageCode));
        Path menuScreensFile(fmt::format(PATH_MENUSCREENS_FILE, gameLanguageCode));
        Path resultFile(fmt::format(PATH_RESULT_FILE, gameLanguageCode));
        Path unitsFile(fmt::format(PATH_UNITS_FILE, gameLanguageCode));
        Path voiceActorsFile(fmt::format(PATH_VOICEACTORS_FILE, gameLanguageCode));

        Vector<Expected<void, Error<TextManagerError>>> results{
            parseCardsFile(cardsFile),
            parseCardsFile(cards2File),
            parseCardArtistNamesFile(cardArtistsFile),
            parseCommentsFile(commentsFile),
            parseFieldNamesFile(fieldNamesFile),
            parseGameMessagesFile(gameMessagesFile),
            parseGameNormaFile(gameNormaFile),
            parseGameSystemFile(gameSystemFile),
            parseMenuScreensFile(menuScreensFile),
            parseResultFile(resultFile),
            parseUnitsFile(unitsFile),
            parseVoiceActorNamesFile(voiceActorsFile)
        };

        for (const Expected<void, Error<TextManagerError>>& result: results) {
            if (!result.has_value()) {
                LOGGER.log(
                    LogLevel::WARNING,
                    "Failed to load file, error {}",
                    result.error().message()
                );
                successful = false;
            }
        }

        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Loading localisation complete!");
        #endif

        return successful;
    }

    /**
     * @brief Clears all localisation dictionaries, to be performed at cleanup.
     */
    void cleanup() RELEASE_NOEXCEPT {
        #ifndef NDEBUG
        LOGGER.log(LogLevel::DEBUG, "Now cleaning localisation contents");
        #endif

        cardNames.clear();
        cardDescriptions.clear();
        cardFlavours.clear();
        cardArtistNames.clear();
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
        LOGGER.log(LogLevel::DEBUG, "Cleaning localisation complete!");
        #endif
    }
public:
    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    TextManager(const TextManager&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying.
     */
    TextManager& operator=(const TextManager&) = delete;

    /**
     * @brief No-operation function.
     * This method exists to ensure that the TextManager is created when needed by the singleton call.
     */
    void noop() const noexcept {}

    /**
     * @brief Gets the singleton instance of TextManager.
     *
     * @return Reference to the singleton instance.
     */
    [[nodiscard]]
    static TextManager& getInstance() {
        static TextManager instance;
        return instance;
    }

    /**
     * @brief Gets a card name by key.
     *
     * @param key The lookup key.
     * @return The name, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getCardName(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = cardNames.find(String(key)); it != cardNames.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a card description by key.
     *
     * @param key The lookup key.
     * @return The description, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getCardDescription(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = cardDescriptions.find(String(key)); it != cardDescriptions.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a card flavour text by key.
     *
     * @param key The lookup key.
     * @return The flavour text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getCardFlavour(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = cardFlavours.find(String(key)); it != cardFlavours.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a card artist name by key.
     *
     * @param key The lookup key.
     * @return The card artist name, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getCardArtistName(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = cardArtistNames.find(String(key)); it != cardArtistNames.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a comment text by key.
     *
     * @param key The lookup key.
     * @return The comment text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getCommentText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = commentTexts.find(String(key)); it != commentTexts.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a field name by key.
     *
     * @param key The lookup key.
     * @return The field name, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getFieldName(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = fieldNames.find(String(key)); it != fieldNames.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a game message by key.
     *
     * @param key The lookup key.
     * @return The game message, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getGameMessage(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = gameMessages.find(String(key)); it != gameMessages.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a norma text by key.
     *
     * @param key The lookup key.
     * @return The norma text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getGameNormaText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = gameNormaTexts.find(String(key)); it != gameNormaTexts.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a game system text by key.
     *
     * @param key The lookup key.
     * @return The game system text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getGameSystemText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = gameSystemTexts.find(String(key)); it != gameSystemTexts.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a menu screen text by key.
     *
     * @param key The lookup key.
     * @return The menu screen text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getMenuScreenText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = menuScreenTexts.find(String(key)); it != menuScreenTexts.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a result text by key.
     *
     * @param key The lookup key.
     * @return The result text, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getResultText(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = resultTexts.find(String(key)); it != resultTexts.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a unit name by key.
     *
     * @param key The lookup key.
     * @return The unit name, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getUnitName(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = unitNames.find(String(key)); it != unitNames.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a unit description by key.
     *
     * @param key The lookup key.
     * @return The unit description, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getUnitDescription(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = unitDescriptions.find(String(key)); it != unitDescriptions.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }

    /**
     * @brief Gets a voice actor name by key.
     *
     * @param key The lookup key.
     * @return The voice actor name, otherwise the error representing the key failure.
     */
    [[nodiscard]]
    Expected<StringView, TextManagerError> getVoiceActorName(StringView key) const noexcept {
        if (key.empty()) {
            return Unexpected(TextManagerError::EMPTY_KEY);
        }

        if (auto it = voiceActorNames.find(String(key)); it != voiceActorNames.end()) {
            return it->second;
        } else {
            return Unexpected(TextManagerError::INVALID_KEY);
        }
    }
};

END_MODULE_NAMESPACE();
