#include "input.h"

const int inputSize = 20;

const char menuString[] = "\nWELCOME TO OTHELLO\n\n\
Enter your selection exactly as the options are shown. Check spelling, and make sure any input is entered only\n\
as lowercase characters, followed by a single press of the \"Enter\" key. Do not add any extra characters or spaces.\n\
Input entered must be 20 characters or less. Any input longer than 20 characters will print multiple error messages.\n\n\
At any time prompted for user input:\n\
Enter \"instructions\" for gameplay instructions.\n\
Enter \"help\" for detailed tips on entering input.\n\
Enter \"quit\" to exit the program.\n\n\
Enter \"start\" to start the game.\n";

const char gameplayInstructions[] = "\n\nGAMEPLAY INSTRUCTIONS\n\n\
A standard Othello board is 8x8 squares.\n\
Pieces can be either black, represented as a \"b\", or white, represented by a \"w\".\n\
An empty square is represented by an asterik, \"*\".\n\
When the gameboard is printed, the numbers down the left side represent the row numbers.\n\
Numbers across the top of the board represent the column numbers.\n\n\
A piece of one color must be placed in an empty location such that there is a horizontal, vertical,\n\
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
	
const char gameTypePrompt[] = "\nGame options are:\n\
Enter \"two player\" to play against another person.\n\
Enter \"easy\" to play against an artificial intelligence.\n\
Enter \"regular\" to play against a more strategic artificial intelligence.\n\
		Keep in mind that this AI is optimal on an 8x8 board and is less challenging on larger boards.\n\n\
Enter your game type selection.\n";

const char boardSizePrompt[] = "\nTraditionally, the Othello game board is 8x8. This size is recommended.\n\
For this game, game boards can be any multiple of four greater than or equal to 8.\n\
Very large boards will not display properly on screen. A game board larger than 40x40 is not recommended.\n\
Game boards are square, so only one number is entered.\n\n\
Enter your desired game board size in numeric digits.\n";

const char namePrompt[] = "\nPlayer name can consist of numbers, letters, and special characters, but must be 20 characters or less.\n\n\
Enter player name.\n";

const char coordinateRowPrompt[] = "\nEnter the row number, referencing the numbers to the left of the board, of the location you wish to place a piece.\n";

const char coordinateColumnPrompt[] = "\nEnter the column number, referencing the numbers above the board, of the location you wish to place a piece.\n";

const char rematchPrompt[] = "\nEnd of game options are:\n\
Enter \"rematch\" to play again with same game type and same board size.\n\
Enter \"menu\" to start over and select different game options.\n\
Enter \"quit\" at any time to close the program.\n\n\
Enter your selection.\n";

const char characterHelp[] = "\n\nINPUT HELP\n\
Enter your selection exactly as the options are shown. Check spelling, and make sure any input is entered only\n\
as lowercase characters, followed by a single press of the \"Enter\" key. Do not add any extra characters or spaces.\n\
Input entered must be 20 characters or less. Any input longer than 20 characters will print multiple error messages.\n";

const char boardSizeHelp[] = "\n\nBOARD SIZE INPUT HELP\n\
Enter the board size as a numeric digit, followed by a single press of the \"Enter\" key.\n\
For example, enter \"8\", not \"eight\".\n\
Do not add any extra characters or spaces.\n\n\
Since board sizes are square, only one number is entered, and this becomes both the number\n\
of rows and the number of columns for the board.\n\n\
A valid board size must be a whole number, larger than 8, and a multiple of 4.\n";

const char nameHelp[] = "\n\nENTER NAME HELP\n\
Player name is used to display wins across multiple games.\n\
In a two player game, both users enter their names. When playing against the computer, the user enters only their name.\n\
Names can be any combination of letters, numbers, and symbols, as long as they are 20 characters or less.\n";

const char coordinateHelp[] = "\n\nENTER COORDINATE HELP\n\
Pieces can be either black, represented as a \"b\", or white, represented by a \"w\".\n\
An empty square is represented by an asterik, \"*\".\n\
To place a piece on an empty square, you will first be prompted to enter the row number of the\n\
empty square you wish to place the piece on. Then you will be prompted to enter the column number.\n\n\
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
gameplay \"instructions\" for specification on valid moves.\n";

/* Displays start menu and instructions once at beginning of program execution
   "start" must be entered to continue
*/
void startMenu() {
	char input[inputSize];
	printf("%s", menuString);
	fgets(input, inputSize, stdin);
	int help = checkForPersistentOptions(input, character);
	while (1) {
		if (strncmp(input, "start\n", inputSize) == 0) return;
		else if (help == 0) printf("\nThat input is invalid.");
		printf("\nEnter \"start\" to start the game.\n");
		fgets(input, inputSize, stdin);
		help = checkForPersistentOptions(input, character);
	}
}

