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
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/*functions*/
int init_instance(SDL_Instance *);
int poll_events();

#endif /* MAZE_H */
