#ifndef _player_h
#define _player_h

#include <stdlib.h>

#include "coordinate.h"
#include "input.h"

typedef struct player{
	Coordinate* nextMove;
	int* moveWeights;
	char* name;
	
	char piece;
	enum type type;
	int wins;
	int moveExists;

} Player;

Player* newPlayer(char, enum type, int);
void destructPlayer(Player* player);
void buildRegularAITable(Player*, int);

#endif
