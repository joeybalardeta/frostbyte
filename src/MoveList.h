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

MLIST *AddMoveLists(MLIST *destination, MLIST *source);

MLENTRY *CreateMoveListEntry(Move *move);

MLENTRY *CloneMoveListEntry(MLENTRY *moveListEntry);

void AddMoveListEntry(MLIST *moveList, MLENTRY *moveListEntry);

MLENTRY *GetMoveListEntry(MLIST *moveList, unsigned int index);

void AddMove(MLIST *moveList, Move *move);

void DeleteMoveListEntry(MLENTRY *moveListEntry);

#endif
