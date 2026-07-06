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
    try {
        Vector<StringView> args(argv, argv + argc);
        Main::main(args);
    } catch (const Exception& e) {
        System::err.println("An error occured: {}", e.what());
        System::err.println(StackTrace::current());
        return System::EXIT_FAILURE;
    } catch (...) {
        System::err.println("An unknown error occured.");
        System::err.println(StackTrace::current());
        return System::EXIT_FAILURE;
    }
    return System::EXIT_SUCCESS;
}
