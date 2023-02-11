#include <ncurses.h>

#include "screen.h"

void printMap(struct map *map) {
  for (int i = 0; i < map->maxY; i++) {
    for (int j = 0; j < map->maxX; j++) {
      printw("%c", map->matrix[i][j]);
    }
    printw("\n");
  }
  printw("\n");
}

void auxPrintCharacterMeal(struct ingredient *ing) {
  if (ing == NULL)
    return;

  auxPrintCharacterMeal(ing->next);
  printw("[%c] ", ing->val);
}

void printCharacterMeal(struct meal *meal) {
  printw("Ingredients:\n");
  struct ingredient *ing = meal->top;

  auxPrintCharacterMeal(ing);

  printw("\n\n");
}

char mealNames[6][11] = {
    {"X-burguer"}, {"X-salada"},    {"Combo 1"},
    {"Combo 2"},   {"Vegetariano"}, {"Vegano"},
};

void printOrders(struct orderQueue *queue) {
  printw("Orders:\n");
  struct order *order = queue->firstOrder;

  while (order) {
    printw("[Cliente %d | %s]", order->clientId, mealNames[order->meal->id]);
    if (order->next)
      printw(" -> ");

    order = order->next;
  }

  printw("\n\n");
}

void printRecipes() {
  printw("Recipes:\n");
  printw("X-burguer:  [p] [H] [Q] [P]\n");
  printw("X-salada    [p] [H] [S] [P]\n");
  printw("Combo 1     [p] [H] [Q] [P] [F] [R]\n");
  printw("Combo 2     [p] [H] [S] [P] [F] [R]\n");
  printw("Vegetariano [p] [Q] [P] [F] [R]\n");
  printw("Vegano      [S] [F] [R]\n");
}
