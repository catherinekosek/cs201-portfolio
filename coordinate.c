#include "coordinate.h"

Coordinate* newCoordinate(int x, int y) {
	Coordinate* coordinate = malloc(sizeof(Coordinate));
	coordinate->x = x;
	coordinate->y = y;
	return coordinate;
}
