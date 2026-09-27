file(GLOB_RECURSE MODULES *.cppm)
add_library(ojmodules)
target_sources(ojmodules
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${MODULES}
)

configure_cpp_module_target(ojmodules)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(ojmodules PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_MODULE_DYNDEP OFF
)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(ojmodules PRIVATE 
        -Wall -Wextra -Wpedantic
        -Wshadow -Wunused-parameter
        -Wconversion -Wsign-conversion 
    )
elseif(MSVC)
    target_compile_options(ojmodules PRIVATE /W4)
endif()

target_link_libraries(ojmodules PUBLIC 
    stdlibx
    discordpp
    ftxui-modules
    nlohmann_json_modules
    re2_module
    tomlpp
)

target_include_directories(ojmodules 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${tomlplusplus_INCLUDE_DIRS}
)

add_sanitizers(ojmodules)
