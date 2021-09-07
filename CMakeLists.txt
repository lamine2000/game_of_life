cmake_minimum_required(VERSION 3.0)
project(gol C)

set(CMAKE_C_STANDARD 99)

add_executable(gol main.c)

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

#add_executable(gol main.c game.h)
target_link_libraries(gol ${SDL_LIBRARY})
