/**
 * @file Main.cpp
 * @brief Entry point for the openJuice application.
 *
 * This file contains the main function of the openJuice application.
 */

import stdx;

import openjuice;

using stdx::collections::Vector;
using stdx::debug::StackTrace;
using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::Main;
using openjuice::engine::managers::GlobalSettings;
using openjuice::engine::util::Constants;

/**
 * @brief The main function of the openJuice application.
 *
 * Delegates to the Main class to launch the engine.
 *
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return Exit code
 */
int main(int argc, char* argv[]) {
    const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("::main()");
    bool hasArgs = argc > 1;
    try {
        Vector<StringView> args(argv + static_cast<usize>(hasArgs), argv + argc);
        GlobalSettings::getInstance()
            .setProgramName(argv[0])
            .setProgramArgs(args);
        LoggerFactory::instance()
            .trace_source(Constants::ENABLE_SOURCE_LOCATION)
            .init(Constants::PATH_DEBUGFILE);
        Main::main(args);
    } catch (const Exception& e) {
        LOGGER->error("An error occured: {}", e.what());
        System::err.println(StackTrace::current());
        return System::EXIT_FAILURE;
    } catch (...) {
        LOGGER->error("An unknown error occured.");
        System::err.println(StackTrace::current());
        return System::EXIT_FAILURE;
    }
    return System::EXIT_SUCCESS;
}
