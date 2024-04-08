#include "../inc/maze.h"

/**
 * render_textures - render textures
 * @instance: sdl instance
 * @dest: destination rect
 */
void render_textures(SDL_Instance *instance, SDL_Rect *dest, int i)
{
	SDL_Color color = {0, 0, 0, 255};
	for (int j = 0; j < 8; j++)
	{
		Uint8 c = (i ^ j) * 8;
		color = (SDL_Color){c + j, c, c, 255};
		if (instance->side == 0)
			SDL_SetRenderDrawColor(instance->renderer, color.r, color.g, color.b, color.a);
		else
			SDL_SetRenderDrawColor(instance->renderer, color.r / 2, color.g / 2, color.b / 2, color.a);
	}
	SDL_RenderFillRect(instance->renderer, dest);
}
