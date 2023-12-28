#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "factory.h"

// Factory function to create and initialize a Card
Card* createCard(const char* name, const char* imagePath) { // Create only one card
    Card* card = (Card *)malloc(sizeof(Card));
    check_if_error(!card, "Error: Memory card");
    strcpy(card->name, name);
    strcpy(card->imagePath, imagePath);
    return card;
}

// Factory function to initialize cards
void initializeSpecificCards(Card* cards) {
    printf("Initializing cards...\n");

    const char basePath[] = "resources/themes/base/";
    char finalPath[48] = {0};

    // Define name, and image names for each specific card
    const char* cardNames[] = {"0", "1", "2", "3", "5", "8", "13", "20", "40", "100", "Cafe", "Interro"};
    const char* imageNames[] = {"cartes_0.png", "cartes_1.png", "cartes_2.png", "cartes_3.png", "cartes_5.png", "cartes_8.png", "cartes_13.png", "cartes_20.png", "cartes_40.png", "cartes_100.png", "cartes_cafe.png", "cartes_interro.png"};

    // Calculate the number of specific cards
    int numSpecificCards = 12;
    for (int i = 0; i < numSpecificCards; i++) {
        // Create and initialize each specific card
        strcpy(finalPath, basePath);
        strcat(finalPath, imageNames[i]);
        cards[i] = *createCard(cardNames[i], finalPath);
        memset(finalPath, '\0', sizeof(char) * 48);
    }
}

Card *cardsCreation(SDL_Window *window, SDL_Renderer *renderer) { // Creates multiple cards
    const int numCards = 12;
    Card* myCards = (Card*)malloc(numCards * sizeof(Card));

    if (myCards != NULL) {
        initializeSpecificCards(myCards);
        //printf("%s\n", cards[5]->imagePath);
        return myCards;
    } else {
        printf("Failed to allocate memory for cards\n");
    }
}

void clearCards(Card *myCards){
    free(myCards);
}