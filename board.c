#include "boggle_functions.h"

//prints the board
void display_board(char **board) {
	for (int row=0; row < BOARD_SIZE; row++) {
        for (int col=0; col < BOARD_SIZE; col++) {
            printf("%c\t", board[row][col]);
        }
        printf("\n\n");
    }
}

//clears the board
void clear_board() {
	system("clear");
}
