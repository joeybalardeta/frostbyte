#ifndef PLAYER_H
#define PLAYER_H

#define COMPUTER 0
#define USER 1

typedef struct {
	unsigned char type;
} Player;

Player *CreatePlayer(unsigned char type);

void DeletePlayer(Player *player);

#endif
