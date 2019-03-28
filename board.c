#include "board.h"

Board* newBoard(int size) {
	Board* board = malloc(sizeof(Board));
	size += 2;
	board->boardArray = (char *)malloc(sizeof(char) * (size) * (size));  
	board->size = size;
	for (int k = 0; k < size; k++) {
		*(board->boardArray + 0 * size + k) = '-';
		*(board->boardArray + k * size + 0) = '-';
		*(board->boardArray + (size-1) * size + k) = '-';
		*(board->boardArray + k * size + (size-1)) = '-';
	}
	for (int i = 1; i < size-1; i++) {
		for (int j = 1; j < size-1; j++) {
			*(board->boardArray + i * size + j) = '*';
		}
	}
	int mid1 = (size-2) / 2;
	int mid2 = mid1 + 1;
	*(board->boardArray + mid1 * size + mid1) = 'w';
	*(board->boardArray + mid1 * size + mid2) = 'b';
	*(board->boardArray + mid2 * size + mid1) = 'b';
	*(board->boardArray + mid2 * size + mid2) = 'w';
	board->whitePieces = 2;
	board->blackPieces = 2;
	return board;
}

void printBoard(Board* board) {
	printf("\t       ");
	for (int k = 1; k < board->size-1; k++) {
		if (k < 10) printf("  %d", k);
		else printf(" %d", k);
	}
	for(int i = 0; i < board->size; i++) {
		printf("\n\t ");
		if (i == 0 || i == board->size-1) printf("   ");
		else if (i < 10) printf("  %d", i);
		else printf(" %d", i);
		for(int j = 0; j < board->size; j++) {
			printf("  %c", *(board->boardArray + i * board->size + j));
		}
	}
	printf("\n\n\tBlack Pieces: %d\t WhitePieces: %d\n", board->blackPieces, board->whitePieces);
	return;
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
	*(board->boardArray + x * board->size + y) = turn;
	if (turn == 'b') board->blackPieces++;
	else board->whitePieces++;
	return 0;
}

int flipPieces(Board* board, int x, int y, int xChange, int yChange, int flip, char turn) {
	char piece = *(board->boardArray + x * board->size + y);

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
		if (turn == 'b') {
			board->blackPieces++;
			board->whitePieces--;
		} else {
			board->whitePieces++;
			board->blackPieces--;
		}
		*(board->boardArray + x * board->size + y) = turn;
	}
	
	return flip;
}

