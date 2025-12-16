/**
 * @file CommandLineInterface.cppm
 * @module openjuice.ui.cli.CommandLineInterface
 * @brief Command line interface implementation
 */

module;

#include "Macros.hpp"

export module openjuice.ui.cli.CommandLineInterface;

import std;

import openjuice.engine.game.Game;
import openjuice.engine.managers.GlobalSettings;
import openjuice.engine.managers.TextManager;
import openjuice.engine.util.Language;
import openjuice.ui.UserInterface;

using std::collections::HashMap;
using std::io::Cin;
using std::io::Stderr;
using std::mem::SharedPointer;
using std::sync::Mutex;
using std::sync::ScopedLock;

using openjuice::engine::game::Game;
using openjuice::engine::managers::GlobalSettings;
using openjuice::engine::managers::TextManager;
using openjuice::engine::util::Language;

BEGIN_MODULE_NAMESPACE(openjuice::ui::cli);

/**
 * @class CommandLineInterface
 * @brief
 *
 * @extends UserInterface
 */
export class CommandLineInterface: public UserInterface {
private:
    /**
     * @brief
     *
     * @return true if there is input, false otherwise
     */
    [[nodiscard]]
    bool hasInput() {
        return false;
    }

    /**
     * @brief
     *
     * @return String
     */
    [[nodiscard]]
    String readInput() {
        return "";
    }

    /**
     * @brief
     *
     * @param cmd
     */
    void processCommand(StringView cmd) {
        return;
    }
public:
    /**
     * @brief Constructor that initialises the base UserInterface
     *
     * @param state Shared pointer to game instance
     * @param mutex Reference to state mutex for synchronisation
     */
    CommandLineInterface(SharedPointer<Game> game, Mutex& mutex):
        UserInterface(std::util::move(game), mutex) {}

    /**
     * @brief
     */
    void init() override {
        initialiseLanguage();
        initialiseFrameRate();
    }

    /**
     * @brief
     */
    void processEvents() override {
        if (hasInput()) {
            String command = readInput();

            if (command == "exit") {
                requestExit();
            } else {
                ScopedLock<Mutex> lock(stateMutex);
                processCommand(command);
            }
        }
    }

    /**
     * @brief
     */
    void render() override {
        std::io::println("Current game state: {}", game->toString());
    }

    /**
     * @brief Initialises the language for the command line interface.
     */
    static void initialiseLanguage() {
        std::io::println("Enter your desired language:");
        std::io::println("Language codes: English [en], Japanese [jp], Simplified Chinese [chs], Traditional Chinese [cht], Russian [ru], Korean [ko], Spanish [sp], Portuguese (Brazil) [ptbr]");
        
        static const HashMap<String, Pair<Language, StringView>> languageMap = {
            {"en", {Language::ENGLISH, "English selected"}},
            {"jp", {Language::JAPANESE, "Japanese selected"}},
            {"chs", {Language::CHINESE_SIMPLIFIED, "Simplified Chinese selected"}},
            {"cht", {Language::CHINESE_TRADITIONAL, "Traditional Chinese selected"}},
            {"ru", {Language::RUSSIAN, "Russian selected"}},
            {"ko", {Language::KOREAN, "Korean selected"}},
            {"sp", {Language::SPANISH, "Spanish selected"}},
            {"ptbr", {Language::PORTUGUESE_BR, "Portuguese (Brazil) selected"}}
        };

        String languageInput;
        while (true) {
            std::io::getline(Cin, languageInput);
            if (auto it = languageMap.find(languageInput); it != languageMap.end()) {
                GlobalSettings::getInstance().setLanguage(it->second.first);
                std::io::println("{}", it->second.second);
                break;
            }
        }
        TextManager::getInstance().noop();
    }

    /**
     * @brief Initialises the frame rate for the command line interface.
     */
    static void initialiseFrameRate() {
        std::io::println("Enter your desired frame rate (fps) (1-600):");
        std::io::println("Press Enter to use the default (60 fps).");

        String frameRateInput;

        while (true) {
            std::io::getline(Cin, frameRateInput);
            if (frameRateInput.empty()) {
                GlobalSettings::getInstance().setFrameRate(60);
                std::io::println("Frame rate: 60 frames per second (default)");
                break;
            }
            usize pos = 0;
            u64 frameRate = std::text::string::stoul(frameRateInput, &pos);

            if (pos == frameRateInput.size() && frameRate >= 1 && frameRate <= 600) {
                GlobalSettings::getInstance().setFrameRate(static_cast<u16>(frameRate));
                std::io::println("Frame rate: {} frames per second", frameRate);
                break;
            } else {
                std::io::println(Stderr, "Invalid frame rate. Please enter a number between 1 and 600.");
            }
        }
    }
};

END_MODULE_NAMESPACE();
