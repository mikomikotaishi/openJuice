/**
 * @file Main.cpp
 * @brief Entry point for the openJuice application.
 *
 * This file contains the main function of the openJuice application.
 */

import std;
import stdx;

import openjuice;

using std::collections::Vector;
using stdx::util::logging::LoggerFactory;

using openjuice::Main;
using openjuice::engine::managers::GlobalSettings;
using openjuice::engine::util::Constants;

/**
 * @brief The main function of the openJuice application.
 *
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return Exit code
 */
int main(int argc, char* argv[]) {
    try {
        Vector<String> args(argv + 1, argv + argc);
        GlobalSettings::getInstance()
            .setProgramName(argv[0])
            .setProgramArgs(args);
        LoggerFactory::instance()
            .init(Constants::PATH_DEBUGFILE);
        Main::main(args);
    } catch (const Exception& e) {
        LoggerFactory::instance().of("::main()")->error("An error occured: {}", e.what());
        return EXIT_FAILURE;
    } catch (...) {
        LoggerFactory::instance().of("::main()")->error("An unknown error occured.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
