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

import :AppConfiguration;

import stdx;

import openjuice.engine;

using stdx::collections::Vector;
using stdx::inject::Injector;
using stdx::mem::SharedPointer;
using stdx::util::ArgumentParser;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;
using stdx::util::logging::SourceLocationFormat;

using openjuice::engine::Engine;

BEGIN_MODULE_NAMESPACE(openjuice);

/**
 * @class Main
 * @brief Artificial entry point for the openJuice application.
 */
export class Main final {
private:
    #ifndef NDEBUG
    static constexpr SourceLocationFormat TRACE_FORMAT = SourceLocationFormat::FILE_LINE;
    #else
    static constexpr SourceLocationFormat TRACE_FORMAT = SourceLocationFormat::NONE;
    #endif

    static constexpr StringView PATH_DEBUG_FILE = "./userdata/debug.txt"; ///< The debug file path.

    inline static const SharedPointer<LoggerFactory> logging = LoggerFactory::Builder()
        .of_source_location_format(TRACE_FORMAT)
        .with_file(PATH_DEBUG_FILE)
        .with_banner()
        .build_shared(); ///< The injected logger factory.

    inline static const SharedPointer<Logger> logger = logging->of<Main>(); ///< The logger instance for the Main class.
public:
    Main() = delete("Main is a utility class and cannot be instantiated.");

    /**
     * @brief The main function of the openJuice application.
     * @param args Command line arguments
     */
    static void main(Span<const StringView> args) {
        try {
            ArgumentParser parser("openJuice", "0.0.x");
            parser.parse_args(args);

            AppConfiguration config(logging, logging->of<AppConfiguration>());
            Injector injector = Injector::create(config);
            Engine& eng = injector.get<Engine&>();
            eng.init();
        } catch (const Exception& e) {
            logger->error("An error occurred: {}!", e.what());
            throw;
        } catch (...) {
            logger->error("An unknown error occurred!");
            throw;
        }
    }
};

END_MODULE_NAMESPACE();
