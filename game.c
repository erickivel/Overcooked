#include<stdlib.h>
#include<ncurses.h>

#include"game.h"
#include"screen.h"

struct game* createGame() {
	struct game* newGame = malloc(sizeof *newGame);
	newGame->score = 0;
	newGame->map = createMap();
	newGame->character = malloc(sizeof(struct character));
	//newGame->order = createOrder();

	return newGame;
}

int initGame(struct game* game) {
	initscr();
	noecho();
	curs_set(0);

	printMap(game->map);

	int maxX = game->map->maxX;
	int maxY = game->map->maxY;

	for(int i = 0; i < maxY; i++) {
		for(int j = 0; j < maxX; j++) {
			if (game->map->matrix[i][j] == '&') {
				game->character->posX = j;
				game->character->posY = i;
			}
		}
	}

	return 1;
}

// If has collision return 1, otherwise return 0
int handleCollision(char nextPosition) {
	switch (nextPosition) {
		case ' ':
			return 0;
		case '|':
			return 1;
		case '[':
			return 1;
		case ']':
			return 1;
		case '-':
			return 1;
		case '@':
			return 1;
		case 'o':
			return 1;
		default:
			return 0;
	}
}

void interpretInput(struct game* game, char userInput) {
	int posX = game->character->posX;
	int posY = game->character->posY;

	switch(userInput) {
		case 'w':
			if (!handleCollision(game->map->matrix[posY-1][posX])) {
				game->map->matrix[posY][posX] = ' ';
				game->map->matrix[posY-1][posX] = '&';
				game->character->posY--;
			}
			break;
		case 'a':
			if (!handleCollision(game->map->matrix[posY][posX-1])) {
				game->map->matrix[posY][posX] = ' ';
				game->map->matrix[posY][posX-1] = '&';
				game->character->posX--;
			}
			break;
		case 's':
			if (!handleCollision(game->map->matrix[posY+1][posX])) {
				game->map->matrix[posY][posX] = ' ';
				game->map->matrix[posY+1][posX] = '&';
				game->character->posY++;
			}
			break;
		case 'd':
			if (!handleCollision(game->map->matrix[posY][posX+1])) {
				game->map->matrix[posY][posX] = ' ';
				game->map->matrix[posY][posX+1] = '&';
				game->character->posX++;
			}
			break;
		defaut:
			break;
	}

	printMap(game->map);
}

int runGame(struct game* game) {
	char userInput = getch(); 

	while(userInput != 'q') {
		interpretInput(game, userInput);
		userInput = getch(); 
	}

	return 1;
}

int endGame(struct game* game) {
	endMap(game->map);
	//endCharacter(game->character);
	//endOrder(game->order);

	endwin();

	return 1;
}
