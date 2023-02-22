#include <stdlib.h>

#include "character.h"

struct character *createCharacter() {
  struct character *newCharacter = malloc(sizeof(struct character));

  newCharacter->mealsDelivered = 0;
  newCharacter->lifes = 5;
  newCharacter->score = 0;

  newCharacter->meal = newMeal();

  return newCharacter;
}

int deliverMeal(struct character *character, struct orderQueue *orders) {
  struct order *firstOrder = orders->firstOrder;
  struct meal *characterMeal = character->meal;
  struct meal *orderMeal = firstOrder->meal;

  struct ingredient *charIng = characterMeal->top;
  struct ingredient *orderIng = orderMeal->top;

  int isWrongMeal = 0;

  while (orderIng != NULL && !isWrongMeal) {
    if (charIng == NULL) {
      isWrongMeal = 1;
    } else {
      if (charIng->val != orderIng->val)
        isWrongMeal = 1;

      charIng = charIng->next;
      orderIng = orderIng->next;
    }
  }

  if (isWrongMeal) {
    character->lifes -= 2;
    character->score -= 10;
  } else {
    character->mealsDelivered += 1;
    popOrder(orders);
    character->score += 15;
  }

  removeAllIngredients(characterMeal->top);
  characterMeal->size = 0;
  characterMeal->top = NULL;

  return 1;
}

int trashMeal(struct character *character) {
  struct meal *meal = character->meal;
  struct ingredient *topIngredient = meal->top;

  if (topIngredient == NULL)
    return 1;

  removeAllIngredients(topIngredient);
  meal->size = 0;
  meal->top = NULL;

  character->score -= 10;
  character->lifes -= 1;

  return 1;
}

void endCharacter(struct character *character) {
  deleteMeal(character->meal);
  free(character);
}
