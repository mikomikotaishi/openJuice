cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
message(STATUS "CMake version: ${CMAKE_VERSION}")

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD ON)

if(CMAKE_VERSION VERSION_LESS_EQUAL "3.31.7")
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
elseif(CMAKE_VERSION VERSION_LESS_EQUAL "4.2.3")
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
elseif(CMAKE_VERSION VERSION_LESS_EQUAL "4.3.4")
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
else()
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
endif()

option(BUILD_STATIC_LIBS "Build static libraries instead of shared" OFF)

set(STDLIB "default" CACHE STRING "C++ standard library to use (default, libstdc++, libc++)")
set_property(CACHE STDLIB PROPERTY STRINGS "default" "libstdc++" "libc++")

if(STDLIB STREQUAL "libc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
elseif(STDLIB STREQUAL "libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
endif()

# Set default build directory if not specified
if(NOT CMAKE_BINARY_DIR)
    set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")
endif()

if(BUILD_STATIC_LIBS)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)

    if(WIN32)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    else()
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    endif()
    
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set(CMAKE_SKIP_BUILD_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH "")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
    
    message(STATUS "Configuring for static library build")
else()
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)
    message(STATUS "Configuring for shared library build")
endif()

if(UNIX)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../build/lib")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

# if(DEFINED ENV{VCPKG_ROOT})
#     set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
# endif()

project(openJuice
    LANGUAGES CXX
    VERSION 0.0.1
)

# set(CMAKE_CXX_MODULE_BMI_DIRECTORY "${CMAKE_BINARY_DIR}/.gens/openJuice/linux/x86_64/release/rules/bmi/cache/modules/4bddce1b")

function(configure_cpp_module_target target)
    set_target_properties(${target} PROPERTIES
        CXX_EXTENSIONS OFF
        CXX_MODULE_BMI_DIRECTORY "${CMAKE_CXX_MODULE_BMI_DIRECTORY}"
        CXX_STANDARD ${CMAKE_CXX_STANDARD}
        CXX_MODULE_STD ON
    )
endfunction()

option(ENABLE_SANITIZERS "Enable sanitizers in debug builds" OFF)
option(USE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
option(USE_SANITIZER_KERNEL "Enable kernel address sanitizer" OFF)
option(USE_SANITIZER_HW "Enable hardware address sanitizer" OFF)
option(USE_SANITIZER_UNDEFINED "Enable undefined behavior sanitizer" OFF)
option(USE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
option(USE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
option(USE_SANITIZER_LEAK "Enable leak sanitizer" OFF)

set(COMPILER_APPLE_CLANG OFF)
set(COMPILER_CLANG OFF)
set(COMPILER_GCC OFF)
set(COMPILER_MSVC OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(COMPILER_APPLE_CLANG ON)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILER_CLANG ON)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_GCC ON)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER_MSVC ON)
endif()

set(ARCH_X86_64 OFF)
set(ARCH_X86 OFF)
set(ARCH_ARM64 OFF)
set(ARCH_ARM OFF)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64")
    set(ARCH_X86_64 ON)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i386|x86")
    set(ARCH_X86 ON)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
    set(ARCH_ARM64 ON)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm|armv7l")
    set(ARCH_ARM ON)
endif()

function(add_sanitizers target)
    if(NOT ENABLE_SANITIZERS)
        return()
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        set(SANITIZER_FLAGS "")
        
        if(USE_SANITIZER_ADDRESS)
            list(APPEND SANITIZER_FLAGS "-fsanitize=address")
        endif()

        if(USE_SANITIZER_KERNEL)
            list(APPEND SANITIZER_FLAGS "-fsanitize=kernel-address")
        endif()

        if(USE_SANITIZER_HW)
            list(APPEND SANITIZER_FLAGS "-fsanitize=hwaddress")
        endif()

        if(USE_SANITIZER_UNDEFINED)
            list(APPEND SANITIZER_FLAGS "-fsanitize=undefined")
        endif()

        if(USE_SANITIZER_THREAD)
            list(APPEND SANITIZER_FLAGS "-fsanitize=thread")
        endif()

        if(USE_SANITIZER_MEMORY)
            list(APPEND SANITIZER_FLAGS "-fsanitize=memory")
        endif()
        
        if(USE_SANITIZER_LEAK)
            list(APPEND SANITIZER_FLAGS "-fsanitize=leak")
        endif()
        
        if(SANITIZER_FLAGS)
            target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS})
            target_link_options(${target} PRIVATE ${SANITIZER_FLAGS})
        endif()
    endif()
endfunction()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
    
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(-O3)
    elseif(MSVC)
        add_compile_options(/O2)
    endif()
    
    set(ENABLE_SANITIZERS OFF)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(STDLIB STREQUAL "libc++")
        message(STATUS "Standard library: libc++")
        add_link_options(-stdlib=libc++)
    elseif(STDLIB STREQUAL "libstdc++")
        message(STATUS "Standard library: libstdc++")
        add_link_options(-stdlib=libstdc++)
    else()
        if(APPLE)
            message(STATUS "Standard library: libc++ (default on macOS)")
        elseif(UNIX)
            message(STATUS "Standard library: libstdc++ (default on Linux)")
        else()
            message(STATUS "Standard library: compiler default")
        endif()
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if(STDLIB STREQUAL "default")
        message(STATUS "Standard library: libstdc++ (GCC default)")
    else()
        message(WARNING "STDLIB option '${STDLIB}' is not applicable with GCC (always uses libstdc++)")
    endif()
