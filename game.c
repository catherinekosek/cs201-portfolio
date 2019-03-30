#include "game.h"

/* Constructor for a new Game
	Prompt user for size of Game board and for Game type
	Allocate space for Game
	Create Board and Players for Game
	Set the turn to Player 1 
	Return a pointer to the Game 
*/
Game* newGame() {
	int size = promptForBoardSize();
	enum type type = promptForGameType();

	Game* game = malloc(sizeof(Game));
	game->board = newBoard(size);	
	game->player1 = newPlayer('b', easyAI, size+2, 0);
	game->player2 = newPlayer('w', type, size+2, 0);
	game->turn = game->player1;
	
	return game;
}

/* Controls logic of gameplay for a Game
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

	printBoard(game->board);
	if (game->board->blackPieces > game->board->whitePieces) { 
		printf("\n\nPlayer 1 won!\n");
		game->player1->wins++;
	}
	else { 
		printf("\n\nPlayer 2 won!\n");
		game->player2->wins++;
	}
	printf("\nCurrent Score:\nPlayer 1: %d\tPlayer 2: %d\n\n", game->player1->wins, game->player2->wins);
	rematch(game);
	printf("\n\nPlayer 1 and Player 2 switch!\n");
	return;
}

void rematch(Game* game) {
	int size = promptForBoardSize();
	enum type type1 = game->player1->type;
	int wins1 = game->player1->wins;
	enum type type2 = game->player2->type;
	int wins2 = game->player2->wins;	

	// creating a clean slate - seg faults otherwise
	free(game->player1->validMoves);
	free(game->player2->validMoves);
	free(game->player1->nextMove);
	free(game->player2->nextMove);
	if (type1 == regularAI) free(game->player1->moveWeights);
	if (type2 == regularAI) free(game->player2->moveWeights);
	free(game->player1);
	free(game->player2);
	free(game->board);
	free(game);

	Game* newGame = malloc(sizeof(Game));
	newGame->board = newBoard(size);
	newGame->player1 = newPlayer('b', type2, size+2, wins2);
	newGame->player2 = newPlayer('w', type1, size+2, wins1);
	newGame->turn = newGame->player1; 

	playGame(newGame);
	return;
}

int checkForWin(Game* game) {
	checkForMoves(game->turn, game->board);
	if (game->turn->moveExists == 1) {
		return 0;
	} else {
		if (game->turn == game->player1) game->turn = game->player2;
		else game->turn = game-> player1;
		checkForMoves(game->turn, game->board);
		if (game->turn->moveExists == 1) {
			printf("No moves.\nSkipping to %c's turn.i\n", game->turn->piece);
			return 0;
		}
	}
	return 1; 
}

void takeHumanTurn(Game* game) {
	printf("\n\n%c's turn.\n", game->turn->piece);
	printBoard(game->board);
	Coordinate* coordinate = promptForCoordinate(game->board->size);
	if (*(game->turn->validMoves + coordinate->r * game->board->size + coordinate->c) == 0) {
		printf("Invalid move. Please try again.\n");
		takeHumanTurn(game);
	} else {
		placePiece(game->board, coordinate->r, coordinate->c, game->turn->piece);
		if (game->turn == game->player1) game->turn = game->player2;
		else game->turn = game->player1;
	}
	return;
}

void takeAITurn(Game* game) {
	printf("\n\n%c's turn.\n", game->turn->piece);
	printBoard(game->board);
	printf("Placing piece in row %d, column %d.\n", game->turn->nextMove->r, game->turn->nextMove->c);
	placePiece(game->board, game->turn->nextMove->r, game->turn->nextMove->c, game->turn->piece);
	if (game->turn == game->player1) game->turn = game->player2;
	else game->turn = game->player1;
	return;
}
