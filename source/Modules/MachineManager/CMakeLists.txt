file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")
add_library(MachineManager STATIC ${SOURCES})
target_link_libraries(MachineManager Common HydraFramework)
target_include_directories(MachineManager PUBLIC src/)
