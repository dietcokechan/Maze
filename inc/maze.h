#pragma once
#ifndef MAZE_H
#define MAZE_H

/*standard io*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*sdl*/
#include <SDL.h>

/*macros*/
#define TITLE "SDL"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TRUE 1
#define FALSE 0

/*structs*/
typedef struct instance
{
    SDL_Window *window;
    SDL_Surface *win_surface;
} instance;

/*functions*/
void create_window(char* title, instance* sdl_ins);
void window_perm();
void destroy_window(instance* sdl_ins);

#endif /* MAZE_H */