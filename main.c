#include "display.h"

int main(int argc, char* argv[]) {
/*	Board* board = newBoard(8);
	printBoard(board);

	int x;
	int y;
	int valid;
	scanf("%d", &x);
	while(x != -1) {
		scanf("%d", &y);
		valid = placePiece(board, y, x);
		if (valid == 1) {	
			printBoard(board);
			printf("black: %d, white: %d\n", board->_blackPieces, board->_whitePieces);	
			checkForMoves(board);
			printf("suggested next move: %d, %d\n", board->_validMoves->_nextMove->_x, board->_validMoves->_nextMove->_y);
		} else printf("invalid move\n");
		scanf("%d", &x);
	}	
*/
	Game* game = newGame();
	game->_mode = easy;
	while(1) takeTurn(game);		
	return 0;
}
