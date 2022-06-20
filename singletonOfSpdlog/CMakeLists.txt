cmake_minimum_required(VERSION 3.15)

project(logs)

add_executable(main main.cpp)

add_definitions(-DSTDOUT_FOR_DEBUG)

target_link_libraries(main pthread)

include_directories(${PROJECT_SOURCE_DIR}/include)