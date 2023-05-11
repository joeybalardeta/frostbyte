#include <stdlib.h>
#include "Player.h"

Player *CreatePlayer(unsigned char type) {
	Player *player = (Player *) malloc(sizeof(Player));
	player->type = type;

	return player;
}

void DeletePlayer(Player *player) {
	if (player) {
		free(player);
	}
}
