#include "game.h"
#include "input.h"

int main(int argc, char* argv[]) {
	int size = promptForBoardSize();
	Game* game = newGame(size);
	playGame(game);	
	return 0;
}
