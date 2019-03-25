#include "display.h"
/*
Display* newDisplay() {
	Display* display = malloc(sizeof(Display));
	display->_game = newGame();
	setMenuDisplay(display);
	return display;	
}

void displayGame(Display* display) {
	printf("displayGame\n");
	printf("%s", display->_game->_mode);
	printDisplay(display, display->_game->_mode);
	char input[10];
	scanf("%s", input);
	while (strcmp(input, "quit") != 0) {
		display->_game->_mode = input;
		printDisplay(display, display->_game->_mode);
		scanf("%s", input);
	}
	checkForMoves(display->_game->_board);
	return;
}

void printDisplay(Display* display, char *input) {
	if(strcmp(input, "menu") == 0) {
		setMenuDisplay(display);
		printf("%s", display->_displayText);
	}else if(strcmp(input, "computer") == 0) {
		setComputerDisplay(display);
		printf("%s", display->_displayText);
	} else if((strcmp(input, "double") == 0) || (strcmp(input, "easy") == 0) || (strcmp(input, "regular") == 0)) {
		setInstructionDisplay(display);
		printf("%s", display->_displayText);
	} else {
		printf("%s", display->_invalidDisplay);
	}
	return;
}

char* _determineMode(char* input) {
	if(strcmp(input, "menu") == 0) {
//		setMenuDisplay(display);
//		printf("%s", display->_displayText);
	}else if(strcmp(input, "computer") == 0) {
//		setComputerDisplay(display);
//		printf("%s", display->_displayText);
	} else if((strcmp(input, "double") == 0) || (strcmp(input, "easy") == 0) || (strcmp(input, "regular") == 0)) {
//		setInstructionDisplay(display);
//		printf("%s", display->_displayText);
	} else {
//		printf("%s", display->_invalidDisplay);
	}
}

void setMenuDisplay(Display* display) {
	display->_displayText = "\n\n\t\tOTHELLO\n\n\
		Welcome to Othello!\n\n\
		At any point, enter \"menu\" to return to this screen.\n\n\
		Please choose the game mode.\n\n\
		Enter \"double\" to start a two-player game.\n\n\
		Enter \"computer\" to play as a single player against the computer.\n\n";
	display->_invalidDisplay = "\n\n\t\tOTHELLO\n\n\
		That input is invalid.\n\n\
		Enter \"double\" to start a two-player game.\n\n\
		Enter \"computer\" to play as a single player against the computer.\n\n";
	return;
}

void setComputerDisplay(Display* display) {
	display->_displayText = "\n\n\t\tOTHELLO\n\n\
		You have selected to play against the computer.\n\n\
		Please select a level of difficulty.\n\n\
		Enter \"easy\" or \"regular\".\n\n";
	display->_invalidDisplay = "\n\n\t\tOTHELLO\n\n\
		That input is invalid.\n\n\
		Enter \"menu\" to return to the home screen.\n\n\
		Enter \"easy\" or \"regular\" to select a level of difficulty.\n\n";
	return;
}

void setInstructionDisplay(Display* display) {
	display->_displayText = "\n\n\t\tOTHELLO\n\n\
		The board will be displayed as above.\n\n\
		The numbers and letters along the side of the grid are used as identifiers for rows and columns.\n\n\
		An asterisk * represents any emppty square.\n\n\
		A w represents a square with a white piece played on it.\n\n\
		A b represents a square with a black piece played on it.\n\n\
		Players take turns placing pieces, with black going first.\n\n\
		A piece of one color must be placed on the board such that there is a\n\
		horizontal, vertical, or diagonal line between the new piece and an\n\
		existing piece of the same color, and there must be one or more contiguous\n\
		pieces of the opposite color between these two pieces.\n\n\
		To place a piece, enter the coordinates of a valid square. For example,\n\
		to place a black piece in the sample board above in the square above the\n\
		top-left white piece, enter \"d6\".\n\n\
		Enter \"start\" to start gameplay.\n\n";
	display->_invalidDisplay = "\n\n\t\tOTHELLO\n\n\
		That input is invalid.\n\n\
		Enter \"menu\" to return to the home screen.\n\n\
		Enter \"next\" to start gameplay.\n\n";
	return;
}
*/
