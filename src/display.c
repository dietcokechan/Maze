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
void draw_rays(SDL_Instance *instance,Player *player, Map *map)
{
	int ray, depth, pX, pY, wallX, wallY, mapPos;
	float rAng, rX, rY, vX, vY, offsetX, offsetY, distV, distH;

	rAng = fix_angle(player->angle + 30);
	pX = player->rect.x;
	pY = player->rect.y;

	for (ray = 0; ray < FOV; ray++)
	{
		/*checks vertical lines*/
		depth = 0;
		distV = 100000;
		float angTan = tan(RAD(rAng));

		/*check if looking left or right*/
		if (cos(RAD(rAng)) > 0.001)
		{
			rX = (((int)pY >> 6) << 6) + 64;
			rY = (pX - rX) * angTan + pY;
			offsetX = 64;
			offsetY = -offsetX * angTan;
		}
		else if (cos(RAD(rAng)) < -0.001)
		{
			rX = (((int)pY >> 6) << 6) - 0.0001;
			rY = (pX - rX) * angTan + pY;
			offsetX = -64;
			offsetY = -offsetX * angTan;
		}
		else
		{
			rX = pX;
			rY = pY;
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
				distV = cos(RAD(rAng)) * (rX - pX)
						 - sin(RAD(rAng)) * (rY, pY);
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
		distH = 100000;
		angTan = 1.0 / angTan;

		/*check if looking up or down*/
		if(sin(RAD(rAng)) > 0.001)
		{
			rY = (((int)pY >> 6) << 6) - 0.0001;
			rX = (pY - rY) * angTan + pX;
			offsetY = -64;
			offsetX = -offsetY * angTan;
		}
		else if (sin(RAD(rAng)) < -0.001)
		{
			rY = (((int)pY >> 6) << 6) + 64;
			rX = (pY - rY) * angTan + pX;
			offsetY = 64;
			offsetX = -offsetY * angTan;
		}
		else
		{
			rX = pX;
			rY = pY;
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
				distH = cos(RAD(rAng)) * (rX - pX)
						 - sin(RAD(rAng)) * (rY, pY);
			}
			else
			{
				rX += offsetX;
				rY += offsetY;
				depth += 1;
			}
		}

		SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x00, 0x80, 0xFF);

		if (distV < distH)
		{
			rX = vX;
			rY = vY;
			distH = distV;
			SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x00, 0xFF, 0xFF);
		}
		SDL_RenderDrawLine(instance->renderer, pX, pY, rX, rY);

		int cAng = fix_angle(player->angle - rAng);
		distH = distH * cos(RAD(cAng));
		int line_height = (map->size * 320) / (distH);
		if (line_height > 320)
			line_height = 320;
		int offsetL = 160 - (line_height >> 1);
		SDL_RenderDrawLine(instance->renderer, ray * 8 + 530,
						   offsetL,
						   ray * 8 + 530,
						   offsetL + line_height);

		rAng = fix_angle(rAng - 1);
	}
}
