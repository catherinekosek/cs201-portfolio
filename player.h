#ifndef _player_h
#define _player_h

#include <stdlib.h>

#include "board.h"

enum type{human, easyAI, regularAI};

typedef struct coordinate {
	int x;
	int y;
	int value;
} Coordinate;

typedef struct player{
	enum type type;
	char piece;
	int wins;
	int* validMoves;
	int moveExists;
	Coordinate* nextMove;
	int* moveWeights;
} Player;

Player* newPlayer(char, enum type, int);
void checkForMoves(Player*, Board*);
void findMoves(Player*, Board*, int, int, int, int, int);
void buildRegularAITable(Player*, int);

#endif
