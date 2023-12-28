#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "factory.h"

typedef struct {
    SDL_Texture *buttonTexture[3];
    SDL_Texture *titleTexture;
    SDL_Texture *cardTextures[12];
    Card *deck_cards;
    SDL_Rect buttons[3];
    SDL_Rect cards[12];
    SDL_Rect titleRect;
} Environment;

Environment *initEnvironment(SDL_Window *window, SDL_Renderer *renderer);

#endif
