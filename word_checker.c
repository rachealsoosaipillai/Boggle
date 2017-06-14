#include "boggle_functions.h"

int word_checker(char **board, DNode *dictionary[BIG_HASH_SIZE], 
				DNode *submitted_words[SMALL_HASH_SIZE], char *word) {
	DNode* result;
	int success = 0;

	result = lookup(dictionary, BIG_HASH_SIZE, word);
	if (result == NULL) { 
		printf("%s is not a valid word. Please try again.\n", word);
	}			
	else {
		int word_on_board = find_word_on_board(board, word);
		if (word_on_board >= 1) { //word exists on board
			result = lookup(submitted_words, SMALL_HASH_SIZE, word);
			if (result == NULL) { //word hasn't been submitted yet
				insert(submitted_words, SMALL_HASH_SIZE, word);
				success = 1;
				printf("Successfully inserted %s.\n", word);
			}
			else {
				printf("%s has been already used. \
Please try a different word.\n", word);
			}
		} else { //word is not on board
			printf("%s does not exist on the board. Please try again.\n",
					word);
		}
	}
	
	return success;
}

int find_word_on_board(char **board, char *word) {
	int result = 0;
	char **board_copy = malloc(sizeof(char *) * 4);

    for (int i=0; i < BOARD_SIZE; i++) {
        board_copy[i] = malloc(sizeof(char) * 4);
    }
	
	//makes a duplicate board
	for (int row=0; row < BOARD_SIZE; row++) {
		for (int col=0; col < BOARD_SIZE; col++) {
			strcpy(&(board_copy[row][col]), &(board[row][col]));
		}
	}

	for (int row=0; row < BOARD_SIZE; row++) {
		for (int col=0; col < BOARD_SIZE; col++) {
			if (board_copy[row][col] == word[0]) {
				int x = row;
				int y = col;
				result += check(x, y, board_copy, word, 1);
			}
		}
	}

	for (int i=3; i >= 0; i--) {
        free(board_copy[i]);
    }

    free(board_copy);

	if (result > 0) {
		return 1;
	} else {
		return 0;
	}
}

int check(int x, int y, char **board, char *word, int i) {
	char board_original = board[x][y];
	int check_return = 0;

	if (strlen(word) == i) {
		if (board[x][y] == word[i-1]) {
			board[x][y] = '1';
			return 1;		
		} else {
			return 0;
		}
	} else {
		int c = 0;
		if (((x-1) >= 0) && (board[x-1][y] == word[i])) {
			board[x][y] = '1';
			check_return = check(x-1, y, board, word, i+1);
			c += check_return;
			if (check_return == 0) {
				board[x][y] = board_original;
			}
		}
		if (((x-1) >= 0) && ((y-1) >= 0) && (board[x-1][y-1] == word[i])) {
			board[x][y] = '1';
			check_return = check(x-1, y-1, board, word, i+1);
			c += check_return;
			if (check_return == 0) {
				board[x][y] = board_original;
			}
		}
		if (((y-1) >= 0) && (board[x][y-1] == word[i])) {
			board[x][y] = '1';
			check_return = check(x, y-1, board, word, i+1);
			c += check_return;
			if (check_return == 0) {
				board[x][y] = board_original;
			}
		}
		if (((x+1) <= 3) && ((y-1) >= 0) && (board[x+1][y-1] == word[i])) {
			board[x][y] = '1';
			check_return = check(x+1, y-1, board, word, i+1);
			c += check_return;
			if (check_return == 0) {
				board[x][y] = board_original;
			}
		}
		if (((x+1) <= 3) && (board[x+1][y] == word[i])) {
			board[x][y] = '1';
			check_return = check(x+1, y, board, word, i+1);
			c += check_return;
			if (check_return == 0) {
				board[x][y] = board_original;
			}
		}
		if (((x+1) <= 3) && ((y+1) <= 3) && (board[x+1][y+1] == word[i])) {
			board[x][y] = '1';
			check_return = check(x+1, y+1, board, word, i+1);
			c += check_return;
			if (check_return == 0) {
				board[x][y] = board_original;
			}
		}
		if (((y+1) <= 3) && (board[x][y+1] == word[i])) {
			board[x][y] = '1';
			check_return = check(x, y+1, board, word, i+1);
			c += check_return;
			if (check_return == 0) {
				board[x][y] = board_original;
			}
		}
		if (((x-1) >= 0) && ((y+1) <= 3) && (board[x-1][y+1] == word[i])) {
			board[x][y] = '1';
			check_return = check(x-1, y+1, board, word, i+1);
			c += check_return;
			if (check_return == 0) {
				board[x][y] = board_original;
			}
		}
		if (c > 0) {
			return 1;
		} else {
			return 0;
		}
	}
}

int score_word(char *word) {
	int score = 0;

	if ((strlen(word) == 3) || (strlen(word) == 4)) {
		score += 1;
	} else if (strlen(word) == 5) {
		score += 2;
	} else if (strlen(word) == 6) {
		score += 3;
	} else if (strlen(word) == 7) {
		score += 5;
	} else if (strlen(word) >= 8) {
		score += 11;			
	}
	
	return score;
}
