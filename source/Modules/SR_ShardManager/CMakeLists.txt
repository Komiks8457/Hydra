file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")
add_library(ShardManager STATIC ${SOURCES})
target_link_libraries(ShardManager Common HydraFramework)
target_include_directories(ShardManager PUBLIC src/)
