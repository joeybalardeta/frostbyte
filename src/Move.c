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


void DeleteMove(Move *move) {
	assert(move);
	free(move);
}
