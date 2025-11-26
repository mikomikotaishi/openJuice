#!/usr/bin/env dub
/+ dub.sdl:
name "quick-cmake-build"
description "A script to run CMake builds with a progress bar, warning and error extraction"
authors "mikomikotaishi (original Java version)"
license "MIT"
dependency "colorize" version="~>1.0.5"
dependency "commandr" version="~>0.2.0"
+/

/**
 * QuickCMakeBuild.d
 * A D script to run CMake builds with a progress bar, warning and error extraction.
 *
 * This script runs "cmake --build build" while displaying a progress bar.
 * It also extracts warnings and errors from the build output,
 * printing them above the progress bar.
 *
 * Usage:
 *   ./QuickCMakeBuild.d [options]
 *
 * Options:
 *   -h, --help           Show help message and exit
 *   -V, --version        Print version information and exit
 *   -c, --clean          Clean only project source files (no building)
 *   -ca, --clean-all     Clean entire project, including dependencies (no building)
 *   -n, --new            Clean the build directory and rebuilds everything, including dependencies
 *   -pd, --preserve-deps Clean the build directory and rebuilds everything (excluding dependencies)
 *   -rc, --reconfigure   Reconfigure CMake build system (for when new files are added)
 *   -g, --graph          Generate dependency graph
 *   -r, --release        Build in release mode (optimised, no sanitisers, NDEBUG defined)
 *   -s, --sanitiser      Enable sanitisers (address, undefined, thread, memory, leak)
 *   -v, --verbose        Enable verbose output (disables progress bar)
 */

import core.atomic;
import core.thread;

import std.algorithm;
import std.array;
import std.concurrency;
import std.conv;
import std.datetime;
import std.file;
import std.format;
import std.path;
import std.process;
import std.range;
import std.regex;
import std.stdio;
import std.string;
import std.typecons;

import colorize;
import commandr;

alias Pair(T, U) = Tuple!(T, "first", U, "second");

const string[] EXTENSIONS_TO_REMOVE = [".o", ".obj", ".a", ".so", ".dylib", ".dll", ".exe"];
const int DEFAULT_CONSOLE_WIDTH = 80;
const Regex ANSI_PATTERN = regex(r"\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])");
const Regex EXTRACT_FILENAME_PATTERN = regex(r"Building CXX object (.+\.cppm?)\.o");
const Regex CMAKE_PROGRESS_PATTERN = regex(r"\[(\d+)/(\d+)\]");
const Regex DETECT_WARNINGS_PATTERN = regex(r"([^:\s]+:\d+:\d+: warning: .+)");
const Regex DETECT_ERRORS_PATTERN = regex(r"([^:\s]+:\d+:\d+: error: .+)");
const Regex DETECT_BUILD_STOPPED_PATTERN = regex(r"ninja: build stopped: (.+)");
const string[] CMAKE_INIT_COMMAND = ["cmake", "-S", ".", "-G", "Ninja", "-B", "build"];
const string[] CMAKE_BUILD_COMMAND = ["cmake", "--build", "build"];
const string[] CMAKE_REGENERATE_COMMAND = ["cmake", "-G", "Ninja", "."];
const string[] CMAKE_RECONFIGURE_COMMAND = ["cmake", "-S", ".", "-B", "build"];
const string[] GENERATE_DEPENDENCIES_GRAPH_IMAGE_COMMAND = ["dot", "-Tpng", "graph.dot", "-o", "dependencies.png"];

/**
 * Main class for the QuickCMakeBuild script.
 */
class QuickCMakeBuild {
    // ANSI color codes
    static struct ANSI {
        static immutable string RESET = "\033[0m";
        static immutable string RED = "\033[31m";
        static immutable string GREEN = "\033[32m";
        static immutable string YELLOW = "\033[33m";
        static immutable string BLUE = "\033[34m";
        static immutable string CLEAR_LINE = "\033[K";
    }

    // Command line arguments
    bool clean = false;
    bool cleanAll = false;
    bool buildNew = false;
    bool preserveDeps = false;
    bool reconfigure = false;
    bool generateGraph = false;
    bool release = false;
    bool verbose = false;
    string[] sanitisers;

