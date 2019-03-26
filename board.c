#include "board.h"

Board* newBoard(int size) {
	Board* board = malloc(sizeof(Board));
	board->size = size;
	for (int k = 0; k <= size + 2; k++) {
		board->boardArray[0][k] = '-';
		board->boardArray[k][0] = '-';
		board->boardArray[size + 1][k] = '-';
		board->boardArray[k][size + 1] = '-';
	}
	for(int i = 1; i <= size; i++) {
		for(int j = 1; j <= size; j++) {
			board->boardArray[i][j] = '*';
		}
	}
	board->boardArray[size/2][size/2] = 'w';
	board->boardArray[size/2][(size/2)+1] = 'b';
	board->boardArray[(size/2)+1][size/2] = 'b';
	board->boardArray[(size/2)+1][(size/2)+1] = 'w';
	board->whitePieces = 2;
	board->blackPieces = 2;
	return board;
}

void printBoard(Board* board) {
	printf("\t\t\t  ");
	for (int k = 1; k <= board->size; k++) {
		printf("%d", k);
	}
	for(int i = 0; i <= board->size + 1; i++) {
		printf("\n\t\t\t");
		if (i == 0 || i == board->size + 1) printf(" ");
		else printf("%d", i);
		for(int j = 0; j <= board->size + 1; j++) {
			printf("%c", board->boardArray[i][j]);
		}
	}
	printf("\n");
}

int placePiece(Board* board, int x, int y, char turn) {
	flipPieces(board, x+1, y, 1, 0, 0, turn);		// right
	flipPieces(board, x+1, y+1, 1, 1, 0, turn);		// right up
	flipPieces(board, x, y+1, 0, 1, 0, turn);		// up
	flipPieces(board, x-1, y+1, -1, 1, 0, turn);		// left up
	flipPieces(board, x-1, y, -1, 0, 0, turn);		// left
	flipPieces(board, x-1, y-1, -1, -1, 0, turn);		// left down
	flipPieces(board, x, y-1, 0, -1, 0, turn);		// down
	flipPieces(board, x+1, y-1, 1, -1, 0, turn);		// right down
	board->boardArray[x][y] = turn;
	if (turn == 'b') board->blackPieces++;
	else board->whitePieces++;

	return 0;
}

int flipPieces(Board* board, int x, int y, int xChange, int yChange, int flip, char turn) {
	char piece = board->boardArray[x][y];

	if (piece == '-') {
		return 0;
	} else if (piece == '*') {
		return 0;
	} else if (piece == turn) {
		return 1;
	} else {
		flip = flipPieces(board, x + xChange, y + yChange, xChange, yChange, flip, turn);
	}

	if(flip == 1) {
		board->boardArray[x][y] = turn;
	}
	
	return flip;
}

