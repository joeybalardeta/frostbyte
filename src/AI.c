#include <time.h>
#include <stdlib.h>
#include "Game.h"
#include "Rules.h"


Move *GetAIMove(Game *game, unsigned int color) {
	MLIST *legalMoves = GenerateAllLegalMoves(game, color);

	srand(time(NULL));

	int index = rand() % legalMoves->length;

	Move *move = CloneMove(GetMoveListEntry(legalMoves, index)->move);

	DeleteMoveList(legalMoves);

	return move;
}