    /**
     * Gets the width of the console window in characters.
     * Returns: int representing the console width or 80 if not available.
     */
    static int getConsoleWidth() {
        try {
            import std.process : environment;
            
            version(Posix) {
                auto result = executeShell("tput cols");
                if (result.status == 0) {
                    return to!int(strip(result.output));
                }
            } else version(Windows) {
                auto result = executeShell("mode con | find \"Columns\"");
                if (result.status == 0) {
                    Captures match = matchFirst(result.output, r"Columns:\s*(\d+)");
                    if (!match.empty) {
                        return to!int(match[1]) + 20;
                    }
                }
            }

            string colsEnv = environment.get("COLUMNS");
            if (colsEnv !is null) {
                return to!int(colsEnv);
            }
        } catch (Exception e) {
            writeln("%sFailure%s to obtain console width, defaulting to %d%n", 
                ANSI.RED, ANSI.RESET, DEFAULT_CONSOLE_WIDTH
            );
        }
        return DEFAULT_CONSOLE_WIDTH;
    }

    /**
     * Calculates the visible length of a string (excluding ANSI escape sequences).
     * Returns: int representing the visible length.
     */
    static int visibleLength(string s) {
        return cast(int)replace(s, ansiRegex, "").length;
    }

    /**
     * Executes a shell command.
     * Params:
     *     command = list of command arguments.
     *     verbose = if true, prints the command output.
     *     captureOutput = if true, returns the command's output.
     * Returns: the output string if captured, otherwise null.
     * Throws: Exception if an I/O error occurs or if interrupted.
     */
    static string runCommand(string[] command, bool verbose, bool captureOutput) {
        try {
            if (verbose) {
                writeln("Running command: ", command.join(" "));
            }
                
            Config config = Config.none;
            if (!verbose && !captureOutput) {
                config |= Config.stderrPassThrough;
            }
                
            ProcessPipes pipes = pipeProcess(command, Redirect.all, null, config);
            
            if (captureOutput) {
                string output = pipes.stdout.byLine.map!(l => l.idup).join("\n");
                int status = wait(pipes.pid);
                return output;
            } else {
                int status = wait(pipes.pid);
                return null;
            }
        } catch (Exception e) {
            stderr.writeln("Command execution failed: ", e.msg);
            return null;
        }
    }

    /**
     * Recursively deletes the specified directory.
     */
    static void deleteDirectory(string path) {
        if (exists(path)) {
            if (isDir(path)) {
                try {
                    rmdirRecurse(path);
                } catch (Exception e) {
                    stderr.writeln("Error deleting directory: ", e.msg);
                }
            } else {
                try {
                    remove(path);
                } catch (Exception e) {
                    stderr.writeln("Error deleting file: ", e.msg);
                }
            }
        }
    }

    /**
     * Cleans the build directories ("build" and "src/build") if they exist.
     */
    void cleanBuildDirectory(bool preserveDeps) {
        writeln(format("%sCleaning%s build files...", ANSI.RED, ANSI.RESET));
        
        string buildDir = "build";
        string srcBuildDir = buildNormalizedPath("src", "build");
        
        if (!exists(buildDir) && !exists(srcBuildDir)) {
            writeln("No build directory found. Nothing to clean.");
            return;
        }
        
        try {
            if (preserveDeps && exists(buildDir)) {
                writeln(format("%sPreserving%s dependencies in build/_deps", ANSI.BLUE, ANSI.RESET));
                
                foreach (string path; dirEntries(buildDir, SpanMode.depth)) {
                    if (path.indexOf(buildNormalizedPath("build", "_deps")) != -1) {
                        continue;
                    }
                        
                    if (isFile(path)) {
                        foreach (ext; EXTENSIONS_TO_REMOVE) {
                            if (path.endsWith(ext)) {
                                try {
                                    remove(path);
                                    if (verbose) {
                                        writeln("Removed: ", path);
                                    }
                                } catch (Exception e) {
                                    stderr.writeln("Failed to delete: ", path);
                                }
                                break;
                            }
                        }
                    }
                }
                
                writeln(format("%sRegenerating%s build system files...", ANSI.GREEN, ANSI.RESET));
                Pid pid = spawnProcess(CMAKE_REGENERATE_COMMAND.dup, null, Config.none, buildDir);
                wait(pid);
                
                writeln(format("%sPreserved dependencies, only project files removed.%s", ANSI.GREEN, ANSI.RESET));
            } else {
                if (exists(buildDir)) {
                    deleteDirectory(buildDir);
                }
                if (exists(srcBuildDir)) {
                    deleteDirectory(srcBuildDir);
                }
                
                writeln(format("%sBuild directory fully cleaned.%s", ANSI.GREEN, ANSI.RESET));
            }
        } catch (Exception e) {
            stderr.writeln("Error cleaning build directory: ", e.msg);
            if (verbose) {
                stderr.writeln(e);
            }
        }
    }

