#ifndef _MAZE_H_
#define _MAZE_H_

/*STANDARD IO*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*SDL*/
#include <SDL.h>
// #include <SDL_image.h>

/*HEADER FILES*/
#include "structures.h"
#include "macros.h"

/*FUNCTIONS*/

/*init_sdl.c*/
int init_instance(SDL_Instance *);
int poll_events(SDL_Instance *, Player *, Map *);
void close_sdl(SDL_Instance *);

/*raycast.c*/
void calculate_vertical_rays(Player *, Map *, float rA,
	 float *distV, float *vX, float *vY);
void calculate_horizontal_rays(Player *, Map *, float rA,
	 float *distH, float *hX, float *hY);
void raycast(Player *, SDL_Instance *, Map *map);

/*display.c*/
void draw_player(Player *, SDL_Instance *);
void draw_map(Map *, SDL_Instance *);
void draw_decoration(SDL_Instance *);
void draw_rays(SDL_Instance *, Player *, float rX, float rY);
void draw_3D_walls(SDL_Instance *, Player *, float rA,
	 Map *, float distH, int r);

/*textures.c*/
void render_textures(SDL_Instance *instance, SDL_Rect *dest, int i);

/*helpers.c*/
int fix_angle(float);
float degToRad(float);

/*file_handling.c*/
void close_file(FILE *);
FILE *open_file(char *filename);
Map read_file(FILE *);
Map handle_file(char *filename);

/*parser.c*/
char *concat(const char *s1, const char *s2);
void free_map(Map *);

#endif /* _MAZE_H_ */
