#include "board.h"

/* Constructor for a new Board with dimensions size x size:
	Allocate size for the Board
	Increment the size by 2 to add the buffer pieces around the edge of the board
	Allocate size for the Board arrays
	Set the buffer pieces, represented by '-'
	Set all other board locations to empty, represented by '*'
	Set the starting setup of the board, with pieces on the center four locations
	Return a pointer to the completed Board
*/
Board* newBoard(int size) {
	Board* board = malloc(sizeof(Board));

	size += 2;
	board->size = size;
	board->boardArray = (char *)malloc(sizeof(char) * size * size);  
	board->validMoves = (int *)malloc(sizeof(int) * size * size);	
	board->visited = (int *)malloc(sizeof(int) * size * size);

	for (int k = 0; k < size; k++) {
		*(board->boardArray + 0 * size + k) = '-';
		*(board->boardArray + k * size + 0) = '-';
		*(board->boardArray + (size-1) * size + k) = '-';
		*(board->boardArray + k * size + (size-1)) = '-';
	}

	for (int i = 1; i < size-1; i++) {
		for (int j = 1; j < size-1; j++) {
			*(board->boardArray + i * size + j) = '*';
		}
	}

	int mid1 = (size-2) / 2;
	int mid2 = mid1 + 1;
	*(board->boardArray + mid1 * size + mid1) = 'w';
	*(board->boardArray + mid1 * size + mid2) = 'b';
	*(board->boardArray + mid2 * size + mid1) = 'b';
	*(board->boardArray + mid2 * size + mid2) = 'w';
	board->whitePieces = 2;
	board->blackPieces = 2;

	return board;
}

/* Destructor for an existing Board:
	Frees space allocated for board arrays
	Frees space allocated for board
*/
void destructBoard(Board* board) {
	free(board->boardArray);
	free(board->validMoves);
	free(board->visited);
	free(board);
	return;
}

/* Prints the Board boardArray to the console:
	Print reference numbers along the top of the board
	Print reference numbers along the left side of the board
	Print the piece at each location on the board 
	Print the current score, the numbers of each piece on the board
*/
void printBoard(Board* board) {
	printf("\n\t       ");
	for (int k = 1; k < board->size-1; k++) {
		if (k < 10) printf("  %d", k);	// spacing issues with single digit vs double digit numbers
		else printf(" %d", k);
	}

	for(int i = 0; i < board->size; i++) {
		printf("\n\t ");
		if (i == 0 || i == board->size-1) printf("   ");
		else if (i < 10) printf("  %d", i);
		else printf(" %d", i);
		for(int j = 0; j < board->size; j++) {
			printf("  %c", *(board->boardArray + i * board->size + j));
		}
	}
	
	printf("\n\n\tBlack Pieces: %d\t WhitePieces: %d\n", board->blackPieces, board->whitePieces);
	return;
}

/* Controls the logic of placing a piece on the Board:
	Sets location r, c on Board equal to the piece turn
	flipsPieces in every direction from location r, c
	Increments the number of pieces of color of turn by 1
*/
void placePiece(Board* board, int r, int c, char turn) {
	*(board->boardArray + r * board->size + c) = turn;

	flipPieces(board, r+1, c, 1, 0, 0, turn);		// right
	flipPieces(board, r+1, c+1, 1, 1, 0, turn);		// right up
	flipPieces(board, r, c+1, 0, 1, 0, turn);		// up
	flipPieces(board, r-1, c+1, -1, 1, 0, turn);		// left up
	flipPieces(board, r-1, c, -1, 0, 0, turn);		// left
	flipPieces(board, r-1, c-1, -1, -1, 0, turn);		// left down
	flipPieces(board, r, c-1, 0, -1, 0, turn);		// down
	flipPieces(board, r+1, c-1, 1, -1, 0, turn);		// right down
	
	if (turn == 'b') board->blackPieces++;
	else board->whitePieces++;
	return;
}