    /**
     * Helper method to configure CMake command with sanitiser options
     */
    string[] configureSanitisers(string[] cmakeCommand) {
        bool addressSan = false;
        bool threadSan = false;
        bool memorySan = false;
        bool undefinedSan = false;
        bool leakSan = false;
        bool kernelSan = false;
        bool hardwareSan = false;

        if (release) {
            writeln(format("%sBuilding in%s Release mode (optimised)", ANSI.BLUE, ANSI.RESET));
            cmakeCommand ~= "-DCMAKE_BUILD_TYPE=Release";

            writeln(format("%sConfiguring%s for static linking (single executable)", ANSI.BLUE, ANSI.RESET));
            cmakeCommand ~= "-DBUILD_SHARED_LIBS=OFF";
            cmakeCommand ~= "-DCMAKE_EXE_LINKER_FLAGS=\"-static\"";
            
            writeln(format("%sConfiguring%s SDL3 for static linking", ANSI.BLUE, ANSI.RESET));
            cmakeCommand ~= "-DSDL_SHARED=OFF";
            cmakeCommand ~= "-DSDL_STATIC=ON";
            cmakeCommand ~= "-DSDL3_IMAGE_SHARED=OFF";
            cmakeCommand ~= "-DSDL3_IMAGE_STATIC=ON";
            cmakeCommand ~= "-DSDL3_MIXER_SHARED=OFF";
            cmakeCommand ~= "-DSDL3_MIXER_STATIC=ON";
            cmakeCommand ~= "-DSDL3_TTF_SHARED=OFF";
            cmakeCommand ~= "-DSDL3_TTF_STATIC=ON";
            cmakeCommand ~= "-DSDL3_NET_SHARED=OFF";
            cmakeCommand ~= "-DSDL3_NET_STATIC=ON";
            
            if (sanitisers.length > 0) {
                writeln(format("%sNote:%s Sanitisers disabled in Release mode", ANSI.YELLOW, ANSI.RESET));
                sanitisers = [];
            }
        }

        if (sanitisers.length > 0) {
            cmakeCommand ~= "-DENABLE_SANITIZERS=ON";
            
            foreach (string sanitiser; sanitisers) {
                switch (sanitiser.toLower()) {
                    case "address":
                        if (threadSan || memorySan) {
                            writeln(format("%sError:%s AddressSanitizer (ASan) cannot be used with ThreadSanitizer (TSan) or MemorySanitizer (MSan).", ANSI.RED, ANSI.RESET));
                            return cmakeCommand;
                        }
                        writeln(format("%sEnabling%s AddressSanitizer", ANSI.BLUE, ANSI.RESET));
                        addressSan = true;
                        break;
            
                    case "kernel-address":
                        writeln(format("%sEnabling%s Kernel AddressSanitizer (KASan)", ANSI.BLUE, ANSI.RESET));
                        kernelSan = true;
                        break;
            
                    case "hw-address":
                        writeln(format("%sEnabling%s Hardware AddressSanitizer (HWASan)", ANSI.BLUE, ANSI.RESET));
                        hardwareSan = true;
                        break;
            
                    case "undefined":
                        writeln(format("%sEnabling%s UndefinedBehaviorSanitizer (UBSan)", ANSI.BLUE, ANSI.RESET));
                        undefinedSan = true;
                        break;
            
                    case "thread":
                        if (addressSan || memorySan) {
                            writeln(format("%sError:%s ThreadSanitizer (TSan) cannot be used with AddressSanitizer (ASan) or MemorySanitizer (MSan).", ANSI.RED, ANSI.RESET));
                            return cmakeCommand;
                        }
                        writeln(format("%sEnabling%s ThreadSanitizer", ANSI.BLUE, ANSI.RESET));
                        threadSan = true;
                        break;
            
                    case "memory":
                        if (addressSan || threadSan) {
                            writeln(format("%sError:%s MemorySanitizer (MSan) cannot be used with AddressSanitizer (ASan) or ThreadSanitizer (TSan).", ANSI.RED, ANSI.RESET));
                            return cmakeCommand;
                        }
                        writeln(format("%sEnabling%s MemorySanitizer", ANSI.BLUE, ANSI.RESET));
                        memorySan = true;
                        break;
            
                    case "leak":
                        writeln(format("%sEnabling%s LeakSanitizer (LSan)", ANSI.BLUE, ANSI.RESET));
                        leakSan = true;
                        break;
            
                    case "all":
                        writeln(format("%sEnabling%s all compatible sanitisers", ANSI.YELLOW, ANSI.RESET));
                        addressSan = true;
                        undefinedSan = true;
                        leakSan = true;
                        break;
            
                    case "all-kernel":
                        writeln(format("%sEnabling%s all sanitisers (Kernel AddressSanitizer)", ANSI.YELLOW, ANSI.RESET));
                        kernelSan = true;
                        undefinedSan = true;
                        memorySan = true;
                        leakSan = true;
                        break;
            
                    case "all-hardware":
                        writeln(format("%sEnabling%s all sanitisers (Hardware AddressSanitizer)", ANSI.YELLOW, ANSI.RESET));
                        hardwareSan = true;
                        undefinedSan = true;
                        memorySan = true;
                        leakSan = true;
                        break;
            
                    default:
                        writeln(format("%sWarning:%s Invalid sanitiser specified: %s", 
                            ANSI.YELLOW, ANSI.RESET, sanitiser)
                        );
                }
            }            
            
            if (addressSan) {
                cmakeCommand ~= "-DUSE_SANITIZER_ADDRESS=ON";
                cmakeCommand ~= "-DUSE_SANITIZER_LEAK=ON"; 
            }
            if (kernelSan) {
                cmakeCommand ~= "-DUSE_SANITIZER_KERNEL=ON";
            }
            if (hardwareSan) {
                cmakeCommand ~= "-DUSE_SANITIZER_HW=ON";
            }
            if (undefinedSan) {
                cmakeCommand ~= "-DUSE_SANITIZER_UNDEFINED=ON";
            }
            if (threadSan) {
                cmakeCommand ~= "-DUSE_SANITIZER_THREAD=ON";
            }
            if (memorySan) {
                cmakeCommand ~= "-DUSE_SANITIZER_MEMORY=ON";
            }
            if (leakSan && !addressSan) {
                cmakeCommand ~= "-DUSE_SANITIZER_LEAK=ON";
            }
        }
        
        return cmakeCommand;
    }

