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

	MLIST *legalMoves = GenerateLegalMoves(game, move->from_rank, move->from_file, color, NULL);

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

	if (color == WHITE) {
		kingRank = game->white_king_location[0];
		kingFile = game->white_king_location[1];
	}
	else {
		kingRank = game->black_king_location[0];
		kingFile = game->black_king_location[1];
	}

	// unused king locating loop
	/*
	for (unsigned char i = 0; i < 8; i++) {
		for (unsigned char j = 0; j < 8; j++) {
			if (HasPiece(game, i, j) && GetPiece(game, i, j)->color == color && GetPiece(game, i , j)->type == KING) {
					kingRank = i;
					kingFile = j;
					break;
			}
		}
	}
	*/	

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

	// printf("No pawn checks.\n");


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

	// printf("No knight checks.\n");

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

	// printf("No checks above.\n");

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

	// printf("No checks below.\n");

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

	// printf("No checks right.\n");

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

	
	// printf("No checks left.\n");

	// printf("No straight checks.\n");
	
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

	// printf("No checks up right.\n");

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

	// printf("No checks down right.\n");

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

	// printf("No checks up left.\n");

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

	// printf("No checks down left.\n");

	// printf("No diagonal checks.\n");

	// scan for king checks
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (LocScanCheck(game, color, kingRank + i, kingFile + j, KING)) {
				return 1;
			}
		}
	}	

	// printf("No king checks.\n");

	return 0;
}

int LocScanCheck(Game *game, unsigned char color, unsigned char rank, unsigned char file, unsigned char pieceType) {
	if (!LocIsOnBoard(rank, file)) {
		return 0;
	}

	if (!HasPiece(game, rank, file)) {
		return 0;
	}

	if (IsColor(GetPiece(game, rank, file), color)) {
		return 0;
	}

	if (!IsType(GetPiece(game, rank, file), pieceType)) {
		return 0;
	}

	return 1;
}


// function return codes
// 0 - no checkmate or stalemate
// -1 - checkmate
// -2 - stalemate
// -3 - draw by insufficient material
int IsCheckOrStaleMated(Game *game, unsigned char color) {
	int whitePieceCount = 0;
	int blackPieceCount = 0;

	int whiteKnightOrBishopPresent = 0;
	int blackKnightOrBishopPresent = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (HasPiece(game, i, j)) {
				Piece *piece = GetPiece(game, i, j);
				if (IsColor(piece, WHITE)) {
					whitePieceCount++;
					if (IsType(piece, KNIGHT) || IsType(piece, BISHOP)) {
						whiteKnightOrBishopPresent = 1;
					} 
				}
				else {
					blackPieceCount++;
					if (IsType(piece, KNIGHT) || IsType(piece, BISHOP)) {
						blackKnightOrBishopPresent = 1;
					} 
				}
			}
		}
	}	

	if (whitePieceCount == 1 && blackPieceCount == 1) {
		return -3;
	}

	if (whitePieceCount == 2 && blackPieceCount == 1 && whiteKnightOrBishopPresent) {
		return -3;
	}

	if (blackPieceCount == 2 && whitePieceCount == 1 && blackKnightOrBishopPresent) {
		return -3;
	}


	MLIST *allLegalMoves = GenerateAllLegalMoves(game, color);

	MLENTRY *moveListEntry = allLegalMoves->first;

	for (int i = 0; i < allLegalMoves->length; i++) {
		// PrintMove(moveListEntry->move);
		moveListEntry = moveListEntry->next;
	}

	// printf("Number of Legal Moves: %d\n", allLegalMoves->length);

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

			// old move generation code, new code better optimized for linked lists
			/*
			MLIST *squareLegalMoves = GenerateLegalMoves(game, i, j, color, NULL);
			allLegalMoves = AddMoveLists(allLegalMoves, squareLegalMoves);
			if (squareLegalMoves != NULL) {
				DeleteMoveList(squareLegalMoves);
			}
			*/

			GenerateLegalMoves(game, i, j, color, allLegalMoves);
		}
	}

	return allLegalMoves;
}


