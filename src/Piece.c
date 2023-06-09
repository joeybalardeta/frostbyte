#include <stdlib.h>
#include "Piece.h"

Piece *CreatePiece(unsigned char color, unsigned char type) {
	Piece *piece = (Piece *) malloc(sizeof(Piece));
	piece->color = color;
	piece->type = type;
	return piece;
}


Piece *ClonePiece(Piece *piece) {
	if (piece == NULL) {
		return NULL;
	}

	Piece *clonedPiece = (Piece *) malloc(sizeof(Piece));

	clonedPiece->color = piece->color;
	clonedPiece->type = piece->type;
	
	return clonedPiece;
}


char IsColor(Piece *piece, unsigned char color) {
	return piece->color == color;
}


char IsType(Piece *piece, unsigned char type) {
	return piece->type == type;
}


void DeletePiece(Piece *piece) {
	if (piece) {
		free(piece);
	}
}

void PromotePiece(Piece *piece, unsigned char type) {
	piece->type = type;
}


char *PieceToString(Piece *piece) {
	char *name = malloc(sizeof(char) * 3);

	name[0] = ' ';
	name[1] = ' ';
	name[2] = '\0';

	if (piece->color == WHITE) {
		name[0] = 'W';
	}
	else {
		name[0] = 'B';
	}


	if (piece->type == PAWN) {
		name[1] = 'P';
	}
	else if (piece->type == ROOK) {
		name[1] = 'R';
	}
	else if (piece->type == KNIGHT) {
		name[1] = 'N';
	}
	else if (piece->type == BISHOP) {
		name[1] = 'B';
	}
	else if (piece->type == QUEEN) {
		name[1] = 'Q';
	}
	else if (piece->type == KING) {
		name[1] = 'K';
	}

	return name;
}
