#!/usr/bin/env python3

"""
@file quick_cmake_build.py
@brief A Python script to run CMake builds with a progress bar and warning extraction.

This script runs `cmake --build build` while displaying a progress bar. It captures warnings and prints them above the progress bar.

@author mikomikotaishi
"""

import os
import re
import shutil
import subprocess
import sys
import time

from argparse import _MutuallyExclusiveGroup as MutuallyExclusiveGroup, ArgumentParser, Namespace
from re import Match, Pattern
from subprocess import CalledProcessError, CompletedProcess, Popen
from threading import Thread

DEFAULT_CONSOLE_WIDTH: int = 80
EXTENSIONS_TO_REMOVE: set[str] = {".o", ".obj", ".a", ".so", ".dylib", ".dll", ".exe"}
CMAKE_INIT_COMMAND: list[str] = ["cmake", "-S", ".", "-G", "Ninja", "-B", "build"]
CMAKE_BUILD_COMMAND: list[str] = ["cmake", "--build", "build"]
CMAKE_REGENERATE_COMMAND: list[str] = ["cmake", "-G", "Ninja", "."]
CMAKE_RECONFIGURE_COMMAND: list[str] = ["cmake", "-S", ".", "-B", "build"]
ANSI_PATTERN: Pattern = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')
GENERATE_DEPENDENCIES_GRAPH_IMAGE_COMMAND: list[str] = ["dot", "-Tpng", "graph.dot", "-o", "dependencies.png"]

class ANSI:
    """
    @enum ANSI
    
    @brief ANSI escape codes for terminal text styling.
    """
    RESET: str = "\033[0m"
    RED: str = "\033[31m"
    GREEN: str = "\033[32m"
    YELLOW: str = "\033[33m"
    BLUE: str = "\033[34m"
    CLEAR_LINE: str = "\033[K"

def console_width() -> int:
    """
    @brief Gets the width of the current console window in characters.

    @return The number of characters that fit on the console width
    """
    try:
        return shutil.get_terminal_size().columns
    except (AttributeError, OSError):
        return DEFAULT_CONSOLE_WIDTH

def visible_length(s: str) -> int:
    """
    @brief Calculates the visible length of a string (excluding ANSI escape sequences).

    @param s (str): The string to calculate the visible length of.
    @return int: The visible length of the string.
    """
    return len(ANSI_PATTERN.sub('', s))

def run_command(command: list[str], verbose: bool, capture_output: bool = False) -> str | None:
    """
    @brief Executes a shell command.

    @param command (list[str]): The command to be executed as a list of arguments.
    @param verbose (bool): If True, print the command output; otherwise, suppress it.
    @param capture_output (bool): If True, captures and returns the command's output.
    @return str | None: Captured output if `capture_output` is True, otherwise None.

    @throws CalledProcessError: If the command returns a non-zero exit code.
    """
    if verbose:
        print(f"Running command: {' '.join(command)}")
        result: CompletedProcess[str] = subprocess.run(command, check = True, text = True)
    else:
        if capture_output:
            result: CompletedProcess[str] = subprocess.run(
                command, check = True, text = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE
            )
            return result.stdout
        else:
            subprocess.run(command, check = True, stdout = subprocess.DEVNULL, stderr = subprocess.DEVNULL)
    return None

def clean_build_directory(preserve_deps: bool = False) -> None:
    """
    @brief Removes the 'build' directory while optionally preserving dependencies.

    @param preserve_deps: If True, preserves dependencies and removes only project build files.
    """
    print(f"{ANSI.RED}Cleaning{ANSI.RESET} build files...")

    if not os.path.exists("build") and not os.path.exists("src/build"):
        print("No build directory found. Nothing to clean.")
        return

    if preserve_deps:
        print(f"{ANSI.BLUE}Preserving{ANSI.RESET} dependencies in build/_deps")

        for root, _, files in os.walk("build"):
            if "build/_deps" in root:
                continue
            for file in files:
                if file.endswith(tuple(EXTENSIONS_TO_REMOVE)):
                    os.remove(os.path.join(root, file))

        print(f"{ANSI.GREEN}Regenerating{ANSI.RESET} build system files...")
        subprocess.run(
            CMAKE_REGENERATE_COMMAND,
            cwd = "build",
            stdout = subprocess.DEVNULL,
            stderr = subprocess.DEVNULL
        )

        print(f"{ANSI.GREEN}Preserved dependencies, only project files removed.{ANSI.RESET}")

    else:
        shutil.rmtree("build", ignore_errors = True)
        shutil.rmtree("src/build", ignore_errors = True)
        print(f"{ANSI.GREEN}Build directory fully cleaned.{ANSI.RESET}")

