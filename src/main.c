#include "../inc/maze.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 * Return: 0
 */
int main(int argc, char **argv)
{
	SDL_Instance instance = {NULL, NULL};
	Player player = {
		{
			150,
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

	player.deltaX = cos(deg_rad(player.angle));
	player.deltaY = -sin(deg_rad(player.angle));

	if (init_instance(&instance) != 0)
		return (1);

	while (poll_events(&instance, &player) != 1)
	{
		SDL_GetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		poll_events(&instance, &player);
		draw_map(&map, &instance);
		draw_rays(&instance, &player, &map);
		draw_player(&player, &instance);
		SDL_SetRenderDrawColor(instance.renderer, 0x90, 0x90, 0x90, 0xFF);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
