#ifndef _board_h
#define _board_h

#include <stdio.h>
#include <stdlib.h>
#include "square.h"

typedef struct coordinate {
	int _x;
	int _y;
	int _value;
} Coordinate;

typedef struct validMoves {
	int _exists;
	int _movesArray[10][10];
	Coordinate* _nextMove;
} ValidMoves;

typedef struct board {
	int _size;
	char  _boardArray[10][10];
	ValidMoves* _validMoves;
	char _turn;
	int _whitePieces;
	int _blackPieces;
} Board;

Board* newBoard(int);
void printBoard(Board*);
int placePiece(Board*, int, int);
int flipPieces(Board*, int, int, int, int, int);
void checkForMoves(Board*);
void findMoves(Board*, int, int, int, int, int);

#endif

