#include "../inc/maze.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 * Return: 0
 */
int main(int argc, char **argv)
{
    instance sdl_ins = {NULL, NULL};

    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initalize! SDL_Error: %s\n", SDL_GetError());
    }

    create_window(TITLE, &sdl_ins);
    destroy_window(&sdl_ins);

    return (0);
}