elseif(MSVC)
    if(STDLIB STREQUAL "default")
        message(STATUS "Standard library: MSVC STL (default)")
    else()
        message(WARNING "STDLIB option '${STDLIB}' is not applicable with MSVC")
    endif()
else()
    if(NOT STDLIB STREQUAL "default")
        message(WARNING "STDLIB option '${STDLIB}' may not be supported with ${CMAKE_CXX_COMPILER_ID}")
    else()
        message(STATUS "Standard library: compiler default")
    endif()
endif()

option(STDLIBX_USE_HARDENED_LIBRARY "Enable C++ standard library hardening (bounds/precondition checks, active even in release builds)" ON)

# libc++ offers graduated levels; libstdc++ and MSVC STL are on/off (the mode
# only selects the extra debug tier there). Default matches stdlibx's own.
set(STDLIBX_HARDENED_LIBRARY_MODE "extensive" CACHE STRING "Standard library hardening level: fast, extensive, or debug")
set_property(CACHE STDLIBX_HARDENED_LIBRARY_MODE PROPERTY STRINGS "fast" "extensive" "debug")

if(STDLIBX_USE_HARDENED_LIBRARY)
    message(STATUS "Standard library hardening: ON (mode '${STDLIBX_HARDENED_LIBRARY_MODE}', applied by stdlibx)")
else()
    message(STATUS "Standard library hardening: OFF (STDLIBX_USE_HARDENED_LIBRARY=OFF)")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(FTXUI_BUILD_MODULES ON CACHE BOOL "Enable FTXUI module support")
set(TOMLPLUSPLUS_BUILD_MODULES ON CACHE BOOL "Enable tomlplusplus module support")
set(STDLIBX_BUILD_EXAMPLES OFF CACHE BOOL "Build the examples for stdlibx" FORCE) # Disable examples
set(STDLIBX_BUILD_TESTS OFF CACHE BOOL "Build the tests for stdlibx" FORCE) # Disable tests

FetchContent_Declare(
    stdlibx
    GIT_REPOSITORY https://github.com/mikomikotaishi/stdlibx.git
    GIT_TAG main
)

FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG v7.0.3
)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    FetchContent_Declare(
        nlohmann-json 
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    )
else()
    FetchContent_Declare(
        nlohmann-json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG develop
    )
endif()

# Check if Abseil is available, fetch if not (required by RE2)
find_package(absl QUIET)
if(NOT absl_FOUND)
    message(STATUS "Abseil not found, fetching via FetchContent")
    FetchContent_Declare(
        abseil-cpp
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
        GIT_TAG 20260526.0
        GIT_SHALLOW TRUE
    )
    set(ABSL_PROPAGATE_CXX_STD ON CACHE BOOL "Propagate project C++ standard to Abseil")
endif()

FetchContent_Declare(
    re2
    GIT_REPOSITORY https://github.com/google/re2.git
    GIT_TAG 2025-11-05
)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
)
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG master
)

# Keep `import std` (CMAKE_CXX_MODULE_STD) from leaking into third-party
# dependencies that build as C++14/17
set(CMAKE_CXX_MODULE_STD OFF)

# Make dependencies available, including Abseil if it was fetched
if(NOT absl_FOUND)
    FetchContent_MakeAvailable(
        stdlibx
        abseil-cpp
        ftxui
        nlohmann-json
        re2
        SFML
        tomlplusplus
    )
else()
    FetchContent_MakeAvailable(
        stdlibx
        ftxui
        nlohmann-json
        re2
        SFML
        tomlplusplus
    )
endif()

# Re-enable import std for openJuice's own module targets.
set(CMAKE_CXX_MODULE_STD ON)

add_subdirectory(deps)

add_subdirectory(src)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR BUILD_SHARED_LIBS STREQUAL "OFF")
    target_link_libraries(openJuice PRIVATE 
        stdlibx
        modules
        ftxui-modules
        nlohmann_json
        sfml
        re2_module
        ${DISCORD_LIBRARY}
    )
else()
    target_link_libraries(openJuice PRIVATE 
        stdlibx
        modules
        ftxui-modules
        sfml
        re2_module
    )
endif()

target_include_directories(openJuice 
    PRIVATE 
    ${SFML_INCLUDE_DIRECTORIES}
    ${tomlplusplus_INCLUDE_DIRS} 
)

if(WIN32 AND NOT (CMAKE_BUILD_TYPE STREQUAL "Release" OR BUILD_SHARED_LIBS STREQUAL "OFF"))
    add_custom_command(TARGET openJuice POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_BINARY_DIR}/lib"
            "${CMAKE_BINARY_DIR}/bin"
        COMMENT "Copying DLLs to bin directory")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

if(UNIX AND NOT APPLE)
    set_target_properties(openJuice PROPERTIES
        INSTALL_RPATH "$ORIGIN:$ORIGIN/../lib:$ORIGIN/lib/discord/linux")
elseif(APPLE)
    set_target_properties(openJuice PROPERTIES
        INSTALL_RPATH "@executable_path:@executable_path/../lib:@executable_path/lib/discord/macos")
endif()
