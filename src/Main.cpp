/**
 * @file Main.cpp
 * @brief Entry point for the openJuice application.
 *
 * This file contains the main function of the openJuice application.
 */

import std;

import openjuice;

using std::collections::Vector;

using openjuice::Main;
using openjuice::engine::managers::GlobalSettings;

using namespace openjuice::engine::util::logging;

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
        Main::main(args);
    } catch (const Exception& e) {
        Logger::getInstance().log(LogLevel::ERROR, "An error occured: {}", e.what());
        return EXIT_FAILURE;
    } catch (...) {
        Logger::getInstance().log(LogLevel::ERROR, "An unknown error occured.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
