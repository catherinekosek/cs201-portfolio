#ifndef _input_h
#define _input_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "coordinate.h"
#include "game.h"

typedef struct input{
	char* stringDisplay;
} Input;

Coordinate* promptForCoordinate(int);
enum mode promptForGameType();
int promptForBoardSize();

#endif
