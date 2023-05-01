#include <ncurses.h>

#include "../include/screen.h"

void printMode(int mode) {
  erase();
  printw("\n\t SELECT GAME MODE\n\n");
  if (mode == -1) {
    printw("\t-> NORMAL MODE <-\n");
    printw("\t   SECRET MODE\n");
  } else if (mode == 1) {
    printw("\t   NORMAL MODE \n");
    printw("\t-> SECRET MODE <-\n");
  }
  printw("\nMove with the arrows and select with SPACE");
  refresh();
}

void printWelcome() {
  erase();

  printw("\n\n  ___                                _            _ \n");
  printw(" / _ \\__   _____ _ __ ___ ___   ___ | | _____  __| |\n");
  printw("| | | \\ \\ / / _ \\ '__/ __/ _ \\ / _ \\| |/ / _ \\/ _` |\n");
  printw("| |_| |\\ V /  __/ | | (_| (_) | (_) |   <  __/ (_| |\n");
  printw(" \\___/  \\_/ \\___|_|  \\___\\___/ \\___/|_|\\_\\___|\\__,_|\n");
  printw("\n\nPress any key to start\n");
  refresh();
}

void printScore(int lifes, struct character *character, int time) {
  printw("\n");
  printw("Lives: %d    Score: %d  Time: %d s", lifes, character->score, time);
  printw("\n\n");
}

void printMap(struct map *map) {
  for (int i = 0; i < map->maxY; i++) {
    printw("\t");
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

char mealNames[6][20] = {
    {"Cheeseburguer"}, {"Cheeseburguer salad"}, {"Combo 1"},
    {"Combo 2"},       {"Vegetarian"},          {"Vegan"},
};

void printOrders(struct orderQueue *queue) {
  printw("Orders:\n");
  struct order *order = queue->firstOrder;

  while (order) {
    printw("[Cliente %d | %s]", order->clientId, mealNames[order->meal->id]);
    if (order->next)
      printw(" -> ");
    printw("\n");

    order = order->next;
  }

  printw("\n");
}

void printRecipes() {
  printw("Recipes:\n");
  printw("Cheeseburguer:       [p] [H] [Q] [P]\n");
  printw("Cheeseburguer salad  [p] [H] [S] [P]\n");
  printw("Combo 1              [p] [H] [Q] [P] [F] [R]\n");
  printw("Combo 2              [p] [H] [S] [P] [F] [R]\n");
  printw("Vegetarian           [p] [Q] [P] [F] [R]\n");
  printw("Vegan                [S] [F] [R]\n");
  printw("\n");
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

  printw("\nPress SPACE to leave the game\n");

  refresh();

  char input;

  do {
    input = getch();
  } while (input != ' ');
}
