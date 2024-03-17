#include "../inc/maze.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 * Return: 0
 */
int main(int argc, char **argv)
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initalize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDl_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            // Update the surface
            SDL_UpdateWindowSurface(window);

            // Hack to get window to stay up
            SDL_Event e;
            int quit = 0;
            while (quit == 0)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = 1;
                }
            }
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return (0);
}