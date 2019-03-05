#include "board.h"
#include "square.h"

Board* newBoard() {
	Board* board = malloc(sizeof(Board));
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			Square* square = newSquare(i, j);
			board->_boardArray[i][j] = square;
		}
	}
	setPiece(board->_boardArray[3][3], 'w');
	setPiece(board->_boardArray[3][4], 'b');
	setPiece(board->_boardArray[4][3], 'b');
	setPiece(board->_boardArray[4][4], 'w');
	return board;
}

void printBoard(Board* board) {
	printf("\t\t\t 01234567\n\t\t\t0");
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			printf("%c", getPiece(board->_boardArray[i][j]));
		}
		printf("\n\t\t\t%d", i+1);
	}
	printf("\n");
}

void placePiece(Board* board, int x, int y, char turn) {
	flipPieces(board, x+1, y, 1, 0, turn, 0);		// right
	flipPieces(board, x+1, y+1, 1, 1, turn, 0);		// right up
	flipPieces(board, x, y+1, 0, 1, turn, 0);		// up
	flipPieces(board, x-1, y+1, -1, 1, turn, 0);		// left up
	flipPieces(board, x-1, y, -1, 0, turn, 0);		// left
	flipPieces(board, x-1, y-1, -1, -1, turn, 0);		// left down
	flipPieces(board, x, y-1, 0, -1, turn, 0);		// down
	flipPieces(board, x+1, y-1, 1, -1, turn, 0);		// right down
	setPiece(board->_boardArray[x][y], turn);
	return;
}

int flipPieces(Board* board, int x, int y, int xChange, int yChange, char turn, int flip) {
	if ((x < 0) || (y < 0) || (x > 7) || (y > 7)) {
		return 0;
	}
	char piece = getPiece(board->_boardArray[x][y]);
	if (piece == '*') {
		return 0;
	} else if (piece == turn) {
		return 1;
	} else {
		flip = flipPieces(board, x + xChange, y + yChange, xChange, yChange, turn, flip);
	}
	if(flip == 1) {
		setPiece(board->_boardArray[x][y], turn);
	}
	return flip;
}

void checkForMoves(Board* board, char turn) {
	int* validSquares[2];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (getPiece(board->_boardArray[i][j]) == turn) {
			findMoves(board, validSquares, i+1, j, 1, 0, turn, 0, 0);		// right
			findMoves(board, validSquares, i+1, j+1, 1, 1, turn, 0, 0);		// right up
			findMoves(board, validSquares, i, j+1, 0, 1, turn, 0, 0);		// up
			findMoves(board, validSquares, i-1, j+1, -1, 1, turn, 0, 0);		// left up
			findMoves(board, validSquares, i-1, j, -1, 0, turn, 0, 0);		// left
			findMoves(board, validSquares, i-1, j-1, -1, -1, turn, 0, 0);		// left down
			findMoves(board, validSquares, i, j-1, 0, -1, turn, 0, 0);		// down
			findMoves(board, validSquares, i+1, j-1, 1, -1, turn, 0, 0);		// right down
			}
		}	
	}	

	return;
}

void findMoves(Board* board, int* validSquares[2], int x, int y, int xChange, int yChange, char turn, int opposite, int index) {
	if ((x < 0) || (y < 0) || (x > 7) || (y > 7)) {
		return;
	}
	char piece = getPiece(board->_boardArray[x][y]);
	if ((piece == turn) || ((piece == '*') && (opposite == 0))) {
		return;
	} else if ((piece == '*') && (opposite == 1)) {
		validSquares[index][0] = x;
		validSquares[index][1] = y;
		index++;
		return;
	} else {
		findMoves(board, validSquares, x + xChange, y + yChange, xChange, yChange, turn, 1, index);
	}
}
