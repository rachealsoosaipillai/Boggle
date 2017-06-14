#include "boggle_functions.h"

//simulates game based on provided test file
//invalid words and final score written to a txt file
void generate_board_from_file(char **board, char *test_filename,
								char *words[MAX_NUM_WORDS], int *ptr_wll) {
	FILE *test_file = fopen(test_filename, "r");
	char board_str[16];
	char words_line[LINE_LENGTH + 1];
	
	//gets first line of test file (board)
	if (fgets(board_str, LINE_LENGTH + 1, test_file) != NULL) {
		int letter = 0;
	
		//copies letters from line 1 of test file into the board
		for (int row=0; row < BOARD_SIZE; row++) {
			for (int col=0; col < BOARD_SIZE; col++) {
			strcpy(&(board[row][col]), &(board_str[letter]));
			letter++;
			}
		}
	} else {
        fprintf(stderr,"Could not open file \"%s\" for reading game board \
and test input words\n", test_filename);
	}

	//gets second line of test file (words)
	if (fgets(words_line, LINE_LENGTH + 1, test_file) != NULL) {
		char *token = strtok(words_line, ",");
		int i;

		for (i=0; i < MAX_NUM_WORDS; i++) {
			words[i] = malloc(sizeof(char) * 17);
		}

		i = 0;

		while(token != NULL) {
			strcpy(words[i], token);
			token = strtok(NULL, ",");
			i++;
			(*ptr_wll)++;
		}
		words[i-1][strcspn(words[i-1], "\n")] = '\0';
	} else {
        fprintf(stderr,"Could not open file \"%s\" for reading game board \
and test input words\n", test_filename);
	}

	fclose(test_file);
}

//creates a randomized board
void generate_randomized_board(char **board) {
	srand((unsigned) time(NULL));

	//dice configuration
    Dice dice;
	strcpy(dice.dice[0], "RIFOBX");
	strcpy(dice.dice[1], "IFEHEY");
	strcpy(dice.dice[2], "DENOWS");
	strcpy(dice.dice[3], "UTOKND");
	strcpy(dice.dice[4], "HMSRAO");
	strcpy(dice.dice[5], "LUPETS");
	strcpy(dice.dice[6], "ACITOA");
	strcpy(dice.dice[7], "YLGKUE");
	strcpy(dice.dice[8], "QBMJOA");
	strcpy(dice.dice[9], "EHISPN");
	strcpy(dice.dice[10], "VETIGN");
	strcpy(dice.dice[11], "BALIYT");
	strcpy(dice.dice[12], "EZAVND");
	strcpy(dice.dice[13], "RALESC");
	strcpy(dice.dice[14], "UWILRG");
	strcpy(dice.dice[15], "PACEMD");
	
	int num_dice = 16;
	int random_dice_pos[num_dice]; //array of random dice positions

	for (int i=0; i < num_dice; i++) { 
		random_dice_pos[i] = i; //fills array with numbers 0-15
	}

	//shuffles array to become randomized dice positions
	for (int i=0; i < num_dice; i++) {
		int temp = random_dice_pos[i];
		int random_index = rand() % 16;
        random_dice_pos[i] = random_dice_pos[random_index];
		random_dice_pos[random_index] = temp;
	}	
	
	int current_die = 0; //from dice 0-16
    int random_letter;
	int die_choice; //a randomly chosen die

	for (int row=0; row < BOARD_SIZE; row++) {
		for (int col=0; col < BOARD_SIZE; col++) {
		random_letter = rand() % 6; //6 letters to choose from per die
		die_choice = random_dice_pos[current_die];
		board[row][col] = dice.dice[die_choice][random_letter];
		current_die++; //go to next die
		}
	}
}
