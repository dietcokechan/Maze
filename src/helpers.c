#include "../inc/maze.h"

int fix_angle(int x)
{
	if (x > 359)
		x -= 360;
	if (x < 0)
		x += 360;
	return (x);
}