def configure_sanitizers(cmake_command: list[str], release: bool, sanitizers: list[str]) -> list[str]:
    """
    @brief Helper function to configure CMake command with sanitizer options.
    
    @param cmake_command (list[str]): The base CMake command list to modify.
    @param release (bool): If True, build for release. Otherwise, debug build.
    @param sanitizers (list[str]): List of sanitizers to enable.
    @return list[str]: The updated CMake command with sanitizer options.
    """
    address_san: bool = False
    thread_san: bool = False
    memory_san: bool = False
    undefined_san: bool = False
    leak_san: bool = False
    kernel_san: bool = False
    hardware_san: bool = False

    if release:
        print(f"{ANSI.BLUE}Building in{ANSI.RESET} Release mode (optimized)")
        cmake_command.append("-DCMAKE_BUILD_TYPE=Release")

        print(f"{ANSI.BLUE}Configuring{ANSI.RESET} for static linking (single executable)")
        cmake_command.append("-DBUILD_SHARED_LIBS=OFF")
        cmake_command.append("-DCMAKE_EXE_LINKER_FLAGS=\"-static\"")
        
        print(f"{ANSI.BLUE}Configuring{ANSI.RESET} SDL3 for static linking")
        cmake_command.append("-DSDL_SHARED=OFF")
        cmake_command.append("-DSDL_STATIC=ON")
        cmake_command.append("-DSDL3_IMAGE_SHARED=OFF")
        cmake_command.append("-DSDL3_IMAGE_STATIC=ON")
        cmake_command.append("-DSDL3_MIXER_SHARED=OFF")
        cmake_command.append("-DSDL3_MIXER_STATIC=ON")
        cmake_command.append("-DSDL3_TTF_SHARED=OFF")
        cmake_command.append("-DSDL3_TTF_STATIC=ON")
        cmake_command.append("-DSDL3_NET_SHARED=OFF")
        cmake_command.append("-DSDL3_NET_STATIC=ON")
        
        if sanitizers:
            print(f"{ANSI.YELLOW}Note:{ANSI.RESET} Sanitizers disabled in Release mode")
            sanitizers = []

    if sanitizers:
        cmake_command.append("-DENABLE_SANITIZERS=ON")

        for sanitizer in sanitizers:
            sanitizer = sanitizer.lower()

            match sanitizer:
                case "address":
                    if thread_san or memory_san:
                        print(f"{ANSI.RED}Error:{ANSI.RESET} AddressSanitizer (ASan) cannot be used with ThreadSanitizer (TSan) or MemorySanitizer (MSan).")
                        return cmake_command
                    print(f"{ANSI.BLUE}Enabling{ANSI.RESET} AddressSanitizer")
                    address_san = True

                case "kernel-address":
                    print(f"{ANSI.BLUE}Enabling{ANSI.RESET} Kernel AddressSanitizer (KASan)")
                    kernel_san = True

                case "hw-address":
                    print(f"{ANSI.BLUE}Enabling{ANSI.RESET} Hardware AddressSanitizer (HWASan)")
                    hardware_san = True

                case "undefined":
                    print(f"{ANSI.BLUE}Enabling{ANSI.RESET} UndefinedBehaviorSanitizer (UBSan)")
                    undefined_san = True

                case "thread":
                    if address_san or memory_san:
                        print(f"{ANSI.RED}Error:{ANSI.RESET} ThreadSanitizer (TSan) cannot be used with AddressSanitizer (ASan) or MemorySanitizer (MSan).")
                        return cmake_command
                    print(f"{ANSI.BLUE}Enabling{ANSI.RESET} ThreadSanitizer (TSan)")
                    thread_san = True

                case "memory":
                    if address_san or thread_san:
                        print(f"{ANSI.RED}Error:{ANSI.RESET} MemorySanitizer (MSan) cannot be used with AddressSanitizer (ASan) or ThreadSanitizer (TSan).")
                        return cmake_command
                    print(f"{ANSI.BLUE}Enabling{ANSI.RESET} MemorySanitizer (MSan)")
                    memory_san = True

                case "leak":
                    print(f"{ANSI.BLUE}Enabling{ANSI.RESET} LeakSanitizer (LSan)")
                    leak_san = True

                case "all":
                    print(f"{ANSI.YELLOW}Enabling{ANSI.RESET} all compatible sanitizers")
                    address_san = True
                    undefined_san = True
                    leak_san = True

                case "all-kernel":
                    print(f"{ANSI.YELLOW}Enabling{ANSI.RESET} all sanitizers (Kernel AddressSanitizer)")
                    kernel_san = True
                    undefined_san = True
                    memory_san = True
                    leak_san = True

                case "all-hardware":
                    print(f"{ANSI.YELLOW}Enabling{ANSI.RESET} all sanitizers (Hardware AddressSanitizer)")
                    hardware_san = True
                    undefined_san = True
                    memory_san = True
                    leak_san = True

                case _:
                    print(f"{ANSI.YELLOW}Warning:{ANSI.RESET} Invalid sanitizer specified: {sanitizer}")

        if address_san:
            cmake_command.append("-DUSE_SANITIZER_ADDRESS=ON")
            cmake_command.append("-DUSE_SANITIZER_LEAK=ON")
        if kernel_san:
            cmake_command.append("-DUSE_SANITIZER_KERNEL=ON")
        if hardware_san:
            cmake_command.append("-DUSE_SANITIZER_HW=ON")
        if undefined_san:
            cmake_command.append("-DUSE_SANITIZER_UNDEFINED=ON")
        if thread_san:
            cmake_command.append("-DUSE_SANITIZER_THREAD=ON")
        if memory_san:
            cmake_command.append("-DUSE_SANITIZER_MEMORY=ON")
        if leak_san and not address_san:
            cmake_command.append("-DUSE_SANITIZER_LEAK=ON")

    return cmake_command

