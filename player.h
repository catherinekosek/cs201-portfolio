#ifndef _player_h
#define _player_h

#include <stdlib.h>

#include "board.h"

enum type{human, easyAI, regularAI, invalid};

typedef struct coordinate {
	int r;
	int c;
	int value;
} Coordinate;

typedef struct player{
	int* validMoves;
	int* visited;
	Coordinate* nextMove;
	int* moveWeights;

	char piece;
	enum type type;
	int wins;
	int moveExists;

} Player;

Player* newPlayer(char, enum type, int, int);
void destructPlayer(Player* player);
void checkForMoves(Player*, Board*);
void DFS(Player*, Board*, int, int);
void findMoves(Player*, Board*, int, int, int, int, int);
void buildRegularAITable(Player*, int);

#endif
