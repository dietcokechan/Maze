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
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 512
#define TRUE 1
#define FALSE 0

/*structs*/
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

typedef struct Player
{
	SDL_Rect rect;
	float angle;
} Player;

/*functions*/
int init_instance(SDL_Instance *);
int poll_events(Player *);
void draw_player(Player *, SDL_Instance *);

#endif /* MAZE_H */
