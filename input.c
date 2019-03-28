#include "input.h"

enum programState currentState;

const char menuString[] = "\nWELCOME TO OTHELLO\n\n\
At any time prompted for user input:\n\
Enter \"help\" for detailed gameplay and input instructions. This will not exit the game.\n\
Enter \"quit\" to exit the program.\n\n\
Enter \"start\" to start the game.\n\n";

const char gameplayInstructions[] = "\nGAMEPLAY INSTRUCTIONS\n\n\
A standard Othello board is 8x8 squares.\n\
Pieces can be either black, represented as a \"b\", or white, represented by a \"w\".\n\
An empty square is represented by an asterik, \"*\".\n\
When the gameboard is printed, the numbers down the left side represent the row numbers.\n\
Numbers across the top of the board represent the column numbers.\n\n\
A piece of one color must be placed in an empty such that there is a horizontal, vertical,\n\
or diagonal line between the new piece and an existing piece of the same color.\n\n\
In between the piece placed and the existing piece of the same color, there must be one or\n\
more contiguous pieces of the opposite color. There cannot be any empty spaces between the\n\
new piece and the existing piece of the same color.\n\n\
For example, if a row of the board is ***bw***, a black piece could be placed to the right of\n\
the white piece, like ***bwb**, because there is a horizontal line between the two black pieces,\n\
and there is at least one white piece in between.\n\n\
The pieces of opposite color between the new and existing piece are then flipped to match the\n\
color of the new and existing pieces.\n\n\
For example, in the move above, the white piece would be flipped and the row would become ***bbb**.\n\n\
If a player can not make a move, their turn is skipped.\n\
If neither player can make moves, the game is over, regardless of whether or not the board is full.\n\n\
The winner is the player with the most pieces of their color on the board.\n\n";
	
const char menuInputHelp[] = "\nMENU INPUT\n\n\
Enter your selection exactly as the options appear. Check spelling, and make sure input is\n\
entered as only lowercase characters, followed by a single press of the \"Enter\" key. Do not\n\
add any extra characters or spaces.\n\n\
Your input options are:\n\
Enter \"help\" for detailed gameplay and input instructions. This will not exit the game.\n\
Enter \"quit\" to exit the program.\n\n";

const char boardSizeInputHelp[] = "\nBOARD SIZE INPUT\n\n\
Enter the board size as a numeric digit, followed by a single press of the \"Enter\" key.\n\
For example, enter \"8\", not \"eight\".\n\
Do not add any extra characters or spaces.\n\n\
Since board sizes are square, only one number is entered, and this becomes both the number\n\
of rows and the number of columns for the board.\n\n\
A valid board size must be a whole number, larger than 8, and a multiple of 4.\n\n";

const char gameTypeInputHelp[] = "\nGAME TYPE INPUT\n\n\
Enter your selection exactly as the options appear. Check spelling, and make sure input is\n\
entered as only lowercase characters, followed by a single press of the \"Enter\" key. Do not\n\
add any extra characters or spaces.\n\n\
Your input options are:\n\
Enter \"two player\" to play against another person.\n\
Enter \"easy\" to play against an artificial intelligence.\n\
Enter \"regular\" to play against a more strategic artificial intelligence. Keep in mind that\n\
		this AI is optimal on a 8x8 board and is less challenging on larger boards.\n\n";

const char enterCoordinateInputHelp[] = "\nPLACE PIECE INPUT\n\n\
To place a piece on an empty square, you will first be prompted to enter the row number of the\n\
empty square you wish to place the piece on. Then you will be prompted for the column number.\n\n\
The row number refers to the number to the left of the board that corresponds to the row of the\n\
desired empty square. The column number refers to the number above the board that corresponds\n\
to the desired empty square.\n\n\
Prompts occur separately, so enter input separately. Enter the row number as a numeric digit,\n\
followed by a single press of the \"Enter\" key. Then, enter the column number as a a numeric \n\
digit, followed by a single press of the \"Enter\" key. For example, enter \"3\" and then \"4\".\n\n\
A row or column number will never be smaller than 1, and it will never be larger than the board\n\
size specified. Inputs less than 1 or larger than the size of the board are invalid.\n\n\
If you receive an error stating that the input is invalid, you are not entering the row and column\n\
numbers correctly. However, if you receive an error that the move is invalid, the row and column numbers\n\
were entered correctly, but the specified square is not a valid move in gameplay. Please refer to\n\
gameplay instructions for specification on valid moves.\n\n";

void startMenu() {
	char input[15];
	printf("%s", menuString);
	fgets(input, 15, stdin);
	int help = checkForPersistentOptions(input);
	while (strncmp(input, "start\n", 15) != 0) {
		if (help != -1) printf("Invalid input. Enter \"start\" to start the game.\n");
		else printf("Enter \"start\" to start the game.\n");
		fgets(input, 15, stdin);
		help = checkForPersistentOptions(input);
	}
}

