#ifndef _board_h
#define _board_h

#include <stdio.h>
#include <stdlib.h>

#include "player.h"

typedef struct board {
	char* boardArray;
	int* validMoves;
	int* visited;

	int size;
	int whitePieces;
	int blackPieces;
} Board;

Board* newBoard(int);
void destructBoard(Board*);
void printBoard(Board*);
void placePiece(Board*, int, int, char);
int flipPieces(Board*, int, int, int, int, int, char);
void checkForMoves(Board*, Player*);
void DFS(Board*, Player*, int, int);
void findMoves(Board*, Player*, int, int, int, int, int);

#endif

