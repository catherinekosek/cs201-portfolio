#include "game.h"

Game* newGame(char* mode) {
	Game* game = malloc(sizeof(Game));
	game->board = newBoard(8);
	game->validMoves = newValidMoves(game->board);
	Player* player1 = newPlayer('b', human);
	game->player1 = player1;
	if (strcmp(mode, "twoPlayer") == 0){
		game->mode = twoPlayer;
		Player* player2 = newPlayer('w', human);
		game->player2 = player2;
	}
	else if (strcmp(mode, "easy") == 0) {
		game->mode = easy;
		Player* player2 = newPlayer('w', easy);
		game->player2 = player2;
	} 
	game->turn = 'b';
	return game;
}

void playGame(Game* game) {
	int win = 0;
	while(win == 0) {
		if (game->turn == 'b' || game->player2->type == human) takeHumanTurn(game);
		else if (game->player2->type == easyAI) takeEasyAITurn(game);
		else printf("yikes\n");
		win = checkForWin(game);
	}
	printf("Congrats! Someone won!\n");
	return;
}

int checkForWin(Game* game) {
	checkForMoves(game->validMoves, game->turn);
	if (game->validMoves->exists == 1) return 0;
	else {
		if (game->turn == 'b') game->turn = 'w';
		else game->turn = 'b';
		checkForMoves(game->validMoves, game->turn);
		if (game->validMoves->exists == 1) {
			printf("No moves.\nSkipping to %c's turn.", game->turn);
			return 0;
		}
	}
	return 1; 
}

void takeHumanTurn(Game* game) {
	printf("\n\n%c's turn.\n", game->turn);
	printBoard(game->board);
	int x;
	int y;
	printf("Please enter the row number you wish to place piece in:\n");
	scanf("%d", &x);
	printf("Please enter the column number you wish to place piece in:\n");
	scanf("%d", &y);
	int valid = validateMove(game->validMoves, x, y);
	if (valid == 0) {
		printf("Invalid move. Please try again.\n");
		takeHumanTurn(game);
	} else {
		placePiece(game->board, x, y, game->turn);
		if (game->turn == 'b') game->turn = 'w';
		else game->turn = 'b';
	}
	return;
}

void takeEasyAITurn(Game* game) {
	printf("\n\n%c's turn.\n", game->turn);
	printBoard(game->board);
	printf("Placing piece in row %d, column %d.\n", game->validMoves->nextMove->x, game->validMoves->nextMove->y);
	placePiece(game->board, game->validMoves->nextMove->x, game->validMoves->nextMove->y, game->turn);
	game->turn = 'b';
	return;
}
