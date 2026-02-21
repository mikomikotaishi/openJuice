file(GLOB_RECURSE SFML_MODULES *.cppm)
add_library(sfml)
target_sources(sfml
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${SFML_MODULES})

configure_cpp_module_target(sfml)

target_link_libraries(sfml
    PUBLIC
    SFML::Audio 
    SFML::Graphics 
    SFML::Network 
    SFML::System 
    SFML::Window
    stdlibx
)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(sfml PROPERTIES 
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)
