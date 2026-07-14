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

using openjuice::Main;

/**
 * @brief The main function of the openJuice application.
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return Exit code
 *
 * Delegates to the Main class to launch the engine.
 * This function acts as a miniature runtime carrier.
 */
int main() {
    try {
        Main::main(Environment::args());
    } catch (const Exception& e) {
        System::err.println("An error occured: {}", e.what());
        System::err.printf("Stack trace: %n%s%n", StackTrace::current());
        return System::EXIT_FAILURE;
    } catch (...) {
        System::err.println("An unknown error occured.");
        System::err.printf("Stack trace: %n%s%n", StackTrace::current());
        return System::EXIT_FAILURE;
    }
    return System::EXIT_SUCCESS;
}
