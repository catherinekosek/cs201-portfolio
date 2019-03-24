#include "game.h"

Game* newGame() {
	Game* game = malloc(sizeof(Game));
	game->_player1 = newPlayer('b');
	game->_player2 = newPlayer('w');
	game->_board = newBoard(8);
	game->_mode = "menu";
	return game;
}

void playGame(Game* game, char* mode) {
	checkForMoves(game->_board);
	return;
}
