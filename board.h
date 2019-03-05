#ifndef _board_h
#define _board_h

#include <stdio.h>
#include <stdlib.h>
#include "square.h"

typedef struct board {
	Square* _boardArray[8][8];
} Board;

Board* newBoard();
void printBoard(Board*);
void placePiece(Board*, int, int, char);
int flipPieces(Board*, int, int, int, int, char, int);
void checkForMoves(Board*, char);
void findMoves(Board*, int**, int, int, int, int, char, int, int);

#endif

