#ifndef _display_h
#define _display_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct display {
	char *_displayText;
	char *_invalidDisplay;
} Display;

Display *newDisplay();
void printDisplay(Display*, char*);
void setMenuDisplay(Display*);
void setComputerDisplay(Display*);
void setInstructionDisplay(Display*);

#endif 
