#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 10
#define MAX_NAME_LENGTH 50
#define MAX_MESSAGES 100
#define MAX_MESSAGE_LENGTH 200

typedef struct {
    char name[MAX_NAME_LENGTH];
    int vote;
} Player;

typedef struct {
    int mode;
    Player players[MAX_PLAYERS];
    int numPlayers;
    int unanimousVote;
    time_t startTime;
} PokerGame;

typedef struct {
    char sender[MAX_NAME_LENGTH];
    char message[MAX_MESSAGE_LENGTH];
} ChatMessage;

typedef struct {
    ChatMessage messages[MAX_MESSAGES];
    int numMessages;
} Chat;

void startGame(PokerGame *game);
void vote(PokerGame *game);
void displayResults(PokerGame *game);
void displayChat(Chat *chat);
void addMessage(Chat *chat, const char *sender, const char *message);
void startTimer(int seconds);

int main() {
    PokerGame game;
    Chat chat;
    chat.numMessages = 0;

    printf("Bienvenue dans l'application de Poker Planning en C!\n");

    // Choix du pseudo
    printf("Entrez votre pseudo : ");
    scanf("%s", game.players[0].name);

    // Choix du mode de jeu
    printf("Choisissez le mode de jeu :\n");
    printf("1. Moyenne\n");
    printf("2. Médiane\n");
    printf("3. Majorité absolue\n");
    printf("4. Majorité relative\n");

    printf("Entrez le numéro du mode de jeu : ");
    scanf("%d", &game.mode);

    if (game.mode < 1 || game.mode > 4) {
        printf("Mode invalide. Choisissez un mode entre 1 et 4.\n");
        return 1;
    }

    // Démarrer la partie
    startGame(&game);

    while (1) {
        // Premier tour de vote à l'unanimité
        vote(&game);

        // Afficher les résultats
        displayResults(&game);

        // Afficher le chat
        displayChat(&chat);

        // Réinitialiser les votes pour le tour suivant
        for (int i = 0; i < game.numPlayers; ++i) {
            game.players[i].vote = -1;
        }

        // Démarrer le chronomètre (3 minutes)
        startTimer(180);  // 180 secondes

        // Attendre la fin du chronomètre avant le prochain tour
        printf("\nAttendez le prochain tour...\n");
        sleep(5);  // Temps de pause pour la démo (peut être remplacé par un mécanisme de minuterie plus précis)
    }

    return 0;
}

void startGame(PokerGame *game) {
    // Initialiser le jeu avec un seul joueur pour le moment (vous pouvez étendre pour plusieurs joueurs)
    game->numPlayers = 1;
    game->players[0].vote = -1; // Initialiser le vote à -1 (non voté)
    game->unanimousVote = -1; // Initialiser à -1 pour indiquer qu'aucun vote n'a été émis
    game->startTime = 0; // Initialiser le chronomètre à 0
}

void vote(PokerGame *game) {
    printf("\nTour de vote :\n");

    for (int i = 0; i < game->numPlayers; ++i) {
        printf("%s, entrez votre vote () : ", game->players[i].name);
        scanf("%d", &(game->players[i].vote));
    }

    // Vérifier si le vote est unanime
    int unanimous = 1;
    for (int i = 1; i < game->numPlayers; ++i) {
        if (game->players[i].vote != game->players[0].vote) {
            unanimous = 0;
            break;
        }
    }

    if (unanimous) {
        printf("Vote à l'unanimité atteint!\n");
        game->unanimousVote = game->players[0].vote;
    } else {
        printf("Le vote n'est pas unanime..\n");
        for (int i = 0; i < game->numPlayers; ++i) {
            printf("%s, entrez votre nouveau vote () : ", game->players[i].name);
            scanf("%d", &(game->players[i].vote));
            
        }
    }
}

void displayResults(PokerGame *game) {
    printf("\nRésultats du Poker Planning :\n");
    printf("Mode de jeu : %d\n", game->mode);
    printf("Unanimous Vote : %d\n", game->unanimousVote);
}

void displayChat(Chat *chat) {
    printf("\nChat :\n");

    for (int i = 0; i < chat->numMessages; ++i) {
        printf("[%s] %s\n", chat->messages[i].sender, chat->messages[i].message);
    }
}

void addMessage(Chat *chat, const char *sender, const char *message) {
    if (chat->numMessages < MAX_MESSAGES) {
        snprintf(chat->messages[chat->numMessages].sender, MAX_NAME_LENGTH, "%s", sender);
        snprintf(chat->messages[chat->numMessages].message, MAX_MESSAGE_LENGTH, "%s", message);
        chat->numMessages++;
    } else {
        printf("Le chat est plein. Impossible d'ajouter plus de messages.\n");
    }
}

void startTimer(int seconds) {
    time_t startTime = time(NULL);
    time_t currentTime;

    printf("Chronomètre en cours...\n");

    do {
        currentTime = time(NULL);
    } while (currentTime - startTime < seconds);

    printf("Chronomètre terminé!\n");
}

   






















   int menu(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("lightup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    check_if_error(!window, "Error: SDL_CreateWindow");
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    Environment *environment = initEnvironment(window, renderer);
    check_if_error(!environment, "Error: Environment");

    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("resources/themes/base/Spider-Man.ttf", 24);
    if (!font) {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_StartTextInput();

    SDL_Event e;
    char inputText[10] = "";
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_TEXTINPUT) {
                strcat(inputText, e.text.text);
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                printf("Entered Text: %s\n", inputText);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 0xFF);
    SDL_RenderClear(renderer);

    SDL_Rect textBoxRect = { (SCREEN_WIDTH - TEXTBOX_WIDTH) / 2, (SCREEN_HEIGHT - TEXTBOX_HEIGHT) / 2, TEXTBOX_WIDTH, TEXTBOX_HEIGHT };
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    SDL_RenderDrawRect(renderer, &textBoxRect);

    // Render the entered text
    SDL_Color textColor = { 240, 240, 240, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, inputText, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_Rect textRect = { (SCREEN_WIDTH - textSurface->w) / 2, (SCREEN_HEIGHT - textSurface->h) / 2, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);

    // Update the screen
    SDL_RenderPresent(renderer);

    clean(window, renderer, environment);
    SDL_StopTextInput();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}