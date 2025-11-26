/**
 * @file Logger.cppm
 * @module openjuice.engine.util.Logging:Logger
 * @brief Implementation of the Logger class.
 *
 * This file contains the implementation of the Logger class, which is used to log debug messages to a file.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util.Logging:Logger;

export import :LogLevel;

import std;

import openjuice.engine.util.Misc;

using std::collections::Queue;
using std::io::IOException;
using std::io::OpenMode;
using std::io::OutputStream;
using std::io::OutputFileStream;
using std::io::Stderr;
using std::io::StringStream;
using std::fmt::FormatString;
using std::fs::Path;
using std::mem::SharedPointer;
using std::mem::UniquePointer;
using std::sync::Mutex;
using std::sync::ScopedLock; 
using std::time::SystemClock;

namespace io = std::io;
namespace fmt = std::fmt;
namespace fs = std::fs;
namespace mem = std::mem;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util::logging);

/**
 * @class Logger
 * @brief Class for logging debug messages.
 *
 * @extends OutputStream (std::ostream)
 *
 * The Logger class is a singleton class that logs debug messages to a file.
 */
export class Logger final: public OutputStream {
public:
    static constexpr StringView PATH_DEBUGFILE = "./userdata/debug.txt"; ///< The debug file path.
    static constexpr StringView USERDATA_DIR = "./userdata"; ///< The user data directory path.
private:
    UniquePointer<OutputFileStream> debugFile; ///< File stream for the debug log file.
    mutable Mutex logMutex; ///< Mutex for logger

    static String getCurrentTimeAsString() {
        return misc::getCurrentTimeAsString();
    }

    /**
     * @brief Private constructor to prevent instantiation.
     *
     * @throws IOException if it fails to open debug.txt
     */
    explicit Logger(StringView logFilePath = PATH_DEBUGFILE) throws(IOException):
        OutputStream(nullptr) {
        fs::create_directories(USERDATA_DIR);
        debugFile = mem::make_unique<OutputFileStream>(Path(logFilePath), OpenMode::APPEND);
        if (!debugFile->is_open()) {
            io::println(Stderr, "Failed to open debug.txt!");
            throw IOException("Failed to open debug.txt.");
        }
        this->rdbuf(debugFile->rdbuf());
        fs::create_directories("userdata");

        OutputFileStream file{Path(logFilePath), OpenMode::TRUNCATE};
        if (!file) {
            io::println(Stderr, "Error opening file for emptying.");
        } else {
            log("====================BEGIN DEBUG LOG====================");
            log("Current time: {}", getCurrentTimeAsString());
            log("=======================================================");
        }
    }

    /**
     * @brief Default destructor.
     */
    ~Logger() = default;
public:
    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    Logger(const Logger&) = delete;

    /**
     * @brief Deleted move constructor to prevent moving.
     */
    Logger(Logger&&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying.
     */
    Logger& operator=(const Logger&) = delete;

    /**
     * @brief Deleted move assignment operator to prevent moving.
     */
    Logger& operator=(Logger&&) = delete;

    /**
     * @brief Get the singleton instance of Logger.
     * @return The singleton instance.
     */
    [[nodiscard]]
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    /**
     * @brief Log a message to the debug file.
     *
     * @tparam Args Template parameter pack for format arguments
     * @param fmt Format string
     * @param args Arguments for the format string
     */
    template <typename... Args>
    void log(const FormatString<Args...>& fmt, Args&&... args) const {
        ScopedLock<Mutex> lock(logMutex);
        io::println(*debugFile, fmt, std::util::forward<Args>(args)...);
    }

    /**
     * @brief Log a message to the debug file.
     *
     * @tparam Args Template parameter pack for format arguments
     * @param type The type of the log message
     * @param fmt Format string
     * @param args Arguments for the format string
     */
    template <typename... Args>
    void log(LogLevel type, const FormatString<Args...>& fmt, Args&&... args) const {
        ScopedLock<Mutex> lock(logMutex);
        io::println(*debugFile, "[{}] {} {}", getCurrentTimeAsString(), type, fmt::format(fmt, std::util::forward<Args>(args)...));
    }
};

END_MODULE_NAMESPACE();
