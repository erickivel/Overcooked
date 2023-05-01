#include "../include/game.h"

int main(int argc, char **argv) {
  char *mapPath = argc == 1 ? "maps/map.txt" : argv[1];

  struct game *game = createGame(mapPath);

  initGame(game);
  runGame(game);
  endGame(game);

  return 0;
}