    /**
     * Runs CMake initialisation ("cmake -S . -G Ninja -B build").
     * This method sets up the initial build system configuration, handling 
     * sanitiser options and build type settings.
     */
    void runCMakeInit() {
        if (verbose) {
            runCommand(CMAKE_INIT_COMMAND.dup, true, false);
            return;
        }

        string[] cmakeCommand = CMAKE_INIT_COMMAND.dup;
        cmakeCommand = configureSanitisers(cmakeCommand);
        
        writeln(format("%sInitialising%s openJuice build", ANSI.GREEN, ANSI.RESET));
        
        ProcessPipes pipes = pipeProcess(cmakeCommand, Redirect.all);
        
        bool inDownload = false;
        int lastDownloadPercent = -1;
        string cloningRepo = null;
        string downloadingLibrary = null;
        
        Tid stderrTid = spawn((Tid parentTid) {
            try {
                foreach (line; pipes.stderr.byLine) {
                    string lineStr = line.idup.strip();
                    Captures cloneMatcher = matchFirst(lineStr, "Cloning into ['\\\"](.*?)['\\\"]");
                    if (!cloneMatcher.empty) {
                        string repoName = cloneMatcher[1].replace("-src", "");
                        writeln(format("%sCloning%s %s dependency...", ANSI.BLUE, ANSI.RESET, repoName));
                    }
                }
            } catch (Exception e) {

            }
        }, thisTid);
        
        foreach (line; pipes.stdout.byLine) {
            string lineStr = line.idup.strip();
            
            if (lineStr.indexOf("compiler identification is") != -1) {
                writeln("Detecting ", lineStr);
            }
            
            Captures downloadMatcher = matchFirst(lineStr, r"\[download (\d+)% complete\]");
            if (!downloadMatcher.empty) {
                int percent = to!int(downloadMatcher[1]);
                if (!inDownload) {
                    writeln(format("%sDownloading%s library...", ANSI.BLUE, ANSI.RESET));
                    inDownload = true;
                }
                
                if (percent != lastDownloadPercent) {
                    lastDownloadPercent = percent;
                    int barLength = 20;
                    int filled = cast(int)(barLength * (percent / 100.0));
                    
                    string bar = replicate("=", filled) ~ 
                                (filled < barLength ? ">" : "") ~ 
                                replicate(" ", barLength - filled - (filled < barLength ? 1 : 0));
                                
                    write(format("\r%s[%s] %d%%%s", ANSI.CLEAR_LINE, bar, percent, ANSI.RESET));
                    stdout.flush();
                }
                
                if (percent == 100) {
                    writeln();
                    inDownload = false;
                    downloadingLibrary = "pending";
                }
            }
            
            if (downloadingLibrary == "pending") {
                if (lineStr.indexOf("Using the multi-header code from") != -1) {
                    Captures libMatcher = matchFirst(lineStr, r"_deps/([^/]+)-src");
                    if (!libMatcher.empty) {
                        string libraryName = libMatcher[1];
                        writeln(format("%sDownloaded%s %s library", ANSI.GREEN, ANSI.RESET, libraryName));
                        downloadingLibrary = null;
                    }
                }
            }
            
            Captures cloneMatcher = matchFirst(lineStr, "Cloning into ['\\\"](.*?)['\\\"]");
            if (!cloneMatcher.empty) {
                string repoName = cloneMatcher[1].replace("-src", "");
                cloningRepo = repoName;
                writeln(format("%sCloning%s %s dependency...", ANSI.BLUE, ANSI.RESET, repoName));
            }
            
            if (lineStr.startsWith("HEAD is now at") && cloningRepo !is null) {
                writeln(format("%sFinished%s cloning %s", ANSI.GREEN, ANSI.RESET, cloningRepo));
                cloningRepo = null;
            }
            
            if (lineStr.startsWith("-- Configuring done")) {
                writeln(format("%sFinalising%s build configuration...", ANSI.BLUE, ANSI.RESET));
            }
            
            if (lineStr.startsWith("-- Build files have been written")) {
                writeln(format("%sBuild system%s configured successfully", ANSI.GREEN, ANSI.RESET));
            }
        }
        
        int status = wait(pipes.pid);
        
        if (status != 0) {
            throw new Exception("CMake initialisation failed with exit code " ~ to!string(status));
        }
    }

