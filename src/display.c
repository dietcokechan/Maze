#include "../inc/maze.h"

/**
 * draw_player - draws rect for player and line for direction
 * @player: player struct
 * @instance: sdl instance
 */
void draw_player(Player *player, SDL_Instance *instance)
{
	SDL_SetRenderDrawColor(instance->renderer, 0x80, 0x80, 0X20, 200);
	SDL_RenderFillRect(instance->renderer, &player->rect);
}

/**
 * draw_map - draws minimap
 * @map: map struct
 * @instance: sdl instance
 */
void draw_map(Map *map, SDL_Instance *instance)
{
	int x, y;

	for (y = 0; y < map->y; y++)
	{
		for (x = 0; x < map->x; x++)
		{
			if (map->map[y * map->x + x] >= 1)
				SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0xFF, 0xFF, 200);
			else
				SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x00, 0x00, 200);
			SDL_Rect rect = {
				x * map->size + 1,
				y * map->size + 1,
				map->x * map->x - 2,
				map->y * map->y - 2
			};
			SDL_RenderFillRect(instance->renderer, &rect);
		}
	}
}

/**
 * draw_decoration - draws any decoration
 * @instance: sdl instance
 */
void draw_decoration(SDL_Instance *instance)
{
	SDL_SetRenderDrawColor(instance->renderer, 0x20, 0x40, 0x60, 0xFF);
	SDL_Rect rect1 = {MINIMAP_W, 0, MINIMAP_W, MINIMAP_H};
	
	SDL_RenderFillRect(instance->renderer, &rect1);

	SDL_SetRenderDrawColor(instance->renderer, 0x20, 0x20, 0x20, 0xFF);
	SDL_Rect rect2 = {MINIMAP_W, MINIMAP_H, MINIMAP_W, MINIMAP_H};

	SDL_RenderFillRect(instance->renderer, &rect2);

	for (int i = 0; i < 34; i++)
	{
		SDL_Point points[5] = {
			{i, i},
			{SCREEN_WIDTH - i, i},
			{SCREEN_WIDTH - i, SCREEN_HEIGHT - i},
			{i, SCREEN_HEIGHT - i},
			{i, i}
		};

		SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
		SDL_RenderDrawLines(instance->renderer, points, 5);
	}
}

/**
 * draw_rays - drawing rays on map
 * @instance: sdl instance
 * @player: player struct
 * @map: map struct
 */
void draw_rays(SDL_Instance *instance, Player *player, float rX, float rY)
{
	SDL_SetRenderDrawColor(instance->renderer, 0, 255, 0, 200);
	SDL_RenderDrawLine(instance->renderer,
							player->rect.x + 5, player->rect.y + 5, rX, rY);
}

/**
 * draw_3D_walls - draw 3D scene
 * 
 * @instance: sdl instance
 * @player: player instance
 * @rA: ray angle
 * @map: map instance
 * @distH: delta distance
 * @r: ray
 */
void draw_3D_walls(SDL_Instance *instance, Player *player,
				 float rA, Map *map, float distH, int r)
{
	int i;
	int ca = fix_angle(player->angle - rA);

	distH = distH * cos(degToRad(ca)); /* fix fisheye */
	int line_height = (map->size * SCREEN_HEIGHT - 56) / (int)distH;

	if (line_height > SCREEN_HEIGHT - 56)
	{
		line_height = SCREEN_HEIGHT - 56;
	} /* line height and limit */
	int lineOff = MINIMAP_H - (line_height >> 1); /* line offset */
	
	/* draw 3D scene */
	for (i = 0; i < 8; i++)
	{
		SDL_Rect dest = {r * 8 + i + MINIMAP_W, lineOff, 1, line_height};
		render_textures(instance, &dest, i);
	}
}
