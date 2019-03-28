#include "input.h"

Coordinate* promptForCoordinate(int size) {
	char input[size];
	printf("Enter the row number you wish to place piece in:\n");
	fgets(input, size, stdin);
	int x = atoi(input);
	while (x == 0 || x > size) {
		printf("That input is not valid. Enter the numerical digit for the row number you wish to place piece in.\n");
		fgets(input, size, stdin);
		x = atoi(input);
	}
	printf("Enter the column number you wish to place piece in:\n");
	fgets(input, size, stdin);
	int y = atoi(input);
	while (y == 0 || y > size) {
		printf("That input is not valid. Enter the numerical digit for the row number you wish to place piece in.\n");
		fgets(input, size, stdin);
		y = atoi(input);
	}
	Coordinate* coordinate = newCoordinate(x, y);
	return coordinate;
}

enum mode promptForGameType() {
	char input[20];
	enum mode mode = invalid;
	while (mode == invalid) {
		printf("Enter the type of game you wish to play. Options are:\ntwo player\neasy\nregular\n\n");
		fgets(input, 20, stdin);
		if (strncmp(input, "two player\n", 20) == 0) mode = twoPlayer;
		else if (strncmp(input, "easy\n", 20) == 0) mode = easy;
		else if (strncmp(input, "regular\n", 20) == 0) mode = regular;
		else printf("\nYour input is invalid. Remember to enter input all lowercase with no additional spaces or characters.\n");
	}
	return mode;
}

int promptForBoardSize() {
	char input[6];
	printf("Enter a numerical digit for the size of board you wish to play on.\n");
	fgets(input, 6, stdin);
	int size = atoi(input);
	while (size == 0 || size < 8 || size % 4 != 0) {
		printf("That input is not valid. Enter the size of board you wish to play on.\n");
		fgets(input, 6, stdin);
		size = atoi(input); 
	}
	return size;
}
