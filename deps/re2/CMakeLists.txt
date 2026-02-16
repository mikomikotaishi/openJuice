file(GLOB_RECURSE RE2_MODULES *.cppm)
add_library(re2_module)
target_sources(re2_module
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${RE2_MODULES})

configure_cpp_module_target(re2_module)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(re2_module PROPERTIES 
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)

target_link_libraries(re2_module PUBLIC re2)
