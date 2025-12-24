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
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)

# Disable -Wextra-semi for card and unit module files
file(GLOB_RECURSE CARD_MODULES card/**/*.cppm)
file(GLOB_RECURSE UNIT_MODULES unit/**/*.cppm)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(modules PRIVATE 
        -Wall -Wextra -Wpedantic
        -Wshadow -Wunused-parameter
        -Wconversion -Wsign-conversion 
    )
    
    # Disable -Wno-extra-semi for card and unit modules
    if(CARD_MODULES OR UNIT_MODULES)
        set_source_files_properties(${CARD_MODULES} ${UNIT_MODULES}
            PROPERTIES COMPILE_FLAGS "-Wno-extra-semi"
        )
    endif()
elseif(MSVC)
    target_compile_options(modules PRIVATE /W4)
endif()

target_link_libraries(modules PUBLIC 
    stdlibx
    boost_asio_modules
    boost_regex_modules
    boost_system_modules
    discordpp
    ftxui-modules
    nlohmann_json_modules
    sfml
    tomlpp
)

target_include_directories(modules 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${boost-asio_SOURCE_DIR}/include
    ${boost-regex_SOURCE_DIR}/include  
    ${boost-system_SOURCE_DIR}/include
    ${tomlplusplus_INCLUDE_DIRS}
)

add_sanitisers(modules)
