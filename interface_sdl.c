#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "environment.c"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define DELAY 10
#define TEXTBOX_WIDTH 300
#define TEXTBOX_HEIGHT 40

typedef struct {
    SDL_Rect rect;
    char text[256];
} InputField;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;
InputField inputField;
Environment *environment = NULL;

/********************************
***         Rendering         ***
********************************/

void renderTitle(SDL_Window *window, SDL_Renderer *renderer, Environment *environment){
    SDL_RenderCopy(renderer, environment->titleTexture, NULL, &(environment->titleRect));
}

void renderCards(SDL_Window *window, SDL_Renderer *renderer, Environment *environment){
    for (int i = 0; i < 12; i++) {
        SDL_RenderCopy(renderer, environment->cardTextures[i], NULL, &(environment->cards[i]));
    }
}

void renderButtons(SDL_Window *window, SDL_Renderer *renderer, Environment *environment){
    for (int i = 0; i < 3; i++) {
        SDL_RenderCopy(renderer, environment->buttonTexture[i], NULL, &(environment->buttons[i]));
    }
}

void renderBackground(SDL_Window *window, SDL_Renderer *renderer, Environment *environment){
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 0xFF);
    SDL_RenderClear(renderer);
}

void renderText(SDL_Window *window, SDL_Renderer *renderer, Environment *environment, const char *text, SDL_Rect position) {
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &position);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void renderInputBox(SDL_Window *window, SDL_Renderer *renderer, Environment *environment) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    inputField.rect.w = 200;
    inputField.rect.h = 30;
    inputField.rect.x = (w - inputField.rect.w) / 2;
    inputField.rect.y = (h - inputField.rect.h) / 2;
    inputField.text[0] = '\0';
    SDL_RenderFillRect(renderer, &inputField.rect);

    renderText(window, renderer, environment, inputField.text, inputField.rect);
    SDL_RenderPresent(renderer);
}

void renderPlayerName(SDL_Window *window, SDL_Renderer *renderer, Environment *environment, const char *text, SDL_Rect position) {
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &position);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void render(SDL_Window *window, SDL_Renderer *renderer, Environment *environment){
    renderButtons(window, renderer, environment);
    renderCards(window, renderer, environment);
    renderTitle(window, renderer, environment);
}

/********************************
***          Cleaning         ***
********************************/

void cleanButtons(SDL_Window *window, SDL_Renderer *renderer, Environment *environment){
    for (int i = 0; i < 12; ++i) {
        SDL_DestroyTexture(environment->buttonTexture[i]);
    }
}

void cleanCards(SDL_Window *window, SDL_Renderer *renderer, Environment *environment){
    for (int i = 0; i < 12; ++i) {
        SDL_DestroyTexture(environment->cardTextures[i]);
    }
}

void cleanTitle(SDL_Window *window, SDL_Renderer *renderer, Environment *environment){
    SDL_DestroyTexture(environment->titleTexture);
}

