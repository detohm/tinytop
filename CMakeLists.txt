cmake_minimum_required(VERSION 3.11.3)
set(CMAKE_CXX_STANDARD 17)

project(TinyTop)

find_package(curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR} include)

file(GLOB project_srcs src/*.cpp)

add_executable(TinyTop ${project_srcs})
target_link_libraries(TinyTop ${CURSES_LIBRARIES})
