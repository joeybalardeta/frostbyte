#ifndef MOVE_H
#define MOVE_H

#include <assert.h>

typedef struct {
	unsigned char from_rank;
	unsigned char from_file;

	unsigned char to_rank;
	unsigned char to_file;

} Move;


Move *CreateMove(unsigned char from_rank, unsigned char from_file, unsigned char to_rank, unsigned char to_file);

void DeleteMove(Move *move);

#endif
