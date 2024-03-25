#include "../inc/maze.h"

void draw_player(Player *player, SDL_Instance *instance)
{
	// int x = SCREEN_WIDTH/4;
	// int y = SCREEN_HEIGHT/4;
	// int size = 12;

	// player->rect.h = player->rect.w = size;
	// player->rect.x = x;
	// player->rect.y = y;

	SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(instance->renderer, &player->rect);
	SDL_RenderFillRect(instance->renderer, &player->rect);
}
