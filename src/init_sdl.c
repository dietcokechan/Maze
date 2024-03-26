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

/**
 * poll_events - sdl events
 * @player: player struct
 * Return: 0 or 1
 */
int poll_events(Player *player)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				player->rect.x += (player->deltaX * SPEED);
				player->rect.y += (player->deltaY * SPEED);
				break;
			case SDLK_s:
				player->rect.x -= (player->deltaX * SPEED);
				player->rect.y -= (player->deltaY * SPEED);
				break;
			case SDLK_a:
				player->angle += 5;
				player->angle = fix_angle(player->angle);
				player->deltaX = cos(RAD(player->angle));
				player->deltaY = -sin(RAD(player->angle));
				break;
			case SDLK_d:
				player->angle -= 5;
				player->angle = fix_angle(player->angle);
				player->deltaX = cos(RAD(player->angle));
				player->deltaY = -sin(RAD(player->angle));
				break;
			case SDLK_ESCAPE:
				return (1);
			default:
				break;
			}
		}
		else if (e.type == SDL_QUIT)
			return (1);
	}
	return (0);
}
