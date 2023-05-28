#ifndef MOVE_H
#define MOVE_H

#include <assert.h>

typedef struct {
	unsigned char from_rank;
	unsigned char from_file;

	unsigned char to_rank;
	unsigned char to_file;


	// promotion flags:
	// 0 - no promotion
	// 1 - promotion to bishop
	// 2 - promotion to knight
	// 3 - promotion to rook
	// 4 - promotion to queen
	unsigned char promotionFlag;

} Move;


Move *CreateMove(unsigned char from_rank, unsigned char from_file, unsigned char to_rank, unsigned char to_file);

Move *CloneMove(Move *move);

int MoveEquals(Move *move1, Move *move2);

void DeleteMove(Move *move);

void PrintMove(Move *move);

#endif
