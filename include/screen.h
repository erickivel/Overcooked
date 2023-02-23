#include "game.h"

#ifndef SCREEN_H
#define SCREEN_H

void printMode(int mode);

void printWelcome();

void printScore(int lifes, struct character *character, int time);

void printMap(struct map *map);

void printCharacterMeal(struct character *character);

void printOrders(struct orderQueue *queue);

void printRecipes();

void printEndGame(struct game *game);

#endif /* SCREEN_H */
