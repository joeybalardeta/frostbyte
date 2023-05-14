#ifndef RULES_H
#define RULES_H

#include "Game.h"
#include "Move.h"

int ValidateUserMove(Game *game, Move *move, unsigned char color);

int ValidateAIMove(Game *game, Move *move, unsigned char color);

int IsValidPieceMove(Game *game, Move *move, unsigned char color);

int IsObstructed(Game *game, Move *move, unsigned char color);

int IsInCheck(Game *game, unsigned char color);

int IsCheckmated(Game *game, unsigned char color);

#endif
