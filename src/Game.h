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

void AddPiece(Game *game, Piece *piece, unsigned char rank, unsigned char file);

void RemovePiece(Game *game, unsigned char rank, unsigned char file);

void MovePiece(Game *game, unsigned char from_rank, unsigned char from_file, unsigned char to_rank, unsigned char to_file);

#endif
