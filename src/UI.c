#include <stdio.h>
#include <stdlib.h>
#include "UI.h"

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
			break;
		}

		case 2:
		{
			printf("Starting Player vs. Computer\n\n");
			break;
		}

		case 3:
		{
			printf("Starting Computer vs. Computer\n\n");
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
		scanf("%d", &user_input);
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
