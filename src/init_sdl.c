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

	/* Set the logical size of the rendering area */
	SDL_RenderSetLogicalSize(instance->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	/* Set the viewport to cover the entire window */
	SDL_Rect viewport = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	SDL_RenderSetViewport(instance->renderer, &viewport);

	return (0);
}

/**
 * poll_events - sdl events
 * @instance: sdl instance
 * @player: player struct
 * @map: map instance
 * Return: 0 or 1
 */
int poll_events(SDL_Instance *instance, Player *player, Map *map)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
					player->rect.x += (player->deltaX * 5);
					player->rect.y += (player->deltaY * 5);
				break;
			case SDLK_s:
					player->rect.x -= (player->deltaX * 5);
					player->rect.y -= (player->deltaY * 5);
				break;
			case SDLK_a:
				player->angle += 2;
				player->angle = fix_angle(player->angle);
				player->deltaX = cos(degToRad(player->angle));
				player->deltaY = -sin(degToRad(player->angle));
				break;
			case SDLK_d:
				player->angle -= 2;
				player->angle = fix_angle(player->angle);
				player->deltaX = cos(degToRad(player->angle));
				player->deltaY = -sin(degToRad(player->angle));
				break;
			case SDLK_m:
				instance->minimap = !instance->minimap;
			default:
				break;
			}
			SDL_RenderPresent(instance->renderer);
		}
		else if (e.type == SDL_QUIT)
			return (1);
	}
	return (0);
}

/**
 * close_sdl - close sdl safely
 * @instance: sdl instance
 */
void close_sdl(SDL_Instance *instance)
{
	if (instance->renderer)
		SDL_DestroyRenderer(instance->renderer);
	if (instance->window)
		SDL_DestroyWindow(instance->window);

	instance->window = NULL;
	instance->renderer = NULL;

	SDL_Quit();
}
