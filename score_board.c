#include "boggle_functions.h"

void insert_user(UserNode **head, char username[LINE_LENGTH], int max_score, int total_games, int total_score) {
	UserNode *link = (UserNode *) malloc(sizeof(UserNode));
	
	strcpy(link->username, username);
	link->max_score = max_score;
	link->total_games = total_games;
	link->total_score = total_score;
	link->next = *head;
	*head = link;
}

char display_score_board(UserNode *head) {
	UserNode *curr = head;
	char user_choice;
	
	printf("USERNAME\tMAX SCORE\tTOTAL GAMES\tTOTAL SCORE\n");	
	
	while (curr->next != NULL) {
		printf("%s\t\t%d\t\t%d\t\t%d\n", curr->username, curr->max_score, curr->total_games, curr->total_score);
		curr = curr->next;
	}
	
	printf("\n");	
	
	printf("Please enter N to start a new game session or Q to quit the game: ");
	scanf(" %c", &user_choice);
	user_choice = (char) toupper(user_choice);
	
	return user_choice;
}
