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
#define FOV 60
#define SPEED 2
#define RAD(x) (x * (M_PI / 180.0))

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

typedef struct Line
{
	SDL_Point p1;
	SDL_Point p2;
} Line;

/*functions start*/
int init_instance(SDL_Instance *);
int poll_events(Player *);

void draw_player(Player *, SDL_Instance *);
void draw_map(Map *, SDL_Instance *);

int fix_angle(int);
/*functions end*/

#endif /* MAZE_H */
