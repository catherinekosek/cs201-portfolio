#ifndef _input_h
#define _input_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coordinate.h"

enum programState{character, boardSize, name, coordinate};

enum type{human, easyAI, regularAI};

void startMenu();
int checkForPersistentOptions(char*, enum programState);
enum type promptForGameType();
int promptForBoardSize();
char* promptForName();
Coordinate* promptForCoordinate(int);
int promptForRematch();

#endif
