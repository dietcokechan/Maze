#include "../inc/maze.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 * Return: 0
 */
int main(int argc, char **argv)
{
	char *map_path;
	SDL_Instance instance = {NULL, NULL, 0};
	Player player = {{200, 400, 12, 12}, 90.0, 0.0, 0.0};
	Map map = {0, 0, 0, NULL};

	player.deltaX = cos(degToRad(player.angle));
	player.deltaY = -sin(degToRad(player.angle));

	// if (argc < 2)
	// {
	// 	printf("Usage: %s 'map_path'", argv[0]);
	// 	exit(EXIT_FAILURE);
	// }
	// map_path = concat("../resources/maps", argv[1]);

	map_path = "../../resources/maps/def";
	map = handle_file(map_path);

	if (init_instance(&instance) != 0)
		return (1);

	while (poll_events(&instance, &player, &map) != 1)
	{
		SDL_GetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);

		poll_events(&instance, &player, &map);
		draw_background(&instance);
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
	free_map(&map);
	close_sdl(&instance);
	return (0);
}