    /**
     * Reconfigures the CMake build system without cleaning.
     * Use this when new files are added to the project to update the build system
     * without requiring a full rebuild of existing files.
     */
    void runCMakeReconfigure() {
        writeln(format("%sReconfiguring%s build system for new files...", ANSI.BLUE, ANSI.RESET));
        
        string[] cmakeCommand = CMAKE_RECONFIGURE_COMMAND.dup;
        cmakeCommand = configureSanitisers(cmakeCommand);
        
        ProcessPipes pipes = pipeProcess(cmakeCommand, Redirect.stdout | Redirect.stderr);
        
        foreach (line; pipes.stdout.byLine) {
            string lineStr = line.idup;
            if (verbose) {
                writeln(lineStr);
            } else if (lineStr.startsWith("-- Configuring done") || 
                        lineStr.startsWith("-- Generating done") || 
                        lineStr.startsWith("-- Build files have been written")) {
                writeln(format("%s%s%s", ANSI.GREEN, lineStr, ANSI.RESET));
            }
        }
        
        int status = wait(pipes.pid);
        
        if (status != 0) {
            throw new Exception("CMake reconfiguration failed with exit code " ~ to!string(status));
        }
        
        writeln(format("%sBuild system reconfigured successfully!%s", ANSI.GREEN, ANSI.RESET));
    }

