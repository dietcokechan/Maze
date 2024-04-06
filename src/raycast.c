#include "../inc/maze.h"

/**
 * calculate_vertical_rays - check if a vertical wall is hit
 * @player: player instance
 * @map: map instance
 * @rA: ray angle
 * @instance: sdl instance
 * @distV: vertical distance
 * @vX: x of vertical ray
 * @vY: y of vertical ray
 */
void calculate_vertical_rays(Player *player, Map *map, float rA,
		 SDL_Instance *instance, float *distV, float *vX, float *vY)
{
	int depth, mX, mY, mPos;
	float rX, rY, xOffset, yOffset;

	depth = 0;
	*distV = 100000;
	double aTan = tan(degToRad(rA));

	if (cos(degToRad(rA)) > 0.001)
	{
		rX = (((int)player->rect.x >> 6) << 6) + 64;
		rY = (player->rect.x - rX) * aTan + player->rect.y;
		xOffset = 64;
		yOffset = -xOffset * aTan;
	} /* looking left */
	else if (cos(degToRad(rA)) < -0.001)
	{
		rX = (((int)player->rect.x >> 6) << 6) - 0.0001;
		rY = (player->rect.x - rX) * aTan + player->rect.y;
		xOffset = -64;
		yOffset = -xOffset * aTan;
	} /* looking right */
	else
	{
		rX = player->rect.x;
		rY = player->rect.y;
		depth = 8;
	} /* looking up or down. no hit */
	while (depth < 8)
	{
		mX = (int)(rX) >> 6;
		mY = (int)(rY) >> 6;
		mPos = mY * map->x + mX;
		if (mPos > 0 && mPos < map->x * map->y && map->map[mPos] == 1)
		{
			depth = 8;
			*distV = cos(degToRad(rA)) * (rX - player->rect.x)
					 - sin(degToRad(rA)) * (rY - player->rect.y);
		} /* hit */
		else
		{
			rX += xOffset;
			rY += yOffset;
			depth += 1;
		} /* check next horizontal */
	}
	*vX = rX;
	*vY = rY;
}

/**
 * calculate_horizontal_rays - check if a horizontal wall is hit
 * @player: player instance
 * @map: map instance
 * @rA: ray angle
 * @instance: sdl instance
 * @distH: horizontal distance
 * @hX: x of horizontal ray
 * @hY: y of horizontal ray
 */
void calculate_horizontal_rays(Player *player, Map *map, float rA,
		 SDL_Instance *instance, float *distH, float *hX, float *hY)
{
	int depth, mX, mY, mPos;
	float rX, rY, xOffset, yOffset;

	depth = 0;
	*distH = 100000;
	double aTan = tan(degToRad(rA));
	
	aTan = 1.0 / aTan;
	if (sin(degToRad(rA)) > 0.001)
	{
		rY = (((int)player->rect.y >> 6) << 6) - 0.0001;
		rX = (player->rect.y - rY) * aTan + player->rect.x;
		yOffset = -64;
		xOffset = -yOffset * aTan;
	} /* looking up */
	else if (sin(degToRad(rA)) < -0.001)
	{
		rY = (((int)player->rect.y >> 6) << 6) + 64;
		rX = (player->rect.y - rY) * aTan + player->rect.x;
		yOffset = 64;
		xOffset = -yOffset * aTan;
	} /* looking down */
	else
	{
		rX = player->rect.x;
		rY = player->rect.y;
		depth = 8;
	} /* looking straight left or right */
	while (depth < 8)
	{
		mX = (int)(rX) >> 6;
		mY = (int)(rY) >> 6;
		mPos = mY * map->x + mX;
		if (mPos > 0 && mPos < map->x * map->y && map->map[mPos] == 1)
		{
			depth = 8;
			*distH = cos(degToRad(rA)) * (rX - player->rect.x)
					 - sin(degToRad(rA)) * (rY - player->rect.y);
		} /* hit */
		else
		{
			rX += xOffset;
			rY += yOffset;
			depth += 1;
		} /* check next horizontal */
	}
	*hX = rX;
	*hY = rY;
}

/**
 * raycast - raycast algorithm
 * @player: player instance
 * @instance: sdl instance
 * @map: map instance
 */
void raycast(Player *player, SDL_Instance *instance, Map *map)
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
			instance->side = 1;
		} /* horizontal hit first */
		else
		{
			rX = hX;
			rY = hY;
			distH = distH;
			instance->side = 0;
		}

		draw_3D_walls(instance, player, rA, map, distH, r);

		/* draw 2D rays */
		// if (instance->minimap)
			draw_rays(instance, player, rX, rY);

		rA = fix_angle(rA - 1);
	}
}
