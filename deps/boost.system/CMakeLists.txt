file(GLOB_RECURSE BOOST_SYSTEM_MODULES *.cppm)
add_library(boost_system_modules)
target_sources(boost_system_modules
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${BOOST_SYSTEM_MODULES})

configure_cpp_module_target(boost_system_modules)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(boost_system_modules PROPERTIES 
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)
