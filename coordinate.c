#include "coordinate.h"

Coordinate* newCoordinate() {
	Coordinate* coordinate = (Coordinate *)malloc(sizeof(Coordinate));
	return coordinate;
}

void destructCoordinate(Coordinate* coordinate) {
	free(coordinate);
}
