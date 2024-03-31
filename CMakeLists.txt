cmake_minimum_required(VERSION 3.7)

project(Maze)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/SDL2/cmake")
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL2/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Maze src/main.c
                    src/init_sdl.c
                    src/display.c
                    src/helpers.c
                    src/raycast.c
                    src/file_handling.c
                    src/parser.c
                )
target_link_libraries(Maze ${SDL2_LIBRARIES})