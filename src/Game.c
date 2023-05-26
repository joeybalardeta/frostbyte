#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Game.h"
#include "Piece.h"

Game *CreateGame(Player *player_white, Player *player_black) {
	
	Game *game = (Game *) malloc(sizeof(Game)); 

	game->player_white = player_white;
	game->player_black = player_black;

	game->lastMove = NULL;

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

	if (game->lastMove) {
		DeleteMove(game->lastMove);
	}

	if (game) {
		free(game);
	}
}



Game *CloneGame(Game *game) {
	Game *clonedGame = (Game *) malloc(sizeof(Game));

	Player *playerW = CreatePlayer(COMPUTER);
	Player *playerB = CreatePlayer(COMPUTER);
	
	clonedGame->player_white = playerW;
	clonedGame->player_black = playerB;

	clonedGame->lastMove = CloneMove(game->lastMove);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (game->board[i][j] == NULL) {
				clonedGame->board[i][j] = NULL;
			}
			else {
				Piece *piece = game->board[i][j];
				Piece *clonedPiece = ClonePiece(piece);

				AddPiece(clonedGame, clonedPiece, i, j);
			}
		}
	}

	return clonedGame;
}


void AddPiece(Game *game, Piece *piece, unsigned char rank, unsigned char file) {
	game->board[rank][file] = piece;
}



void RemovePiece(Game *game, unsigned char rank, unsigned char file) {
	if (game->board[rank][file]) {
		DeletePiece(game->board[rank][file]);
	}

	game->board[rank][file] = NULL;
}


void MovePiece(Game *game, Move *move) {
	
	// all of this stuff is for en passant
	Piece *piece = GetPiece(game, move->from_rank, move->from_file);

	piece->moveCount += 1;

	int move_dir;

	if (piece->color == WHITE) {
		move_dir = 1;
	}
	else {
		move_dir = -1;
	}


	if (!HasPiece(game, move->to_rank, move->to_file) && piece->type == PAWN && move->from_rank != move->to_rank) {
		RemovePiece(game, move->to_rank, move->to_file - move_dir);
	}
	// end of en passant code


	RemovePiece(game, move->to_rank, move->to_file);
	game->board[move->to_rank][move->to_file] = game->board[move->from_rank][move->from_file];
	game->board[move->from_rank][move->from_file] = NULL;
	
	if (piece->type == KING) {
		if (move->to_rank - move->from_rank == 2) {
			game->board[move->from_rank + 1][move->from_file] = game->board[move->from_rank + 3][move->from_file];
			game->board[move->from_rank + 3][move->from_file] = NULL;		
		}
		else if (move->to_rank - move->from_rank == -2) {
			game->board[move->from_rank - 1][move->from_file] = game->board[move->from_rank - 4][move->from_file];
			game->board[move->from_rank - 4][move->from_file] = NULL;
		}
	}

	if (game->lastMove) {
		DeleteMove(game->lastMove);
	}

	game->lastMove = CloneMove(move);
}


int HasPiece(Game *game, unsigned char rank, unsigned char file) {
	if (game->board[rank][file] != NULL) {
		return 1;
	}

	return 0;
}


Piece *GetPiece(Game *game, unsigned char rank, unsigned char file) {
	if (!HasPiece(game, rank, file)) {
		return NULL;
	}
	return game->board[rank][file];
}


int LocIsOnBoard(unsigned char rank, unsigned char file) {
	if (rank < 8 && file < 8) {
		return 1;
	}
	return 0;
}
