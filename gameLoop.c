#include <stdio.h>
#include <string.h>
#include "state.c"
#include "interface_sdl.c"
#include "factory.c"

int WinMain(int argc, int **argv){
    //game game = newEmptyGame(); // newGame("mode", 10, 1, 2, 3);
    //game = loadJSON("test.json");
    //printfGame(game);
    //saveJSON(game, "test2.json");
    interface();
    
    return 0;
}

