#include <ncurses.h>

#include "screen.h"

void printWelcome() {
  printw("\n\n _    _           _                          _            _ \n");
  printw("| |  | |         | |                        | |          | |\n");
  printw("| |  | |_ __   __| | ___ _ __ ___ ___   ___ | | _____  __| |\n");
  printw("| |  | | '_ \\ / _` |/ _ \\ '__/ __/ _ \\ / _ \\| |/ / _ \\/ _` |\n");
  printw("| |__| | | | | (_| |  __/ | | (_| (_) | (_) |   <  __/ (_| |\n");
  printw(" \\____/|_| |_|\\__,_|\\___|_|  \\___\\___/ "
         "\\___/|_|\\_\\___|\\__,_|\n");
  printw("\n\nPress any key to start\n");
}

void printScore(struct character *character) {
  printw("Lifes: %d    Score: %d", character->lifes, character->score);
  printw("\n\n");
}

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

void printCharacterMeal(struct character *character) {
  printw("Ingredients:\n");
  struct meal *meal = character->meal;
  struct ingredient *ing = meal->top;

  auxPrintCharacterMeal(ing);

  printw("\n\n");
}

char mealNames[6][12] = {
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

void printEndGame(struct game *game) {
  erase();

  printw(" ____                        ___         \n");
  printw("/ ___|  __ _ _ __ ___   ___ / _ \\__   _____ _ __ \n");
  printw("| |  _ / _` | '_ ` _ \\ / _ \\ | | \\ \\ / / _ \\ '__|\n");
  printw("| |_| | (_| | | | | | |  __/ |_| |\\ V /  __/ |   \n");
  printw(" \\____|\\__,_|_| |_| |_|\\___|\\___/  \\_/ \\___|_|   \n\n");

  printw("Score: %d\n", game->character->score);
  printw("Meals successfully delivered: %d\n", game->character->mealsDelivered);

  printw("Press any key to leave the game\n");

  refresh();

  getch();
}
