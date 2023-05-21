#ifndef GAME_H
#define GAME_H

#include "Piece.h"
#include "Player.h"
#include "Move.h"

typedef struct {
	Piece* board[8][8];
	Player *player_white;
	Player *player_black;
	Move *lastMove;

} Game;

Game *CreateGame(Player *player_white, Player *player_black);

void DeleteGame(Game *game);

void AddPiece(Game *game, Piece *piece, unsigned char rank, unsigned char file);

void RemovePiece(Game *game, unsigned char rank, unsigned char file);

void MovePiece(Game *game, Move *move);

int HasPiece(Game *game, unsigned char rank, unsigned char file);

Piece *GetPiece(Game *game, unsigned char rank, unsigned char file);

int LocIsOnBoard(unsigned char rank, unsigned char file);

#endif
