cmake_minimum_required(VERSION 3.11.3)
set(CMAKE_CXX_STANDARD 17)

project(TinyTop)

file(GLOB project_srcs src/*.cpp)
add_executable(TinyTop ${project_srcs})
