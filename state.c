#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "game.c"
#include "game.h"

void saveJSON(game game, char *filename){
    int fd = open(filename, O_CREAT|O_WRONLY);
    check_if_error(!fd, "File opening failed");
    char temp[5] = {0};
    char temp2[5] = {", "};
    char temp3[5] = {0};
    char endOfLine[3] = {";\n\0"};

    write(fd, game->gamemode, 4); // Saving gamemode
    check_if_error(!fd, "Writing gamemode error");
    write(fd, endOfLine, 2);
    check_if_error(!fd, "Writing gamemode error");

    itoa(game->stateOfGame, temp, 10); // Saving State (Pending, etc.)
    strcat(temp, endOfLine);
    //printf("%s", temp);
    write(fd, temp, 4);
    check_if_error(!fd, "Writing stateOfGame error");
    memset(temp, '\0', sizeof(char) * 5);

    itoa((game->totalTasks-game->lastTask), temp, 10); // Saving remaining tasks
    strcat(temp, endOfLine);
    //printf("%s", temp);
    write(fd, temp, 3);
    check_if_error(!fd, "Writing totalTasks-lastTask error");
    memset(temp, '\0', sizeof(char) * 5);

    itoa(game->lastTask, temp, 10); // Saving Last Task voted
    strcat(temp, endOfLine);
    //printf("%s", temp);
    write(fd, temp, 3);
    check_if_error(!fd, "Writing lastTask error");
    memset(temp, '\0', sizeof(char) * 5);

    for(int i = 0; i < game->lastTask; i++){ // Saving tasks that are done
        //printf("%d\n", strlen(game->tasks[i]->text));
        write(fd, game->tasks[i]->text, strlen(game->tasks[i]->text));
        check_if_error(!fd, "Writing gamemode error");
        itoa(game->tasks[i]->vote, temp, 10);
        strcat(temp3, temp2);
        strcat(temp3, temp);
        write(fd, temp3, strlen(temp3));
        memset(temp, '\0', sizeof(char) * 5);
        memset(temp3, '\0', sizeof(char) * 5);
        write(fd, endOfLine, 2);
        check_if_error(!fd, "Writing gamemode error");
    }

    for(int i = game->lastTask; i < game->totalTasks; i++){ // Saving tasks not done
        write(fd, game->tasks[i]->text, strlen(game->tasks[i]->text));
        check_if_error(!fd, "Writing gamemode error");
        write(fd, endOfLine, 2);
        check_if_error(!fd, "Writing gamemode error");
    }
    close(fd);
}

game loadJSON(char *filename){
    game g = newEmptyGame();
    int fd = open(filename, O_RDONLY);
    check_if_error(!fd, "File opening failed");
    char temp[100] = {0};
    char gamemode[4] = {0}; // Needed for now because else the temp is reset and we lose the gamemode in game.
    int lineNumber = 0;
    int lines[50] = {0};
    int posTemp = 0;

    /* GAMEMODE READ */
    read(fd, gamemode, 4);
    check_if_error(!fd, "Reading gamemode error");
    strcpy(g->gamemode, gamemode);
    //printf("%s\n", g->gamemode);
    lseek(fd, 3, SEEK_CUR); // skips the ;\n

    /* STATE OF GAME READ */
    read(fd, temp, 2);
    check_if_error(!fd, "Reading stateOfGame error");
    //printf("%s\n", temp);
    g->stateOfGame = atoi(temp);
    memset(temp, '\0', sizeof(char) * 100);
    lseek(fd, 3, SEEK_CUR); // skips the ;\n

    /* TOTAL TASKS READ */
    read(fd, temp, 1);
    check_if_error(!fd, "Reading totalTasks error");
    //printf("%s\n", temp);
    g->totalTasks = atoi(temp); // Only the remaining tasks but will add the rest right after.
    memset(temp, '\0', sizeof(char) * 100);
    lseek(fd, 3, SEEK_CUR); // skips the ;\n

    /* LAST TASK READ */
    read(fd, temp, 1);
    check_if_error(!fd, "Reading lastTasks error");
    //printf("%s\n", temp);
    g->lastTask = atoi(temp);
    g->totalTasks += atoi(temp); // Adding the rest of the tasks
    memset(temp, '\0', sizeof(char) * 100);
    posTemp = lseek(fd, 3, SEEK_CUR); // skips the ;\n

    /* Counting number of lines, and the location of each */
    while(read(fd, temp, 1) > 0){
        check_if_error(!fd, "Reading while counting lines error");
        if (temp[0] == '\n'){
            lines[lineNumber] = lseek(fd, 0, SEEK_CUR)/sizeof(char) - 20 - 3; // -3 because of ;\n
            lineNumber++;
        }
    }
    lines[lineNumber] = lseek(fd, 0, SEEK_CUR)/sizeof(char) - 20 - 1; // -1 because of ;
    lseek(fd, posTemp, SEEK_SET); // Stepping back for the read of our data

    /* TASKS READ */
    for (int i = 0; i <= lineNumber; i++){
        if (i == 0){
            read(fd, temp, lines[i]);
        } else {
            read(fd, temp, (lines[i] - lines[i-1]-3)); // -3 to skip the read of the ;\n of the previous line
        }
        check_if_error(!fd, "Reading tasks error");
        lseek(fd, 3, SEEK_CUR); // skip the 3 bites of ;\n
        //printf("%s\n", temp); // printing it for the host to check for any errors in the tasks listing.
        g->tasks[i] = newTask(i, -1, temp);
        memset(temp, '\0', sizeof(char) * 100);
    }

    close(fd);
    return g;
}