#include <stdlib.h>
#include <assert.h>
#include "Game.h"

Game *CreateGame(Player *player_white, Player *player_black) {
	Game *game = (Game *) malloc(sizeof(game)); 
	game->player_white = player_white;
	game->player_black = player_black;

	AddPiece(game, CreatePiece(WHITE, PAWN), 1, 1);


	return game;
}


void DeleteGame(Game *game) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			RemovePiece(game, i, j);
		}
	}
	if (game) {
		free(game);
	}
}

void AddPiece(Game *game, Piece *piece, char rank, char file) {
	game->board[rank - 1][file - 1] = piece;
}


void RemovePiece(Game *game, char rank, char file) {
	if (game->board[rank - 1][file - 1]) {
		DeletePiece(game->board[rank - 1][file - 1]);
	}
}
