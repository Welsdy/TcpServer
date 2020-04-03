# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.1)

# 项目信息
project (lib C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(src/)
add_subdirectory(test/)
