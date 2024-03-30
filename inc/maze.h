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
#define SCREEN_HEIGHT 510
#define FOV 60
#define MINIMAP_W SCREEN_WIDTH / 2
#define MINIMAP_H SCREEN_HEIGHT / 2

/*structs*/
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	int minimap;
	int hit;
} SDL_Instance;

typedef struct Player
{
	SDL_Rect rect;
	float angle;
	float deltaX;
	float deltaY;
} Player;

typedef struct Map
{
	int x;
	int y;
	int size;
	int map[];
} Map;

/*functions start*/
int init_instance(SDL_Instance *);
int poll_events(SDL_Instance *, Player *, Map *);

void draw_player(Player *, SDL_Instance *);
void draw_map(Map *, SDL_Instance *);
void draw_rays(SDL_Instance *, Player *, Map *);

int fix_angle(int);
float degToRad(float);
/*functions end*/

#endif /* MAZE_H */
