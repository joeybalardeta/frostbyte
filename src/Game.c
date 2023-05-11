#include "Game.h"
#include "Piece.h"
#include <stdlib.h>
#include <assert.h>

Game *CreateGame(Player *player_white, Player *player_black) {
	
	Game *game = (Game *) malloc(sizeof(Game)); 

	game->player_white = player_white;
	game->player_black = player_black;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			game->board[i][j] = NULL;
		}
	}

	AddPiece(game, CreatePiece(WHITE, PAWN), 0, 1);
	AddPiece(game, CreatePiece(WHITE, PAWN), 1, 1);
	AddPiece(game, CreatePiece(WHITE, PAWN), 2, 1);
	AddPiece(game, CreatePiece(WHITE, PAWN), 3, 1);
	AddPiece(game, CreatePiece(WHITE, PAWN), 4, 1);
	AddPiece(game, CreatePiece(WHITE, PAWN), 5, 1);
	AddPiece(game, CreatePiece(WHITE, PAWN), 6, 1);
	AddPiece(game, CreatePiece(WHITE, PAWN), 7, 1);
	AddPiece(game, CreatePiece(WHITE, ROOK), 0, 0);
	AddPiece(game, CreatePiece(WHITE, KNIGHT), 1, 0);
	AddPiece(game, CreatePiece(WHITE, BISHOP), 2, 0);
	AddPiece(game, CreatePiece(WHITE, QUEEN), 3, 0);
	AddPiece(game, CreatePiece(WHITE, KING), 4, 0);
	AddPiece(game, CreatePiece(WHITE, BISHOP), 5, 0);
	AddPiece(game, CreatePiece(WHITE, KNIGHT), 6, 0);
	AddPiece(game, CreatePiece(WHITE, ROOK), 7, 0);

	AddPiece(game, CreatePiece(BLACK, PAWN), 0, 6);
	AddPiece(game, CreatePiece(BLACK, PAWN), 1, 6);
	AddPiece(game, CreatePiece(BLACK, PAWN), 2, 6);
	AddPiece(game, CreatePiece(BLACK, PAWN), 3, 6);
	AddPiece(game, CreatePiece(BLACK, PAWN), 4, 6);
	AddPiece(game, CreatePiece(BLACK, PAWN), 5, 6);
	AddPiece(game, CreatePiece(BLACK, PAWN), 6, 6);
	AddPiece(game, CreatePiece(BLACK, PAWN), 7, 6);
	AddPiece(game, CreatePiece(BLACK, ROOK), 0, 7);
	AddPiece(game, CreatePiece(BLACK, KNIGHT), 1, 7);
	AddPiece(game, CreatePiece(BLACK, BISHOP), 2, 7);
	AddPiece(game, CreatePiece(BLACK, QUEEN), 3, 7);
	AddPiece(game, CreatePiece(BLACK, KING), 4, 7);
	AddPiece(game, CreatePiece(BLACK, BISHOP), 5, 7);
	AddPiece(game, CreatePiece(BLACK, KNIGHT), 6, 7);
	AddPiece(game, CreatePiece(BLACK, ROOK), 7, 7);

	return game;
}


void DeleteGame(Game *game) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			RemovePiece(game, i, j);
		}
	}

	DeletePlayer(game->player_white);
	game->player_white = NULL;

	DeletePlayer(game->player_black);
	game->player_black = NULL;

	if (game) {
		free(game);
	}
}

void AddPiece(Game *game, Piece *piece, unsigned char rank, unsigned char file) {
	game->board[rank][file] = piece;
}


void RemovePiece(Game *game, unsigned char rank, unsigned char file) {
	if (game->board[rank][file]) {
		DeletePiece(game->board[rank][file]);
	}
}


void MovePiece(Game *game, unsigned char from_rank, unsigned char from_file, unsigned char to_rank, unsigned char to_file) {
	RemovePiece(game, to_rank, to_file);
	game->board[to_rank][to_file] = game->board[from_rank][from_file];
	game->board[from_rank][from_file] = NULL;

}


