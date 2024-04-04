cmake_minimum_required(VERSION 3.7)

project(Maze)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/SDL2/cmake")
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL2/cmake")

# list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/SDL2_image/cmake")

# $(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
# gcc src/*.c -ISDL2/include -lSDL2main -lSDL2 -lSDL2_image -o maze
# COMPILER gcc
# OBJS main.c etc...
# INCLUDE PATHS -ISDL2/include
# COMPILER FLAGS -Wall -Werror -Wextra -pedantic
# LINKER FLAGS -lSDL2main -lSDL2 -lSDL2_image
# OBJECT -o maze

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# find_package(SDL2_image REQUIRED)

add_executable(Maze
    src/main.c
    src/init_sdl.c
    src/display.c
    src/helpers.c
    src/raycast.c
    src/file_handling.c
    src/parser.c
)

target_link_libraries(Maze ${SDL2_LIBRARIES})
