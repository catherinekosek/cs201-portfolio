#include "game.h"
#include "input.h"

/* Main method of the program
	Displays the starting message
	playGame in a continous loop
		exited through exit(0) method if user enters "quit"
*/
int main(int argc, char* argv[]) {
	startMenu();
	while (1) {
		Game* game = newGame();
		playGame(game);	
	}
	return 0;
}
