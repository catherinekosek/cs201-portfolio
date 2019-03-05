#include "square.h"

Square* newSquare(int x, int y) {
	Square* square = malloc(sizeof(Square));
	square->_piece = '*';
	return square;
}

char getPiece(Square *square) {
	return square->_piece;
}

void setPiece(Square *square, char piece) {
	square->_piece = piece;
	return;
}
