#include<ncurses.h>

#include"screen.h"

void printMap(struct map* map) {
	for(int i = 0; i < map->maxY; i++) {
		for(int j = 0; j < map->maxX; j++) {
			printw("%c", map->matrix[i][j]);
		}
		printw("\n");
	}
	printw("\n");
};

void auxPrintCharacterMeal(struct ingredient* ing) {
	if (ing == NULL) 
		return;

	auxPrintCharacterMeal(ing->next);
	printw("[%c] ", ing->val);
}

void printCharacterMeal(struct meal* meal) {
	printw("Ingredients:\n");
	struct ingredient* ing = meal->top;

	auxPrintCharacterMeal(ing);

	printw("\n");
};
