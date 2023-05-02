#include <stdlib.h>
#include "Piece.h"

Piece *CreatePiece(PieceColor color, PieceType type) {
	Piece *piece = (Piece *) malloc(sizeof(Piece));
	piece->color = color;
	piece->type = type;

	return piece;
}

void DeletePiece(Piece *piece) {
	if (piece) {
		free(piece);
	}
}

void PromotePiece(Piece *piece, PieceType type) {
	piece->type = type;
}
