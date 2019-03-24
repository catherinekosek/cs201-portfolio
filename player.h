#ifndef _player_h
#define _player_h

#include <stdlib.h>

typedef struct player{
	char _piece;
	int _wins;
	int _score;	
} Player;

Player* newPlayer(char);

#endif
