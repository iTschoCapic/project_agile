#include <SDL2/SDL.h>
#ifndef FACTORY_H
#define FACTORY_H

typedef struct {
    char name[32];
    char imagePath[48];
} Card;

Card* createCard(const char* name, const char* imagePath);
void initializeSpecificCards(Card* cards);
Card *cardsCreation(SDL_Window *window, SDL_Renderer *renderer);

#endif
