#include "../inc/maze.h"

/**
 * fix_angle - clamp angle
 * @x: angle
 * Return: fixed angle
 */
int fix_angle(int x)
{
	if (x > 360)
		x -= 360;
	if (x <= 0)
		x += 360;
	return (x);
}