def run_cmake_init(verbose: bool, release: bool, sanitizers: list[str] = None) -> None:
    """
    @brief Runs the CMake initialization process with detailed progress reporting.

    @param verbose (bool): If True, prints all output. Otherwise, shows progress indicators.
    @param release (bool): If True, sets CMake to build for release. Otherwise, builds a debug build.
    @param sanitizers (list[str]): List of sanitizers to enable.

    @throws CalledProcessError
    """
    if sanitizers is None:
        sanitizers = []

    cmake_command: list[str] = configure_sanitizers(CMAKE_INIT_COMMAND, release, sanitizers)

    if verbose:
        run_command(cmake_command, verbose = True)
        return

    print(f"{ANSI.GREEN}Initialising{ANSI.RESET} openJuice build...")

    process: Popen = Popen(
        cmake_command,
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        text = True
    )

    in_download: bool = False
    last_download_percent: int = -1
    cloning_repo: str | None = None
    downloading_library: str | None = None

    def process_stderr() -> None:
        for line in process.stderr:
            line = line.strip()
            clone_match: Match | None = re.search(r"Cloning into ['\"](.*?)['\"]", line)
            if clone_match:
                repo_name = clone_match.group(1).replace("-src", "")
                print(f"{ANSI.BLUE}Cloning{ANSI.RESET} {repo_name} dependency...")
            build_stopped = detect_build_stopped(line)
            if build_stopped:
                print(f"\r{ANSI.CLEAR_LINE}{ANSI.RED}Build stopped:{ANSI.RESET} {build_stopped}")

    stderr_thread: Thread = Thread(target = process_stderr, daemon = True)
    stderr_thread.start()

    try:
        for line in process.stdout:
            line = line.strip()

            if "compiler identification is" in line:
                print(f"Detecting {line}")

            download_match: Match | None = re.search(r"\[download (\d+)% complete]", line)
            if download_match:
                percent = int(download_match.group(1))
                if not in_download:
                    print(f"{ANSI.BLUE}Downloading{ANSI.RESET} library...")
                    in_download = True

                if percent != last_download_percent:
                    last_download_percent = percent
                    bar_length = 20
                    filled = int(bar_length * (percent / 100))
                    
                    bar = "=" * filled + (">" if filled < bar_length else "") + " " * (bar_length - filled - (1 if filled < bar_length else 0))
                    
                    print(f"\r{ANSI.CLEAR_LINE}[{bar}] {percent}%{ANSI.RESET}", end="", flush=True)

                if percent == 100:
                    print()
                    in_download = False
                    downloading_library = "pending"

            if downloading_library == "pending":
                if "Using the multi-header code from" in line:
                    lib_match: Match | None = re.search(r"_deps/([^/]+)-src", line)
                    if lib_match:
                        library_name = lib_match.group(1)
                        print(f"{ANSI.GREEN}Downloaded{ANSI.RESET} {library_name} library")
                        downloading_library = None

            clone_match: Match | None = re.search(r"Cloning into ['\"](.*?)['\"]", line)
            if clone_match:
                repo_name = clone_match.group(1).replace("-src", "")
                cloning_repo = repo_name
                print(f"{ANSI.BLUE}Cloning{ANSI.RESET} {repo_name} dependency...")

            if line.startswith("HEAD is now at") and cloning_repo:
                print(f"{ANSI.GREEN}Finished{ANSI.RESET} cloning {cloning_repo}")
                cloning_repo = None

            if line.startswith("-- Configuring done"):
                print(f"{ANSI.BLUE}Finalizing{ANSI.RESET} build configuration...")

            if line.startswith("-- Build files have been written"):
                print(f"{ANSI.GREEN}Build system{ANSI.RESET} configured successfully!")

            build_stopped: str | None = detect_build_stopped(line)
            if build_stopped:
                print(f"\r{ANSI.CLEAR_LINE}{ANSI.RED}Build stopped:{ANSI.RESET} {build_stopped}")

        process.wait()
        stderr_thread.join(timeout = 1)

    except KeyboardInterrupt:
        process.kill()
        sys.exit(1)

    if process.returncode != 0:
        raise CalledProcessError(process.returncode, process.args)

