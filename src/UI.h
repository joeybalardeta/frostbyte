#ifndef UI_H
#define UI_H

#include <stdio.h>
#include "Game.h"
#include "Move.h"

void PrintMenu();

void ProcessInput(int input);

void UILoop();

void PrintBoard(Game *game);

void PrintBoardR(Game *game);

Move *GetMove(Game *game, unsigned char color);

#endif
