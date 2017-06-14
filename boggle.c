#include "boggle_functions.h"

int main (int argc, char **argv) {
	FILE *input_FP;
	char line[MAX_LINE];
	char *file_name = "EnglishWords.txt";
	int result;
	int score = 0;
	int *ptr_score = &score;
	static DNode *dictionary[BIG_HASH_SIZE];
	static DNode *submitted_words[SMALL_HASH_SIZE];
	UserNode *head = NULL;
	head = (UserNode *) malloc(sizeof(UserNode));
	char user_choice = 'N';

    char **board = malloc(sizeof(char *) * 4);

	if(!(input_FP = fopen(file_name, "r"))) {
        fprintf(stderr,"Could not open file \"%s\" for reading \
				dictionary words\n", file_name);
        return 1;
    }

	while(fgets(line, MAX_LINE, input_FP)!= NULL) {
		line[strcspn(line, "\r\n")] = '\0';  //trim new line characters
		for (int letter=0; letter < strlen(line); letter++) {
			line[letter] = (char) toupper(line[letter]);
		}
		insert(dictionary, BIG_HASH_SIZE, line);
	}

	fclose(input_FP);

    for (int i=0; i < BOARD_SIZE; i++) {
        board[i] = malloc(sizeof(char) * 4);
    }

    if (argc > 1) { //read input from the provided test file
		char *words[MAX_NUM_WORDS];
		int word_list_len = 0;
		int *ptr_wll = &word_list_len;
		int w;

		generate_board_from_file(board, argv[1], words, ptr_wll);
		
		FILE *output_fp;

	   	output_fp = fopen("output.txt", "w");

		for (w=0; w < word_list_len; w++) {
			result = word_checker(board, dictionary, submitted_words, 
									words[w]);
			if ((w < word_list_len - 1) && (result == 0)) {
				fprintf(output_fp, "%s,", words[w]);
			} else if ((w == word_list_len - 1) && (result == 0)) {
				fprintf(output_fp, "%s", words[w]);
			} else if (result == 1) {
				score += score_word(words[w]);
			}
		}
		
		fprintf(output_fp, "\n");
		fprintf(output_fp, "%d", score);

	   	fclose(output_fp);
		
		for (int i=0; i < MAX_NUM_WORDS; i++) {
			free(words[i]);
		}
    } else { //generate a new randomized board
		while (user_choice == 'N') {
			generate_randomized_board(board);
			display_board(board);
			//user input
			get_word(board, dictionary, submitted_words, ptr_score, &head);
			user_choice = display_score_board(head);
			free_dictionary(submitted_words, SMALL_HASH_SIZE);
			score = 0;
		}
		if (user_choice == 'Q') {
			printf("The game has ended.\n");
		}
	}

    for (int i=3; i >= 0; i--) {
        free(board[i]);
    }

    free(board);
	free_dictionary(dictionary, BIG_HASH_SIZE);
	
	UserNode *curr = head;
	
	while ((curr = head) != NULL) {
		head = head->next;
		free(curr);
	}

    return 0;
}
