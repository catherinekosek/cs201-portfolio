#ifndef _coordinate_h
#define _coordinate_h

#include <stdlib.h>

typedef struct coordinate {
	int r;
	int c;
	int value;
} Coordinate;

Coordinate* newCoordinate();
void destructCoordinate(Coordinate*);

#endif
