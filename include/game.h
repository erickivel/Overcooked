#include "character.h"
#include "map.h"
#include "meal.h"
#include "order.h"

#ifndef GAME_H
#define GAME_H

struct game {
  struct map *map;
  struct character *character;
  struct character *character2;
  struct orderQueue *orders;
  int totalCharacters;
  int startTime;
  int maxTime;
  int timeLeft;
};

struct game *createGame(char *mapPath);

int initGame(struct game *game);

int runGame(struct game *game);

int endGame(struct game *game);

#endif /* GAME_H */
