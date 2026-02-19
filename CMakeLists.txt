cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
message(STATUS "CMake version: ${CMAKE_VERSION}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD ON)

if(CMAKE_VERSION VERSION_LESS_EQUAL "3.31.7")
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
elseif(CMAKE_VERSION VERSION_LESS "4.3")
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
endif()

# Set default build directory if not specified
if(NOT CMAKE_BINARY_DIR)
    set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR BUILD_SHARED_LIBS STREQUAL "OFF")
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
    
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set(CMAKE_SKIP_BUILD_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH "")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
    
    message(STATUS "Configuring for static linking (single executable)")
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

set(CMAKE_CXX_MODULE_BMI_DIRECTORY "${CMAKE_BINARY_DIR}/.gens/openJuice/linux/x86_64/release/rules/bmi/cache/modules/4bddce1b")

function(configure_cpp_module_target target)
    set_target_properties(${target} PROPERTIES 
        CXX_EXTENSIONS OFF
        CXX_MODULE_BMI_DIRECTORY "${CMAKE_CXX_MODULE_BMI_DIRECTORY}"
        CMAKE_CXX_STANDARD 23
        CMAKE_CXX_MODULE_STD ON
    )
endfunction()

option(ENABLE_SANITIZERS "Enable sanitisers in debug builds" OFF)
option(USE_SANITIZER_ADDRESS "Enable address sanitiser" OFF)
option(USE_SANITIZER_KERNEL "Enable kernel address sanitiser" OFF)
option(USE_SANITIZER_HW "Enable hardware address sanitiser" OFF)
option(USE_SANITIZER_UNDEFINED "Enable undefined behaviour sanitiser" OFF)
option(USE_SANITIZER_THREAD "Enable thread sanitiser" OFF)
option(USE_SANITIZER_MEMORY "Enable memory sanitiser" OFF)
option(USE_SANITIZER_LEAK "Enable leak sanitiser" OFF)

function(add_sanitisers target)
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
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-stdlib=libstdc++>)
    add_link_options(-stdlib=libstdc++)
    # add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-stdlib=libc++>)
    # add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-I/usr/include/c++/v1>)
    # add_link_options(-stdlib=libc++)
    # add_link_options(-lc++abi)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(STDLIBX_EXTENSIONS ON CACHE BOOL "Enable the stdx.* modules" FORCE)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(FTXUI_BUILD_MODULES ON CACHE BOOL "Enable FTXUI module support")
set(TOMLPLUSPLUS_BUILD_MODULES ON CACHE BOOL "Enable tomlplusplus module support")

FetchContent_Declare(
    stdlibx
    GIT_REPOSITORY https://github.com/mikomikotaishi/stdlibx.git
    GIT_TAG main
)

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG master
)
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG main
)
FetchContent_Declare(
    nlohmann-json 
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_Declare(
    re2
    GIT_REPOSITORY https://github.com/google/re2.git
    GIT_TAG main
)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        master
)
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(
    stdlibx
    ftxui
    nlohmann-json
    re2
    SFML
    tomlplusplus
)

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
