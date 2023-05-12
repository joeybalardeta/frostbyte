#ifndef MOVELIST_H
#define MOVELIST_H

#include "Move.h"

typedef struct MoveList MLIST;
typedef struct MoveListEntry MLENTRY;

struct MoveList {
	MLENTRY *first;
	MLENTRY *last;
	unsigned int length;
};

struct MoveListEntry {
	MLIST *moveList;
	MLENTRY *prev;
	MLENTRY *next;
	Move *move;
};


MLIST *CreateMoveList();

void RemoveMoveListEntry(MLIST *moveList, unsigned int entry);

void DeleteMoveList(MLIST *moveList);

MLENTRY *CreateMoveListEntry(Move *move);

void AddMoveListEntry(MLIST *moveList, MLENTRY *moveListEntry);

void DeleteMoveListEntry(MLENTRY *moveListEntry);

#endif
