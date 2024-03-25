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
	Player player;
	Map map = {8, 8, 64, {
		1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,1,
		1,0,1,1,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1
	}};
	player.rect.x = SCREEN_WIDTH / 4;
	player.rect.y = SCREEN_HEIGHT / 2;
	player.rect.h = player.rect.w = 12;


	if (init_instance(&instance) != 0) return (1);

	while (poll_events(&player) != 1)
	{
		SDL_GetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		// if (poll_events(&player) == 1)
		// 	break;
		poll_events(&player);
		draw_player(&player, &instance);
		draw_map(&map, &instance);
		SDL_SetRenderDrawColor(instance.renderer, 0x80, 0x80, 0x80, 0x80);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
