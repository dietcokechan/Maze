#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include <SDL.h>

/**
 * struct SDL_Instance - sdl global variables
 * @window: sdl window
 * @renderer: sdl renderer
 * @minimap: to check if minimap active
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	int minimap;
} SDL_Instance;

/**
 * struct Player - player data
 * @rect: player position and display
 * @angle: player angle
 * @deltaX: direction in x axis
 * @deltaY: direction in y axis
 */
typedef struct Player
{
	SDL_Rect rect;
	float angle;
	float deltaX;
	float deltaY;
	float rayX;
	float rayY;
} Player;

/**
 * struct Map - map data
 * @x: rows count
 * @y: columns count
 * @size: map size
 * @map: map array
 */
typedef struct Map
{
	int x;
	int y;
	int size;
	int *map;
} Map;

#endif