    /**
     * Parses a line for progress in the format [current/total].
     */
    static Nullable!(Pair!(int, int)) parseCMakeProgress(string line) {
        Nullable!(Pair!(int, int)) result;
        Captures m = matchFirst(line, CMAKE_PROGRESS_PATTERN);
        if (!m.empty) {
            int current = to!int(m[1]);
            int total = to!int(m[2]);
            result = Pair!(int, int)(current, total);
        }
        return result;
    }

    /**
     * Extracts the filename from a compilation command line.
     */
    static string extractFilename(string line) {
        Captures m = matchFirst(line, EXTRACT_FILENAME_PATTERN);
        if (!m.empty) {
            return m[1].strip();
        }
        return null;
    }

    /**
     * Detects warnings in a line.
     */
    static string detectWarnings(string line) {
        Captures m = matchFirst(line, DETECT_WARNINGS_PATTERN);
        if (!m.empty) {
            return m[1];
        }
        return null;
    }

    /**
     * Detects errors in a line.
     */
    static string detectErrors(string line) {
        Captures m = matchFirst(line, DETECT_ERRORS_PATTERN);
        if (!m.empty) {
            return m[1];
        }
        return null;
    }

    /**
     * Detects "build stopped" messages in a line.
     */
    static string detectBuildStopped(string line) {
        Captures m = matchFirst(line, DETECT_BUILD_STOPPED_PATTERN);
        if (!m.empty) {
            return m[0];
        }
        return null;
    }

    /**
     * Updates the progress bar display.
     */
    static void updateProgressBar(string bar, int percentage, int current, int total, string file) {
        int width = to!string(total).length;
        string progressStr = format("[%s] %d%% [%*d/%*d] %sCompiling:%s %s", 
            bar, percentage, width, current, width, total > 0 ? total : 1, 
            ANSI.GREEN, ANSI.RESET, file !is null ? file : ""
        );
        
        string outputString = "\r" ~ ANSI.CLEAR_LINE ~ progressStr;
        
        if (visibleLength(outputString) > getConsoleWidth() - 1) {
            int visibleLimit = getConsoleWidth() - 1;
            string result = "";
            int visibleCount = 0;
            
            for (int i = 0; i < outputString.length; ++i) {
                if (outputString[i] == '\033') {
                    int j = i;
                    while (j < outputString.length && outputString[j] != 'm') j++;
                    if (j < outputString.length) {
                        result ~= outputString[i..j+1];
                        i = j;
                    }
                } else {
                    result ~= outputString[i];
                    visibleCount++;
                    if (visibleCount >= visibleLimit) break;
                }
            }
            outputString = result;
        }
        
        write(outputString);
        stdout.flush();
    }

