#include <stdio.h>
#include "game.h"
#include "toolbox.c"

struct game_s {
    char *gamemode;
    int stateOfGame;
    int contestantNumber;
    int lastTask;
    int totalTasks;
    task tasks[100];
    player playerList[10];
};

struct task_s {
    int number;
    int vote;
    char *text;
};

struct player_s {
    int number;
    char name[10];
    int vote;
};

game newGame(char *gamemode, int stateOfGame, int contestantNumber, int lastTask, int totalTasks){
    struct game_s *g = (game)malloc(sizeof(struct game_s));
    check_if_error(g == NULL, "Not enought memory : Game");
    g->gamemode = (char *)malloc(sizeof(char *)*5); // Memory allocation
    check_if_error(g->gamemode == NULL, "Not enought memory : Gamemode");
    g->gamemode = gamemode;
    g->stateOfGame = stateOfGame;
    g->contestantNumber = contestantNumber;
    g->lastTask = lastTask;
    g->totalTasks = totalTasks;
    return g;
}

game newEmptyGame(){
    struct game_s *g = (game)malloc(sizeof(struct game_s));
    check_if_error(g == NULL, "Not enought memory : Game");

    g->gamemode = (char *)malloc(sizeof(char *)*5); // Memory allocation
    check_if_error(g->gamemode == NULL, "Not enought memory : Game Gamemode");

    struct task_s *t = (task)malloc(sizeof(struct task_s)*100); // can have 100 tasks
    check_if_error(t == NULL, "Not enought memory : Task");
    return g;
}

task newTask(int number, int vote, char *text){
    struct task_s *t = (task)malloc(sizeof(struct task_s));
    check_if_error(t == NULL, "Not enought memory : Task");
    t->text = (char *)malloc(sizeof(char *)*100); // Memory allocation // task can be 100 char long
    check_if_error(t->text == NULL, "Not enought memory : Task Text");
    t->number = number;
    t->vote = vote;
    strcpy(t->text, text);
    return t;
}

task newEmptyTask(){
    struct task_s *t = (task)malloc(sizeof(struct task_s));
    check_if_error(t == NULL, "Not enought memory : Task");
    t->text = (char *)malloc(sizeof(char *)*100); // Memory allocation
    check_if_error(t->text == NULL, "Not enought memory : Task Text");
    return t;
}

void printfGame(game g){
    printf("%s\n", g->gamemode);
    printf("%d\n", g->stateOfGame);
    printf("%d\n", g->lastTask);
    printf("%d\n", g->totalTasks);
    for (int i = 0; i < g->totalTasks; i++){
        printf("%s\n", g->tasks[i]->text);
    }
}