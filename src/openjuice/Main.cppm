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
import openjuice.engine.util;

using stdx::collections::Vector;
using stdx::mem::SharedPointer;
using stdx::util::ArgumentParser;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::Engine;
using openjuice::engine::util::Constants;

BEGIN_MODULE_NAMESPACE(openjuice);

/**
 * @class Main
 * @brief Artificial entry point for the openJuice application.
 */
export class Main final {
private:
    inline static const SharedPointer<LoggerFactory> logging = LoggerFactory::Builder()
        .trace_source(Constants::ENABLE_SOURCE_LOCATION)
        .with_file(Constants::PATH_DEBUG_FILE)
        .with_banner()
        .build_shared(); ///< The injected logger factory.

    inline static const SharedPointer<Logger> logger = logging->of("Main"); ///< The logger instance for the Main class.
public:
    Main() = delete("Main is a utility class and cannot be instantiated.");

    /**
     * @brief The main function of the openJuice application.
     * @param args Command line arguments
     */
    static void main(Span<const StringView> args) {
        try {
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
            Engine eng(mode, logging);
            eng.init();
        } catch (const Exception& e) {
            logger->error("An error occurred: {}", e.what());
            throw;
        } catch (...) {
            logger->error("An unknown error occurred.");
            throw;
        }
    }
};

END_MODULE_NAMESPACE();
