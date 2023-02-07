#include<ncurses.h>

#include"game.h"

void printMap(struct map* map) {
	erase();

	for(int i = 0; i < map->maxY; i++) {
		for(int j = 0; j < map->maxX; j++) {
			printw("%c", map->matrix[i][j]);
		}
		printw("\n");
	}

	refresh(); 
};
