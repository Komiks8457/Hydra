file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")
add_library(AgentServer STATIC ${SOURCES})
target_link_libraries(AgentServer Common)
target_include_directories(AgentServer PUBLIC src/)
