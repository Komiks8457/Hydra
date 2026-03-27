file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")
add_library(DownloadServer STATIC ${SOURCES})
target_link_libraries(DownloadServer Common)
target_include_directories(DownloadServer PUBLIC src/)
