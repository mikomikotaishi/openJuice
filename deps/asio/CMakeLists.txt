file(GLOB_RECURSE ASIO_MODULES *.cppm)
add_library(asio_module)
target_sources(asio_module
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${ASIO_MODULES})

configure_cpp_module_target(asio_module)

# Set include directories for the header includes in module file
target_include_directories(asio_module PRIVATE
    ${asio_SOURCE_DIR}/include
)

# Asio requires these definitions for standalone mode (not using Boost)
target_compile_definitions(asio_module PRIVATE
    ASIO_STANDALONE
    ASIO_NO_DEPRECATED
)

# Link against threading library
find_package(Threads REQUIRED)
target_link_libraries(asio_module PRIVATE Threads::Threads)

# Platform-specific requirements
if(WIN32)
    target_link_libraries(asio_module PRIVATE ws2_32 wsock32)
endif()

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(asio_module PROPERTIES 
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)
