#ifndef BOGGLE_FUNCTIONS_H
#define BOGGLE_FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dictionary.h"

#define MAX_LINE 100
#define LINE_LENGTH 80
#define MAX_NUM_WORDS 50
#define BOARD_SIZE 4

typedef struct Dice {
    char dice[16][7];
} Dice;

typedef struct UserNode {
	char username[LINE_LENGTH];
	int max_score;
	int total_games;
	int total_score;
    struct UserNode *next;
} UserNode;

int toupper(int c);
char *strtok(char * str, const char * delimiters);

//board_generator.c
void generate_board_from_file(char **board, char *test_filename,
								char *words[MAX_NUM_WORDS], int *ptr_wll);
void generate_randomized_board(char **board);

//board.c
void display_board(char **board);
void clear_board();

//user_input.c
void get_word(char **board, DNode *dictionary[BIG_HASH_SIZE], 
				DNode *submitted_words[SMALL_HASH_SIZE], int *score,
				UserNode **head);

//word_checker.c
int word_checker(char **board, DNode *dictionary[BIG_HASH_SIZE], 
				DNode *submitted_words[SMALL_HASH_SIZE], char *word);
int find_word_on_board(char **board, char *word);
int check(int x, int y, char **board, char *word, int i);
int score_word(char *word);

//score_board.c
void insert_user(UserNode **head, char username[LINE_LENGTH], int max_score, int total_games, int total_score);
char display_score_board(UserNode *head);

#endif
