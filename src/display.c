#include "../inc/maze.h"

/**
 * draw_player - draws rect for player and line for direction
 * @player: player struct
 * @instance: sdl instance
 */
void draw_player(Player *player, SDL_Instance *instance)
{
	SDL_SetRenderDrawColor(instance->renderer, 0x80, 0x80, 0X20, 0xFF);
	SDL_RenderFillRect(instance->renderer, &player->rect);
	// SDL_RenderDrawPoint(instance->renderer, player->rect.x, player->rect.y);
	// SDL_RenderDrawLine(instance->renderer, player->rect.x + 5,
	//  player->rect.y + 5,
	//  player->rect.x + player->deltaX * 20,
	//  player->rect.y + player->deltaY * 20);
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
				SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0xFF, 0xFF, 0x90);
			else
				SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x00, 0x00, 0x90);
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
	SDL_SetRenderDrawColor(instance->renderer, 0x40, 0x60, 0x90, 0xFF);
	SDL_Rect rect1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	
	SDL_RenderFillRect(instance->renderer, &rect1);

	SDL_SetRenderDrawColor(instance->renderer, 0x20, 0x60, 0x40, 0xFF);
	SDL_Rect rect2 = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT};

	SDL_RenderFillRect(instance->renderer, &rect2);

	for (int i = 0; i < 16; i++)
	{
		SDL_Point points[5] = {
			{i, i},
			{SCREEN_WIDTH - i, i},
			{SCREEN_WIDTH - i, SCREEN_HEIGHT - i},
			{i, SCREEN_HEIGHT - i},
			{i, i}
		};

		SDL_SetRenderDrawColor(instance->renderer, 155, 155, 155, 255);
		SDL_RenderDrawLines(instance->renderer, points, 5);
	}
}

/**
 * draw_rays - drawing rays on map
 * @instance: sdl instance
 * @player: player struct
 * @map: map struct
 */
void draw_rays(SDL_Instance *instance, Player *player, Map *map)
{
	int r;
	float rA, rX, rY, vX, vY, hX, hY, distV, distH;

	rA = fix_angle(player->angle + 30);

	for (r = 0; r < FOV; r++)
	{
		rX = player->rect.x;
		rY = player->rect.y;

		calculate_vertical_rays(player, map, rA, instance, &distV, &vX, &vY);
		calculate_horizontal_rays(player, map, rA, instance, &distH, &hX, &hY);

		if (distV < distH)
		{
			rX = vX;
			rY = vY;
			distH = distV;
		} /* horizontal hit first */
		else
		{
			rX = hX;
			rY = hY;
			distH = distH;
		}

		/* draw 2D ray */
		if (instance->minimap)
		{
			SDL_SetRenderDrawColor(instance->renderer, 0, 255, 0, 255);
			SDL_RenderDrawLine(instance->renderer,
							   player->rect.x + 5, player->rect.y + 5, rX, rY);
		}
		
		rA = fix_angle(rA - 1);
	}
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
	int line_height = (map->size * 320) / (int)distH;

	if (line_height > 320)
	{
		line_height = 320;
	} /* line height and limit */

	int drawStart = -line_height / 2 + SCREEN_HEIGHT / 2;
	int drawEnd = line_height / 2 + SCREEN_HEIGHT / 2;

	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT;

	/* draw 3D scene */
	for (i = 0; i < 8; i++)
	{
		// SDL_RenderDrawLine(instance->renderer,
		// 					r * 8 + i + 16, i + drawStart, r * 8 + i + 16, drawEnd);

		SDL_Rect wallRect = {
			(int)(r * 8 + i + 16),
			drawStart,
			1,
			drawEnd - drawStart
		};
		SDL_RenderFillRect(instance->renderer, &wallRect);
	}
}
