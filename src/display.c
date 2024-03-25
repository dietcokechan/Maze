#include "../inc/maze.h"

void draw_player(Player *player, SDL_Instance *instance)
{
	SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(instance->renderer, &player->rect);
	SDL_RenderFillRect(instance->renderer, &player->rect);
}

void draw_map(Map *map, SDL_Instance *instance)
{
	int x, y;
	SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x00, 0x00, 0xFF);

	for (y = 0; y < map->y; y++)
	{
		for (x = 0; x < map->x; x++)
		{
			if (map->map[y * map->x + x] == 1)
			{
				SDL_Rect rect = {
					x * map->size,
					y * map->size,
					map->size,
					map->size
				};
				SDL_RenderFillRect(instance->renderer, &rect);
			}
		}
	}
}