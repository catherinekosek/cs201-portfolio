#include "game.h"

Game* newGame() {
	Game* game = malloc(sizeof(Game));
	int size = promptForBoardSize();
	game->board = newBoard(size);	
	game->player1 = newPlayer('b', human, size+2, 0);
	enum type type = promptForGameType();
	game->player2 = newPlayer('w', type, size+2, 0);
	game->turn = game->player1;
	return game;
}

void playGame(Game* game) {
	int win = checkForWin(game);
	while(win == 0) {
		if (game->turn->type == human) takeHumanTurn(game);
		else takeAITurn(game);
		win = checkForWin(game);
	}
	printf("\n");
	printBoard(game->board);
	if (game->board->blackPieces > game->board->whitePieces) { 
		printf("\n\nPlayer 1 won!\n");
		game->player1->wins++;
	}
	else { 
		printf("\n\nPlayer 2 won!\n");
		game->player2->wins++;
	}
	rematch(game);
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
	}else {
		if (game->turn == game->player1) game->turn = game->player2;
		else game->turn = game-> player1;
		checkForMoves(game->turn, game->board);
		if (game->turn->moveExists == 1) {
			printf("No moves.\nSkipping to %c's turn.", game->turn->piece);
			return 0;
		}
	}
	return 1; 
}

void takeHumanTurn(Game* game) {
	printf("\n\n%c's turn.\n", game->turn->piece);
	printBoard(game->board);
	Coordinate* coordinate = promptForCoordinate(game->board->size);
	if (*(game->turn->validMoves + coordinate->x * game->board->size + coordinate->y) == 0) {
		printf("Invalid move. Please try again.\n");
		takeHumanTurn(game);
	} else {
		placePiece(game->board, coordinate->x, coordinate->y, game->turn->piece);
		if (game->turn == game->player1) game->turn = game->player2;
		else game->turn = game->player1;
	}
	return;
}

void takeAITurn(Game* game) {
	printf("\n\n%c's turn.\n", game->turn->piece);
	printBoard(game->board);
	printf("Placing piece in row %d, column %d.\n", game->turn->nextMove->x, game->turn->nextMove->y);
	placePiece(game->board, game->turn->nextMove->x, game->turn->nextMove->y, game->turn->piece);
	if (game->turn == game->player1) game->turn = game->player2;
	else game->turn = game->player1;
	return;
}
