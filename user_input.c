#include "boggle_functions.h"

//gets user input, one word at a time and checks validity
//scores word if it is valid
void get_word(char **board, DNode *dictionary[BIG_HASH_SIZE], 
				DNode *submitted_words[SMALL_HASH_SIZE], int *score,
				UserNode **head) {
	char word[17];
	int i;
	char username[LINE_LENGTH];
	
	printf("Please enter a word: ");
	scanf("%s", word);
	for (i=0; i < strlen(word); i++) {
		word[i] = (char) toupper(word[i]);	
	}
	while ((strlen(word) > 1) || ((strlen(word) == 1) 
			&& (word[0] != 'Q') && (word[0] != 'N'))) {
		if (strlen(word) < 3) {
			printf("Your word was not submitted because it is less \
than 3 characters long. Please try again.\n");
		} else {
			int result = word_checker(board, dictionary, submitted_words, word);
			if (result == 1) {
				*score += score_word(word);
				printf("Your score is now %d\n", *score);
			}
		}
		printf("\n");
		display_board(board);
		printf("Please enter a word: ");
		scanf("%s", word);
		for (i=0; i < strlen(word); i++) {
			word[i] = (char) toupper(word[i]);	
		}

		clear_board();
		display_board(board);
	}

	//must be N or Q to exit while

	printf("Your current score is %d\n", *score);
	printf("Please enter your user name: ");
	scanf("%s", username);
	for (i=0; i < strlen(username); i++) {
		username[i] = (char) toupper(username[i]);	
	}

	printf("\n");

	UserNode *curr;
	curr = (UserNode *) malloc(sizeof(UserNode));
	curr = *head;

	while ((curr != NULL) && (strcmp((curr)->username, username) != 0)) {
		curr = curr->next;
	}

	if (curr == NULL) { //user doesn't exist yet
		insert_user(head, username, *score, 1, *score);
	} else if (strcmp(curr->username, username) == 0) { //update user info
		curr->total_games = curr->total_games + 1;
		curr->total_score = curr->total_score + *score;
		if (curr->max_score < *score) {
			curr->max_score = *score;
		}
	}
}
