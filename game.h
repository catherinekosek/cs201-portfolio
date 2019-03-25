#ifndef _game_h
#define _game_h

#include <stdio.h>

#include "player.h"
#include "board.h"

enum mode{twoPlayer, easy, regular};

typedef struct game {
	Player* _player1;
	Player* _player2;
	Board* _board;
	enum mode _mode;
} Game;

Game* newGame();
void playGame();
void takeTurn();

#endif
