#include <stdio.h>
#include <stdlib.h>
#include "FEN.h"

unsigned char OpenFEN(Game *game, const char *filepath) {
	// open file with FEN string
	FILE *fenFile = fopen(filepath, "r");

	// return NULL if file is NULL (meaning the file couldn't be opened/found)
	if (fenFile == NULL) {
		printf("FEN file at '%s' not found!\n", filepath);
		return 100;
	}

	// create a buffer for storing the data found inside the file
	char buffer[1000] = {0};

	// write the data inside the file into the buffer (up to 1000 characters)
	fgets(buffer, 1000, fenFile);

	// close the file stream
	fclose(fenFile);

	// clear the game board to make way for FEN string pieces
	ClearBoard(game);

	// rank and file variables to keep track of where pieces should be placed when parsing the FEN string
	unsigned char rank = 0;
	unsigned char file = 7;

	unsigned int index = 0;


	while (buffer[index] != ' ') {
		switch (buffer[index]) {
			case 'p':
				AddPiece(game, CreatePiece(BLACK, PAWN), rank, file);
				rank++;
				break;

			case 'b':
				AddPiece(game, CreatePiece(BLACK, BISHOP), rank, file);
				rank++;
				break;

			case 'n':
				AddPiece(game, CreatePiece(BLACK, KNIGHT), rank, file);
				rank++;
				break;

			case 'r':
				AddPiece(game, CreatePiece(BLACK, ROOK), rank, file);
				rank++;
				break;

			case 'q':
				AddPiece(game, CreatePiece(BLACK, QUEEN), rank, file);
				rank++;
				break;

			case 'k':
				AddPiece(game, CreatePiece(BLACK, KING), rank, file);
				game->black_king_location[0] = rank;
				game->black_king_location[1] = file;
				rank++;
				break;


			case 'P':
				AddPiece(game, CreatePiece(WHITE, PAWN), rank, file);
				rank++;
				break;

			case 'B':
				AddPiece(game, CreatePiece(WHITE, BISHOP), rank, file);
				rank++;
				break;

			case 'N':
				AddPiece(game, CreatePiece(WHITE, KNIGHT), rank, file);
				rank++;
				break;

			case 'R':
				AddPiece(game, CreatePiece(WHITE, ROOK), rank, file);
				rank++;
				break;

			case 'Q':
				AddPiece(game, CreatePiece(WHITE, QUEEN), rank, file);
				rank++;
				break;

			case 'K':
				AddPiece(game, CreatePiece(WHITE, KING), rank, file);
				game->white_king_location[0] = rank;
				game->white_king_location[1] = file;
				rank++;
				break;


			case '1':
				rank += 1;
				break;

			case '2':
				rank += 2;
				break;

			case '3':
				rank += 3;
				break;

			case '4':
				rank += 4;
				break;

			case '5':
				rank += 5;
				break;

			case '6':
				rank += 6;
				break;

			case '7':
				rank += 7;
				break;

			case '8':
				rank += 8;
				break;


			case '/':
				rank = 0;
				file--;
				break;


			default:
				break;

		}
		index++;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (HasPiece(game, i, j)) {
				GetPiece(game, i, j)->moveCount = 1;
				if (j == 1 && GetPiece(game, i, j)->type == PAWN && GetPiece(game, i, j)->color == WHITE) {
					GetPiece(game, i, j)->moveCount = 0;
				}
				if (j == 6 && GetPiece(game, i, j)->type == PAWN && GetPiece(game, i, j)->color == BLACK) {
					GetPiece(game, i, j)->moveCount = 0;
				}
			}
		}
	}

	unsigned char moveColor;


	unsigned char spaceCount = 0;
	while (spaceCount < 3) {
		switch (buffer[index]) {
			case 'w':
				moveColor = WHITE;
				break;

			case 'b':
				moveColor = BLACK;
				break;


			case 'K':
				GetPiece(game, 4, 0)->moveCount = 0;
				GetPiece(game, 7, 0)->moveCount = 0;
				break;

			case 'Q':
				GetPiece(game, 4, 0)->moveCount = 0;
				GetPiece(game, 0, 0)->moveCount = 0;
				break;

			case 'k':
				GetPiece(game, 4, 7)->moveCount = 0;
				GetPiece(game, 7, 7)->moveCount = 0;
				break;

			case 'q':
				GetPiece(game, 4, 7)->moveCount = 0;
				GetPiece(game, 0, 7)->moveCount = 0;
				break;


			case ' ':
				spaceCount++;
				break;


			default:
				break;
		}
		index++;
	}

	char enPassantRank = buffer[index];

	index++;

	char enPassantFile = buffer[index];

	if (enPassantRank != '-') {
		enPassantRank -= 'a';
		enPassantFile -= '1';
	}
	else {
		return moveColor;
	}

	printf("En passant rank: %d\n", enPassantRank);
	printf("En passant file: %d\n", enPassantFile);

	unsigned char moveDir;

	if (moveColor == WHITE) {
		moveDir = 1;
	}
	else {
		moveDir = -1;
	}

	GetPiece(game, enPassantRank, enPassantFile - moveDir)->moveCount = 1;

	game->lastMove = CreateMove(enPassantRank, enPassantFile + moveDir, enPassantRank, enPassantFile - moveDir);
	
	return moveColor;
}
