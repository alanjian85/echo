cmake_minimum_required(VERSION 3.21)
project(echo)

find_package(Threads REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_executable(echo ${SOURCE_FILES})
target_include_directories(echo PRIVATE include)
target_link_libraries(echo Threads::Threads)