/* Checks if any persistent command has been entered
	"instructions" - display gameplay instructions
	"help" - display help based on currentState of the program
	"quit" - stops program execution

   Return 0 if input does not match any of these commands
   Return 1 if input matches one of these commands
*/
int checkForPersistentOptions(char* input, enum programState currentState) {
	if (strncmp(input, "instructions\n", 20) == 0) printf("%s", gameplayInstructions);
	else if (strncmp(input, "help\n", 10) == 0) {
		if (currentState == boardSize) printf("%s", boardSizeHelp);
		else if (currentState == name) printf("%s", nameHelp); 
		else if (currentState == coordinate) printf("%s", coordinateHelp);
		else printf("%s", characterHelp);
	}
	else if (strncmp(input, "quit\n", 10) == 0) exit(0);
	else return 0;
	
	return 1;
}

/* Prompts user to enter the type of game to play:
	"two player" - user vs another user
	"easy" - user vs easyAI
	"regular" - user vs regularAI
   Return the type indicated
*/
enum type promptForGameType() {
	char input[inputSize];
	int help;
	while (1) {
		printf("%s", gameTypePrompt);
		fgets(input, inputSize, stdin);
		help = checkForPersistentOptions(input, character);
		if (strncmp(input, "two player\n", inputSize) == 0) return human;
		else if (strncmp(input, "easy\n", inputSize) == 0) return easyAI;
		else if (strncmp(input, "regular\n", inputSize) == 0) return regularAI;
		else if (help == 0) printf("\nThat input is invalid.");
	}
}

/* Prompts user to enter the size of board to play on:
	Must be greater than 8 
	Must be a multiple of 4
   Return the size entered
*/
int promptForBoardSize() {
	char input[inputSize];
	printf("%s", boardSizePrompt);
	fgets(input, inputSize, stdin);
	int help = checkForPersistentOptions(input, boardSize);
	int size = atoi(input);
	while (size < 8 || (size % 4) != 0) {
		if (help == 0) printf("\nThat input is invalid.");
		printf("%s", boardSizePrompt);
		fgets(input, inputSize, stdin);
		help = checkForPersistentOptions(input, boardSize);
		size = atoi(input); 
	}
	return size;
}

/* Prompts user to enter their name:
	Any characters allowed
	Must be inputSize characters or less
	Remove the \n character from the input
   Return the name entered
*/
char* promptForName() {
	char* input = (char *)malloc(sizeof(char) * inputSize);
	printf("%s", namePrompt); 
	fgets(input, inputSize, stdin);
	int help = checkForPersistentOptions(input, name);
	while (help) {
		printf("%s", namePrompt);
		fgets(input, inputSize, stdin);
		help = checkForPersistentOptions(input, name);
	}
	for (int i = 0; i < inputSize; i++) if (input[i] == '\n') input[i] = '\0';
	return input;
}

/* Prompts user to enter coordinate for placing a piece:
	Prompt for row, then
	Prompt for column
	Row or column must be less than size of board
*/
Coordinate* promptForCoordinate(int size) {
	char input[inputSize];
	printf("%s", coordinateRowPrompt);
	fgets(input, inputSize, stdin);
	int help = checkForPersistentOptions(input, coordinate);	
	int r = atoi(input);
	while (r == 0 || r > size) {
		if (help == 0) printf("That input is invalid.");
		printf("%s", coordinateRowPrompt);
		fgets(input, inputSize, stdin);
		help = checkForPersistentOptions(input, coordinate);
		r = atoi(input);
	}

	printf("%s", coordinateColumnPrompt);
	fgets(input, inputSize, stdin);
	help = checkForPersistentOptions(input, coordinate);
	int c = atoi(input);
	while (c == 0 || c > size) {
		if (help == 0) printf("That input is invalid.");
		printf("%s", coordinateColumnPrompt);
		fgets(input, inputSize, stdin);
		help = checkForPersistentOptions(input, coordinate);
		c = atoi(input);
	}

	Coordinate* coordinate = newCoordinate();
	coordinate->r = r;
	coordinate->c = c;
	return coordinate;
}

/* Prompts user for rematch or return to menu:
	"rematch" - play another game with same players and board size
	"menu" - reselect game type and board size

   Return 0 if returning to menu
   Return 1 if rematching 
*/
int promptForRematch() {
	char input[inputSize];
	int help;
	while (1) {
		printf("%s", rematchPrompt);
		fgets(input, inputSize, stdin);
		help = checkForPersistentOptions(input, character);
		if (strncmp(input, "rematch\n", inputSize) == 0) return 1;
		else if (strncmp(input, "menu\n", inputSize) == 0) return 0;
		else if (help == 0) printf("\nThat input is invalid.");
	}	
}
