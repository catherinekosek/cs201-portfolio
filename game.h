#ifndef _game_h
#define _game_h

#include <stdio.h>
#include <string.h>

#include "board.h"
#include "player.h"

enum mode{twoPlayer, easy, regular};

typedef struct game {
	Board* board;
	enum mode mode;
	Player* player1;
	Player* player2;
	Player* turn;
} Game;

Game* newGame(char* mode, int size);
int checkForWin(Game* game);
void playGame(Game* game);
void takeHumanTurn(Game* game);
void takeAITurn(Game* game);

#endif
