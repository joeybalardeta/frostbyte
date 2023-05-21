#include <stdlib.h>
#include "Rules.h"
#include "Piece.h"


// validate the user move before attempting to make it on the board
// error codes:
//  0 - Move is not on the board
// -1 - No piece (of user color) at location
// -2 - Invalid move
int ValidateUserMove(Game *game, Move *move, unsigned char color) {
	if (!LocIsOnBoard(move->from_rank, move->from_file) || !(LocIsOnBoard(move->to_rank, move->to_file))) {
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
	unsigned char kingRank = 0;
	unsigned char kingFile = 0;

	for (unsigned char i = 0; i < 8; i++) {
		for (unsigned char j = 0; j < 8; j++) {
			if (HasPiece(game, i, j) && GetPiece(game, i, j)->color == color && GetPiece(game, i , j)->type == KING) {
					kingRank = i;
					kingFile = j;
			}
		}
	}

	int opponent_move_dir;

	if (color == WHITE) {
		opponent_move_dir = -1;
	}
	else {
		opponent_move_dir = 1;
	}

	// scan for pawn checks
	if (LocScanCheck(game, color, kingRank - 1, kingFile - opponent_move_dir, PAWN)) {
		return 1;
	}

	if (LocScanCheck(game, color, kingRank + 1, kingFile - opponent_move_dir, PAWN)) {
		return 1;
	}


	// scan for knight checks
	if (LocScanCheck(game, color, kingRank - 1, kingFile - 2, KNIGHT)) {
		return 1;
	}
	if (LocScanCheck(game, color, kingRank - 1, kingFile + 2, KNIGHT)) {
		return 1;
	}
	if (LocScanCheck(game, color, kingRank + 1, kingFile - 2, KNIGHT)) {
		return 1;
	}
	if (LocScanCheck(game, color, kingRank + 1, kingFile + 2, KNIGHT)) {
		return 1;
	}
	if (LocScanCheck(game, color, kingRank - 2, kingFile - 1, KNIGHT)) {
		return 1;
	}
	if (LocScanCheck(game, color, kingRank - 2, kingFile + 1, KNIGHT)) {
		return 1;
	}
	if (LocScanCheck(game, color, kingRank + 2, kingFile - 1, KNIGHT)) {
		return 1;
	}
	if (LocScanCheck(game, color, kingRank + 2, kingFile + 1, KNIGHT)) {
		return 1;
	}


	// scan for rook and queen checks
	for (int i = 1; i < 8; i++) {
		LocScanCheck(game, color, kingRank, kingFile + i, ROOK);
		LocScanCheck(game, color, kingRank, kingFile + i, QUEEN);

		if (LocIsOnBoard(kingRank, kingFile + i) && HasPiece(game, kingRank, kingFile + i)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		LocScanCheck(game, color, kingRank, kingFile - i, ROOK);
		LocScanCheck(game, color, kingRank, kingFile - i, QUEEN);

		if (LocIsOnBoard(kingRank, kingFile - i) && HasPiece(game, kingRank, kingFile - i)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		LocScanCheck(game, color, kingRank + i, kingFile, ROOK);
		LocScanCheck(game, color, kingRank + i, kingFile, QUEEN);

		if (LocIsOnBoard(kingRank + i, kingFile) && HasPiece(game, kingRank + i, kingFile)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		LocScanCheck(game, color, kingRank - i, kingFile, ROOK);
		LocScanCheck(game, color, kingRank - i, kingFile, QUEEN);

		if (LocIsOnBoard(kingRank - i, kingFile) && HasPiece(game, kingRank - i, kingFile)) {
			break;
		}
	}

	
	// scan for bishop and queen checks
	for (int i = 1; i < 8; i++) {
		LocScanCheck(game, color, kingRank + i, kingFile + i, BISHOP);
		LocScanCheck(game, color, kingRank + i, kingFile + i, QUEEN);

		if (LocIsOnBoard(kingRank + i, kingFile + i) && HasPiece(game, kingRank + i, kingFile + i)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		LocScanCheck(game, color, kingRank + i, kingFile - i, BISHOP);
		LocScanCheck(game, color, kingRank + i, kingFile - i, QUEEN);

		if (LocIsOnBoard(kingRank + i, kingFile - i) && HasPiece(game, kingRank + i, kingFile - i)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		LocScanCheck(game, color, kingRank - i, kingFile + i, BISHOP);
		LocScanCheck(game, color, kingRank - i, kingFile + i, QUEEN);

		if (LocIsOnBoard(kingRank - i, kingFile + i) && HasPiece(game, kingRank - i, kingFile + i)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		LocScanCheck(game, color, kingRank - i, kingFile - i, BISHOP);
		LocScanCheck(game, color, kingRank - i, kingFile - i, QUEEN);

		if (LocIsOnBoard(kingRank - i, kingFile - i) && HasPiece(game, kingRank - i, kingFile - i)) {
			break;
		}
	}
	

	return 0;
}

int LocScanCheck(Game *game, unsigned char color, unsigned char rank, unsigned char file, unsigned char pieceType) {
	if (!LocIsOnBoard(rank, file)) {
		return 0;
	}

	if (!HasPiece(game, rank, file)) {
		return 0;
	}

	if (GetPiece(game, rank, file)->color == color) {
		return 0;
	}

	if (GetPiece(game, rank, file)->type != pieceType) {
		return 0;
	}

	return 1;
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
			if (LocIsOnBoard(rank, file + move_dir) && !HasPiece(game, rank, file + move_dir)) {
				AddMove(legalMoves, CreateMove(rank, file, rank, file + move_dir));
			}

			// first pawn move (can move 2 squares forward as well)
			if (LocIsOnBoard(rank, file + (move_dir * 2)) && piece->moveCount == 0 && !HasPiece(game, rank, file + move_dir) && !HasPiece(game, rank, file + (move_dir * 2))) {
				AddMove(legalMoves, CreateMove(rank, file, rank, file + (move_dir * 2)));
			}

			// basic pawn capture
			if (LocIsOnBoard(rank - 1, file + move_dir) && HasPiece(game, rank - 1, file + move_dir) && GetPiece(game, rank - 1, file + move_dir)->color != color) {
				AddMove(legalMoves, CreateMove(rank, file, rank - 1, file + move_dir));
			}

			if (LocIsOnBoard(rank + 1, file + move_dir) && HasPiece(game, rank + 1, file + move_dir) && GetPiece(game, rank + 1, file + move_dir)->color != color) {
				AddMove(legalMoves, CreateMove(rank, file, rank + 1, file + move_dir));
			}

			// En Passant	
			if (LocIsOnBoard(rank - 1, file + move_dir) && HasPiece(game, rank - 1, file) && GetPiece(game, rank - 1, file)->color != color && GetPiece(game, rank - 1, file)->type == PAWN) {
				Move *lastMove = game->lastMove;
				if (lastMove->from_rank == rank - 1 && lastMove->from_file == file + (move_dir * 2) && lastMove->to_rank == rank - 1 && lastMove->to_file == file) {
					AddMove(legalMoves, CreateMove(rank, file, rank - 1, file + move_dir));
				}
			}

			if (LocIsOnBoard(rank + 1, file + move_dir) && HasPiece(game, rank + 1, file) && GetPiece(game, rank + 1, file)->color != color && GetPiece(game, rank + 1, file)->type == PAWN) {
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
