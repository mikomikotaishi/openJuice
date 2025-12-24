file(GLOB_RECURSE RE2_MODULES *.cppm)
add_library(re2)
target_sources(re2
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${RE2_MODULES})

configure_cpp_module_target(re2)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(re2 PROPERTIES 
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)
