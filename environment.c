#include "environment.h"
#include "factory.h"

#define BUTTON_SAVE_IMAGE "textures/button_save.png"
#define BUTTON_LOAD_IMAGE "textures/button_load.png"
#define BUTTON_NEW_IMAGE "textures/button_new.png"
#define TITLE_IMAGE "textures/title.png"

Environment *initEnvironment(SDL_Window *window, SDL_Renderer *renderer) { // Environment should contain all of our items that are rendered like buttons, cards, titles etc.
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    
    Environment *environment = malloc(sizeof(Environment));
    
    environment->deck_cards = cardsCreation(window, renderer); // Getting all of our cards

    // Load button texture
    environment->buttonTexture[0] = IMG_LoadTexture(renderer, BUTTON_SAVE_IMAGE);
    check_if_error(!environment->buttonTexture[0], "Error loading button save texture");
    environment->buttonTexture[1] = IMG_LoadTexture(renderer, BUTTON_LOAD_IMAGE);
    check_if_error(!environment->buttonTexture[1], "Error loading button load texture");
    environment->buttonTexture[2] = IMG_LoadTexture(renderer, BUTTON_NEW_IMAGE);
    check_if_error(!environment->buttonTexture[2], "Error loading button new texture");

    // Load card textures
    for (int i = 0; i < 12; i++) {
        environment->cardTextures[i] = IMG_LoadTexture(renderer, environment->deck_cards[i].imagePath);
        check_if_error(!environment->cardTextures[i], "Error loading card texture");
    }

    // Load title texture
    environment->titleTexture = IMG_LoadTexture(renderer, TITLE_IMAGE);
    check_if_error(!environment->titleTexture, "Error loading title texture");

    // Defining all positions and size of our items in environment.
    int buttonsWidth = w / 12;
    int buttonsHeight = h / 12;
    for (int i = 0; i < 3; i++) {
        environment->buttons[i].w = buttonsWidth;
        environment->buttons[i].h = buttonsHeight;
        environment->buttons[i].x = (w - environment->buttons[i].w) / 2;
        environment->buttons[i].y = i * (buttonsHeight+buttonsHeight/3) + (h/3);
    }

    int cardWidth = w / 12;
    int cardHeight = h / 4;
    for (int i = 0; i < 12; i++) {
        environment->cards[i].w = cardWidth;
        environment->cards[i].h = cardHeight;
        environment->cards[i].x = i * cardWidth;
        environment->cards[i].y = h - cardHeight - 20;
    }

    environment->titleRect.w = 300;
    environment->titleRect.h = 50;
    environment->titleRect.x = (w - environment->titleRect.w) / 2;
    environment->titleRect.y = 10;

    return environment;
}