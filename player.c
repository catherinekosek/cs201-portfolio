#include "player.h"

Player* newPlayer(char piece, enum type type) {
	Player* player = malloc(sizeof(Player));
	player->type = type;
	player->piece = piece;
	player->wins = 0;
	return player;
}
