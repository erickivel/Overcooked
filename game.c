#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "screen.h"

struct game *createGame() {
  struct game *newGame = malloc(sizeof *newGame);
  newGame->map = createMap();
  newGame->character = createCharacter();
  newGame->orders = createOrderQueue();
	newGame->maxTime = 25;
	newGame->timeLeft = 25;
  populateOrderQueue(newGame->orders, 5);

  return newGame;
}

void refreshScreen(struct game *game) {
  erase();
  printScore(game->character, game->timeLeft);
  printMap(game->map);
  printCharacterMeal(game->character);
  printOrders(game->orders);
  printRecipes();
  refresh();
}

int initGame(struct game *game) {
  initscr();
  keypad(stdscr, TRUE);
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

  erase();
  printWelcome();
  refresh();
  getch();

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

void handleInput(struct game *game, int userInput) {
  int posX = game->character->posX;
  int posY = game->character->posY;

  struct character *character = game->character;
  struct orderQueue *orders = game->orders;

  switch (userInput) {
  case 'W':
  case 'w':
  case KEY_UP:
    if (!handleCollision(character, orders,
                         game->map->matrix[posY - 1][posX])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY - 1][posX] = '&';
      game->character->posY--;
    }
    break;
  case 'A':
  case 'a':
  case KEY_LEFT:
    if (!handleCollision(character, orders,
                         game->map->matrix[posY][posX - 1])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY][posX - 1] = '&';
      game->character->posX--;
    }
    break;
  case 'S':
  case 's':
  case KEY_DOWN:
    if (!handleCollision(character, orders,
                         game->map->matrix[posY + 1][posX])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY + 1][posX] = '&';
      game->character->posY++;
    }
    break;
  case 'D':
  case 'd':
  case KEY_RIGHT:
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
  int userInput = getch();

	//
	int startTime = clock(); 
	//

	timeout(0);
  while (userInput != 'q' && game->character->lifes > 0 && game->timeLeft > 0) {
    handleInput(game, userInput);

    if (game->orders->size == 0) {
      populateOrderQueue(game->orders, 5);
    }

		clock_t currentTime = clock();
		game->timeLeft = game->maxTime - ((currentTime - startTime) / (CLOCKS_PER_SEC));
    refreshScreen(game);
    userInput = getch();
  }
	timeout(-1);

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
