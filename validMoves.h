#ifndef _validMoves_h_
#define _validMoves_h_

#include "board.h"

typedef struct coordinate {
	int x;
	int y;
	int value;
} Coordinate;

typedef struct validMoves {
	int exists;
	int movesArray[10][10];
	Coordinate* nextMove;
	Board* board;
} ValidMoves;

ValidMoves* newValidMoves(Board*);
int validateMove(ValidMoves*, int, int);
void checkForMoves(ValidMoves*, char);
void findMoves(ValidMoves*, int, int, int, int, int, char);

#endif

