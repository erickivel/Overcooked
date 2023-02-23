#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "screen.h"

struct game *createGame(char *mapPath) {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);

  // Random seed
  srand(clock());

  // -1 = single-player
  //  1 = co-op
  int mode = -1;
  printMode(mode);

  int inputMode = getch();
  while(inputMode != ' ') {
    if (inputMode == KEY_DOWN || inputMode == KEY_UP) {
      mode = mode * -1;
      printMode(mode);
    }
    inputMode = getch();
  }

  struct game *newGame = malloc(sizeof *newGame);
  newGame->map = createMap(mapPath);
  newGame->character = createCharacter('&');
  newGame->totalCharacters = mode == -1 ? 1 : 2;
  if (mode == 1) {
    newGame->character2 = createCharacter('$');
  }
  newGame->orders = createOrderQueue();
  newGame->maxTime = 25;
  newGame->timeLeft = 25;
  populateOrderQueue(newGame->orders, 5);

  return newGame;
}

void refreshScreen(struct game *game) {
  erase();
  printScore(game->character->lifes, game->character, game->timeLeft);
  printMap(game->map);
  printCharacterMeal(game->character);
  printRecipes();
  printOrders(game->orders);
  refresh();
}

int initGame(struct game *game) {

  struct map* map = game->map;
  int maxX = map->maxX;
  int maxY = map->maxY;

  int x, y;
  do {
      x = rand() % (maxX - 1);
      y = rand() % (maxY - 1);
  } while (map->matrix[y][x] != ' ');

  map->matrix[y][x] = '&';
  game->character->posX = x;
  game->character->posY = y;

  if (game->totalCharacters == 2)  {
    do {
        x = rand() % (maxX - 1);
        y = rand() % (maxY - 1);
    } while (map->matrix[y][x] != ' ');

    map->matrix[y][x] = '$';
    game->character2->posX = x;
    game->character2->posY = y;
  }

  printWelcome();
  getch();

  return 1;
}

void resetTimer(struct game *game) {
  game->startTime = clock();
  game->timeLeft = game->maxTime;
}

// If has collision return 1, otherwise return 0
int handleCollision(struct game *game, char nextPosition) {
  struct character *character = game->character;
  struct orderQueue *orders = game->orders;

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
    if (character->meal->size > 0 && deliverMeal(character, orders)) {
      int addSecs = game->totalCharacters == 2 ? 7*CLOCKS_PER_SEC : 15*CLOCKS_PER_SEC;
      game->startTime = game->startTime + addSecs;
    }
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

void handleInput(struct game *game, struct character *character,
                 int userInput) {
  int posX = character->posX;
  int posY = character->posY;
  char charSkin = character->skin;

  switch (userInput) {
  case 'W':
  case 'w':
  case KEY_UP:
    if (!handleCollision(game, game->map->matrix[posY - 1][posX])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY - 1][posX] = charSkin;
      character->posY--;
    }
    break;
  case 'A':
  case 'a':
  case KEY_LEFT:
    if (!handleCollision(game, game->map->matrix[posY][posX - 1])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY][posX - 1] = charSkin;
      character->posX--;
    }
    break;
  case 'S':
  case 's':
  case KEY_DOWN:
    if (!handleCollision(game, game->map->matrix[posY + 1][posX])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY + 1][posX] = charSkin;
      character->posY++;
    }
    break;
  case 'D':
  case 'd':
  case KEY_RIGHT:
    if (!handleCollision(game, game->map->matrix[posY][posX + 1])) {
      game->map->matrix[posY][posX] = ' ';
      game->map->matrix[posY][posX + 1] = charSkin;
      character->posX++;
    }
    break;
  }
}

int runGame(struct game *game) {
  refreshScreen(game);
  int userInput = getch();

  game->startTime = clock();

  timeout(0);
  while (userInput != 'q' && game->character->lifes > 0 && game->timeLeft > 0) {

    if (game->totalCharacters == 2 &&
        (userInput == KEY_UP || userInput == KEY_DOWN ||
         userInput == KEY_LEFT || userInput == KEY_RIGHT)) {
      handleInput(game, game->character2, userInput);
    } else {
      handleInput(game, game->character, userInput);
    }

    if (game->orders->size == 0) {
      populateOrderQueue(game->orders, 5);
      game->maxTime -= game->totalCharacters == 2 ? 3 : 5;
    }

    clock_t currentTime = clock();
    game->timeLeft =
        game->maxTime - ((currentTime - game->startTime) / (CLOCKS_PER_SEC));

    if (game->timeLeft == 0) {
      game->character->lifes -= 2;
      game->character->score -= 10;
      popOrder(game->orders);
      resetTimer(game);
    }
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
  if (game->totalCharacters == 2)
    endCharacter(game->character2);
  endOrders(game->orders);

  free(game);
  endwin();

  return 1;
}
