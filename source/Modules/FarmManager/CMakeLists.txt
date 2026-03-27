file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")
add_library(FarmManager STATIC ${SOURCES})
target_link_libraries(FarmManager Common)
target_include_directories(FarmManager PUBLIC src/)
