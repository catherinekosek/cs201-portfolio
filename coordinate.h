#ifndef _coordinate_h
#define _coordinate_h

#include <stdlib.h>

typedef struct coordinate {
	int x;
	int y;
	int value;
} Coordinate;

Coordinate* newCoordinate(int, int);

#endif
