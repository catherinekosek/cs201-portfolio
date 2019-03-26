#ifndef _game_h
#define _game_h

#include <stdio.h>
#include <string.h>

#include "board.h"
#include "validMoves.h"
#include "player.h"

enum mode{twoPlayer, easy, regular};

typedef struct game {
	Board* board;
	ValidMoves* validMoves;
	enum mode mode;
	Player* player1;
	Player* player2;
	char turn;
} Game;

Game* newGame(char* mode);
int checkForWin(Game* game);
void playGame(Game* game);
void takeHumanTurn(Game* game);
void takeEasyAITurn(Game* game);

#endif
