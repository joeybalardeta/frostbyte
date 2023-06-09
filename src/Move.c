#include <stdio.h>
#include <stdlib.h>
#include "Move.h"

Move *CreateMove(unsigned char from_rank, unsigned char from_file, unsigned char to_rank, unsigned char to_file) {
	Move *move = (Move *) malloc(sizeof(Move));

	move->from_rank = from_rank;
	move->from_file = from_file;
	move->to_rank = to_rank;
	move->to_file = to_file;

	move->promotionFlag = 0;

	return move;
}

Move *CloneMove(Move *move) {
	if (move == NULL) {
		return NULL;
	}

	Move *clonedMove = CreateMove(move->from_rank, move->from_file, move->to_rank, move->to_file);

	clonedMove->promotionFlag = move->promotionFlag;

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

	if (move1->promotionFlag != move2->promotionFlag) {
		return 0;
	}

	return 1;
}

void DeleteMove(Move *move) {
	assert(move);
	free(move);
}

void PrintMove(Move *move) {
	printf("Move: %c%c, %c%c", move->from_rank + 'a', move->from_file + '1', move->to_rank + 'a', move->to_file + '1');

	if (move->promotionFlag != 0) {
		printf(" | Promotion Flag: %d\n", move->promotionFlag);
	}
	else {
		printf("\n");
	}
}
