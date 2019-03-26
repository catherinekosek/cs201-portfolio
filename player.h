#ifndef _player_h
#define _player_h

#include <stdlib.h>

enum type{human, easyAI, regularAI};

typedef struct player{
	enum type type;
	char piece;
	int wins;	
} Player;

Player* newPlayer(char, enum type);

#endif
