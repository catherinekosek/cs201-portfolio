#ifndef _board_h
#define _board_h

#include <stdio.h>
#include <stdlib.h>

typedef struct board {
	int size;
	char* boardArray;
	int whitePieces;
	int blackPieces;
} Board;

Board* newBoard(int);
void destructBoard(Board*);
void printBoard(Board*);
void placePiece(Board*, int, int, char);
int flipPieces(Board*, int, int, int, int, int, char);

#endif

