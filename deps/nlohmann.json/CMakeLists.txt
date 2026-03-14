file(GLOB_RECURSE NLOHMANN_JSON_MODULES *.cppm)
add_library(nlohmann_json_modules)
target_sources(nlohmann_json_modules
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${NLOHMANN_JSON_MODULES})

configure_cpp_module_target(nlohmann_json_modules)

target_include_directories(nlohmann_json_modules
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(nlohmann_json_modules PUBLIC nlohmann_json::nlohmann_json stdlibx)

## Ignore module circular dependencies, remove when CMake fixes this
set_target_properties(nlohmann_json_modules PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_MODULE_DYNDEP OFF
)
