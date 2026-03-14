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

import stdx;

import openjuice.engine;

using stdx::collections::Vector;
using stdx::util::ArgumentParser;

using openjuice::engine::Engine;

BEGIN_MODULE_NAMESPACE(openjuice);

/**
 * @class Main
 * @brief Utility Main class to directly handle args as a vector
 */
export class Main final {
private:
    UTILITY_CLASS(Main);
public:
    /**
     * @brief The main function of the openJuice application.
     *
     * @param args Array of command line arguments
     */
    static void main(Span<String> args) {
        ArgumentParser parser("openJuice", "0.0.x");
        parser.add_argument("-c", "--cli")
            .help("launch in CLI mode")
            .default_value(false)
            .implicit_value(true)
            .nargs(0uz);

        parser.parse_args(Vector<String>(args.begin(), args.end()));

        Engine::LaunchMode mode = parser.get<bool>("-c")
            ? Engine::LaunchMode::CLI
            : Engine::LaunchMode::TUI;
        Engine eng(mode);
        eng.init();
    }

    /**
     * @brief The main function of the openJuice application.
     *
     * @param args Array of command line arguments
     */
    static void main(Span<char*> args) {
        Vector<String> sargs(args.begin(), args.end());
        main(Span<String>(sargs));
    }
};

END_MODULE_NAMESPACE();
