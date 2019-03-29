#include "player.h"

/* Constructor for a new Player:
	Allocates space for Player 
	Allocates space for Player data structures
	Assigns attributes to Player
	Returns pointer to complete Player 
*/
Player* newPlayer(char piece, enum type type, int size, int wins) {
	Player* player = malloc(sizeof(Player));
	player->validMoves = malloc(sizeof(int) * size * size);
	player->visited = malloc(sizeof(int) * size * size);
	if (type != human) player->nextMove = malloc(sizeof(Coordinate));
	if (type == regularAI) {
		player->moveWeights = malloc(sizeof(int) * size * size);
		buildRegularAITable(player, size);
	}
	
	player->piece = piece;
	player->type = type;
	player->wins = wins;	
	
	return player;
}

/* Destructor for existing Player:
	Frees space allocated for Player arrays
 	Frees space allocated for Player
*/
void destructPlayer(Player* player) {
	free(player->validMoves);
	free(player->visited);
	if (player->type != human) free(player->nextMove);
	if (player->type == regularAI) free(player->moveWeights);
	
	free(player);
	return;
}

/* Searches a Board for valid moves that can be made by a Player:
	Resets anything set by a previous checkForMoves
	Begins a depth-first search of the board
*/
void checkForMoves(Player* player, Board* board) {	
	player->moveExists = 0;
	if (player->type != human) player->nextMove->value = 0;
	for (int i = 0; i < board->size * board->size; i++) {
		*(player->validMoves + i) = 0;
		*(player->visited + i) = 0;
	}

	// Board location (board->size-2)/2, (board->size-2)/2 will always be occupied
	DFS(player, board, (board->size-2)/2, (board->size-2)/2);
	return;
}

/* Performs a depth-first search of a Board, searching for existing pieces to base new move:
	Marks current location as visited
	Analyzes piece at current location, action performed in three cases:
		'*' Board piece indicates empty square
			Search is for an existing piece
			All existing pieces are adjacent to at least one other existing piece
			There is no reason to continue search from an empty square
			Return
		'-' Board indicates the edge of board
			Return
		Board piece matches Player piece
			Use findMoves function to find moves in all directions based from this location
	Continue depth-first search
		Each location has eight adjacencies 
		Adjacencies are calculated, not stored in a list
*/
void DFS(Player* player, Board* board, int r, int c) {
	*(player->visited + r * board->size + c) = 1;
	
	if (*(board->boardArray + r * board->size + c) == '*') return;
	else if (*(board->boardArray + r * board->size + c) == '-') return;
	else if (*(board->boardArray + r * board->size + c) == player->piece) {
		findMoves(player, board, r+1, c, 1, 0, 0);		// right
		findMoves(player, board, r+1, c+1, 1, 1, 0);		// right up
		findMoves(player, board, r, c+1, 0, 1, 0);		// up
		findMoves(player, board, r-1, c+1, -1, 1, 0);		// left up
		findMoves(player, board, r-1, c, -1, 0, 0);		// left
		findMoves(player, board, r-1, c-1, -1, -1, 0);		// left down
		findMoves(player, board, r, c-1, 0, -1, 0);		// down
		findMoves(player, board, r+1, c-1, 1, -1, 0);		// right down
	}

	if (*(player->visited + (r+1) * board->size + c) == 0) DFS(player, board, r+1, c);	// right
	if (*(player->visited + (r+1) * board->size + (c+1)) == 0) DFS(player, board, r+1, c+1);// right up
	if (*(player->visited + r * board->size + (c+1)) == 0) DFS(player, board, r, c+1);	// up
	if (*(player->visited + (r-1) * board->size + (c+1)) == 0) DFS(player, board, r-1, c+1);// left up
	if (*(player->visited + (r-1) * board->size + c) == 0) DFS(player, board, r-1, c);	// left
	if (*(player->visited + (r-1) * board->size + (c-1)) == 0) DFS(player, board, r-1, c-1);// left down
	if (*(player->visited + r * board->size + (c-1)) == 0) DFS(player, board, r, c-1);	// down
	if (*(player->visited + (r+1) * board->size + (c-1)) == 0) DFS(player, board, r+1, c-1);// right down
	
	return;
}

/* Determines if a location on the board is a valid move
   A valid move must:
	Be an empty location on the board, indicated by '*'
	Have a vertical, horizontal, or diagonal line with a piece of the same color
	Have one or more contiguous pieces of the opposite color between it and the piece forming the line
	Have no empty squares or other pieces of the same color between it and the piece forming the line
   findMoves begins with a piece of the same color and recursively draws a line outwards from it
   
   int r, int c - indicated the location of the board currently being analyzed
   int rChange, int cChange - indicate the direction the line is being drawn in
   int count - the number of pieces of the opposite color encountered in the line 
		this must be > 1 for a valid move, and is the basis of the 'easy' AI
   char piece - the piece on the board at location r,c currently being analyzed
   char turn - the piece to be placed for this turn

   findMoves:
	Analyzes piece:
		'-' piece is the edge of the board
			Line cannot continue
			Return
		piece is the same color as turn
			No pieces of the same color can be inside the line, so line cannot continue
			Return
		'*' piece is empty AND count is zero
			There are currently no pieces of the opposite color inside the line, so move is not valid
			There cannot be any empty pieces inside the line, so line cannot continue 
			Return
		'*' piece is empty AND count is >= 1
			At least one piece of the opposite color inside the line
			Empty location to place new piece on
			Store move in array validMoves
			If Player is an AI, store move in nextMove if move is more advantageous
		else
			piece is of the opposite color
			increment count
			continue search in same direction
*/
void findMoves(Player* player, Board* board, int r, int c, int rChange, int cChange, int count) {
	char piece = *(board->boardArray + r * board->size + c);
	char turn = player->piece;

	if ((piece == '-') || (piece == turn) || ((piece == '*') && (count == 0))) return;
	else if ((piece == '*') && (count >= 1)) {
		player->moveExists = 1;
		if (player->type == regularAI) {
			*(player->validMoves + r * board->size + c) = *(player->moveWeights + r * board->size + c);
		}
		else *(player->validMoves + r * board->size + c) += count;

		if (player->type != human && *(player->validMoves + r * board->size + c) > player->nextMove->value) {
			player->nextMove->r = r;
			player->nextMove->c = c;
			player->nextMove->value = *(player->validMoves + r * board->size + c);
		}
		return;
	} else {
		count++;
		findMoves(player, board, r + rChange, c + cChange, rChange, cChange, count);
	}

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
