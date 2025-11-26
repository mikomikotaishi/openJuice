file(GLOB_RECURSE BOOST_ASIO_MODULES *.cppm)
add_library(boost_asio_modules)
target_sources(boost_asio_modules
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${BOOST_ASIO_MODULES})

configure_cpp_module_target(boost_asio_modules)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(boost_asio_modules PROPERTIES 
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)
