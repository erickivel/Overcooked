#include"game.h"

int main () {
	struct game* game = createGame();

	initGame(game);
	runGame(game);
	endGame(game);

	return 0;
}
