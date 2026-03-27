include(version/VersionInfo.cmake)

generate_product_version(VersionInfo
        VERSION_MAJOR       1
        FILE_DESCRIPTION    "Module Extension"
        COMPANY_NAME        "8ATHALA Co., Ltd."
        COMPANY_COPYRIGHT   "Copyright (C) 2026"
        ORIGINAL_FILENAME   "HYDRA.DLL"
        INTERNAL_NAME       "HYDRA"
        BUNDLE              "HydraFramework Module Helper"
)

set(RESOURCE_FILES "src/Hydra.cpp" "src/Hydra.def" "src/Library.cpp" "src/StaticPatches.cpp")
add_library(Hydra SHARED ${RESOURCE_FILES} ${VersionInfo})

target_link_libraries(Hydra
        Common
        AgentServer
        DownloadServer
        GatewayServer
        FarmManager
        GlobalManager
        MachineManager
        ShardManager
        GameServer
)

if(MSVC)
    set_target_properties(Hydra PROPERTIES LINK_FLAGS "/DEF:\"src/Hydra.def\"")
endif()

add_custom_command(
        TARGET Hydra
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR}
)

add_custom_command(
        TARGET Hydra
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Hydra> "H:/silkroadr/Hydra.dll"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Hydra> "H:/silkroadr/ASGS/AgentServer1/Hydra.dll"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Hydra> "H:/silkroadr/ASGS/GameServer1/Hydra.dll"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Hydra> "H:/silkroadr/SMC/Hydra.dll"
)