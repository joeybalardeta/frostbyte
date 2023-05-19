#include <stdlib.h>
#include "Rules.h"
#include "Piece.h"

int ValidateUserMove(Game *game, Move *move, unsigned char color) {
	if (!IsValidPieceMove(game, move, color)) {
		return 0;
	}

	if (IsObstructed(game, move, color)) {
		return 0;
	}

	return 1;
}

int ValidateAIMove(Game *game, Move *move, unsigned char color) {
	return 0;
}

int IsValidPieceMove(Game *game, Move *move, unsigned char color) {
	Piece *piece = game->board[move->from_rank][move->from_file];

	if (!piece) {
		return 0;
	}

	if (!(piece->color == color)) {
		return 0;
	}

	if (move->from_rank == move->to_rank && move->from_file == move->to_file) {
		return 0;
	}

	switch (piece->type) {
		case PAWN:
		{
			;
		}

		case BISHOP:
		{
			;
		}

		case KNIGHT:
		{
			;
		}

		case ROOK:
		{
			;
		}

		case QUEEN:
		{
			;
		}

		case KING:
		{
			;
		}

		default:
		{
			;
		}
	}

	return 0;
}

int IsObstructed(Game *game, Move *move, unsigned char color) {
	return 0;
}

int IsInCheck(Game *game, unsigned char color) {
	return 0;
}

int IsCheckmated(Game *game, unsigned char color) {
	return 0;
}

MLIST *GenerateLegalMoves(Game *game, Piece *piece, unsigned char color) {
	return NULL;
}