def run_cmake_reconfigure(verbose: bool, release: bool, sanitizers: list[str] = None) -> None:
    """
    @brief Reconfigures the CMake build system without cleaning.

    This function is used to reconfigure the build system without cleaning all build files.
    Use this when new files are added to the project to update the build system
    without requiring a full rebuild of existing files.

    @param verbose (bool): If True, prints all output. Otherwise, shows progress indicators.
    @param release (bool): If True, sets CMake to build for release. Otherwise, builds a debug build.
    @param sanitizers (list[str]): List of sanitizers to enable.

    @throws CalledProcessError
    """
    if sanitizers is None:
        sanitizers = []

    print(f"{ANSI.BLUE}Reconfiguring{ANSI.RESET} build system for new files...")

    cmake_command: list[str] = configure_sanitizers(CMAKE_BUILD_COMMAND, release, sanitizers)

    process: Popen = Popen(
        cmake_command,
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        text = True
    )

    try:
        for line in process.stdout:
            line = line.strip()
            if verbose:
                print(line)
            elif line.startswith("-- Configuring done") or \
                line.startswith("-- Generating done") or \
                line.startswith("-- Build files have been written"):
                print(f"{ANSI.GREEN}{line}{ANSI.RESET}")

        process.wait()

    except KeyboardInterrupt:
        process.kill()
        sys.exit(1)

    if process.returncode != 0:
        raise CalledProcessError(process.returncode, process.args)

    print(f"{ANSI.GREEN}Build system reconfigured successfully!{ANSI.RESET}")

def parse_cmake_progress(line: str) -> tuple[int, int] | None:
    """
    @brief Extracts the current step and total steps from CMake build output.

    @param line (str): A line of CMake output.
    @return tuple[int, int] | None: A tuple (current_step, total_steps) if found, otherwise None.
    """
    match: Match | None = re.search(r"\[(\d+)/(\d+)]", line)
    return (int(match.group(1)), int(match.group(2))) if match else None

def extract_filename(line: str) -> str | None:
    """
    @brief Extracts the filename from a compilation command.

    @param line (str): A line of CMake build output.
    @return str | None: The extracted filename if found, otherwise None.
    """
    match: Match | None = re.search(r"Building CXX object (.+\.cppm?)\.o", line)
    return match.group(1).strip() if match else None

def detect_warnings(line: str) -> str | None:
    """
    @brief Detects warnings in the compiler output.

    @param line (str): A line of compiler output.
    @return str | None: The filename associated with a warning, if found.
    """
    match: Match | None = re.search(r"([^:\s]+:\d+:\d+: warning: .+)", line)
    return match.group(1) if match else None

def detect_errors(line: str) -> str | None:
    """
    @brief Detects compilation errors in the compiler output.

    @param line (str): A line of compiler output.
    @return str | None: The error message if found, otherwise None.
    """
    match: Match | None = re.search(r"([^:\s]+:\d+:\d+: error: .+)", line)
    return match.group(1) if match else None

