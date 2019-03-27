#include "game.h"

int main(int argc, char* argv[]) {
	Game* game = newGame("twoPlayer", 8);
	playGame(game);
	return 0;
}
