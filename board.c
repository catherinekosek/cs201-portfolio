#include "board.h"
#include "square.h"

Board* newBoard(int size) {
	Board* board = malloc(sizeof(Board));
	board->_size = size;
	for (int k = 0; k <= size + 2; k++) {
		board->_boardArray[0][k] = '-';
		board->_boardArray[k][0] = '-';
		board->_boardArray[size + 1][k] = '-';
		board->_boardArray[k][size + 1] = '-';
	}
	for(int i = 1; i <= size; i++) {
		for(int j = 1; j <= size; j++) {
			board->_boardArray[i][j] = '*';
		}
	}
	board->_boardArray[size/2][size/2] = 'w';
	board->_boardArray[size/2][(size/2)+1] = 'b';
	board->_boardArray[(size/2)+1][size/2] = 'b';
	board->_boardArray[(size/2)+1][(size/2)+1] = 'w';
	board->_whitePieces = 2;
	board->_blackPieces = 2;
	
	ValidMoves* validMoves = malloc(sizeof(ValidMoves));
	Coordinate* nextMove = malloc(sizeof(Coordinate));
	validMoves->_nextMove = nextMove;
	board->_validMoves = validMoves;
	board->_turn = 'b';
	checkForMoves(board);	
	return board;
}

void printBoard(Board* board) {
	printf("\t\t\t  ");
	for (int k = 1; k <= board->_size; k++) {
		printf("%d", k);
	}
	for(int i = 0; i <= board->_size + 1; i++) {
		printf("\n\t\t\t");
		if (i == 0 || i == board->_size + 1) printf(" ");
		else printf("%d", i);
		for(int j = 0; j <= board->_size + 1; j++) {
			printf("%c", board->_boardArray[i][j]);
		}
	}
	printf("\n");
}

int placePiece(Board* board, int x, int y) {
	if (board->_validMoves->_movesArray[x][y] != '\0') { 
		flipPieces(board, x+1, y, 1, 0, 0);		// right
		flipPieces(board, x+1, y+1, 1, 1, 0);		// right up
		flipPieces(board, x, y+1, 0, 1, 0);		// up
		flipPieces(board, x-1, y+1, -1, 1, 0);		// left up
		flipPieces(board, x-1, y, -1, 0, 0);		// left
		flipPieces(board, x-1, y-1, -1, -1, 0);		// left down
		flipPieces(board, x, y-1, 0, -1, 0);		// down
		flipPieces(board, x+1, y-1, 1, -1, 0);		// right down
		board->_boardArray[x][y] = board->_turn;
		if (board->_turn == 'b') {
			board->_blackPieces++;
			board->_turn = 'w';
		} else {
			board->_whitePieces++;
			board->_turn = 'b';
		}
		return 1;
	}
	printf("%d\n", board->_validMoves->_movesArray[x][y]);
	return 0;
}

int flipPieces(Board* board, int x, int y, int xChange, int yChange, int flip) {
	char piece = board->_boardArray[x][y];
	char turn = board->_turn;
	if (piece == '-') {
		return 0;
	} else if (piece == '*') {
		return 0;
	} else if (piece == turn) {
		return 1;
	} else {
		flip = flipPieces(board, x + xChange, y + yChange, xChange, yChange, flip);
	}

	if(flip == 1) {
		board->_boardArray[x][y] = turn;
	}
	
	return flip;
}

void checkForMoves(Board* board) {
	ValidMoves* validMoves = board->_validMoves;
	validMoves->_exists = 0;
	for (int k = 1; k <= board->_size; k++) {
		for (int l = 0; l <= board->_size; l++) {
			validMoves->_movesArray[k][l] = 0;
		}
	}

	validMoves->_nextMove->_value = -1;

	for (int i = 1; i <= board->_size; i++) {
		for (int j = 1; j <= board->_size; j++) {
			if (board->_boardArray[i][j] == board->_turn) {
				findMoves(board, i+1, j, 1, 0, 0);		// right
				findMoves(board, i+1, j+1, 1, 1, 0);		// right up
				findMoves(board, i, j+1, 0, 1, 0);		// up
				findMoves(board, i-1, j+1, -1, 1, 0);		// left up
				findMoves(board, i-1, j, -1, 0, 0);		// left
				findMoves(board, i-1, j-1, -1, -1, 0);		// left down
				findMoves(board, i, j-1, 0, -1, 0);		// down
				findMoves(board, i+1, j-1, 1, -1, 0);		// right down
			}
		}	
	}	
	
	return;
}

void findMoves(Board* board, int x, int y, int xChange, int yChange, int count) {
	char piece = board->_boardArray[x][y];
	char turn = board->_turn;
	if (piece == '-') {
		return;
	}
	else if ((piece == turn) || ((piece == '*') && (count == 0))) {
		return;
	} else if ((piece == '*') && (count >= 1)) {
		board->_validMoves->_movesArray[x][y] = count;
		board->_validMoves->_exists = 1;
		if (board->_validMoves->_nextMove->_value < count) {
			board->_validMoves->_nextMove->_x = x;
			board->_validMoves->_nextMove->_y = y;
			board->_validMoves->_nextMove->_value = count;
		}
		return;
	} else {
		count++;
		findMoves(board, x + xChange, y + yChange, xChange, yChange, count);
	}
}
