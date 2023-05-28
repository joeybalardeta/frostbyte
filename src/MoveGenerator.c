#include <stdio.h>

#include "MoveGenerator.h"
#include "MoveList.h"
#include "Move.h"
#include "Game.h"
#include "Player.h"
#include "Rules.h"


unsigned int GenerateMoves(Game *game, unsigned char color, int depth) {
	unsigned int possibleMoves = 0;

	MLIST *legalMoves = GenerateAllLegalMoves(game, color);

	unsigned int legalMovesLength = legalMoves->length;

	if (depth == 0) {
		DeleteMoveList(legalMoves);
		return 1;
	}

	if (depth == 1) {
		/*
		MLENTRY *moveEntry = legalMoves->first;

		
		for (int i = 0; i < legalMoves->length; i++) {
			PrintMove(moveEntry->move);
			moveEntry = moveEntry->next;
		}
		*/

		DeleteMoveList(legalMoves);
		return legalMovesLength;
	}

	MLENTRY *moveEntry = legalMoves->first;

	for (int i = 0; i < legalMoves->length; i++) {
		Game *clonedGame = CloneGame(game);

		MovePiece(clonedGame, moveEntry->move);

		unsigned char newColor;

		if (color == WHITE) {
			newColor = BLACK;
		}
		else {
			newColor = WHITE;
		}

		

		unsigned int newMoves = GenerateMoves(clonedGame, newColor, depth - 1);

		possibleMoves += newMoves;

		if (depth == 2) {
		//	PrintMove(moveEntry->move);
		//	printf("Possible moves: %d\n", newMoves);
		}

		DeleteGame(clonedGame);

		moveEntry = moveEntry->next;

	}

	DeleteMoveList(legalMoves);

	return possibleMoves;
}
