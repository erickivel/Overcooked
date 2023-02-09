#include"meal.h"

#ifndef CHARACTER_H
#define CHARACTER_H

struct character {
	int posX;
	int posY;
	struct meal* meal;
};

struct character* createCharacter();

#endif /* CHARACTER_H */
