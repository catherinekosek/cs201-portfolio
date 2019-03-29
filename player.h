#ifndef _player_h
#define _player_h

#include <stdlib.h>

#include "board.h"
#include "coordinate.h"

enum type{human, easyAI, regularAI, invalid};

typedef struct player{
	enum type type;
	char piece;
	int wins;
	int* validMoves;
	int* visited;
	int moveExists;
	Coordinate* nextMove;
	int* moveWeights;
} Player;

Player* newPlayer(char, enum type, int, int);
Player* rematchPlayer(Player*, int);
void DFS(Player*, Board*, int, int);
void checkForMoves(Player*, Board*);
void findMoves(Player*, Board*, int, int, int, int, int);
void buildRegularAITable(Player*, int);

#endif
