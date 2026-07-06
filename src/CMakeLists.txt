add_subdirectory(openjuice)

add_executable(openJuice Main.cpp)

target_link_libraries(openJuice PUBLIC modules)

target_include_directories(openJuice
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(openJuice PRIVATE 
        -Wall -Wextra -Wpedantic
        -Wshadow -Wconversion 
        -Wsign-conversion -Wunused-parameter
    )
elseif(MSVC)
    target_compile_options(openJuice PRIVATE /W4)
endif()

add_sanitizers(openJuice)

add_custom_command(TARGET openJuice POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        $<TARGET_FILE:openJuice> 
        ${CMAKE_SOURCE_DIR}
    COMMENT "Copying executable to project root directory"
)