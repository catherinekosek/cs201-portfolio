#include "display.h"

int main(int argc, char* argv[]) {
	Board* board = newBoard(8);
	printBoard(board);

	int x;
	int y;
	scanf("%d", &x);
	while(x != -1) {
		scanf("%d", &y);
		if (board->_validMoves->_movesArray[y][x] == '!') {
			placePiece(board, y, x);
			printBoard(board);
			printf("black: %d, white: %d\n", board->_blackPieces, board->_whitePieces);
			checkForMoves(board);
		} else printf("invalid move\n");
		scanf("%d", &x);
	}	
	
	return 0;
}