MLIST *GenerateLegalMoves(Game *game, unsigned char rank, unsigned char file, unsigned char color, MLIST *masterMoveList) {
	Piece *piece = game->board[rank][file];

	if (!piece) {
		return NULL;
	}

	if (piece->color != color) {
		return NULL;
	}

	MLIST *legalMoves = masterMoveList;


	if (masterMoveList == NULL) {
		legalMoves = CreateMoveList();
	}


	int checkScanStartIndex = legalMoves->length;

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
				unsigned char to_rank = rank;
				unsigned char to_file = file + move_dir;
				if ((color == WHITE && (to_file) == 7) || (color == BLACK && (to_file) == 0)) {
					for (int i = 1; i < 5; i++) {
						Move *promotionMove = CreateMove(rank, file, to_rank, to_file);
						promotionMove->promotionFlag = i;
						AddMove(legalMoves, promotionMove);
					}
				}
				else {
					Move *move = CreateMove(rank, file, to_rank, to_file);
					AddMove(legalMoves, move);
				}
			}

			// first pawn move (can move 2 squares forward as well)
			if (LocIsOnBoard(rank, file + (move_dir * 2)) && piece->moveCount == 0 && !HasPiece(game, rank, file + move_dir) && !HasPiece(game, rank, file + (move_dir * 2))) {
				AddMove(legalMoves, CreateMove(rank, file, rank, file + (move_dir * 2)));
			}

			// basic pawn capture
			if (LocIsOnBoard(rank - 1, file + move_dir) && HasPiece(game, rank - 1, file + move_dir) && !IsColor(GetPiece(game, rank - 1, file + move_dir), color)) {
				unsigned char to_rank = rank - 1;
				unsigned char to_file = file + move_dir;
				if ((color == WHITE && (to_file) == 7) || (color == BLACK && (to_file) == 0)) {
					for (int i = 1; i < 5; i++) {
						Move *promotionMove = CreateMove(rank, file, to_rank, to_file);
						promotionMove->promotionFlag = i;
						AddMove(legalMoves, promotionMove);
					}
				}
				else {
					Move *move = CreateMove(rank, file, to_rank, to_file);
					AddMove(legalMoves, move);
				}
			}

			if (LocIsOnBoard(rank + 1, file + move_dir) && HasPiece(game, rank + 1, file + move_dir) && !IsColor(GetPiece(game, rank + 1, file + move_dir), color)) {
				unsigned char to_rank = rank + 1;
				unsigned char to_file = file + move_dir;
				if ((color == WHITE && (to_file) == 7) || (color == BLACK && (to_file) == 0)) {
					for (int i = 1; i < 5; i++) {
						Move *promotionMove = CreateMove(rank, file, to_rank, to_file);
						promotionMove->promotionFlag = i;
						AddMove(legalMoves, promotionMove);
					}
				}
				else {
					Move *move = CreateMove(rank, file, to_rank, to_file);
					AddMove(legalMoves, move);
				}
			}

			// En Passant	
			if (LocIsOnBoard(rank - 1, file + move_dir) && HasPiece(game, rank - 1, file) && !IsColor(GetPiece(game, rank - 1, file), color) && IsType(GetPiece(game, rank - 1, file), PAWN)) {
				Move *lastMove = game->lastMove;
				if (lastMove->from_rank == rank - 1 && lastMove->from_file == file + (move_dir * 2) && lastMove->to_rank == rank - 1 && lastMove->to_file == file) {
					unsigned char to_rank = rank - 1;
					unsigned char to_file = file + move_dir;
					if ((color == WHITE && (to_file) == 7) || (color == BLACK && (to_file) == 0)) {
						for (int i = 1; i < 5; i++) {
							Move *promotionMove = CreateMove(rank, file, to_rank, to_file);
							promotionMove->promotionFlag = i;
							AddMove(legalMoves, promotionMove);
						}
					}
					else {
						Move *move = CreateMove(rank, file, to_rank, to_file);
						AddMove(legalMoves, move);
					}
				}
			}

			if (LocIsOnBoard(rank + 1, file + move_dir) && HasPiece(game, rank + 1, file) && !IsColor(GetPiece(game, rank + 1, file), color) && IsType(GetPiece(game, rank + 1, file), PAWN)) {
				Move *lastMove = game->lastMove;
				if (lastMove->from_rank == rank + 1 && lastMove->from_file == file + (move_dir * 2) && lastMove->to_rank == rank + 1 && lastMove->to_file == file) {
					unsigned char to_rank = rank + 1;
					unsigned char to_file = file + move_dir;
					if ((color == WHITE && (to_file) == 7) || (color == BLACK && (to_file) == 0)) {
						for (int i = 1; i < 5; i++) {
							Move *promotionMove = CreateMove(rank, file, to_rank, to_file);
							promotionMove->promotionFlag = i;
							AddMove(legalMoves, promotionMove);
						}
					}
					else {
						Move *move = CreateMove(rank, file, to_rank, to_file);
						AddMove(legalMoves, move);
					}
				}
			}

			break;
		}
		case BISHOP:
		{
			unsigned char to_rank;
			unsigned char to_file;
			for (int iteration = 0; iteration < 4; iteration++) {
				for (int i = 1; i < 8; i++) {
					if (iteration == 0) {
						to_rank = rank + i;
						to_file = file + i;
					}
					else if (iteration == 1) {
						to_rank = rank - i;
						to_file = file + i;
					}
					else if (iteration == 2) {
						to_rank = rank + i;
						to_file = file - i;
					}
					else {
						to_rank = rank - i;
						to_file = file - i;
					}
					if (LocIsOnBoard(to_rank, to_file)) {
						if (HasPiece(game, to_rank, to_file)) {
							Piece *piece = GetPiece(game, to_rank, to_file);

							if (!IsColor(piece, color)) {
								AddMove(legalMoves, CreateMove(rank, file, to_rank, to_file));
								break;
							}
							else {
								break;
							}
						}
						else {
							AddMove(legalMoves, CreateMove(rank, file, to_rank, to_file));
						}
					}
					else {
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
				if (LocIsOnBoard(rank + possibleMoves[i][0], file + possibleMoves[i][1]) && ((!HasPiece(game, rank + possibleMoves[i][0], file + possibleMoves[i][1])) || (HasPiece(game, rank + possibleMoves[i][0], file + possibleMoves[i][1]) && !IsColor(GetPiece(game, rank + possibleMoves[i][0], file + possibleMoves[i][1]), color)))) {
					AddMove(legalMoves, CreateMove(rank, file, rank + possibleMoves[i][0], file + possibleMoves[i][1]));
				}
			}

			break;
		}
		case ROOK:
		{
			unsigned char to_rank;
			unsigned char to_file;
			for (int iteration = 0; iteration < 4; iteration++) {
				for (int i = 1; i < 8; i++) {
					if (iteration == 0) {
						to_rank = rank + i;
						to_file = file;
					}
					else if (iteration == 1) {
						to_rank = rank - i;
						to_file = file;
					}
					else if (iteration == 2) {
						to_rank = rank;
						to_file = file + i;
					}
					else {
						to_rank = rank;
						to_file = file - i;
					}
					if (LocIsOnBoard(to_rank, to_file)) {
						if (HasPiece(game, to_rank, to_file)) {
							Piece *piece = GetPiece(game, to_rank, to_file);

							if (!IsColor(piece, color)) {
								AddMove(legalMoves, CreateMove(rank, file, to_rank, to_file));
								break;
							}
							else {
								break;
							}
						}
						else {
							AddMove(legalMoves, CreateMove(rank, file, to_rank, to_file));
						}
					}
					else {
						break;
					}
				}
			}

			break;
		}
		case QUEEN:
		{
			unsigned char to_rank;
			unsigned char to_file;
			for (int iteration = 0; iteration < 8; iteration++) {
				for (int i = 1; i < 8; i++) {
					if (iteration == 0) {
						to_rank = rank + i;
						to_file = file;
					}
					else if (iteration == 1) {
						to_rank = rank - i;
						to_file = file;
					}
					else if (iteration == 2) {
						to_rank = rank;
						to_file = file + i;
					}
					else if (iteration == 3) {
						to_rank = rank;
						to_file = file - i;
					}
					else if (iteration == 4) {
						to_rank = rank + i;
						to_file = file + i;
					}
					else if (iteration == 5) {
						to_rank = rank - i;
						to_file = file + i;
					}
					else if (iteration == 6) {
						to_rank = rank + i;
						to_file = file - i;
					}
					else {
						to_rank = rank - i;
						to_file = file - i;
					}

					if (LocIsOnBoard(to_rank, to_file)) {
						if (HasPiece(game, to_rank, to_file)) {
							Piece *piece = GetPiece(game, to_rank, to_file);

							if (!IsColor(piece, color)) {
								AddMove(legalMoves, CreateMove(rank, file, to_rank, to_file));
								break;
							}
							else {
								break;
							}
						}
						else {
							AddMove(legalMoves, CreateMove(rank, file, to_rank, to_file));
						}
					}
					else {
						break;
					}
				}
			}

			break;
		}
		case KING:
		{
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (LocIsOnBoard(rank + i, file + j) && ((!HasPiece(game, rank + i, file + j)) || (HasPiece(game, rank + i, file + j) && !IsColor(GetPiece(game, rank + i, file + j), color)))) {
						AddMove(legalMoves, CreateMove(rank, file, rank + i, file + j));
					}
				}
			}

			// castling
			{
				Piece *king = GetPiece(game, rank, file);

				
				if (king->moveCount == 0 && HasPiece(game, rank + 3, file) && IsType(GetPiece(game, rank + 3, file), ROOK) && IsColor(GetPiece(game, rank + 3, file), color) && GetPiece(game, rank + 3, file)->moveCount == 0) {
					if (!HasPiece(game, rank + 1, file) && !HasPiece(game, rank + 2, file)) {
						
						// printf("Running right side castle check.\n");

						if (!IsInCheck(game, color)) {
							int castleNotValid = 0;
							for (int i = 1; i < 3; i++) {
								Game *clonedGame = CloneGame(game);
								Move *move = CreateMove(rank, file, rank + i, file);
								MovePiece(clonedGame, move);

								if (IsInCheck(clonedGame, color)) {
									castleNotValid = 1;
								}

								DeleteMove(move);
								DeleteGame(clonedGame);
							}

							if (!castleNotValid) {
								AddMove(legalMoves, CreateMove(rank, file, rank + 2, file));
							}

						}

					}


				}

				
				if (king->moveCount == 0 && HasPiece(game, rank - 4, file) && IsType(GetPiece(game, rank - 4, file), ROOK) && IsColor(GetPiece(game, rank - 4, file), color) && GetPiece(game, rank - 4, file)->moveCount == 0) {
					if (!HasPiece(game, rank - 1, file) && !HasPiece(game, rank - 2, file) && !HasPiece(game, rank - 3, file)) {
						
						// printf("Running left side castle check.\n");

						int castleNotValid = 0;
						for (int i = 1; i < 4; i++) {
							Game *clonedGame = CloneGame(game);

							Move *move = CreateMove(rank, file, rank - i, file);

							MovePiece(clonedGame, move);

							if (IsInCheck(clonedGame, color)) {
								castleNotValid = 1;
							}

							DeleteMove(move);
							DeleteGame(clonedGame);
						}

						if (!castleNotValid) {
							AddMove(legalMoves, CreateMove(rank, file, rank - 2, file));
						}
					}
				}
				
			}
		}

		break;
	}



	// scanning for checks in generated moves
	int legalMovesLength = legalMoves->length;

	MLENTRY *currentTestedMoveEntry = legalMoves->last;

	for (int i = legalMovesLength - 1; i >= checkScanStartIndex; i--) {
		Game *clonedGame = CloneGame(game);

		Move *move = currentTestedMoveEntry->move;

		// PrintMove(move);

		MovePiece(clonedGame, move);


		currentTestedMoveEntry = currentTestedMoveEntry->prev;

		if (IsInCheck(clonedGame, color)) {
			RemoveMoveListEntry(legalMoves, i);
		}

		DeleteGame(clonedGame);
	}

	return legalMoves;
}


unsigned char GetPromotionChoice() {
	unsigned char choice = 0;
	while (1) {
		printf("\n\n");

		printf("A pawn is avilable for promotion!\n");
		printf("Choices:\n");

		printf("1 - Bishop\n");
		printf("2 - Knight\n");
		printf("3 - Rook\n");
		printf("4 - Queen\n");


		scanf("%c", &choice);

		printf("\n\n");

		if (choice > 0 && choice < 5) {
			break;
		}
	}

	return choice;
}
