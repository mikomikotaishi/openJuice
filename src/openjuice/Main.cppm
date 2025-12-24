/**
 * @file Main.cpp
 * @module openjuice:Main
 * @brief Main class for the openJuice application.
 *
 * This file contains the main class called by the main function of the openJuice application.
 */

module;

#include "Macros.hpp"

export module openjuice:Main;

import std;

import openjuice.engine;

using std::collections::Vector;

using openjuice::engine::Engine;
using openjuice::engine::util::GameExecuteMode;
using openjuice::engine::util::InputParser;

BEGIN_MODULE_NAMESPACE(openjuice);

/**
 * @class Main
 * @brief Utility Main class to directly handle args as a vector
 */
export class Main final {
private:
    UTILITY_CLASS(Main);

    /**
     * @brief Determines the launch mode to launch the engine with.
     * 
     * @param mode The game execute mode evaluated from input parser.
     * @return Optional<Engine::LaunchMode> where nullopt represents no launch mode from execute mode.
     */
    [[nodiscard]]
    static constexpr Optional<Engine::LaunchMode> getLaunch(GameExecuteMode mode) noexcept {
        switch (mode) {
            case GameExecuteMode::TUI_MODE:
                return Engine::LaunchMode::TUI;
            case GameExecuteMode::CLI_MODE:
                return Engine::LaunchMode::CLI;
            case GameExecuteMode::HELP_MESSAGE:
                return nullopt;
            default:
                std::sys::unreachable();
        }
    }
public:
    /**
     * @brief The main function of the openJuice application.
     *
     * @param args Vector of command line arguments
     */
    static void main(const Vector<String>& args) {
        InputParser inputs(args);
        if (Optional<Engine::LaunchMode> lm = getLaunch(inputs.handleInputs()); lm.has_value()) {
            Engine eng(*lm);
            eng.init();
        }
    }
};

END_MODULE_NAMESPACE();
