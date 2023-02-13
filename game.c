#include <ncurses.h>
#include <stdlib.h>

#include "game.h"
#include "screen.h"

struct game *createGame() {
  struct game *newGame = malloc(sizeof *newGame);
  newGame->map = createMap();
  newGame->character = createCharacter();
  newGame->orders = createOrderQueue();
  populateOrderQueue(newGame->orders, 5);

  return newGame;
}

void refreshScreen(struct game *game) {
  erase();
  printScore(game->character);
  printMap(game->map);
  printCharacterMeal(game->character);
  printOrders(game->orders);
  printRecipes();
  refresh();
}

int initGame(struct game *game) {
  initscr();
  noecho();
  curs_set(0);

  int maxX = game->map->maxX;
  int maxY = game->map->maxY;

  for (int i = 0; i < maxY; i++) {
    for (int j = 0; j < maxX; j++) {
      if (game->map->matrix[i][j] == '&') {
        game->character->posX = j;
        game->character->posY = i;
      }
    }
  }

  return 1;
}

// If has collision return 1, otherwise return 0
int handleCollision(struct character *character, struct orderQueue *orders,
                    char nextPosition) {
  switch (nextPosition) {
  case ' ':
    return 0;
  case '|':
    return 1;
  case '[':
    return 1;
  case ']':
    return 1;
  case '-':
    return 1;
  case '@':
    deliverMeal(character, orders);
    return 1;
  case 'o':
    trashMeal(character);
    return 1;
  case 'H':
    addIngredient(character->meal, 'H');
    return 1;
  case 'p':
    addIngredient(character->meal, 'p');
    return 1;
  case 'P':
    addIngredient(character->meal, 'P');
    return 1;
  case 'Q':
    addIngredient(character->meal, 'Q');
    return 1;
  case 'S':
    addIngredient(character->meal, 'S');
    return 1;
  case 'F':
    addIngredient(character->meal, 'F');
    return 1;
  case 'R':
    addIngredient(character->meal, 'R');
    return 1;
  default:
    return 1;
  }
}

void handleInput(struct game *game, char userInput) {
  int posX = game->character->posX;
  int posY = game->character->posY;

  struct character *character = game->character;
  struct orderQueue *orders = game->orders;

  switch (userInput) {
  case 'w':
    if (!handleCollision(character, orders,
                         game->map->matrix[posY - 1][posX])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY - 1][posX] = '&';
      game->character->posY--;
    }
    break;
  case 'a':
    if (!handleCollision(character, orders,
                         game->map->matrix[posY][posX - 1])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY][posX - 1] = '&';
      game->character->posX--;
    }
    break;
  case 's':
    if (!handleCollision(character, orders,
                         game->map->matrix[posY + 1][posX])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY + 1][posX] = '&';
      game->character->posY++;
    }
    break;
  case 'd':
    if (!handleCollision(character, orders,
                         game->map->matrix[posY][posX + 1])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY][posX + 1] = '&';
      game->character->posX++;
    }
    break;
  }
}

int runGame(struct game *game) {
  refreshScreen(game);
  char userInput = getch();

  while (userInput != 'q' && game->character->lifes > 0) {
    handleInput(game, userInput);

    if (game->orders->size == 0) {
      populateOrderQueue(game->orders, 5);
    }

    refreshScreen(game);
    userInput = getch();
  }

  return 1;
}

int endGame(struct game *game) {
  printEndGame(game);

  endMap(game->map);
  endCharacter(game->character);
  endOrders(game->orders);

  free(game);
  endwin();

  return 1;
}