def detect_build_stopped(line: str) -> str | None:
    """
    @brief Detects build stopped messages from ninja.

    @param line (str): A line of compiler output.
    @return str | None: The build stopped message if found, otherwise None.
    """
    match: Match | None = re.search(r"ninja: build stopped: (.+)", line)
    return match.group(0) if match else None

def run_cmake_build(verbose: bool) -> None:
    """
    @brief Runs `cmake --build build` while showing a progress bar if `verbose` is False.

    @param verbose (bool): If True, prints build logs. Otherwise, shows a progress bar.

    @throws CalledProcessError
    """
    if verbose:
        run_command(["cmake", "--build", "build"], verbose = True)
        return

    print(f"{ANSI.GREEN}Building{ANSI.RESET} openJuice...")

    process: Popen = Popen(
        ["cmake", "--build", "build"],
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        text = True
    )

    first_line: str = process.stdout.readline().strip()
    if "ninja: no work to do" in first_line:
        print(f"{ANSI.GREEN}Everything up to date!{ANSI.RESET} No compilation needed.")
        process.wait()
        return

    bar_length: int = 40
    last_percentage: int = 0
    total_steps: int = 0
    current_step: int = 0
    current_file: str | None = None
    bar: str = "-" * bar_length
    error_files: set[str] = set()

    if first_line:
        progress = parse_cmake_progress(first_line)
        if progress:
            current_step, total_steps = progress
            percentage = int((current_step / total_steps) * 100)
            last_percentage = percentage
            filled = int(bar_length * (percentage / 100))
            bar = "#" * filled + "-" * (bar_length - filled)

        new_file = extract_filename(first_line)
        if new_file:
            current_file = new_file

    def update_progress_bar() -> None:
        """
        @brief Update the progress bar.
        """
        width: int = len(str(total_steps)) if total_steps > 0 else 1
        
        filled = int(bar_length * (last_percentage / 100))
        progress_bar = "=" * filled + (">" if filled < bar_length else "") + " " * (bar_length - filled - (1 if filled < bar_length else 0))
        
        output_string: str = (
            f"\r{ANSI.CLEAR_LINE}[{progress_bar}] {last_percentage}% "
            f"[{current_step:{width}d}/{total_steps or 1}] "
            f"{ANSI.GREEN}Compiling:{ANSI.RESET} {current_file or ''} "
        )
        if visible_length(output_string) > console_width() - 1:
            output_string = output_string[:console_width() - 1]
        print(output_string, end = "", flush = True)

    update_progress_bar()

    error_lines: list[str] = []

    def read_stderr() -> None:
        """
        @brief Read from the stderr stream.
        """
        for line in process.stderr:
            line = line.strip()
            error_lines.append(line)
            error_msg = detect_errors(line)
            if error_msg:
                error_file = error_msg.split(':')[0]
                if error_file not in error_files:
                    print()
                    error_files.add(error_file)
                print(f"\r{ANSI.CLEAR_LINE}{ANSI.RED}Error:{ANSI.RESET} {error_msg}")
                update_progress_bar()
            build_stopped = detect_build_stopped(line)
            if build_stopped:
                print(f"\r{ANSI.CLEAR_LINE}{ANSI.RED}Build stopped:{ANSI.RESET} {build_stopped}")
                update_progress_bar()

    stderr_thread: Thread = Thread(target = read_stderr, daemon = True)
    stderr_thread.start()

    try:
        for line in process.stdout:
            line = line.strip()

            warning_msg: str | None = detect_warnings(line)
            if warning_msg:
                print(f"\r{ANSI.CLEAR_LINE}{ANSI.YELLOW}Warning:{ANSI.RESET} {warning_msg} (enable verbose for details)")
                update_progress_bar()

            error_msg: str | None = detect_errors(line)
            if error_msg:
                error_file = error_msg.split(':')[0]
                if error_file not in error_files:
                    print()
                    error_files.add(error_file)
                print(f"\r{ANSI.CLEAR_LINE}{ANSI.RED}Error:{ANSI.RESET} {error_msg}")
                update_progress_bar()

            progress: tuple[int, int] | None = parse_cmake_progress(line)
            if progress:
                current_step, total_steps = progress
                percentage: int = int((current_step / total_steps) * 100)

                if percentage > last_percentage:
                    last_percentage = percentage
                    filled: int = int(bar_length * (percentage / 100))
                    bar = "#" * filled + "-" * (bar_length - filled)
                    update_progress_bar()

            new_file: str | None = extract_filename(line)
            if new_file:
                current_file = new_file
                update_progress_bar()

            build_stopped: str | None = detect_build_stopped(line)
            if build_stopped:
                print(f"\r{ANSI.CLEAR_LINE}{ANSI.RED}Build stopped:{ANSI.RESET} {build_stopped}")
                update_progress_bar()

        process.wait()
        stderr_thread.join(timeout = 1)

        if process.returncode != 0:
            print(f"\r{ANSI.CLEAR_LINE}{ANSI.RED}Build failed!{ANSI.RESET} Check the errors above or run with --verbose for details.")
        else:
            print()

    except KeyboardInterrupt:
        process.kill()
        sys.exit(1)

    if process.returncode != 0:
        raise CalledProcessError(process.returncode, process.args)

