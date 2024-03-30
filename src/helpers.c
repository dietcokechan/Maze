#include "../inc/maze.h"

/**
 * fix_angle - clamp angle
 * @x: angle
 * Return: fixed angle
 */
int fix_angle(int x)
{
	if (x > 359)
		x -= 360;
	if (x < 0)
		x += 360;
	return (x);
}

float degToRad(float x)
{
	return x * (M_PI / 180.0);
}