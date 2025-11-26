file(GLOB_RECURSE BOOST_REGEX_MODULES *.cppm)
add_library(boost_regex_modules)
target_sources(boost_regex_modules
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${BOOST_REGEX_MODULES})

configure_cpp_module_target(boost_regex_modules)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(boost_regex_modules PROPERTIES 
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)
