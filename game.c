#include "game.h"

Game* newGame(char* mode, int size) {
	Game* game = malloc(sizeof(Game));
	game->board = newBoard(size);	
	Player* player1 = newPlayer('b', human, size);
	game->player1 = player1;
	if (strcmp(mode, "twoPlayer") == 0){
		game->mode = twoPlayer;
		Player* player2 = newPlayer('w', human, size);
		game->player2 = player2;
	} else if (strcmp(mode, "easy") == 0) {
		game->mode = easy;
		Player* player2 = newPlayer('w', easy, size);
		game->player2 = player2;
	} else if (strcmp(mode, "regular") == 0) {
		game->mode = regular;
		Player* player2 = newPlayer('w', regular, size);
		game->player2 = player2;
	}
	game->turn = player1;
	return game;
}

void playGame(Game* game) {
	printf("entered play game, about to checkForWin\n");
	int win = checkForWin(game);
	printf("checked for wins, about to enter turn loop\n");
	while(win == 0) {
		if (game->turn->type == human) takeHumanTurn(game);
		else takeAITurn(game);
		win = checkForWin(game);
	}
	if (game->board->blackPieces > game->board->whitePieces) 
		printf("\n\nPlayer 1 won!\n");
	else printf("\n\nPlayer 2 won!\n");
	return;
}

int checkForWin(Game* game) {
	printf("entered checkForWin\n");
	checkForMoves(game->turn, game->board);
	printf("chcked for moves\n");
	if (game->turn->moveExists == 1) return 0;
	else {
		if (game->turn == game->player1) game->turn = game->player2;
		else game->turn = game-> player1;
		printf("entered checkForMoves\n");
		checkForMoves(game->turn, game->board);
		printf("exited checkForMoves\n");
		if (game->turn->moveExists == 1) {
			printf("No moves.\nSkipping to %c's turn.", game->turn->piece);
			return 0;
		}
	}
	printf("exiting checkForWin\n");
	return 1; 
}

void takeHumanTurn(Game* game) {
	printf("\n\n%c's turn.\n", game->turn->piece);
	printBoard(game->board);
	int x;
	int y;
	printf("Please enter the row number you wish to place piece in:\n");
	scanf("%d", &x);
	printf("Please enter the column number you wish to place piece in:\n");
	scanf("%d", &y);
	if (*(game->turn->validMoves + x * game->board->size + y) == 0) {
		printf("Invalid move. Please try again.\n");
		takeHumanTurn(game);
	} else {
		printf("about to place piece\n");
		placePiece(game->board, x, y, game->turn->piece);
		printf("piece placed\n");
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
