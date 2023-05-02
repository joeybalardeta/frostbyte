typedef enum {COMPUTER = 0, PLAYER} PlayerType;

typedef struct {
	PlayerType type;

} Player;

Player *CreatePlayer(PlayerType type);

void DeletePlayer(Player *player);
