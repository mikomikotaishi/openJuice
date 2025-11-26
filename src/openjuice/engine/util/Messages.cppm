/**
 * @file Messages.cppm
 * @module openjuice.engine.util.Messages
 * @brief Implementation of the Messages namespace.
 *
 * This file contains the implementation of the Messages namespace, which is used to print various messages.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util.Messages;

import std;

namespace io = std::io;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @namespace messages
 * @brief Namespace for printing messages.
 */
export namespace messages {
    /**
     * @brief Print the help message.
     */
    void printHelp() {
        io::println("Help message");
    }

    /**
     * @brief Print the credits message.
     */
    void printCredits() {
        io::println("Version: 0.0.x");
        io::println("Credits message");
    }
}

END_MODULE_NAMESPACE();
