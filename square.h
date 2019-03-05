#ifndef _square_h
#define _square_h

#include <stdlib.h>

typedef struct square {
	char _piece;
	int _x;
	int _y;
} Square;

Square* newSquare(int, int); 
char getPiece(Square*);
void setPiece(Square*, char);

#endif
