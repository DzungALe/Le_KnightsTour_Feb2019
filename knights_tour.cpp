/*=====================================================================================================================================
columnName: Le_CoveringKnights_Dec28 2018.c
columnType: C Source column
Author: Dung Le
Created On: 12/28/2018 9:12:00 PM
Last Modified On: 12/28/2018 10:32:00 PM
Description:
Editor: Notepad++ Ver. 7.6.2
Complier: Raspbian 6.3.0
Kernel: Linux raspberrypi 4.9.59-v7+
=====================================================================================================================================*/

#include "pch.h"
#include <stdio.h>
#include <string.h> //mem.cpy()
#include <ctype.h> //tolower() 
#include <iostream>
#include "chessboard_draw.h"

#define CHESSBOARDMAX 8

typedef short int16_t;
typedef int16_t chessboard_t[CHESSBOARDMAX][CHESSBOARDMAX]; //chess board is an empty 8x8 array
typedef int int32_t;
typedef struct {
	int16_t x;
	int16_t y;
} knight_pos_t;

knight_pos_t knight_positions[CHESSBOARDMAX * CHESSBOARDMAX]; //Array containing 64 x and y values of knights, showing sequence of moves
char steps[CHESSBOARDMAX * CHESSBOARDMAX];
unsigned long long step_counter = 0;

static char x_end, y_end;

void get_number_notate(char *column, char *row);
void find_order(knight_pos_t *knight_positions);

/*
	Gathers two user-input squares for beginning and ending chess squares
*/
void gather_inputs(char *begin, char *end)  
{
inputs: 
	printf("Enter your starting square of your knight: ");
	scanf(" %s", begin);
	printf("Enter your ending square of your knight: ");
	scanf(" %s", end);

	begin[0] = tolower(begin[0]);
	end[0] = tolower(end[0]);

	if ((begin[0] < 'a') || (begin[0] > 'h') || (end[0] < 'a') || (end[0] > 'h')
		|| (begin[1] < '0') || (begin[1] > '8') || (end[1] < '0') || (end[1] > '8')) {
		printf("Invalid inputs, please try again\n\n");
		goto inputs;
	}

	get_number_notate(&begin[0], &begin[1]);
	get_number_notate(&end[0], &end[1]);
}

/*
	Converts letter notation into usable numbers
*/
void get_number_notate(char *column, char *row)
{
	*column = *column - 'a';
	*row = '8' - *row;
}

/*
	Calculates where the knight will go
*/
const int16_t delta_x[8] = {  1,  2, 2, 1, -1, -2, -2, -1 };
const int16_t delta_y[8] = { -2, -1, 1, 2,  2,  1, -1, -2 };

void calc_knights(int16_t knight_index, chessboard_t board, int16_t pos_knight_x, int16_t pos_knight_y)
{
	int16_t i;
	int16_t pos_knight_x_tmp, pos_knight_y_tmp;
	int16_t choice;

	step_counter++;
	if (step_counter % 1000000000 == 0)
		printf("Step counter = %llu\n", step_counter);

	for (i = 0; i < 8; i++) {
		//memcpy((void *)local_board, board, sizeof(chessboard_t));
		pos_knight_x_tmp = pos_knight_x + delta_x[i];
		pos_knight_y_tmp = pos_knight_y + delta_y[i];

		if ((pos_knight_x_tmp >= 0) && (pos_knight_x_tmp < CHESSBOARDMAX) && (pos_knight_y_tmp >= 0) && (pos_knight_y_tmp < CHESSBOARDMAX)) {
			if (board[pos_knight_x_tmp][pos_knight_y_tmp] == 0) {
				knight_positions[knight_index].x = pos_knight_x_tmp;
				knight_positions[knight_index].y = pos_knight_y_tmp;

				if (knight_index < CHESSBOARDMAX * CHESSBOARDMAX - 1) {
					board[pos_knight_x_tmp][pos_knight_y_tmp] = 1;
					calc_knights(knight_index + 1, board, pos_knight_x_tmp, pos_knight_y_tmp);
					board[pos_knight_x_tmp][pos_knight_y_tmp] = 0;
				}
				else {
					if ((knight_positions[knight_index].x == x_end) && (knight_positions[knight_index].y == y_end)) {
						find_order(knight_positions);
						printf("Done! Knight_index = %d\n", knight_index + 1);
						printf("Step number = %d\n", step_counter);
						print_board(steps);  
						printf("Press any number to continue: ");
						scanf("%d", &choice);
					}
				}
			}
		}
	}
}

/*
	Finds the order to print out chess board
*/
void find_order(knight_pos_t *knight_positions)
{
	char row, column, i = 0, knight_index;

	for (row = 0; row < CHESSBOARDMAX; row++) {
		for (column = 0; column < CHESSBOARDMAX; column++) {
			for(knight_index = 0; knight_index < CHESSBOARDMAX * CHESSBOARDMAX; knight_index++){
				if ((knight_positions[knight_index].x == column) && (knight_positions[knight_index].y == row)) {
					steps[i] = knight_index + 1;
					i++;
					break;
				}
			}
		}
	}
}

int main(void)
{
	int16_t x, y;
	char begin[2], end[2], x_begin, y_begin;	//Beginning and ending point of knights
	chessboard_t board;

	//Initiates 8x8 chess board with all values to 0
	for (x = 0; x < CHESSBOARDMAX; x++) {
		for (y = 0; y < CHESSBOARDMAX; y++) {
			board[x][y] = 0;
		}
	}
	
	gather_inputs((char *)&begin, (char *)&end);
	x_begin = begin[0];   
	y_begin = begin[1];
	x_end = end[0];
	y_end = end[1];

	calc_knights(1, board, x_begin, y_begin);

	return 0;
}
