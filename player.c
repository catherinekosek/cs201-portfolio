#include "player.h"

/* Constructor for a new Player:
	Allocates space for Player 
	Allocates space for AIs
	Assigns attributes to Player
	Returns pointer to complete Player 
*/
Player* newPlayer(char piece, enum type type, int size) {
	Player* player = (Player *)malloc(sizeof(Player));
	if (type != human) player->nextMove = newCoordinate();
	if (type == regularAI) {
		player->moveWeights = (int *)malloc(sizeof(int) * size * size);
		buildRegularAITable(player, size);
	}

	if (type == human) player->name = promptForName();
	else player->name = "Computer";
		
	player->piece = piece;
	player->type = type;
	player->wins = 0;	
	
	return player;
}

/* Destructor for existing Player:
	Frees space allocated for AIs
 	Frees space allocated for Player
*/
void destructPlayer(Player* player) {
	if (player->type != human) destructCoordinate(player->nextMove);
	if (player->type == regularAI) free(player->moveWeights);
	if (player->type == human) free(player->name);
	free(player);
	return;
}

/* Builds an array that gives a weight to each location on the board
   Some board locations are more valuable than others
   Each location on the board assigned a weight from 1 to 8, with 1 being the "worst" location and 8 being the "best" location:
	1: X-Sqaures - diagonally adjacent to corners
		Creates easiest opponent access to corners
	2: C-Squares - vertically or horizontally adjacent to corners
		Creates opponent access to corners
	3: Danger Zone - rows and columns immediately inside the edge rows and columns
		Creates opponent access to edges
	4: Internal Sqaures - anything not otherwise specified
		Not harmful but not particularly advantageous
	5: Internal Edges - locations along the edge of the board not otherwise specified
		Can only be flipped if opponent has position on the same edge
	6: Internal Corners - diagonally adjacent to X-Squares
		Creates access to corners
	7: Edge Edges - vertically or horizontally adjacent to C-Squares
		Creates access to corners and can only be flipped if opponent has position on same edge
	8: Corners - four corner squares
		Cannot be flipped
*/
void buildRegularAITable(Player* player, int size) {
	// the size of the board includes buffer zones not relevant here
	int edge = size - 2;

	// set x-squares to 1
	*(player->moveWeights + 2 * size + 2) = 1;
	*(player->moveWeights + 2 * size + (edge-1)) = 1;
	*(player->moveWeights + (edge-1) * size + 2) = 1;
	*(player->moveWeights + (edge-1) * size + (edge-1)) = 1;
	
	// set c-squares to 2
	*(player->moveWeights + 1 * size + 2) = 2;
	*(player->moveWeights + 1 * size + (edge-1)) = 2;
	*(player->moveWeights + 2 * size + 1) = 2;
	*(player->moveWeights + 2 * size + edge) = 2;
	*(player->moveWeights + (edge-1) * size + 1) = 2;
	*(player->moveWeights + (edge-1) * size + edge) = 2;
	*(player->moveWeights + edge * size + 2) = 2;
	*(player->moveWeights + edge * size + (edge-1)) = 2;

	// set danger zone to 3
	for (int k = 3; k < edge-1; k++) {
		*(player->moveWeights + 2 * size + k) = 3;
		*(player->moveWeights + k * size + 2) = 3;
		*(player->moveWeights + (edge-1) * size + k) = 3;
		*(player->moveWeights + k * size + (edge-1)) = 3;
	}
	
	// set internal squares to 4
	for (int l = 4; l < edge-2; l++) {
		*(player->moveWeights + 3 * size + l) = 4;
		*(player->moveWeights + l * size + 3) = 4;
		*(player->moveWeights + (edge-2) * size + l) = 4;
		*(player->moveWeights + l * size + (edge-2)) = 4;
	}
	for (int m = 4; m < edge-2; m++) {
		for (int n = 4; n < edge-2; n++) {
			*(player->moveWeights + m * size + n) = 4;
		}
	}

	// set interal edges to 5
	for (int i = 4; i < edge-2; i++) {
		*(player->moveWeights + 1 * size + i) = 5;
		*(player->moveWeights + i * size + 1) = 5;
		*(player->moveWeights + edge * size + i) = 5;
		*(player->moveWeights + i * size + edge) = 5;
	}

	// set internal corners to 6
	*(player->moveWeights + 3 * size + 3) = 6;
	*(player->moveWeights + 3 * size + (edge-2)) = 6;
	*(player->moveWeights + (edge-2) * size + 3) = 6;
	*(player->moveWeights + (edge-2) * size + (edge-2)) = 6;
	
	// set edge edges to 7
	*(player->moveWeights + 1 * size + 3) = 7;
	*(player->moveWeights + 1 * size + (edge-2)) = 7;
	*(player->moveWeights + 3 * size + 1) = 7;
	*(player->moveWeights + 3 * size + edge) = 7;
	*(player->moveWeights + (edge-2) * size + 1) = 7;
	*(player->moveWeights + (edge-2) * size + edge) = 7;
	*(player->moveWeights + edge * size + 3) = 7;
	*(player->moveWeights + edge * size + (edge-2)) = 7;

	// set corners to 8
	*(player->moveWeights + 1 * size + 1) = 8;
	*(player->moveWeights + 1 * size + edge) = 8;
	*(player->moveWeights + edge * size + 1) = 8;
	*(player->moveWeights + edge * size + edge) = 8;
		
	return;
}
