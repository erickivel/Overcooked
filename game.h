#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "map.h"
#include "order.h"

struct game {
  int score;
  struct map *map;
  struct character *character;
  struct orderQueue *orders;
};

struct game *createGame();

int initGame(struct game *game);

int runGame(struct game *game);

int endGame(struct game *game);

#endif /* GAME_H */
