#include <stdlib.h>
#include "Game.h"

Game *CreateGame(Player *player_white, Player *player_black){
	Game *game = (Game *) malloc(sizeof(game)); 
	game->player_white = player_white;
	game->player_black = player_black;

	return game;
}


void DeleteGame(Game *game){
	if (game) {
		free(game);
	}
}
