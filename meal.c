#include <stdlib.h>
#include <time.h>

#include "meal.h"

struct ingredient *createIngredient(char val) {
  struct ingredient *newIngredient = malloc(sizeof(struct ingredient));

  newIngredient->val = val;
  newIngredient->next = NULL;

  return newIngredient;
}

struct meal *newMeal() {
  struct meal *newMeal = malloc(sizeof(struct meal));

  newMeal->size = 0;
  newMeal->id = 0;
  newMeal->top = NULL;

  return newMeal;
}

// Push
int addIngredient(struct meal *meal, char value) {
  struct ingredient *ing = createIngredient(value);

  if (meal->size == 0) {
    meal->top = ing;
    meal->size = 1;
    return 1;
  }

  struct ingredient *oldTop = meal->top;
  meal->top = ing;
  ing->next = oldTop;
  meal->size += 1;

  return 1;
}

struct meal *createRandomMeal() {
  srand(clock());

  // int randNum = rand() % 5;

  struct meal *meal = newMeal();

  switch (rand() % 6) {
  // X-burguer
  case 0:
    addIngredient(meal, 'p');
    addIngredient(meal, 'H');
    addIngredient(meal, 'Q');
    addIngredient(meal, 'P');
    meal->id = 0;
    return meal;
  // X-salada
  case 1:
    addIngredient(meal, 'p');
    addIngredient(meal, 'H');
    addIngredient(meal, 'S');
    addIngredient(meal, 'P');
    meal->id = 1;
    return meal;
  // Combo 1
  case 2:
    addIngredient(meal, 'p');
    addIngredient(meal, 'H');
    addIngredient(meal, 'Q');
    addIngredient(meal, 'P');
    addIngredient(meal, 'F');
    addIngredient(meal, 'R');
    meal->id = 2;
    return meal;
  // Combo 2
  case 3:
    addIngredient(meal, 'p');
    addIngredient(meal, 'H');
    addIngredient(meal, 'S');
    addIngredient(meal, 'P');
    addIngredient(meal, 'F');
    addIngredient(meal, 'R');
    meal->id = 3;
    return meal;
  // Vegetariano
  case 4:
    addIngredient(meal, 'p');
    addIngredient(meal, 'Q');
    addIngredient(meal, 'P');
    addIngredient(meal, 'F');
    addIngredient(meal, 'R');
    meal->id = 4;
    return meal;
  // Vegano
  case 5:
    addIngredient(meal, 'S');
    addIngredient(meal, 'F');
    addIngredient(meal, 'R');
    meal->id = 5;
    return meal;
  default:
    return NULL;
  }
}

// Pop
struct ingredient *removeIngredient(struct meal *meal) {
  if (meal->size == 0)
    return NULL;

  struct ingredient *ing = meal->top;
  meal->top = meal->top->next;
  meal->size -= 1;

  return ing;
}

void removeAllIngredients(struct ingredient *ing) {
  if (ing == NULL)
    return;

  ing = ing->next;
  removeAllIngredients(ing);
  free(ing);
}

int deleteMeal(struct meal *meal) {
  struct ingredient *topIngredient = meal->top;

  removeAllIngredients(topIngredient);
  free(meal);

  return 1;
}
