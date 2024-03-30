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
				SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0xFF, 0xFF, 0x60);
			else
				SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x00, 0x00, 0x60);
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
	SDL_SetRenderDrawColor(instance->renderer, 0x40, 0x60, 0x90, 0xFF);
	SDL_Rect rect1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderFillRect(instance->renderer, &rect1);

	SDL_SetRenderDrawColor(instance->renderer, 0x20, 0x60, 0x40, 0xFF);
	SDL_Rect rect2 = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderFillRect(instance->renderer, &rect2);

	int r, depth, mX, mY, mPos, side;
	float rA, rX, rY, vX, vY, xOffset, yOffset, distV, distH;

	rA = fix_angle(player->angle + 30);

	for (r = 0; r < FOV; r++)
	{
		// Vertical
		depth = 0;
		side = 0;
		distV = 100000;
		float aTan = tan(degToRad(rA));
		if (cos(degToRad(rA)) > 0.001)
		{
			rX = (((int)player->rect.x >> 6) << 6) + 64;
			rY = (player->rect.x - rX) * aTan + player->rect.y;
			xOffset = 64;
			yOffset = -xOffset * aTan;
		} // looking left
		else if (cos(degToRad(rA)) < -0.001)
		{
			rX = (((int)player->rect.x >> 6) << 6) - 0.0001;
			rY = (player->rect.x - rX) * aTan + player->rect.y;
			xOffset = -64;
			yOffset = -xOffset * aTan;
		} // looking right
		else
		{
			rX = player->rect.x;
			rY = player->rect.y;
			depth = 8;
		} // looking up or down. no hit

		while (depth < 8)
		{
			mX = (int)(rX) >> 6;
			mY = (int)(rY) >> 6;
			mPos = mY * map->x + mX;
			if (mPos > 0 && mPos < map->x * map->y && map->map[mPos] == 1)
			{
				depth = 8;
				distV = cos(degToRad(rA)) * (rX - player->rect.x) - sin(degToRad(rA)) * (rY - player->rect.y);
				instance->hit = 1;
			} // hit
			else
			{
				rX += xOffset;
				rY += yOffset;
				depth += 1;
			} // check next horizontal
			instance->hit = 0;
		}
		vX = rX;
		vY = rY;

		// Horizontal
		depth = 0;
		distH = 100000;
		aTan = 1.0 / aTan;
		if (sin(degToRad(rA)) > 0.001)
		{
			rY = (((int)player->rect.y >> 6) << 6) - 0.0001;
			rX = (player->rect.y - rY) * aTan + player->rect.x;
			yOffset = -64;
			xOffset = -yOffset * aTan;
		} // looking up
		else if (sin(degToRad(rA)) < -0.001)
		{
			rY = (((int)player->rect.y >> 6) << 6) + 64;
			rX = (player->rect.y - rY) * aTan + player->rect.x;
			yOffset = 64;
			xOffset = -yOffset * aTan;
		} // looking down
		else
		{
			rX = player->rect.x;
			rY = player->rect.y;
			depth = 8;
		} // looking straight left or right

		while (depth < 8)
		{
			mX = (int)(rX) >> 6;
			mY = (int)(rY) >> 6;
			mPos = mY * map->x + mX;
			if (mPos > 0 && mPos < map->x * map->y && map->map[mPos] == 1)
			{
				depth = 8;
				distH = cos(degToRad(rA)) * (rX - player->rect.x) - sin(degToRad(rA)) * (rY - player->rect.y);
				instance->hit = 1;
			} // hit
			else
			{
				rX += xOffset;
				rY += yOffset;
				depth += 1;
			} // check next horizontal
			instance->hit = 0;
		}

		SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x80, 0x00, 0xFF);

		if (distV < distH)
		{
			rX = vX;
			rY = vY;
			distH = distV;
			SDL_SetRenderDrawColor(instance->renderer, 0x80, 0x60, 0x80, 0xFF);
		} // horizontal hit first
		else
			SDL_SetRenderDrawColor(instance->renderer, 0x60, 0x40, 0x60, 0xFF);

		// draw 2D ray
		if (instance->minimap)
			SDL_RenderDrawLine(instance->renderer, player->rect.x + 6, player->rect.y + 6, rX, rY);

		int ca = fix_angle(player->angle - rA);
		distH = distH * cos(degToRad(ca)); // fix fisheye

		int line_height = map->size * SCREEN_HEIGHT / (int)distH;
		if (line_height > SCREEN_HEIGHT)
		{
			line_height = SCREEN_HEIGHT;
		} // line height and limit

		int drawStart = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = line_height / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		// draw 3D scene
		for (int i = 0; i < 8; i++)
		{
			SDL_RenderDrawLine(instance->renderer, r * 8 - i, drawStart, r * 8 - i, drawEnd);
		}

		rA = fix_angle(rA - 1);
	}
}
