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

	unsigned char white_king_location[2];
	unsigned char black_king_location[2];

	// castling rights encoding
	// 1 - white king side
	// 2 - white queen side
	// 4 - black king side
	// 8 - black queen side
	// (15 at start of game)
	unsigned char castlingRights;

	unsigned char enPassantTargetSquare;

} Game;

Game *CreateGame(Player *player_white, Player *player_black);

void SetDefaultPosition(Game *game);

void ClearBoard(Game *game);

void DeleteGame(Game *game);

Game *CloneGame(Game *game);

void AddPiece(Game *game, Piece *piece, unsigned char rank, unsigned char file);

void RemovePiece(Game *game, unsigned char rank, unsigned char file);

void MovePiece(Game *game, Move *move);

int HasPiece(Game *game, unsigned char rank, unsigned char file);

Piece *GetPiece(Game *game, unsigned char rank, unsigned char file);

int LocIsOnBoard(unsigned char rank, unsigned char file);

#endif
