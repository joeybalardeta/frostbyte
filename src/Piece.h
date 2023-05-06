#ifndef PIECE_H
#define PIECE_H

typedef enum {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING} PieceType;
typedef enum {WHITE = 0, BLACK} PieceColor;

typedef struct {
	PieceColor color;
	PieceType type;
	
} Piece;

Piece *CreatePiece(PieceColor color, PieceType type);

void DeletePiece(Piece *piece);

void PromotePiece(Piece *piece, PieceType type);

char *PieceToString(Piece *piece);

#endif
