#ifndef _game_h
#define _game_h

#include <stdio.h>

#include "board.h"
#include "player.h"
#include "input.h"

typedef struct game {
	Board* board;
	Player* player1;
	Player* player2;
	Player* turn;
} Game;

Game* newGame();
void destructGame(Game* game);
void playGame(Game* game);
void rematch(Game* game);
int checkForWin(Game* game);
void takeHumanTurn(Game* game);
void takeAITurn(Game* game);

#endif
