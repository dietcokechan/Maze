#include "../inc/maze.h"

/**
 * init_instance - initialize sdl instance
 * @instance: sdl instance
 * Return: 0 or 1
 */
int init_instance(SDL_Instance *instance)
{
	/* initialize */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	/* create a new window instance */
	instance->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,
		 SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/* create a new renderer instance linked to window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
		 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}

int poll_events()
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				return (1);
			case SDL_KEYDOWN:
				key = event.key;
				if(key.keysym.scancode == 0x29)
					return (1);
				break;
		}
	}
	return (0);
}