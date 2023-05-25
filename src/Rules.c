#include <stdio.h>
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

	DeleteMoveList(legalMoves);

	if (legalMoveFound) {
		return 1;
	}

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
		if (LocScanCheck(game, color, kingRank, kingFile + i, ROOK)) {
			return 1;
		}
		if (LocScanCheck(game, color, kingRank, kingFile + i, QUEEN)) {
			return 1;
		}

		if (LocIsOnBoard(kingRank, kingFile + i) && HasPiece(game, kingRank, kingFile + i)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		if (LocScanCheck(game, color, kingRank, kingFile - i, ROOK)) {
			return 1;
		}
		if (LocScanCheck(game, color, kingRank, kingFile - i, QUEEN)) {
			return 1;
		}

		if (LocIsOnBoard(kingRank, kingFile - i) && HasPiece(game, kingRank, kingFile - i)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		if (LocScanCheck(game, color, kingRank + i, kingFile, ROOK)) {
			return 1;
		}
		if (LocScanCheck(game, color, kingRank + i, kingFile, QUEEN)) {
			return 1;
		}

		if (LocIsOnBoard(kingRank + i, kingFile) && HasPiece(game, kingRank + i, kingFile)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		if (LocScanCheck(game, color, kingRank - i, kingFile, ROOK)) {
			return 1;
		}
		if (LocScanCheck(game, color, kingRank - i, kingFile, QUEEN)) {
			return 1;
		}

		if (LocIsOnBoard(kingRank - i, kingFile) && HasPiece(game, kingRank - i, kingFile)) {
			break;
		}
	}

	
	// scan for bishop and queen checks
	for (int i = 1; i < 8; i++) {
		if (LocScanCheck(game, color, kingRank + i, kingFile + i, BISHOP)) {
			return 1;
		}
		if (LocScanCheck(game, color, kingRank + i, kingFile + i, QUEEN)) {
			return 1;
		}

		if (LocIsOnBoard(kingRank + i, kingFile + i) && HasPiece(game, kingRank + i, kingFile + i)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		if (LocScanCheck(game, color, kingRank + i, kingFile - i, BISHOP)) {
			return 1;
		}
		if (LocScanCheck(game, color, kingRank + i, kingFile - i, QUEEN)) {
			return 1;
		}

		if (LocIsOnBoard(kingRank + i, kingFile - i) && HasPiece(game, kingRank + i, kingFile - i)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		if (LocScanCheck(game, color, kingRank - i, kingFile + i, BISHOP)) {
			return 1;
		}
		if (LocScanCheck(game, color, kingRank - i, kingFile + i, QUEEN)) {
			return 1;
		}

		if (LocIsOnBoard(kingRank - i, kingFile + i) && HasPiece(game, kingRank - i, kingFile + i)) {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		if (LocScanCheck(game, color, kingRank - i, kingFile - i, BISHOP)) {
			return 1;
		}
		if (LocScanCheck(game, color, kingRank - i, kingFile - i, QUEEN)) {
			return 1;
		}

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


// function return codes
// 0 - no checkmate or stalemate
// -1 - checkmate
// -2 - stalemate
int IsCheckOrStaleMated(Game *game, unsigned char color) {
	MLIST *allLegalMoves = GenerateAllLegalMoves(game, color);

	MLENTRY *moveListEntry = allLegalMoves->first;

	for (int i = 0; i < allLegalMoves->length; i++) {
		PrintMove(moveListEntry->move);
		moveListEntry = moveListEntry->next;
	}

	printf("Number of Legal Moves: %d\n", allLegalMoves->length);

	if (allLegalMoves->length != 0) {
		DeleteMoveList(allLegalMoves);
		return 0;
	}
		
	DeleteMoveList(allLegalMoves);

	if (IsInCheck(game, color)) {
		return -1;
	}
	else {
		return -2;
	}
}

MLIST *GenerateAllLegalMoves(Game *game, unsigned char color) {
	MLIST *allLegalMoves = CreateMoveList();
	for (int i = 0; i < 8; i ++) {
		for (int j = 0; j < 8; j++) {
			MLIST *squareLegalMoves = GenerateLegalMoves(game, i, j, color);
			allLegalMoves = AddMoveLists(allLegalMoves, squareLegalMoves);
			if (squareLegalMoves != NULL) {
				DeleteMoveList(squareLegalMoves);
			}
		}
	}

	return allLegalMoves;
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

			break;
		}
		case BISHOP:
		{
			for (int quadrant = 0; quadrant < 4; quadrant++) {
				int x_mult = 1;
				int y_mult = 1;

				if (quadrant == 1) {
					x_mult = -1;
					y_mult = 1;
				}
				else if (quadrant == 2) {
					x_mult = -1;
					y_mult = -1;
				}
				else if (quadrant == 3) {
					x_mult = 1;
					y_mult = -1;
				}	

				for (int i = 1; i < 8; i++) {
					if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && !HasPiece(game, rank + (i * x_mult), file + (i * y_mult))) {
						AddMove(legalMoves, CreateMove(rank, file, rank + (i * x_mult), file + (i * y_mult)));
					}
					else if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && HasPiece(game, rank + (i * x_mult), file + (i * y_mult)) && GetPiece(game, rank + (i * x_mult), file + (i * y_mult))->color != color) {
						AddMove(legalMoves, CreateMove(rank, file, rank + (i * x_mult), file + (i * y_mult)));
						break;
					}
					else if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && HasPiece(game, rank + (i * x_mult), file + (i * y_mult)) && GetPiece(game, rank + (i * x_mult), file + (i * y_mult))->color == color) {
						break;
					}
				}
			}

			break;
		}
		case KNIGHT:
		{
			char possibleMoves[8][2] = { {2, 1},
										 {2, -1},
									     {-2, 1},									
										 {-2, -1},
										 {1, 2},
										 {1, -2},
										 {-1, 2},
										 {-1, -2} };
			
			for (int i = 0; i < 8; i++) {
				if (LocIsOnBoard(rank + possibleMoves[i][0], file + possibleMoves[i][1]) && ((!HasPiece(game, rank + possibleMoves[i][0], file + possibleMoves[i][1])) || (HasPiece(game, rank + possibleMoves[i][0], file + possibleMoves[i][1]) && GetPiece(game, rank + possibleMoves[i][0], file + possibleMoves[i][1])->color != color))) {
					AddMove(legalMoves, CreateMove(rank, file, rank + possibleMoves[i][0], file + possibleMoves[i][1]));
				
				}
			}

			break;
		}
		case ROOK:
		{
			for (int quadrant = 0; quadrant < 4; quadrant++) {
				int x_mult = 1;
				int y_mult = 0;

				if (quadrant == 1) {
					x_mult = 0;
					y_mult = 1;
				}
				else if (quadrant == 2) {
					x_mult = -1;
					y_mult = 0;
				}
				else if (quadrant == 3) {
					x_mult = 0;
					y_mult = -1;
				}	

				for (int i = 1; i < 8; i++) {
					if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && !HasPiece(game, rank + (i * x_mult), file + (i * y_mult))) {
						AddMove(legalMoves, CreateMove(rank, file, rank + (i * x_mult), file + (i * y_mult)));
					}
					else if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && HasPiece(game, rank + (i * x_mult), file + (i * y_mult)) && GetPiece(game, rank + (i * x_mult), file + (i * y_mult))->color != color) {
						AddMove(legalMoves, CreateMove(rank, file, rank + (i * x_mult), file + (i * y_mult)));
						break;
					}
					else if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && HasPiece(game, rank + (i * x_mult), file + (i * y_mult)) && GetPiece(game, rank + (i * x_mult), file + (i * y_mult))->color == color) {
						break;
					}
				}
			}

			break;
		}
		case QUEEN:
		{

			for (int quadrant = 0; quadrant < 4; quadrant++) {
				int x_mult = 1;
				int y_mult = 1;

				if (quadrant == 1) {
					x_mult = -1;
					y_mult = 1;
				}
				else if (quadrant == 2) {
					x_mult = -1;
					y_mult = -1;
				}
				else if (quadrant == 3) {
					x_mult = 1;
					y_mult = -1;
				}	

				for (int i = 1; i < 8; i++) {
					if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && !HasPiece(game, rank + (i * x_mult), file + (i * y_mult))) {
						AddMove(legalMoves, CreateMove(rank, file, rank + (i * x_mult), file + (i * y_mult)));
					}
					else if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && HasPiece(game, rank + (i * x_mult), file + (i * y_mult)) && GetPiece(game, rank + (i * x_mult), file + (i * y_mult))->color != color) {
						AddMove(legalMoves, CreateMove(rank, file, rank + (i * x_mult), file + (i * y_mult)));
						break;
					}
					else if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && HasPiece(game, rank + (i * x_mult), file + (i * y_mult)) && GetPiece(game, rank + (i * x_mult), file + (i * y_mult))->color == color) {
						break;
					}
				}
			}

			for (int quadrant = 0; quadrant < 4; quadrant++) {
				int x_mult = 1;
				int y_mult = 0;

				if (quadrant == 1) {
					x_mult = 0;
					y_mult = 1;
				}
				else if (quadrant == 2) {
					x_mult = -1;
					y_mult = 0;
				}
				else if (quadrant == 3) {
					x_mult = 0;
					y_mult = -1;
				}	

				for (int i = 1; i < 8; i++) {
					if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && !HasPiece(game, rank + (i * x_mult), file + (i * y_mult))) {
						AddMove(legalMoves, CreateMove(rank, file, rank + (i * x_mult), file + (i * y_mult)));
					}
					else if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && HasPiece(game, rank + (i * x_mult), file + (i * y_mult)) && GetPiece(game, rank + (i * x_mult), file + (i * y_mult))->color != color) {
						AddMove(legalMoves, CreateMove(rank, file, rank + (i * x_mult), file + (i * y_mult)));
						break;
					}
					else if (LocIsOnBoard(rank + (i * x_mult), file + (i * y_mult)) && HasPiece(game, rank + (i * x_mult), file + (i * y_mult)) && GetPiece(game, rank + (i * x_mult), file + (i * y_mult))->color == color) {
						break;
					}
				}
			}

			break;
		}
		case KING:
		{
			for (int i = -1; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					if (LocIsOnBoard(rank + i, file + j) && ((!HasPiece(game, rank + i, file + j)) || (HasPiece(game, rank + i, file + j) && GetPiece(game, rank + i, file + j)->color != color))) {
						AddMove(legalMoves, CreateMove(rank, file, rank + i, file + j));
					}
				}
			}
		}

		break;
	}

	int legalMovesLength = legalMoves->length;

	MLENTRY *currentTestedMoveEntry = legalMoves->last;

	for (int i = legalMovesLength - 1; i >= 0; i--) {
		Game *clonedGame = CloneGame(game);

		Move *move = currentTestedMoveEntry->move;

		MovePiece(clonedGame, move);


		currentTestedMoveEntry = currentTestedMoveEntry->prev;

		if (IsInCheck(clonedGame, color)) {
			RemoveMoveListEntry(legalMoves, i);
		}

		DeleteGame(clonedGame);
	}

	return legalMoves;
}
