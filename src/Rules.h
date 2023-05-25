#ifndef RULES_H
#define RULES_H

#include "Game.h"
#include "Move.h"
#include "MoveList.h"

int ValidateUserMove(Game *game, Move *move, unsigned char color);

int IsInCheck(Game *game, unsigned char color);

int LocScanCheck(Game *game, unsigned char color, unsigned char rank, unsigned char file, unsigned char pieceType);

int IsCheckOrStaleMated(Game *game, unsigned char color);

MLIST *GenerateAllLegalMoves(Game *game, unsigned char color);

MLIST *GenerateLegalMoves(Game *game, unsigned char rank, unsigned char file, unsigned char color);

#endif
