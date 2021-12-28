project(echo_server)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_executable(echo_server ${SOURCE_FILES})
target_include_directories(echo_server PRIVATE include)
target_link_libraries(echo_server Threads::Threads)
