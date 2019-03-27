#include "player.h"

Player* newPlayer(char piece, enum type type, int size) {
	Player* player = malloc(sizeof(Player));
	player->validMoves = malloc(sizeof(char) * size * size);
	player->type = type;
	player->piece = piece;
	player->wins = 0;
	Coordinate* nextMove = malloc(sizeof(Coordinate));
	player->nextMove = nextMove;	
	if (type == regularAI) {
		player->moveWeights = malloc(sizeof(char) * size * size);
		buildRegularAITable(player, size);
	}
	return player;
}

void checkForMoves(Player* player, Board* board) {	
	printf("entered check for moves\n");
	player->moveExists = 0;
	for (int k = 1; k < board->size-1; k++) {
		for (int l = 0; l < board->size-1; l++) {
			*(player->validMoves + k * board->size + l) = 0;
			printf("in double for loop\n");
		}
	}
	player->nextMove->value = -1;
	printf("resets successful\n");
	for (int i = 1; i <= board->size; i++) {
		for (int j = 1; j <= board->size; j++) {
			if (*(board->boardArray + i * board->size + j) == player->piece) {
				findMoves(player, board, i+1, j, 1, 0, 0);		// right
				findMoves(player, board, i+1, j+1, 1, 1, 0);		// right up
				findMoves(player, board, i, j+1, 0, 1, 0);		// up
				findMoves(player, board, i-1, j+1, -1, 1, 0);		// left up
				findMoves(player, board, i-1, j, -1, 0, 0);		// left
				findMoves(player, board, i-1, j-1, -1, -1, 0);		// left down
				findMoves(player, board, i, j-1, 0, -1, 0);		// down
				findMoves(player, board, i+1, j-1, 1, -1, 0);		// right down
			}
		}	
	}	
	
	return;
}

void findMoves(Player* player, Board* board, int x, int y, int xChange, int yChange, int count) {
	char piece = *(board->boardArray + x * board->size + y);
	char turn = player->piece;
	if (piece == '-') {
		return;
	}
	else if ((piece == turn) || ((piece == '*') && (count == 0))) {
		return;
	} else if ((piece == '*') && (count >= 1)) {
		player->moveExists = 1;
	
		if (player->type == regularAI) {
			*(player->validMoves + x * board->size + y) = *(player->moveWeights + x * board->size * y);
		}
		else *(player->validMoves + x * board->size + y) = count;
	
		if (player->type != human && *(player->validMoves + x * board->size + y) > player->nextMove->value) {
			player->nextMove->x = x;
			player->nextMove->y = y;
			player->nextMove->value = *(player->validMoves + x * board->size + y);
		}
		return;
	} else {
		count++;
		findMoves(player, board, x + xChange, y + yChange, xChange, yChange, count);
	}
}

void buildRegularAITable(Player* player, int size) {
	// set corners as "best" squares with value of 8
	*(player->moveWeights + 1 * size + 1) = 8;
	*(player->moveWeights + 1 * size + size) = 8;
	*(player->moveWeights + size * size + 1) = 8;
	*(player->moveWeights + size * size + size) = 8;

	// set x-squares as "worst" sqaurs with value of 1
	*(player->moveWeights + 2 * size + 2) = 1;
	*(player->moveWeights + 2 * size + (size-1)) = 1;
	*(player->moveWeights + (size-1) * size + 2) = 1;
	*(player->moveWeights + (size-1) * size + (size-1)) = 1;
	
	// set c-squares as second-worst with value of 2
	*(player->moveWeights + 1 * size + 2) = 2;
	*(player->moveWeights + 1 * size + (size-1)) = 2;
	*(player->moveWeights + 2 * size + 1) = 2;
	*(player->moveWeights + 2 * size + size) = 2;
	*(player->moveWeights + (size-1) * size + 1) = 2;
	*(player->moveWeights + (size-1) * size + size) = 2;
	*(player->moveWeights + size * size + 2) = 2;
	*(player->moveWeights + size * size + (size-1)) = 2;

	
	// set internal corners as a good option with value of 6
	*(player->moveWeights + 3 * size + 3) = 6;
	*(player->moveWeights + 3 * size + (size-2)) = 6;
	*(player->moveWeights + (size-2) * size + 3) = 6;
	*(player->moveWeights + (size-2) * size + (size-2)) = 6;
	
	// set internal edges as a good option with value of 5
	*(player->moveWeights + 1 * size + (size/2)) = 5;
	*(player->moveWeights + 1 * size + ((size/2)+1)) = 5;
	*(player->moveWeights + (size/2) * size + 1) = 5;
	*(player->moveWeights + ((size/2)+1) * size + 1) = 5;
	*(player->moveWeights + (size/2) * size + size) = 5;
	*(player->moveWeights + ((size/2)+1) * size + size) = 5;
	*(player->moveWeights + size * size + (size/2)) = 5;
	*(player->moveWeights + size * size + ((size/2)+1)) = 5;

	// set edges as second best option with value of 7
	for (int i = 3; i < size/2; i++) {
		*(player->moveWeights + 1 * size + i) = 7;
		*(player->moveWeights + i * size + 1) = 7;
		*(player->moveWeights + size * size + i) = 7;
		*(player->moveWeights + i * size + size) = 7;
	}
	for (int j = (size/2)+2; j < size-1; j++) {
		*(player->moveWeights + 1 * size + j) = 7;
		*(player->moveWeights + j * size + 1) = 7;
		*(player->moveWeights + size * size + j) = 7;
		*(player->moveWeights + j * size + size) = 7;
	}

	// set danger zone as a bad option with value of 3
	for (int k = 3; k < size-1; k++) {
		*(player->moveWeights + 2 * size + k) = 3;
		*(player->moveWeights + k * size + 2) = 3;
		*(player->moveWeights + (size-1) * size + k) = 3;
		*(player->moveWeights + k * size + (size-1)) = 3;
	}

	// set internal squares as a neutral option with value of 4
	for (int l = 4; l < size-2; l++) {
		*(player->moveWeights + 3 * size + l) = 4;
		*(player->moveWeights + l * size + 3) = 4;
		*(player->moveWeights + (size-2) * size + l) = 4;
		*(player->moveWeights + l * size + (size-2)) = 4;
	}
	for (int m = 4; m < size-2; m++) {
		for (int n = 4; n < size-2; n++) {
			*(player->moveWeights + m * size + n) = 4;
		}
	}

	return;
}
