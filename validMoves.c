#include "validMoves.h"

ValidMoves* newValidMoves(Board* board) {
	ValidMoves* validMoves = malloc(sizeof(ValidMoves));
	validMoves->board = board;
	Coordinate* nextMove = malloc(sizeof(Coordinate));
	validMoves->nextMove = nextMove;
	checkForMoves(validMoves, 'b');
	return validMoves;
}

int validateMove(ValidMoves* validMoves, int x, int y) {
	if (validMoves->movesArray[x][y] != 0) return 1;
	return 0;
}

void DFS(int* visited, int* validMoves, int x, int y, int size, char turn) {
	*(visited + x * size + y) = 1;
	
	if (*(validMoves->movesArray
	if (*(validMoves + x * size + y) == piece) {
		findMoves(validMoves, i+1, j, 1, 0, 0, turn);		// right
		findMoves(validMoves, i+1, j+1, 1, 1, 0, turn);		// right up
		findMoves(validMoves, i, j+1, 0, 1, 0, turn);		// up
		findMoves(validMoves, i-1, j+1, -1, 1, 0, turn);	// left up
		findMoves(validMoves, i-1, j, -1, 0, 0, turn);		// left
		findMoves(validMoves, i-1, j-1, -1, -1, 0, turn);	// left down
		findMoves(validMoves, i, j-1, 0, -1, 0, turn);		// down
		findMoves(validMoves, i+1, j-1, 1, -1, 0, turn);	// right down
	} else if (*(validMoves + x * size + y) == '*') {
		return;
	} else {
		// all directions
	}
	
}

void checkForMoves(ValidMoves* validMoves, char turn) {
	Board* board = validMoves->board;

	validMoves->exists = 0;
	for (int k = 1; k <= board->size; k++) {
		for (int l = 0; l <= board->size; l++) {
			validMoves->movesArray[k][l] = 0;
		}
	}
	validMoves->nextMove->value = -1;

	for (int i = 1; i <= board->size; i++) {
		for (int j = 1; j <= board->size; j++) {
			if (board->boardArray[i][j] == turn) {
				findMoves(validMoves, i+1, j, 1, 0, 0, turn);		// right
				findMoves(validMoves, i+1, j+1, 1, 1, 0, turn);		// right up
				findMoves(validMoves, i, j+1, 0, 1, 0, turn);		// up
				findMoves(validMoves, i-1, j+1, -1, 1, 0, turn);	// left up
				findMoves(validMoves, i-1, j, -1, 0, 0, turn);		// left
				findMoves(validMoves, i-1, j-1, -1, -1, 0, turn);	// left down
				findMoves(validMoves, i, j-1, 0, -1, 0, turn);		// down
				findMoves(validMoves, i+1, j-1, 1, -1, 0, turn);	// right down
			}
		}	
	}	
	
	return;
}

void findMoves(ValidMoves* validMoves, int x, int y, int xChange, int yChange, int count, char turn) {
	char piece = validMoves->board->boardArray[x][y];

	if (piece == '-') {
		return;
	}
	else if ((piece == turn) || ((piece == '*') && (count == 0))) {
		return;
	} else if ((piece == '*') && (count >= 1)) {
		validMoves->movesArray[x][y] = count;
		validMoves->exists = 1;
		if (validMoves->nextMove->value < count) {
			validMoves->nextMove->x = x;
			validMoves->nextMove->y = y;
			validMoves->nextMove->value = count;
		}
		return;
	} else {
		count++;
		findMoves(validMoves, x + xChange, y + yChange, xChange, yChange, count, turn);
	}
}
