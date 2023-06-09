#ifndef PIECE_H
#define PIECE_H

#define WHITE 0
#define BLACK 1

#define PAWN 0
#define KNIGHT 1
#define BISHOP 2
#define ROOK 3
#define QUEEN 4
#define KING 5


typedef struct {
	unsigned char color;
	unsigned char type;
} Piece;

Piece *CreatePiece(unsigned char color, unsigned char type);

Piece *ClonePiece(Piece *piece);

char IsColor(Piece *piece, unsigned char color);

char IsType(Piece *piece, unsigned char type);

void DeletePiece(Piece *piece);

void PromotePiece(Piece *piece, unsigned char type);

char *PieceToString(Piece *piece);

#endif
