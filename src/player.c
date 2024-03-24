#include "../inc/maze.h"

void draw_player(SDL_Instance *instance)
{
    int x = SCREEN_WIDTH/4;
    int y = SCREEN_HEIGHT/4;
    int size = 12;
    SDL_Rect player;

    player.h = player.w = size;
    player.x = x;
    player.y = y;

    SDL_SetRenderDrawColor(instance->renderer, 0x00, 0x00, 0x00, 0xFF);
    // SDL_RenderDrawPoint(instance->renderer, x, y);
    SDL_RenderDrawRect(instance->renderer, &player);
    SDL_RenderFillRect(instance->renderer, &player);
    SDL_SetRenderDrawColor(instance->renderer, 0x80, 0x80, 0x80, 0x80);
}