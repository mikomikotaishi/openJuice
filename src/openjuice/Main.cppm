/**
 * @file Main.cppm
 * @module openjuice:Main
 * @brief Main class for the openJuice application.
 *
 * This file contains the main class called by the main function of the openJuice application.
 */

module;

#include "Macros.hpp"

export module openjuice:Main;

import stdx;

import openjuice.engine;

using stdx::collections::Vector;
using stdx::util::ArgumentParser;

using openjuice::engine::Engine;

BEGIN_MODULE_NAMESPACE(openjuice);

/**
 * @class Main
 * @brief Artificial entry point for the openJuice application.
 */
export class Main final {
public:
    Main() = delete("Main is a utility class and cannot be instantiated.");

    /**
     * @brief The main function of the openJuice application.
     *
     * @param args Command line arguments
     */
    static void main(Span<StringView> args) {
        ArgumentParser parser("openJuice", "0.0.x");
        parser.add_argument("-c", "--cli")
            .help("launch in CLI mode")
            .default_value(false)
            .implicit_value(true)
            .nargs(0uz);

        parser.parse_args(args);

        Engine::LaunchMode mode = parser.get<bool>("-c")
            ? Engine::LaunchMode::CLI
            : Engine::LaunchMode::TUI;
        Engine eng(mode);
        eng.init();
    }
};

END_MODULE_NAMESPACE();
