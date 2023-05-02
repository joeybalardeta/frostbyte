#ifndef GAME_H
#define GAME_H

#include "Piece.h"
#include "Player.h"

typedef struct {
	Piece* board[8][8];
	Player *player_white;
	Player *player_black;

} Game;

Game *CreateGame(Player *player_white, Player *player_black);

void DeleteGame(Game *game);

#endif
