#include "meal.h"
#include "order.h"

#ifndef CHARACTER_H
#define CHARACTER_H

struct character {
  char skin;
  int posX;
  int posY;
  int lifes;
  int score;
  int mealsDelivered;
  struct meal *meal;
};

struct character *createCharacter(char skin);

int deliverMeal(struct character *character, struct orderQueue *orders);

int trashMeal(struct character *character);

void endCharacter(struct character *character);

#endif /* CHARACTER_H */
