#ifndef GAME_H
#define GAME_H

#include"map.h"
#include"character.h"
//#include"order.h"

struct game {
 int score;	
 struct map* map;
 struct character* character;
 //struct order* carachter;
};

struct game* createGame();

int initGame(struct game* game);

int runGame(struct game* game);

int endGame(struct game* game);
	
#endif /* GAME_H */
