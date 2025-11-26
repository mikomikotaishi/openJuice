file(GLOB_RECURSE DISCORDPP_MODULES *.cppm)
add_library(discordpp)

target_include_directories(discordpp 
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/discordpp"
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(discordpp
    PUBLIC
    FILE_SET CXX_MODULES FILES
    ${DISCORDPP_MODULES}
)

configure_cpp_module_target(discordpp)

set_target_properties(discordpp PROPERTIES 
    CXX_STANDARD 23 
    CXX_EXTENSIONS OFF 
    CXX_MODULE_DYNDEP OFF
)
if(WIN32)
    set(DISCORD_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/discord/win32")
    
    add_library(discord_partner_sdk SHARED IMPORTED)
    
    set_target_properties(discord_partner_sdk PROPERTIES
        IMPORTED_LOCATION "${DISCORD_LIB_DIR}/discord_partner_sdk.dll"
        IMPORTED_IMPLIB "${DISCORD_LIB_DIR}/discord_partner_sdk.lib"
    )
    
    if(NOT EXISTS "${DISCORD_LIB_DIR}/discord_partner_sdk.dll")
        message(FATAL_ERROR "Discord DLL not found: ${DISCORD_LIB_DIR}/discord_partner_sdk.dll")
    endif()
    if(NOT EXISTS "${DISCORD_LIB_DIR}/discord_partner_sdk.lib")
        message(FATAL_ERROR "Discord import library not found: ${DISCORD_LIB_DIR}/discord_partner_sdk.lib")
    endif()
    
    target_link_libraries(discordpp PRIVATE discord_partner_sdk)
    
    add_custom_command(TARGET discordpp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DISCORD_LIB_DIR}/discord_partner_sdk.dll"
            "$<TARGET_FILE_DIR:discordpp>/discord_partner_sdk.dll"
    )
elseif(APPLE)
    set(DISCORD_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/discord/darwin")
    set(DISCORD_LIB_NAME "discord_partner_sdk")
    
    find_library(DISCORD_LIBRARY
        NAMES ${DISCORD_LIB_NAME}
        PATHS ${DISCORD_LIB_DIR}
        NO_DEFAULT_PATH
    )
    
    if(NOT DISCORD_LIBRARY)
        message(FATAL_ERROR "Discord library not found. Expected in: ${DISCORD_LIB_DIR}")
    endif()
    
    target_link_libraries(discordpp PRIVATE ${DISCORD_LIBRARY})
elseif(UNIX)
    set(DISCORD_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/discord/linux")
    set(DISCORD_LIB_NAME "discord_partner_sdk")
    
    find_library(DISCORD_LIBRARY
        NAMES ${DISCORD_LIB_NAME}
        PATHS ${DISCORD_LIB_DIR}
        NO_DEFAULT_PATH
    )
    
    if(NOT DISCORD_LIBRARY)
        message(FATAL_ERROR "Discord library not found. Expected in: ${DISCORD_LIB_DIR}")
    endif()
    
    target_link_libraries(discordpp PRIVATE ${DISCORD_LIBRARY})
endif()

target_include_directories(discordpp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/discordpp")
