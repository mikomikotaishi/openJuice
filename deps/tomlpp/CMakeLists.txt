file(GLOB_RECURSE TOMLPP_MODULES *.cppm)
add_library(tomlpp)
target_sources(tomlpp
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${TOMLPP_MODULES}
)

configure_cpp_module_target(tomlpp)

target_link_libraries(tomlpp 
    PRIVATE tomlplusplus_modules
)

target_compile_definitions(tomlpp 
    PRIVATE TOMLPLUSPLUS_BUILD_MODULES
)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(tomlpp PROPERTIES 
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)