void clean(SDL_Window *window, SDL_Renderer *renderer, Environment *environment){
    cleanButtons(window, renderer, environment);
    cleanCards(window, renderer, environment);
    cleanTitle(window, renderer, environment);

    free(environment);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

/********************************
***       Initialization      ***
********************************/

void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("Poker Planning", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    check_if_error(!window, "Error: SDL_CreateWindow");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    environment = initEnvironment(window, renderer);
    check_if_error(!environment, "Error: Environment");

    font = TTF_OpenFont("resources/themes/base/Ubuntu-Light.ttf", 24);
    if (!font) {
        printf("Error: Unable to load font. %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/********************************
***        Processing         ***
********************************/

bool processButtons(SDL_Window *window, SDL_Renderer *renderer, Environment *environment, SDL_Event *e, int *currentState, game game){
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Point click;
    if (e->type == SDL_MOUSEBUTTONDOWN){ // If there is a click
        SDL_GetMouseState(&click.x, &click.y);
    }
    if (SDL_PointInRect(&click, &(environment->buttons[0]))){
        //saveJSON(game, "output.json");
        printf("save\n");
    } else if (SDL_PointInRect(&click, &(environment->buttons[1]))){
        //game game = newEmptyGame();
        //game = loadJSON("input.json");
        printf("load\n");
        *currentState = 3;
    } else if (SDL_PointInRect(&click, &(environment->buttons[2]))){
        //game game = newEmptyGame();
        printf("new\n");
    }
    return false;
}

bool processText(SDL_Window *window, SDL_Renderer *renderer, Environment *environment, SDL_Event *e, int *currentState, game game){ // Only function not working and it makes the case 2 not working too
    if (e->type == SDL_TEXTINPUT || e->type == SDL_KEYDOWN) {
        printf("%d, %d, %d\n", e->type == SDL_KEYDOWN, e->key.keysym.sym == SDLK_RETURN, strlen(inputField.text) > 0);
        if (e->type == SDL_TEXTINPUT) {
            strcat(inputField.text, e->text.text);
            printf("1%s\n", inputField.text);
        } else if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_BACKSPACE && strlen(inputField.text) > 0) {
            game->contestantNumber = atoi(inputField.text);
            printf("2%s\n", inputField.text);
            printf("%d\n", game->contestantNumber);
            inputField.text[strlen(inputField.text) - 1] = '\0';
        }
    }
    int i = 0;
    while(game->contestantNumber > i){
        if (e->type == SDL_TEXTINPUT || e->type == SDL_KEYDOWN) {
            if (e->type == SDL_TEXTINPUT) {
                strcat(inputField.text, e->text.text);
            } else if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_BACKSPACE && strlen(inputField.text) > 0) {
                inputField.text[strlen(inputField.text) - 1] = '\0';
                strcpy(game->playerList[i]->name, inputField.text);
                printf("%s\n", game->playerList[i]->name);
                i++;
            }
        }
    }
    
    //*currentState = 2;
    return false;
}

bool processCards(SDL_Window *window, SDL_Renderer *renderer, Environment *environment, SDL_Event *e, int *currentState, player player){
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Point click;
    if (e->type == SDL_MOUSEBUTTONDOWN){ // If there is a click
        SDL_GetMouseState(&click.x, &click.y);
    }
    for (int i = 0; i < 12; i++){
        if (SDL_PointInRect(&click, &(environment->cards[i]))){
            printf("%d\n", atoi(environment->deck_cards[i].name)); // display in the console which card you clicked on
            player->vote = atoi(environment->deck_cards[i].name);
        }
    }
    //*currentState = 2;
    return false;
}

/********************************
***         Interface         ***
********************************/

int interface(){
    initSDL();
    game game = newEmptyGame();
    int currentState = 0;
    SDL_Event e;
    SDL_StartTextInput();
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e) != 0) {
            renderBackground(window, renderer, environment); // We want them on every interface
            renderTitle(window, renderer, environment);

            switch (currentState){ // Switching from an interface (like the first menu) to another (like the display of the cards)
                case 0: // First Menu
                    quit = processButtons(window, renderer, environment, &e, &currentState, game);
                    renderButtons(window, renderer, environment);
                    break;
                case 1: // Seconde interface with the inputBox
                    quit = processText(window, renderer, environment, &e, &currentState, game);
                    renderInputBox(window, renderer, environment);
                    break;
                case 2: // Interface of vote with cards
                    int w, h;
                    SDL_GetWindowSize(window, &w, &h);
                    for(int i = 0; i < game->contestantNumber; i++){
                        SDL_Rect posPlayer;
                        posPlayer.w = 300;
                        posPlayer.h = 50;
                        posPlayer.x = (w - posPlayer.w) / 2;
                        posPlayer.y = 70;
                        renderPlayerName(window, renderer, environment, game->playerList[i]->name, posPlayer);
                        renderCards(window, renderer, environment);
                        quit = processCards(window, renderer, environment, &e, &currentState, game->playerList[i]);
                    }
                    break;
                case 3: // Test to check the card display change line 146 to see the others interfaces
                    renderCards(window, renderer, environment);
                    quit = processCards(window, renderer, environment, &e, &currentState, game->playerList[0]);
                    break;
                default:
                    break;
                if (quit) break;
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(DELAY);
        }
    }
    SDL_StopTextInput();
    clean(window, renderer, environment);
    return EXIT_SUCCESS;
}