#include <stdlib.h>
#include "Rules.h"
#include "Piece.h"



// validate the user move before attempting to make it on the board
// error codes:
//  0 - Move is not on the board
// -1 - No piece (of user color) at location
// -2 - Invalid move
int ValidateUserMove(Game *game, Move *move, unsigned char color) {
	if (!MoveIsOnBoard(move->from_rank, move->from_file) || !(MoveIsOnBoard(move->to_rank, move->to_file))) {
		return 0;
	}

	MLIST *legalMoves = GenerateLegalMoves(game, move->from_rank, move->from_file, color);

	if (legalMoves == NULL) {
		return -1;
	}

	int legalMoveFound = 0;

	MLENTRY *moveLegalEntry = legalMoves->first;

	for (int i = 0; i < legalMoves->length; i++) {
		if (MoveEquals(move, moveLegalEntry->move)) {
			legalMoveFound = 1;
			break;
		}
		moveLegalEntry = moveLegalEntry->next;
	}

	if (legalMoveFound) {
		return 1;
	}

	return 0;
}

int ValidateAIMove(Game *game, Move *move, unsigned char color) {
	return 0;
}

int IsInCheck(Game *game, unsigned char color) {
	return 0;
}

int IsCheckmated(Game *game, unsigned char color) {
	return 0;
}

MLIST *GenerateLegalMoves(Game *game, unsigned char rank, unsigned char file, unsigned char color) {
	Piece *piece = game->board[rank][file];

	if (!piece) {
		return NULL;
	}

	if (piece->color != color) {
		return NULL;
	}

	MLIST *legalMoves = CreateMoveList();

	switch(piece->type) {
		case PAWN:
		{
			int move_dir;
			if (color == WHITE) {
				move_dir = 1;
			}	
			else {
				move_dir = -1;
			}

			// moving forward
			if (MoveIsOnBoard(rank, file + move_dir) && !HasPiece(game, rank, file + move_dir)) {
				AddMove(legalMoves, CreateMove(rank, file, rank, file + move_dir));
			}

			// first pawn move (can move 2 squares forward as well)
			if (MoveIsOnBoard(rank, file + (move_dir * 2)) && piece->moveCount == 0 && !HasPiece(game, rank, file + move_dir) && !HasPiece(game, rank, file + (move_dir * 2))) {
				AddMove(legalMoves, CreateMove(rank, file, rank, file + (move_dir * 2)));
			}

			// basic pawn capture
			if (MoveIsOnBoard(rank - 1, file + move_dir) && HasPiece(game, rank - 1, file + move_dir) && GetPiece(game, rank - 1, file + move_dir)->color != color) {
				AddMove(legalMoves, CreateMove(rank, file, rank - 1, file + move_dir));
			}

			if (MoveIsOnBoard(rank + 1, file + move_dir) && HasPiece(game, rank + 1, file + move_dir) && GetPiece(game, rank + 1, file + move_dir)->color != color) {
				AddMove(legalMoves, CreateMove(rank, file, rank + 1, file + move_dir));
			}

			// En Passant	
			if (MoveIsOnBoard(rank - 1, file + move_dir) && HasPiece(game, rank - 1, file) && GetPiece(game, rank - 1, file)->color != color && GetPiece(game, rank - 1, file)->type == PAWN) {
				Move *lastMove = game->lastMove;
				if (lastMove->from_rank == rank - 1 && lastMove->from_file == file + (move_dir * 2) && lastMove->to_rank == rank - 1 && lastMove->to_file == file) {
					AddMove(legalMoves, CreateMove(rank, file, rank - 1, file + move_dir));
				}
			}

			if (MoveIsOnBoard(rank + 1, file + move_dir) && HasPiece(game, rank + 1, file) && GetPiece(game, rank + 1, file)->color != color && GetPiece(game, rank + 1, file)->type == PAWN) {
				Move *lastMove = game->lastMove;
				if (lastMove->from_rank == rank + 1 && lastMove->from_file == file + (move_dir * 2) && lastMove->to_rank == rank + 1 && lastMove->to_file == file) {
					AddMove(legalMoves, CreateMove(rank, file, rank + 1, file + move_dir));
				}
			}
		}
		case BISHOP:
		{

		}
		case KNIGHT:
		{

		}
		case ROOK:
		{

		}
		case QUEEN:
		{

		}
		case KING:
		{

		}
	}

	return legalMoves;
}