/* Determines if pieces need to be flipped and performs appropriate flips:
   Pieces need to be flipped if there is:
	A line vertically, horizontally, or diagonally from the newly placed piece to a piece of the same color
	No empty spaces or other pieces of the same color in this line
	One or more pieces of the opposite color in the line between the two pieces

   int r, int c - the location r,c on Board being analyzed
   int rChange, int cChange - the direction the line is being drawn
   int flip - whether or not pieces need to be flipped
   char turn - the piece being placed on the board, and therefore the piece being searched for
   char piece - the piece at location r,c being analyzed

   flipPieces:
	Analyzes piece at location r,c as one of 3 cases:
		'-' piece is an edge piece or '*' piece is empty
			No piece of the same color found in the direction
			Return 0, do not flip
		piece is the same color as turn
			A piece of the same color has been found
			Return 1, flip any pieces in betweem
		piece is the opposite color of turn
			If a piece of the same color is found, this piece needs to be flipped
			Set flip to the return of a recursive call
	Flip any pieces of the opposite color if necessary
	Update the counts of white and black pieces if a piece if flipped
			
*/
int flipPieces(Board* board, int r, int c, int rChange, int cChange, int flip, char turn) {
	char piece = *(board->boardArray + r * board->size + c);

	if (piece == '-'|| piece == '*') return 0;
	else if (piece == turn) return 1;
	else flip = flipPieces(board, r + rChange, c + cChange, rChange, cChange, flip, turn);

	if(flip == 1) {
		*(board->boardArray + r * board->size + c) = turn;
		if (turn == 'b') {
			board->blackPieces++;
			board->whitePieces--;
		} else {
			board->whitePieces++;
			board->blackPieces--;
		}
	}
	
	return flip;
}

/* Searches a Board for valid moves that can be made by a Player:
	Resets anything set by a previous checkForMoves
	Begins a depth-first search of the board
*/
void checkForMoves(Board* board, Player* player) {	
	player->moveExists = 0;
	if (player->type != human) player->nextMove->value = 0;
	for (int i = 0; i < board->size * board->size; i++) {
		*(board->validMoves + i) = 0;
		*(board->visited + i) = 0;
	}

	// Board location (board->size-2)/2, (board->size-2)/2 is set in constructor and will always be occupied
	DFS(board, player, (board->size-2)/2, (board->size-2)/2);
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
void DFS(Board* board, Player* player, int r, int c) {
	*(board->visited + r * board->size + c) = 1;
	
	if (*(board->boardArray + r * board->size + c) == '*') return;
	else if (*(board->boardArray + r * board->size + c) == '-') return;
	else if (*(board->boardArray + r * board->size + c) == player->piece) {
		findMoves(board, player, r+1, c, 1, 0, 0);		// right
		findMoves(board, player, r+1, c+1, 1, 1, 0);		// right up
		findMoves(board, player, r, c+1, 0, 1, 0);		// up
		findMoves(board, player, r-1, c+1, -1, 1, 0);		// left up
		findMoves(board, player, r-1, c, -1, 0, 0);		// left
		findMoves(board, player, r-1, c-1, -1, -1, 0);		// left down
		findMoves(board, player, r, c-1, 0, -1, 0);		// down
		findMoves(board, player, r+1, c-1, 1, -1, 0);		// right down
	}

	if (*(board->visited + (r+1) * board->size + c) == 0) DFS(board, player, r+1, c);	// right
	if (*(board->visited + (r+1) * board->size + (c+1)) == 0) DFS(board, player, r+1, c+1);	// right up
	if (*(board->visited + r * board->size + (c+1)) == 0) DFS(board, player, r, c+1);	// up
	if (*(board->visited + (r-1) * board->size + (c+1)) == 0) DFS(board, player, r-1, c+1);	// left up
	if (*(board->visited + (r-1) * board->size + c) == 0) DFS(board, player, r-1, c);	// left
	if (*(board->visited + (r-1) * board->size + (c-1)) == 0) DFS(board, player, r-1, c-1);	// left down
	if (*(board->visited + r * board->size + (c-1)) == 0) DFS(board, player, r, c-1);	// down
	if (*(board->visited + (r+1) * board->size + (c-1)) == 0) DFS(board, player, r+1, c-1);	// right down
	
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
			Piece is of the opposite color
			Increment count
			Continue search in same direction
*/
void findMoves(Board* board, Player* player, int r, int c, int rChange, int cChange, int count) {
	char piece = *(board->boardArray + r * board->size + c);
	char turn = player->piece;

	if ((piece == '-') || (piece == turn) || ((piece == '*') && (count == 0))) return;
	else if ((piece == '*') && (count >= 1)) {
		player->moveExists = 1;
		if (player->type == regularAI) {
			*(board->validMoves + r * board->size + c) = *(player->moveWeights + r * board->size + c);
		}
		else *(board->validMoves + r * board->size + c) += count;

		if (player->type != human && *(board->validMoves + r * board->size + c) > player->nextMove->value) {
			player->nextMove->r = r;
			player->nextMove->c = c;
			player->nextMove->value = *(board->validMoves + r * board->size + c);
		}
		return;
	} else {
		count++;
		findMoves(board, player, r + rChange, c + cChange, rChange, cChange, count);
	}

	return;
}
