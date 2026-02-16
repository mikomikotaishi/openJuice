/**
 * @file InputParser.cppm
 * @module openjuice.engine.util:InputParser
 * @brief Implementation of the InputParser class.
 *
 * This file contains the implementation of the InputParser class, which extends the InputParserBase class to handle specific command line options.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.util:InputParser;

#define INPUTPARSER_DEPRECATION_MESSAGE "Do not use InputParser, instead use stdx::util::ArgumentParser as it is simpler."

import stdx;

import :Misc;

using stdx::collections::Vector;
using stdx::ranges::views::Iota;
using stdx::ranges::views::TakeWhile;
using stdx::ranges::views::Transform;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

export enum class GameExecuteMode: u8 {
    HELP_MESSAGE,
    TUI_MODE,
    CLI_MODE,
};

/**
 * @class InputParserBase
 * @brief Class for parsing command line input.
 */
class [[deprecated(INPUTPARSER_DEPRECATION_MESSAGE)]] InputParserBase {
private:
    Vector<String> args; ///< Vector of command line arguments.
    Vector<String> envs; ///< Vector of environment variables.
public:
        /**
     * @brief Constructor that initialises the parser with command line arguments.
     *
     * @param args Vector of command line arguments
     * @param envp Array of environment variable arguments.
     */
    explicit InputParserBase(const Vector<String>& args, char* envp[] = nullptr):
        args{args} {
        if (envp) {
            stdx::ranges::for_each(
                Iota(0uz)
                    | Transform([envp](auto i) -> char* { return envp[i]; })
                    | TakeWhile([](auto p) -> bool { return p != nullptr; }),
                [this](auto env) -> void { envs.emplace_back(env); }
            );
        }
    }

    /**
     * @brief Constructor that initialises the parser with command line arguments.
     *
     * @param args Array of command line arguments (String)
     * @param envp Array of environment variable arguments.
     */
    explicit InputParserBase(Span<String> args, char* envp[] = nullptr):
        InputParserBase(args.empty() ? Vector<String>() : Vector<String>(args.begin() + 1, args.end()), envp, Vector<String>()) {}

    /**
     * @brief Constructor that initialises the parser with command line arguments.
     *
     * @param args Array of command line arguments (char*)
     * @param envp Array of environment variable arguments.
     */
    explicit InputParserBase(Span<char*> args, char* envp[] = nullptr):
        InputParserBase(args.empty() ? Vector<String>() : Vector<String>(args.begin() + 1, args.end()), envp, Vector<String>()) {}

    /**
     * @brief Constructor that initialises the parser with command line arguments and valid options.
     *
     * @param args Vector of command line arguments.
     * @param envp Array of environment variable arguments.
     * @param validOptions Vector of valid options.
     * @throws InvalidArgumentException if an invalid argument is found
     */
    explicit InputParserBase(const Vector<String>& args, char* envp[] = nullptr, const Vector<String>& validOptions = {}) throws (InvalidArgumentException):
        args{args} {
        bool foundValue = false;
        if (envp) {
            stdx::ranges::for_each(
                Iota(0uz)
                    | Transform([envp](auto i) -> char* { return envp[i]; })
                    | TakeWhile([](auto p) -> bool { return p != nullptr; }),
                [this](auto env) -> void { envs.emplace_back(env); }
            );
        }
        for (const String& arg: args) {
            if (stdx::ranges::contains(validOptions, arg)) {
                if (Integer::parse(arg) && !foundValue) {
                    foundValue = true;
                    continue;
                }
                throw InvalidArgumentException(stdx::fmt::format("Invalid option: {}", arg));
            }
        }
    }

    /**
     * @brief Constructor that initializes the parser with command line arguments and valid options.
     *
     * @param args Array of command line arguments (String).
     * @param envp Array of environment variable arguments.
     * @param validOptions Vector of valid options.
     *
     * @throws InvalidArgumentException if an invalid argument is found
     */
    explicit InputParserBase(Span<String> args, char* envp[] = nullptr, const Vector<String>& validOptions = {}) throws (InvalidArgumentException):
        InputParserBase(args.empty() ? Vector<String>() : Vector<String>(args.begin() + 1, args.end()), envp, validOptions) {}

    /**
     * @brief Constructor that initializes the parser with command line arguments and valid options.
     *
     * @param args Array of command line arguments (char*).
     * @param envp Array of environment variable arguments.
     * @param validOptions Vector of valid options.
     *
     * @throws InvalidArgumentException if an invalid argument is found
     */
    explicit InputParserBase(Span<char*> args, char* envp[] = nullptr, const Vector<String>& validOptions = {}) throws (InvalidArgumentException): 
        InputParserBase(args.empty() ? Vector<String>() : Vector<String>(args.begin() + 1, args.end()), envp, validOptions) {}

    /**
     * @brief Gets the value of a specified option.
     *
     * @param option The option to get the value for.
     * @return The value of the option, or an empty string if the option does not exist.
     */
    [[nodiscard]]
    String getOptionValue(StringView option) const noexcept {
        if (auto it = stdx::ranges::find(args, option); it != args.end()) {
            ++it;
            if (it != args.end()) {
                return *it;
            }
        }
        return "";
    }

    /**
     * @brief Checks if a specified option exists.
     *
     * @param option The option to check for.
     * @return true if the option exists, false otherwise.
     */
    [[nodiscard]]
    bool optionExists(const String& option) const noexcept {
        return stdx::ranges::contains(args, option);
    }
};

/**
 * @class InputParser
 * @brief Class for parsing and handling specific command line options.
 *
 * @extends InputParserBase
 *
 * The InputParser class extends the InputParserBase class to handle specific command line options.
 */
export class [[deprecated(INPUTPARSER_DEPRECATION_MESSAGE)]] InputParser final: private InputParserBase {
private:
    static inline const Vector<String> validOptions = {
        "-h", // Print help
        "-v", // Print version + credits
        "-c"  // Custom option
    }; ///< Vector of valid command line options.
public:
    /**
     * @brief Constructor that initialises the parser with command line arguments.
     *
     * @param argc Number of command line arguments.
     * @param argv Array of command line arguments.
     * @param envp Array of environment variable arguments.
     */
    explicit InputParser(Span<String> args, char* envp[] = nullptr):
        InputParserBase(args, envp, validOptions) {}

    /**
     * @brief Constructor that initialises the parser with command line arguments.
     *
     * @param argc Number of command line arguments.
     * @param argv Array of command line arguments.
     * @param envp Array of environment variable arguments.
     */
    explicit InputParser(Span<char*> args, char* envp[] = nullptr):
        InputParserBase(args, envp, validOptions) {}

    /**
     * @brief Constructor that initialises the parser with command line arguments.
     *
     * @param args Vector of command line arguments
     * @param envp Array of environment variable arguments.
     */
    explicit InputParser(const Vector<String>& args, char* envp[] = nullptr):
        InputParserBase(args, envp, validOptions) {}

    /**
     * @brief Handle the parsed command line inputs.
     *
     * @return An integer indicating the result of handling the inputs.
     */
    [[nodiscard]]
    GameExecuteMode handleInputs() const {
        if (optionExists("-h")) {
            openjuice::engine::util::misc::printHelp();
            return GameExecuteMode::HELP_MESSAGE;
        } else if (optionExists("-v")) {
            openjuice::engine::util::misc::printCredits();
            return GameExecuteMode::HELP_MESSAGE;
        }

        if (optionExists("-c")) {
            return GameExecuteMode::CLI_MODE;
        }

        return GameExecuteMode::TUI_MODE;
    }
};

END_MODULE_NAMESPACE();
