#include "../inc/maze.h"

void load_textures(SDL_Instance *instance)
{
	SDL_Surface *surface = IMG_Load("resources/images/tile01.jpg");
	
	if (surface == NULL)
	{
		printf("Unable to load image! SDL_image Error: %s", IMG_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	instance->wallTex = SDL_CreateTextureFromSurface(instance->renderer, surface);
	SDL_FreeSurface(surface);
}

void render_textures(SDL_Instance *instance, SDL_Rect *dest)
{
	SDL_RenderCopy(instance->renderer, instance->wallTex, NULL, dest);
}