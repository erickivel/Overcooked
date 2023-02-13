#include "meal.h"
#include "order.h"

#ifndef CHARACTER_H
#define CHARACTER_H

struct character {
  int posX;
  int posY;
  int lifes;
  int score;
  int mealsDelivered;
  struct meal *meal;
};

struct character *createCharacter();

int deliverMeal(struct character *character, struct orderQueue *orders);

int trashMeal(struct character *character);

#endif /* CHARACTER_H */