    /**
     * Runs CMake build ("cmake --build build") while displaying a progress bar.
     * The progress bar shows the percentage, file count ([current/total]) with space padding, and the current file.
     * Warnings and errors are printed above the progress bar.
     */
    void runCMakeBuild() {
        if (verbose) {
            runCommand(CMAKE_BUILD_COMMAND.dup, true, false);
            return;
        }
        writeln(format("%sBuilding%s openJuice...", ANSI.GREEN, ANSI.RESET));

        ProcessPipes pipes = pipeProcess(CMAKE_BUILD_COMMAND.dup, Redirect.all);

        string firstLine;
        foreach (line; pipes.stdout.byLineCopy()) {
            firstLine = line.idup;
            break;
        }

        if (firstLine !is null && firstLine.indexOf("ninja: no work to do") != -1) {
            writeln(format("%sEverything up to date!%s No compilation needed.", ANSI.GREEN, ANSI.RESET));
            wait(pipes.pid);
            return;
        }

        immutable int barLength = 40;
        shared string bar = ">" ~ replicate(" ", barLength - 1);
        shared int lastPercentage = 0;
        shared int currentStep = 0;
        shared int totalSteps = 0;
        shared string currentFile = null;
        string[] errorFiles;
        
        if (firstLine !is null) {
            firstLine = firstLine.strip();
            auto progress = parseCMakeProgress(firstLine);
            if (!progress.isNull) {
                currentStep = progress.get.first;
                totalSteps = progress.get.second;
                int percentage = cast(int)((cast(double)currentStep / totalSteps) * 100);
                lastPercentage = percentage;
                int filled = cast(int)(barLength * (percentage / 100.0));
                
                bar = replicate("=", filled) ~ 
                    (filled < barLength ? ">" : "") ~ 
                    replicate(" ", barLength - filled - (filled < barLength ? 1 : 0));
            }
            
            string newFile = extractFilename(firstLine);
            if (newFile !is null) {
                currentFile = newFile;
            }
        }

        Tid stderrTid = spawn((Tid parentTid) {
            try {
                foreach (line; pipes.stderr.byLine) {
                    string lineStr = line.idup.strip();
                    string errorMsg = detectErrors(lineStr);
                    if (errorMsg !is null) {
                        string errorFile = errorMsg.split(":")[0];
                        if (!errorFiles.canFind(errorFile)) {
                            writeln();
                            errorFiles ~= errorFile;
                        }
                        writeln(format("\r%s%sError:%s %s", ANSI.CLEAR_LINE, ANSI.RED, ANSI.RESET, errorMsg));
                        
                        updateProgressBar(bar, lastPercentage, currentStep, totalSteps, currentFile);
                    }
                    
                    string buildStopped = detectBuildStopped(lineStr);
                    if (buildStopped !is null) {
                        writeln(format("\r%s%sBuild stopped:%s %s", ANSI.CLEAR_LINE, ANSI.RED, ANSI.RESET, buildStopped));
                        updateProgressBar(bar, lastPercentage, currentStep, totalSteps, currentFile);
                    }
                }
            } catch (Exception e) {

            }
        }, thisTid);
        
        updateProgressBar(bar, lastPercentage, currentStep, totalSteps, currentFile);

        foreach (line; pipes.stdout.byLine) {
            string lineStr = line.idup.strip();
            
            string warningMsg = detectWarnings(lineStr);
            if (warningMsg !is null) {
                writeln(format("\r%s%sWarning:%s %s (enable verbose for details)", ANSI.CLEAR_LINE, ANSI.YELLOW, ANSI.RESET, warningMsg));
                updateProgressBar(bar, lastPercentage, currentStep, totalSteps, currentFile);
            }
            
            string errorMsg = detectErrors(lineStr);
            if (errorMsg !is null) {
                string errorFile = errorMsg.split(":")[0];
                if (!errorFiles.canFind(errorFile)) {
                    writeln();
                    errorFiles ~= errorFile;
                }
                writeln(format("\r%s%sError:%s %s", ANSI.CLEAR_LINE, ANSI.RED, ANSI.RESET, errorMsg));
                updateProgressBar(bar, lastPercentage, currentStep, totalSteps, currentFile);
            }

            auto progress = parseCMakeProgress(lineStr);
            if (!progress.isNull) {
                currentStep = progress.get.first;
                totalSteps = progress.get.second;
                int percentage = cast(int)((cast(double)currentStep / totalSteps) * 100);
                if (percentage > lastPercentage) {
                    lastPercentage = percentage;
                    int filled = cast(int)(barLength * (percentage / 100.0));
                    
                    bar = replicate("=", filled) ~ 
                        (filled < barLength ? ">" : "") ~ 
                        replicate(" ", barLength - filled - (filled < barLength ? 1 : 0));

                    updateProgressBar(bar, lastPercentage, currentStep, totalSteps, currentFile);
                }
            }

            string newFile = extractFilename(lineStr);
            if (newFile !is null) {
                currentFile = newFile;
                updateProgressBar(bar, lastPercentage, currentStep, totalSteps, currentFile);
            }
            
            string buildStopped = detectBuildStopped(lineStr);
            if (buildStopped !is null) {
                writeln(format("\r%s%sBuild stopped:%s %s", ANSI.CLEAR_LINE, ANSI.RED, ANSI.RESET, buildStopped));
                updateProgressBar(bar, lastPercentage, currentStep, totalSteps, currentFile);
            }
        }

        int status = wait(pipes.pid);
        
        if (status != 0) {
            writeln(format("\r%s%sBuild failed!%s Check the errors above or run with --verbose for details.", ANSI.CLEAR_LINE, ANSI.RED, ANSI.RESET));
            throw new Exception("Build failed with exit code " ~ to!string(status));
        } else {
            writeln();
        }
    }