def main() -> int:
    """
    @brief Main function.
    
    Main function to execute the build and dependency generation steps for the openJuice project.
    Supports various flags for different operations.

    @return int: Return code (0 for success, non-zero for failure).
    """
    if os.path.basename(os.getcwd()) == "scripts":
        os.chdir("..")
    
    parser: ArgumentParser = ArgumentParser(description = "Build script for openJuice project.")

    operation_group: MutuallyExclusiveGroup = parser.add_mutually_exclusive_group()
    parser.add_argument("-r", "--release", action = "store_true",
                        help = "Build in release mode (optimized, no sanitizers, NDEBUG defined)")
    
    operation_group.add_argument("-c", "--clean", action = "store_true",
                                help = "Clean only project source files (no building)")
    operation_group.add_argument("-ca", "--clean-all", action = "store_true",
                                help = "Clean entire project, including dependencies (no building)")
    operation_group.add_argument("-n", "--new", action = "store_true",
                                help = "Cleans the build directory and rebuilds everything, including dependencies (mandatory for first build)")
    operation_group.add_argument("-pd", "--preserve-deps", action = "store_true",
                                help = "Cleans the build directory and rebuilds everything (excluding dependencies)")
    operation_group.add_argument("-rc", "--reconfigure", action = "store_true",
                                help = "Reconfigure CMake build system (for when new files are added)")

    parser.add_argument("-g", "--graph", action = "store_true", help = "Generate dependency graph")
    parser.add_argument("-s", "--sanitizer", nargs = "+", default = [],
                        help = "Enable sanitizers (address, undefined, thread, memory, leak, all)")
    parser.add_argument("-v", "--verbose", action = "store_true",
                        help = "Enable verbose output (lacks progress bar or other graphical features)")

    args: Namespace = parser.parse_args()
    release: bool = args.release
    clean: bool = args.clean
    clean_all: bool = args.clean_all
    generate_graph: bool = args.graph
    build_new: bool = args.new
    preserve_deps: bool = args.preserve_deps
    reconfigure: bool = args.reconfigure
    verbose: bool = args.verbose
    sanitizers: list[str] = args.sanitizer

    start_time: float = time.time()

    try:
        if clean_all:
            clean_build_directory(False)
            return 0
        elif clean:
            clean_build_directory(True)
            return 0
        elif build_new:
            clean_build_directory(False)
            run_cmake_init(verbose, release, sanitizers)
        elif preserve_deps:
            clean_build_directory(True)
            run_cmake_init(verbose, release, sanitizers)
        elif reconfigure:
            run_cmake_reconfigure(verbose, release, sanitizers)
        else:
            if sanitizers and not os.path.exists("build/CMakeCache.txt"):
                run_cmake_init(verbose, release, sanitizers)

        if not (clean_all or clean):
            run_cmake_build(verbose)

        if generate_graph:
            print(f"{ANSI.GREEN}Generating{ANSI.RESET} dependency graph (output: graph.dot, dependencies.png)")
            run_command(["mgt"], verbose)
            run_command(GENERATE_DEPENDENCIES_GRAPH_IMAGE_COMMAND, verbose)

    except CalledProcessError as e:
        if verbose:
            print(f"Error: {e}", file = sys.stderr)
        return e.returncode

    end_time: float = time.time()
    elapsed_time: float = round(end_time - start_time, 3)

    print(f"{ANSI.GREEN}Build complete!{ANSI.RESET} Time taken: {elapsed_time:.3f} seconds")

    return 0

if __name__ == "__main__":
    sys.exit(main())
