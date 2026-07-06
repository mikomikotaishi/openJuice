file(GLOB_RECURSE MODULES *.cppm)
add_library(modules)
target_sources(modules
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${MODULES}
)

configure_cpp_module_target(modules)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(modules PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_MODULE_DYNDEP OFF
)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(modules PRIVATE 
        -Wall -Wextra -Wpedantic
        -Wshadow -Wunused-parameter
        -Wconversion -Wsign-conversion 
    )
elseif(MSVC)
    target_compile_options(modules PRIVATE /W4)
endif()

target_link_libraries(modules PUBLIC 
    stdlibx
    discordpp
    ftxui-modules
    nlohmann_json_modules
    re2_module
    sfml
    tomlpp
)

target_include_directories(modules 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${tomlplusplus_INCLUDE_DIRS}
)

add_sanitizers(modules)
