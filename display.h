#ifndef _display_h
#define _display_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"

typedef struct display {
	Game* _game;
	char *_displayText;
	char *_invalidDisplay;
} Display;

Display *newDisplay();
void displayGame(Display*);
void printDisplay(Display*, char*);
void setMenuDisplay(Display*);
void setComputerDisplay(Display*);
void setInstructionDisplay(Display*);

#endif 
