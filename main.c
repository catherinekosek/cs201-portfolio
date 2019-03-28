#include "game.h"
#include "input.h"

int main(int argc, char* argv[]) {
	startMenu();
	Game* game = newGame();
	playGame(game);	
	return 0;
}
