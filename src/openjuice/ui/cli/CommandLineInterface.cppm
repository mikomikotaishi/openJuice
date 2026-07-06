/**
 * @file CommandLineInterface.cppm
 * @module openjuice.ui.cli.CommandLineInterface
 * @brief Command line interface implementation
 */

module;

#include "Macros.hpp"

export module openjuice.ui.cli:CommandLineInterface;

import stdx;

import openjuice.engine.game;
import openjuice.engine.services;
import openjuice.engine.util;
import openjuice.ui.UserInterface;

using stdx::collections::HashMap;
using stdx::io::Scanner;
using stdx::mem::SharedPointer;
using stdx::sync::Mutex;
using stdx::sync::ScopedLock;

using openjuice::engine::game::Game;
using openjuice::engine::services::ConfigurationService;
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
    SharedPointer<ConfigurationService> config; ///< The injected configuration/settings service.

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
     * @brief Constructor that initializes the base UserInterface
     *
     * @param game Shared pointer to game instance
     * @param mutex Reference to state mutex for synchronization
     * @param config The injected configuration/settings service
     */
    CommandLineInterface(SharedPointer<Game> game, Mutex& mutex, SharedPointer<ConfigurationService> config):
        UserInterface(Ops::move(game), mutex),
        config{Ops::move(config)} {}

    /**
     * @brief
     */
    void init() override {
        initLanguage();
        initFrameRate();
        if (Expected<void, ConfigurationService::Error> result = config->save(); !result) {
            System::err.println("Failed to persist settings: {}", result.error());
        }
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
        System::out.println("Current game state: {}", game->toString());
    }

    /**
     * @brief Initializes the language for the command line interface.
     */
    void initLanguage() {
        System::out.println("Enter your desired language:");
        System::out.println("Language codes: English [en], Japanese [jp], Simplified Chinese [chs], Traditional Chinese [cht], Russian [ru], Korean [ko], Spanish [sp], Portuguese (Brazil) [ptbr]");
        
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

        Scanner scanner(System::in);
        while (Optional<String> languageInput = scanner.next_line()) {
            if (auto it = languageMap.find(*languageInput); it != languageMap.end()) {
                config->setLanguage(it->second.first);
                System::out.println("{}", it->second.second);
                break;
            }
        }
    }

    /**
     * @brief Initializes the frame rate for the command line interface.
     */
    void initFrameRate() {
        System::out.println("Enter your desired frame rate (fps) (1-600):");
        System::out.println("Press Enter to use the default (60 fps).");

        Scanner scanner(System::in);
        while (Optional<String> frameRateInputResult = scanner.next_line()) {
            const String& frameRateInput = *frameRateInputResult;
            if (frameRateInput.empty()) {
                config->setFrameRate(60);
                System::out.println("Frame rate: 60 frames per second (default)");
                break;
            }
            usize pos = 0;
            u64 frameRate = stdx::text::string::stoul(frameRateInput, &pos);

            if (pos == frameRateInput.size() && frameRate >= 1 && frameRate <= 600) {
                config->setFrameRate(static_cast<u16>(frameRate));
                System::out.println("Frame rate: {} frames per second", frameRate);
                break;
            } else {
                System::err.println("Invalid frame rate. Please enter a number between 1 and 600.");
            }
        }
    }
};

END_MODULE_NAMESPACE();
