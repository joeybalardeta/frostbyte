#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "MoveList.h"

MLIST *CreateMoveList() {
	MLIST *moveList = (MLIST *) malloc(sizeof(MLIST));

	moveList->first = NULL;
	moveList->last = NULL;
	moveList->length = 0;

	return moveList;
}

void RemoveMoveListEntry(MLIST *moveList, unsigned int entry) {
	assert(entry < moveList->length);
	MLENTRY *current = moveList->first;
	for (int i = 0; i < entry; i++) {
		current = current->next;
	}

	

	if (moveList->length == 1) {
		moveList->first = NULL;
		moveList->last = NULL;
	}
	else if (entry == 0) {
		moveList->first = current->next;
		current->next->prev = NULL;
	}
	else if (entry == moveList->length - 1) {
		moveList->last = current->prev;
		current->prev->next = NULL;
	}
	else {
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}

	moveList->length -= 1;

	DeleteMoveListEntry(current);
}

void DeleteMoveList(MLIST *moveList) {
	unsigned int moveListLength = moveList->length;
	for (int i = 0; i < moveListLength; i++) {
		RemoveMoveListEntry(moveList, 0);
	}

	free(moveList);
}



MLIST *AddMoveLists(MLIST *destination, MLIST *source) {
	if (destination == NULL && source != NULL) {
		return source;
	}
	else if (destination == NULL) {
		return NULL;
	}
	else if (source == NULL) {
		return destination;
	}

	MLENTRY *toClone = source->first;

	for (int i = 0; i < source->length; i++) {
		AddMoveListEntry(destination, CloneMoveListEntry(toClone));
		toClone = toClone->next;
	}

	return destination;
}


MLENTRY *CreateMoveListEntry(Move *move) {
	MLENTRY *moveListEntry = (MLENTRY *) malloc(sizeof(MLENTRY));

	moveListEntry->moveList = NULL;

	moveListEntry->prev = NULL;
	moveListEntry->next = NULL;

	moveListEntry->move = move;

	return moveListEntry;
}


MLENTRY *CloneMoveListEntry(MLENTRY *moveListEntry) {
	MLENTRY *clonedEntry = CreateMoveListEntry(CloneMove(moveListEntry->move));

	return clonedEntry;	
}

void AddMoveListEntry(MLIST *moveList, MLENTRY *moveListEntry) {
	if (moveList->length == 0) {
		moveList->first = moveListEntry;
	}
	else {
		moveList->last->next = moveListEntry;
	}

	moveListEntry->moveList = moveList;

	moveListEntry->prev = moveList->last;

	moveList->last = moveListEntry;

	moveList->length += 1;
}

MLENTRY *GetMoveListEntry(MLIST *moveList, unsigned int index) {
	if (index > moveList->length - 1) {
		return NULL;
	}

	MLENTRY *moveListEntry = moveList->first;

	for (int i = 0; i < index; i++) {
		moveListEntry = moveListEntry->next;
	}

	return moveListEntry;
}

void AddMove(MLIST *moveList, Move *move) {
	MLENTRY *moveListEntry = CreateMoveListEntry(move);
	AddMoveListEntry(moveList, moveListEntry);
}

void DeleteMoveListEntry(MLENTRY *moveListEntry) {
	assert(moveListEntry);
	if (moveListEntry->move) {
		free(moveListEntry->move);
	}

	free(moveListEntry);
}
