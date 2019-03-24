#ifndef _board_h
#define _board_h

#include <stdio.h>
#include <stdlib.h>
#include "square.h"

typedef struct validMoves {
	int _exists;
	char _movesArray[10][10];
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
void placePiece(Board*, int, int);
int flipPieces(Board*, int, int, int, int, int);
void checkForMoves(Board*);
void findMoves(Board*, ValidMoves*, int, int, int, int, int);

#endif

