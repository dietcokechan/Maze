#include "../inc/maze.h"

/**
 * draw_player - draws rect for player and line for direction
 * @player: player struct
 * @instance: sdl instance
 */
void draw_player(Player *player, SDL_Instance *instance)
{
	SDL_SetRenderDrawColor(instance->renderer, 0x80, 0x20, 0X80, 0xFF);
	SDL_RenderFillRect(instance->renderer, &player->rect);
	SDL_RenderDrawPoint(instance->renderer, player->rect.x, player->rect.y);
	SDL_RenderDrawLine(instance->renderer, player->rect.x + 6, player->rect.y + 6,
	 player->rect.x + player->deltaX * 20,
	 player->rect.y + player->deltaY * 20);
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
			if (map->map[y * map->x + x] == 1)
				SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			else
				SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_Rect rect = {
				x * map->size + 1,
				y * map->size + 1,
				map->size - 2,
				map->size - 2
			};
			SDL_RenderFillRect(instance->renderer, &rect);
		}
	}
}

/**
 * draw_rays - drawing rays on map
 * @player: player struct
 * @map: map struct
 */
void draw_rays(SDL_Instance *instance, Player *player, Map *map)
{
	SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x40, 0x80, 0xFF);
	SDL_Rect rect1 = {512, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
	SDL_RenderFillRect(instance->renderer, &rect1);

	SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x10, 0x80, 0xFF);
	SDL_Rect rect2 = {512, 160, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderFillRect(instance->renderer, &rect2);

	int ray, depth, wallX, wallY, mapPos, side;
	float rAng, rX, rY, vX, vY, offsetX, offsetY, distV, distH;

	rAng = fix_angle(player->angle + 30);

	for (ray = 0; ray < FOV; ray++)
	{
		/*checks vertical lines*/
		depth = 0;
		side = 0;
		distV = 1000000;
		float angTan = tan(deg_rad(rAng));

		/*check if looking left or right*/
		if (cos(deg_rad(rAng)) > 0.001)
		{
			rX = (((int)player->rect.x >> 6) << 6) + 64;
			rY = (player->rect.x - rX) * angTan + player->rect.y;
			offsetX = 64;
			offsetY = -offsetX * angTan;
		}
		else if (cos(deg_rad(rAng)) < -0.001)
		{
			rX = (((int)player->rect.x >> 6) << 6) - 0.0001;
			rY = (player->rect.x - rX) * angTan + player->rect.y;
			offsetX = -64;
			offsetY = -offsetX * angTan;
		}
		else
		{
			rX = player->rect.x;
			rY = player->rect.y;
			depth = 8;
		}

		while (depth < 8)
		{
			wallX = (int)(rX) >> 6;
			wallY = (int)(rY) >> 6;
			mapPos = wallY * map->x + wallX;
			if (mapPos > 0 && mapPos < map->size && map->map[mapPos] == 1)
			{
				depth = 8;
				distV = cos(deg_rad(rAng)) * (rX - player->rect.x)
						 - sin(deg_rad(rAng)) * (rY, player->rect.y);
			}
			else
			{
				rX += offsetX;
				rY += offsetY;
				depth += 1;
			}
		}
		vX = rX;
		vY = rY;

		/*checking horizontal lines*/
		depth = 0;
		distH = 1000000;
		angTan = 1.0 / angTan;

		/*check if looking up or down*/
		if(sin(deg_rad(rAng)) > 0.001)
		{
			rY = (((int)player->rect.y >> 6) << 6) - 0.0001;
			rX = (player->rect.y - rY) * angTan + player->rect.x;
			offsetY = -64;
			offsetX = -offsetY * angTan;
		}
		else if (sin(deg_rad(rAng)) < -0.001)
		{
			rY = (((int)player->rect.y >> 6) << 6) + 64;
			rX = (player->rect.y - rY) * angTan + player->rect.x;
			offsetY = 64;
			offsetX = -offsetY * angTan;
		}
		else
		{
			rX = player->rect.x;
			rY = player->rect.y;
			depth = 8;
		}

		while (depth < 8)
		{
			wallX = (int)(rX) >> 6;
			wallY = (int)(rY) >> 6;
			mapPos = wallY * map->x + wallX;
			if (mapPos > 0 && mapPos < map->size && map->map[mapPos] == 1)
			{
				depth = 8;
				distH = cos(deg_rad(rAng)) * (rX - player->rect.x)
						 - sin(deg_rad(rAng)) * (rY, player->rect.y);
			}
			else
			{
				rX += offsetX;
				rY += offsetY;
				depth += 1;
			}
		}

		SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x80, 0x00, 0xFF);

		if (distV < distH)
		{
			rX = vX;
			rY = vY;
			distH = distV;
		}
		SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x60, 0x00, 0xFF);
		SDL_RenderDrawLine(instance->renderer, player->rect.x + 6, player->rect.y + 6, rX, rY);

		int cAng = fix_angle(player->angle - rAng);
		distH = distH * cos(deg_rad(cAng));

		int line_height = (int)(SCREEN_HEIGHT / distH);

		int lineOff = 160 - (line_height >> 1);

		// int drawStart = -line_height / 2 + SCREEN_HEIGHT / 2;
		// if (drawStart < 0)
		// 	drawStart = 0;
		// int drawEnd = line_height / 2 + SCREEN_HEIGHT / 2;
		// if (drawEnd >= SCREEN_HEIGHT)
		// 	drawEnd = SCREEN_HEIGHT - 1;

		SDL_RenderDrawLine(instance->renderer, ray + 530, lineOff,
							ray + 530, lineOff + line_height);

		rAng = fix_angle(rAng - 0.5);
	}
}
