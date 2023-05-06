#ifndef UI_H
#define UI_H

#include <stdio.h>
#include "Game.h"

void PrintMenu();

void ProcessInput(int input);

void UILoop();

void PrintBoard(Game *game);

void PrintBoardR(Game *game);

#endif
