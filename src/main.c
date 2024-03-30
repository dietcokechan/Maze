#include "../inc/maze.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 * Return: 0
 */
int main(int argc, char **argv)
{
	SDL_Instance instance = {NULL, NULL, 0, 0};
	Player player = {
		{
			240,
			400,
			12, 12
		},
		90.0, 0.0, 0.0
	};
	Map map = {8, 8, 64,
	 	{
			1, 1, 1, 1, 1, 1, 1, 1, 
			1, 0, 1, 0, 0, 0, 0, 1, 
			1, 0, 1, 1, 0, 0, 0, 1, 
			1, 0, 0, 0, 0, 0, 0, 1, 
			1, 0, 0, 0, 0, 0, 0, 1, 
			1, 0, 1, 0, 0, 1, 1, 1, 
			1, 0, 0, 0, 0, 0, 0, 1, 
			1, 1, 1, 1, 1, 1, 1, 1
		}
	};
	double time = 0;	// time of current frame
	double oldTime = 0; // time of previous frame

	player.deltaX = cos(degToRad(player.angle));
	player.deltaY = -sin(degToRad(player.angle));

	if (init_instance(&instance) != 0)
		return (1);

	while (poll_events(&instance, &player, &map) != 1)
	{
		SDL_GetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);

		// timing for input and fps counter
		oldTime = time;
		time = SDL_GetTicks();
		double frameTime = (time - oldTime) / 1000.0; // frameTime is the time this frame has taken in seconds

		poll_events(&instance, &player, &map);
		draw_rays(&instance, &player, &map);
		if (instance.minimap)
		{
			draw_map(&map, &instance);
			draw_player(&player, &instance);
		}
		SDL_SetRenderDrawColor(instance.renderer, 0x90, 0x90, 0x90, 0xFF);
		SDL_SetRenderDrawBlendMode(instance.renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