int checkForPersistentOptions(char* input) {
	if (strncmp(input, "help\n", 10) == 0) {
		printf("\nWould you like help with gameplay or with input?\n\
Enter \"instructions\" to view gameplay instructions.\n\
Enter \"input\" to view detailed instructions on entering input for this screen.\n\
Enter \"done\" to exit help.\n");
		char helpInput[15];
		fgets(helpInput, 15, stdin);
		checkForPersistentOptions(helpInput);
		int exit = 1;
		while (exit) {
			if (strncmp(helpInput, "instructions\n", 15) == 0) {
				printf("%s", gameplayInstructions);
				exit = 0;
			}
			else if (strncmp(helpInput, "input\n", 15) == 0) {
				switch (currentState) {
					case menu: 
						printf("%s", menuInputHelp);
						exit = 0;
						break;
					case boardSize:
						printf("%s", boardSizeInputHelp);
						exit = 0;
						break;
					case gameType:
						printf("%s", gameTypeInputHelp);
						exit = 0;
						break;
					case enterCoordinate:
						printf("%s", enterCoordinateInputHelp);
						exit = 0;
						break;
				}
			} else if (strncmp(helpInput, "done\n", 15) == 0) return -1;
			else {
				printf("Invalid input. Input options are:\n\
Enter \"instructions\" to view gameplay instructions.\n\
Enter \"input\" to view detailed instructions on entering input for this screen.\n\
Enter \"done\" to exit help.\n");
				fgets(helpInput, 15, stdin);
				checkForPersistentOptions(helpInput);
			}
		}
		printf("Enter \"done\" to exit help and enter other input.\n");
		fgets(helpInput, 15, stdin);
		checkForPersistentOptions(helpInput);
		while (strncmp(helpInput, "done\n", 15) != 0) {
			printf("That input is invalid. Please enter \"done\" to exit help, then enter other input.\n");
			fgets(helpInput, 15, stdin);
			checkForPersistentOptions(helpInput);
		}
		return -1;
	}
	else if (strncmp(input, "quit\n", 10) == 0) exit(0);
	return 0;
}

Coordinate* promptForCoordinate(int size) {
	currentState = enterCoordinate;
	char input[size];
	printf("Enter the row number you wish to place piece in:\n");
	fgets(input, size, stdin);
	int help = checkForPersistentOptions(input);	 // if help = -1, user asked for help and invalid message should not be displayed
	int x = atoi(input);
	while (x == 0 || x > size) {
		if (help != -1) printf("That input is not valid. Enter the numerical digit for the row number you wish to place piece in.\n");
		else printf("Enter the row number you wish to place piece in:\n");
		fgets(input, size, stdin);
		help = checkForPersistentOptions(input);
		x = atoi(input);
	}
	printf("Enter the column number you wish to place piece in:\n");
	fgets(input, size, stdin);
	help = checkForPersistentOptions(input);
	int y = atoi(input);
	while (y == 0 || y > size) {
		if (help != -1) printf("That input is not valid. Enter the numerical digit for the row number you wish to place piece in.\n");
		else printf("Enter the column number you wish to place piece in:\n");
		fgets(input, size, stdin);
		help = checkForPersistentOptions(input);
		y = atoi(input);
	}
	Coordinate* coordinate = newCoordinate(x, y);
	return coordinate;
}

enum type promptForGameType() {
	currentState = gameType;
	char input[20];
	enum type type = invalid;
	int help;
	while (type == invalid) {
		printf("\nEnter the type of game you wish to play. Options are:\ntwo player\neasy\nregular\n\n");
		fgets(input, 20, stdin);
		help = checkForPersistentOptions(input);
		if (strncmp(input, "two player\n", 20) == 0) type = human;
		else if (strncmp(input, "easy\n", 20) == 0) type = easyAI;
		else if (strncmp(input, "regular\n", 20) == 0) type = regularAI;
		else if (help != -1) printf("\nYour input is invalid. Remember to enter input all lowercase with no additional spaces or characters.\n");
		else printf("Enter the type of game you wish to play. Options are:\ntwo player\neasy\nregular\n\n");
	}
	return type;
}

int promptForBoardSize() {
	currentState = boardSize;
	char input[6];
	printf("\nEnter a numerical digit for the size of board you wish to play on.\n");
	fgets(input, 6, stdin);
	int help = checkForPersistentOptions(input);
	int size = atoi(input);
	while (size == 0 || size < 8 || size % 4 != 0) {
		if (help != -1) printf("That input is not valid. Enter the size of board you wish to play on.\n");
		else printf("Enter a numerical digit for the size of the board you wish to play on.\n");
		fgets(input, 6, stdin);
		help = checkForPersistentOptions(input);
		size = atoi(input); 
	}
	return size;
}
