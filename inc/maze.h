#ifndef _MAZE_H_
#define _MAZE_H_

/*STANDARD IO*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*SDL*/
#include <SDL.h>

/*HEADER FILES*/
#include "structures.h"
#include "macros.h"

/*FUNCTIONS*/

/*init_sdl.c*/
int init_instance(SDL_Instance *);
int poll_events(SDL_Instance *, Player *, Map *);
void close_sdl(SDL_Instance *instance);

/*raycast.c*/
void calculate_vertical_rays(Player *player, Map *map, float rA,
	 SDL_Instance *instance, float *distV, float *vX, float *vY);
void calculate_horizontal_rays(Player *player, Map *map, float rA,
	 SDL_Instance *instance, float *distH, float *hX, float *hY);

/*display.c*/
void draw_player(Player *, SDL_Instance *);
void draw_map(Map *, SDL_Instance *);
void draw_background(SDL_Instance *instance);
void draw_rays(SDL_Instance *, Player *, Map *);
void draw_3D_walls(SDL_Instance *instance, Player *player, float rA,
	 Map *map, float distH, int r);
void raycast(Player *player, SDL_Instance *instance, Map *map);

	/*helpers.c*/
	int fix_angle(int);
float degToRad(float);

/*file_handling.c*/
void close_file(FILE *fp);
FILE *open_file(char *filename);
Map read_file(FILE *fp);
Map handle_file(char *filename);

/*parser.c*/
char *concat(const char *s1, const char *s2);
void free_map(Map *map);

#endif /* _MAZE_H_ */
