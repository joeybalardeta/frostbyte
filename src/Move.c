#include <stdlib.h>
#include "Move.h"

Move *CreateMove(unsigned char from_rank, unsigned char from_file, unsigned char to_rank, unsigned char to_file) {
	Move *move = (Move *) malloc(sizeof(Move));

	move->from_rank = from_rank;
	move->from_file = from_file;
	move->to_rank = to_rank;
	move->to_file = to_file;

	return move;
}

Move *CloneMove(Move *move) {
	if (move == NULL) {
		return NULL;
	}

	Move *clonedMove = CreateMove(move->from_rank, move->from_file, move->to_rank, move->to_file);
	return clonedMove;
}

int MoveEquals(Move *move1, Move *move2) {
	if (move1->from_rank != move2->from_rank) {
		return 0;
	}
	if (move1->from_file != move2->from_file) {
		return 0;
	}
	if (move1->to_rank != move2->to_rank) {
		return 0;
	}
	if (move1->to_file != move2->to_file) {
		return 0;
	}

	return 1;
}

void DeleteMove(Move *move) {
	assert(move);
	free(move);
}
