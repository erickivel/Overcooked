#include<stdlib.h>

#include"character.h"

struct character* createCharacter() {
	struct character* newCharacter = malloc(sizeof(struct character));

	newCharacter->meal = newMeal();

	return newCharacter;
}
