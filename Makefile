all:
	gcc -I include -L lib -o gameLoop gameLoop.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf