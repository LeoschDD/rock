cmake_minimum_required(VERSION 3.25)
project(rock)

set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(rock src/main.cpp)