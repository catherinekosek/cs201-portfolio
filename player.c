#include "player.h"

Player* newPlayer(char piece) {
	Player* player = malloc(sizeof(Player));
	player->_piece = piece;
	player->_wins = 0;
	player->_score = 2;
	return player;
}
