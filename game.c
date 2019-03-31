#include "game.h"

/* Constructor for a new Game:
	Prompt user for size of Game board and for Game type
	Allocate space for Game
	Create Board and Players for Game
	Set the turn to Player 1 
	Return a pointer to the Game 
*/
Game* newGame() {
	enum type type = promptForGameType();
	int size = promptForBoardSize();

	Game* game = malloc(sizeof(Game));
	game->board = newBoard(size);	
	game->player1 = newPlayer('b', human, size+2, 0);
	game->player2 = newPlayer('w', type, size+2, 0);
	game->turn = game->player1;
	
	return game;
}

/* Destructor for Game:
	Destruct Player and Board components using respective destructors
	Free space allocated for Game
*/
void destructGame(Game* game) {
	destructPlayer(game->player1);
	destructPlayer(game->player2);
	destructBoard(game->board);
	free(game);
	return;
}

/* Controls logic of gameplay for a Game:
	While there is no win, a player takes a turn
		Human turn prompts for input, AI turn does not
	Once the Game is won, display winner and score
	Begin rematch of Game
*/ 
void playGame(Game* game) {
	int win = checkForWin(game);
	
	while(win == 0) {
		if (game->turn->type == human) takeHumanTurn(game);
		else takeAITurn(game);
		win = checkForWin(game);
	}
	
	printf("\nGame over! Final board:\n");
	printBoard(game->board);
	if (game->board->blackPieces > game->board->whitePieces) { 
		printf("\n\n%s won!\n", game->player1->name);
		game->player1->wins++;
	}
	else { 
		printf("\n\n%s won!\n", game->player2->name);
		game->player2->wins++;
	}
	printf("\nWins:\n%s: %d\t%s: %d\n\n", game->player1->name, game->player1->wins, game->player2->name, game->player2->wins);
	
	int rematchOrMenu = promptForRematch();
	if (rematchOrMenu == 1) rematch(game);
	else destructGame(game);
	
	return;
}

/* Sets up Game for an another round:
	Destructs Board
	Creates a new Board
	Switches the Players, so player2 from the previous game now goes first
	Switches the pieces for the Players
	Starts the new Game
*/
void rematch(Game* game) {
	int size = game->board->size - 2;	// remove buffer

	destructBoard(game->board);
	game->board = newBoard(size);

	game->turn = game->player2;
	game->player2 = game->player1;
	game->player1 = game->turn;

	game->player1->piece = 'b';
	game->player2->piece = 'w';

	playGame(game);
	return;
}

/* Checks for win:
	checkForMoves on Board for Player turn
	If a move exists for Player turn: return 0, there is no win
	If a move does not exist for Player turn:
		Set turn to Player's opponent
		checkForMoves on Board for new Player turn
		If a move exists for Player turn: return 0, there is no win
		If a move does not exist for Player turn: return 1, the game is over
*/
int checkForWin(Game* game) {
	checkForMoves(game->board, game->turn);
	if (game->turn->moveExists == 1) {
		return 0;
	} else {
		char* temp = game->turn->name;	// stored for display purposes
		if (game->turn == game->player1) game->turn = game->player2;
		else game->turn = game-> player1;
		checkForMoves(game->board, game->turn);
		if (game->turn->moveExists == 1) {
			printf("\n%s has no moves! Skipping to %s's turn.\n", temp, game->turn->name);
			return 0;
		}
	}
	return 1; 
}

/* Control and display for a user turn:
	Indicate to the user whose turn it is
	Print the Board
	Prompt user to input a move
	Check if move is valid
	Prompt again if invalid, placePiece and switch the turn if valid
*/
void takeHumanTurn(Game* game) {
	printf("\n\n%s's turn.\n", game->turn->name);
	printBoard(game->board);
	Coordinate* coordinate = promptForCoordinate(game->board->size);
	if (*(game->board->validMoves + coordinate->r * game->board->size + coordinate->c) == 0) {
		printf("\n\nRow %d, Column %d is not a valid move. Try again, or enter \"instructions\" for gameplay instructions.\n", coordinate->r, coordinate->c);
		takeHumanTurn(game);
	} else {
		placePiece(game->board, coordinate->r, coordinate->c, game->turn->piece);
		if (game->turn == game->player1) game->turn = game->player2;
		else game->turn = game->player1;
	}
	return;
}

/* Control and display for an AI turn:
	Indicate to the user whose turn it is
	Print the board
	Indicate to the user where the piece is being placed
	Place the piece at location r,c from nextMove on the Board, calculated in checkForMoves
	Switch the turn
*/
void takeAITurn(Game* game) {
	printf("\n\n%s's turn.\n", game->turn->name);
	printBoard(game->board);
	printf("\nPlacing piece in row %d, column %d.\n", game->turn->nextMove->r, game->turn->nextMove->c);
	placePiece(game->board, game->turn->nextMove->r, game->turn->nextMove->c, game->turn->piece);
	if (game->turn == game->player1) game->turn = game->player2;
	else game->turn = game->player1;
	return;
}
