file(GLOB_RECURSE SQLITECPP_MODULES *.cppm)
add_library(sqlitecpp)
target_sources(sqlitecpp
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${SQLITECPP_MODULES})

configure_cpp_module_target(sqlitecpp)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(sqlitecpp PROPERTIES 
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)
