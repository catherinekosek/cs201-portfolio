#ifndef _input_h
#define _input_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "game.h"

enum programState{menu, boardSize, gameType, enterCoordinate};

typedef struct input{
	char* stringDisplay;
} Input;

void startMenu();
int checkForPersistentOptions(char*);
Coordinate* promptForCoordinate(int);
enum type promptForGameType();
int promptForBoardSize();

#endif
