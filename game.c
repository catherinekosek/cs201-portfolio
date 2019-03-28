#include "game.h"

Game* newGame(int size) {
	Game* game = malloc(sizeof(Game));
	game->board = newBoard(size);	
	game->player1 = newPlayer('b', human, size+2);
	enum type type = promptForGameType();
/*	if (strcmp(mode, "twoPlayer") == 0){
		game->mode = twoPlayer;
		Player* player2 = newPlayer('w', human, size+2);
		game->player2 = player2;
	} else if (strcmp(mode, "easy") == 0) {
		game->mode = easy;
		Player* player2 = newPlayer('w', easy, size+2);
		game->player2 = player2;
	} else if (strcmp(mode, "regular") == 0) {
		game->mode = regular;
		Player* player2 = newPlayer('w', regular, size+2);
		game->player2 = player2;
	}
*/	game->player2 = newPlayer('w', type, size+2);
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
	if (game->board->blackPieces > game->board->whitePieces) 
		printf("\n\nPlayer 1 won!\n");
	else printf("\n\nPlayer 2 won!\n");
	return;
}

int checkForWin(Game* game) {
	checkForMoves(game->turn, game->board);
	if (game->turn->moveExists == 1) return 0;
	else {
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
/*	int x;
	int y;
	printf("Please enter the row number you wish to place piece in:\n");
	scanf("%d", &x);
	printf("Please enter the column number you wish to place piece in:\n");
	scanf("%d", &y);
*/	Coordinate* coordinate = promptForCoordinate(game->board->size);
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