    int run(string[] args) {
        StopWatch sw;
        sw.start();
        
        try {
            args = args[1..$];
            
            Program program = new Program("QuickCMakeBuild", "Build script for openJuice project")
                .add(new Flag("h", "help", "Show help message and exit").optional)
                .add(new Flag("V", "version", "Print version information and exit").optional)
                .add(new Flag("c", "clean", "Clean only project source files (no building)").optional)
                .add(new Flag("ca", "clean-all", "Clean entire project, including dependencies (no building)").optional)
                .add(new Flag("n", "new", "Clean the build directory and rebuilds everything, including dependencies").optional)
                .add(new Flag("pd", "preserve-deps", "Clean the build directory and rebuilds everything (excluding dependencies)").optional)
                .add(new Flag("rc", "reconfigure", "Reconfigure CMake build system (for when new files are added)").optional)
                .add(new Flag("g", "graph", "Generate dependency graph").optional)
                .add(new Flag("r", "release", "Build in release mode (optimised, no sanitisers, NDEBUG defined)").optional)
                .add(new Flag("v", "verbose", "Enable verbose output (disables progress bar)").optional)
                .add(new ListArgument("s", "sanitiser", "Enable sanitisers").optional);
                
            auto parsedArgs = program.parseArgs(args);

            if (parsedArgs.hasFlag("help") || parsedArgs.hasFlag("h")) {
                program.printHelp();
                return 0;
            }
            
            if (parsedArgs.hasFlag("version") || parsedArgs.hasFlag("V")) {
                writeln("QuickCMakeBuild 0.0.1");
                return 0;
            }
            
            clean = parsedArgs.hasFlag("clean") || parsedArgs.hasFlag("c");
            cleanAll = parsedArgs.hasFlag("clean-all") || parsedArgs.hasFlag("ca");
            buildNew = parsedArgs.hasFlag("new") || parsedArgs.hasFlag("n");
            preserveDeps = parsedArgs.hasFlag("preserve-deps") || parsedArgs.hasFlag("pd");
            reconfigure = parsedArgs.hasFlag("reconfigure") || parsedArgs.hasFlag("rc");
            generateGraph = parsedArgs.hasFlag("graph") || parsedArgs.hasFlag("g");
            release = parsedArgs.hasFlag("release") || parsedArgs.hasFlag("r");
            verbose = parsedArgs.hasFlag("verbose") || parsedArgs.hasFlag("v");
            
            if (parsedArgs.hasArgument("sanitiser") || parsedArgs.hasArgument("s"))
                sanitisers = parsedArgs.getList("sanitiser");
            
            if (cleanAll) {
                cleanBuildDirectory(false);
                return 0;
            } else if (clean) {
                cleanBuildDirectory(true);
                return 0;
            } else if (buildNew) {
                cleanBuildDirectory(false);
                runCMakeInit();
            } else if (preserveDeps) {
                cleanBuildDirectory(true);
                runCMakeInit();
            } else if (reconfigure) {
                runCMakeReconfigure();
            }
            
            if (!cleanAll && !clean) {
                runCMakeBuild();
            }
            
            if (generateGraph) {
                writeln(format("%sGenerating%s dependency graph (output: graph.dot, dependencies.png)", ANSI.GREEN, ANSI.RESET));
                runCommand(["mgt"], verbose, false);
                runCommand(GENERATE_DEPENDENCIES_GRAPH_IMAGE_COMMAND.dup, verbose, false);
            }
            
            sw.stop();
            float elapsedTime = sw.peek().total!"msecs" / 1000.0;
            writeln(format("%sBuild complete!%s Time taken: %.3f seconds", ANSI.GREEN, ANSI.RESET, elapsedTime));
            
            return 0;
        } catch (Exception e) {
            if (verbose)
                stderr.writeln(e);
            return 1;
        }
    }
}

/**
 * Main function - creates a QuickCMakeBuild instance and runs it.
 *
 * Params:
 *     args = Command line arguments.
 * Returns: Exit code (0 for success, non-zero for failure).
 */
int main(string[] args) {
    QuickCMakeBuild quickCMakeBuild = new QuickCMakeBuild();
    return quickCMakeBuild.run(args);
}
