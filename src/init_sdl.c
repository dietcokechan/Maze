#include "../inc/maze.h"

void create_window(char* title, instance* sdl_ins)
{
    sdl_ins->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (sdl_ins->window == NULL)
    {
        printf("Window could not be created! SDl_Error: %s\n", SDL_GetError());
    }
    else
    {
        // get window surface
        sdl_ins->win_surface = SDL_GetWindowSurface(sdl_ins->window);
        // fill the surface white
        SDL_FillRect(sdl_ins->win_surface, NULL, SDL_MapRGB(sdl_ins->win_surface->format, 0xFF, 0xFF, 0xFF));
        // update the surface
        SDL_UpdateWindowSurface(sdl_ins->window);

        window_perm();
    }
}

void window_perm()
{
    // get window to stay up
    SDL_Event e;
    int quit = FALSE;
    while (quit == FALSE)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = TRUE;
        }
    }
}

void destroy_window(instance* sdl_ins)
{
    // destroy window
    SDL_DestroyWindow(sdl_ins->window);
    // quit SDL subsystems
    SDL_Quit();
}