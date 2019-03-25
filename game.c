#include "game.h"

Game* newGame() {
	Game* game = malloc(sizeof(Game));
	game->_player1 = newPlayer('b');
	game->_player2 = newPlayer('w');
	game->_board = newBoard(8);
	return game;
}

void playGame(Game* game, char* mode) {
	checkForMoves(game->_board);
	return;
}

void takeTurn(Game* game) {
	checkForMoves(game->_board);
	printBoard(game->_board);
	if (game->_mode == twoPlayer || game->_board->_turn == 'b') {
		int x;
		int y;
		int valid;
		printf("Please enter the row number you wish to place piece in:\n");
		scanf("%d", &x);
		printf("Please enter the column number you wish to place piece in:\n");
		scanf("%d", &y);
		valid = placePiece(game->_board, x, y);
		if (valid == 0) printf("invalid input\n");
	} else if(game->_mode == easy) {
		printf("placing piece x: %d, y: %d\n", game->_board->_validMoves->_nextMove->_x, game->_board->_validMoves->_nextMove->_y);
		placePiece(game->_board, game->_board->_validMoves->_nextMove->_x, game->_board->_validMoves->_nextMove->_y);		
	}
}

