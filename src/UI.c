#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "UI.h"
#include "Player.h"
#include "Rules.h"
#include "AI.h"

void PrintMenu() {
	printf("Choose an option:\n\n");
	
	printf("1 - Player vs. Player\n");
	printf("2 - Player vs. Computer\n");
	printf("3 - Computer vs. Computer\n");
	printf("4 - Computer vs. Computer (Machine Learning)\n");
	printf("5 - View previous game log\n");
	printf("6 - Exit\n\n");

	printf("Enter choice here: ");
}


void ProcessInput(int input) {
	switch (input) {
		case 1:
		{
			printf("Starting Player vs. Player\n\n");
			Game *game = CreateGame(CreatePlayer(USER), CreatePlayer(USER));
			GameLoop(game);
			DeleteGame(game);
			break;
		}

		case 2:
		{
			printf("Starting Player vs. Computer\n\n");
			Game *game = CreateGame(CreatePlayer(USER), CreatePlayer(COMPUTER));
			GameLoop(game);
			DeleteGame(game);
			break;
		}

		case 3:
		{
			printf("Starting Computer vs. Computer\n\n");
			Game *game = CreateGame(CreatePlayer(COMPUTER), CreatePlayer(COMPUTER));
			GameLoop(game);
			DeleteGame(game);
			break;
		}

		case 4:
		{
			printf("Starting Computer vs. Computer (Machine Learning)\n\n");
			break;
		}		

		case 5:
		{
			printf("Printing previous game log:\n\n");
			break;
		}
		
		case 6:
		{
			printf("Exiting program.\n\n");
			break;
		}		

		default:
			printf("Invalid input.\n\n");
			break;
	}
}


void UILoop() {
	int user_input = 0;
	while (user_input != 6) {
		PrintMenu();
		while (!(scanf("%d", &user_input) > 0)) {
			;
		}
		ProcessInput(user_input);
	}
}


void PrintBoard(Game *game) {
	
	for (int i = 8; i > 0; i--){
		printf("  +----+----+----+----+----+----+----+----+\n");

		printf("%d |", i);
		for (int j = 0; j <= 7; j++){
			char *name;
			if (game->board[j][i - 1] != NULL){
				name = PieceToString(game->board[j][i - 1]);
				printf(" %s |", name);
				free(name);
			}
			else {
				name = "  ";
				printf(" %s |", name);
			}
		}
		printf("\n");
	}

	printf("  +----+----+----+----+----+----+----+----+\n");
	printf("    A    B    C    D    E    F    G    H\n");
}


void PrintBoardR(Game *game) {
	for (int i = 0; i < 8; i++){
        printf("  +----+----+----+----+----+----+----+----+\n");

        printf("%d |", i + 1);
        for (int j = 8; j > 0; j--){
            char *name = "  ";
            if (game->board[j - 1][i] != NULL){
				name = PieceToString(game->board[j - 1][i]);
				printf(" %s |", name);
				free(name);
			}
			else {
				name = "  ";
				printf(" %s |", name);
            }
        }
        printf("\n");
    }

    printf("  +----+----+----+----+----+----+----+----+\n");
    printf("    H    G    F    E    D    C    B    A\n");
}

Move *GetUserMove(Game *game, unsigned char color) {
	unsigned char from_rank;
	unsigned char from_file;

	unsigned char to_rank;
	unsigned char to_file;

	unsigned int iteration = 0;

	int moveErrorCode = -3301;

	Move *move = NULL;

	do {
		if (move) {
			DeleteMove(move);
		}

		char buffer[1000];
		bzero(buffer, 1000);		

		if (moveErrorCode == 0) {
			printf("Incorrect move format!\n\n");
		}
		else if (moveErrorCode == -1) {
			printf("No piece of user color at location!\n\n");
		}
		else if (moveErrorCode == -2) {
			printf("Illegal move!\n\n");
		}

		printf("\nEnter move (for format enter '-f'): ");

		scanf("%s", buffer);
		sscanf(buffer, "%c%c,%c%c", &from_rank, &from_file, &to_rank, &to_file);

		if (from_rank == '-' && from_file == 'f') {
			printf("\nMove format: starting square,ending square\n");
			printf("Starting square - the square of the piece you would like to move.\n");
			printf("Ending square - the square you would like to move to.\n\n");
			printf("Example - 'e2,e4'\n\n");

			iteration = 0;
		}
		else {
			from_rank = from_rank - 'a';
			from_file = from_file  - '1';
			to_rank = to_rank - 'a';
			to_file = to_file - '1';

			iteration++;
		}		

		if (iteration != 0) {
			move = CreateMove(from_rank, from_file, to_rank, to_file);

			moveErrorCode = ValidateUserMove(game, move, color);
		}

	} while (moveErrorCode != 1);


	printf("\n\n");

	return move;
}

void GameLoop(Game *game) {
	while(1) {
		PrintBoard(game);

		// checkmate scanning		
		int gameState = IsCheckOrStaleMated(game, WHITE);

		if (gameState == -1) {
			printf("Black wins by checkmate!\n\n");
			break;
		}
		else if (gameState == -2) {
			printf("Draw by stalemate!\n\n");
			break;
		}
		else if (gameState == -3) {
			printf("Draw by insufficient material!\n\n");
			break;
		}


		// get white's move
		if (game->player_white->type == USER) {
			Move *move = GetUserMove(game, WHITE);
			MovePiece(game, move);
			DeleteMove(move);
		}
		else {
			Move *move = GetAIMove(game, WHITE);
			MovePiece(game, move);
			DeleteMove(move);
		}

		CheckPromotions(game, WHITE);

		PrintBoardR(game);


		// checkmate scanning
		gameState = IsCheckOrStaleMated(game, BLACK);

		if (gameState == -1) {
			printf("White wins by checkmate!\n\n");
			break;
		}
		else if (gameState == -2) {
			printf("Draw by stalemate!\n\n");
			break;
		}
		else if (gameState == -3) {
			printf("Draw by insufficient material!\n\n");
			break;
		}


		// get black's move
		if (game->player_black->type == USER) {
			Move *move = GetUserMove(game, BLACK);
			MovePiece(game, move);
			DeleteMove(move);
		}
		else {
			Move *move = GetAIMove(game, BLACK);
			MovePiece(game, move);
			DeleteMove(move);
		}


		CheckPromotions(game, BLACK);

	}
}
