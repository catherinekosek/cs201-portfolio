#include "game.h"

int main(int argc, char* argv[]) {
	Game* game = newGame("easy");
	playGame(game);
	return 0;
}
