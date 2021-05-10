/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/
#include <stdio.h>
#include<stdlib.h>
#include "hw8_lib.h"

#define WORDSIZE 30
#define WORD_COUNT 10

// recursive Strlen function
int myStrlen(const char *word_one)
{
	if(*word_one == '\0')
		return 0;
	else
	{
		return myStrlen(word_one + 1) + 1;
	}
}

//recursive strcmp function
int myStrcmp(const char *word_one, const char *word_two)
{
	if(myStrlen(word_one) == myStrlen(word_two))
	{
		if(*word_one < *word_two)
		{
			return -1;
		}
		if(*word_one > *word_two)
		{
			return 1;
		}
		if(*word_one == '\0')
		{
			return 0;
		}
	}
	else
	{
		return -2;
	}
		return myStrcmp(word_one + 1, word_two + 1);
}

//recursively compare the word in the text and word to delet list
int compare_list(char *word[WORDSIZE], char *str)
{
	if(*word == NULL)
	{
		return -1;
	}
	int cmp = myStrcmp(str,*word);
	if(cmp == 0)
	{
		return 0;
	}
	//compare word from text with whole delete list
	compare_list(word+1,str);
}

void delete_words (FILE* infid, FILE* outfid, char *word_to_delete[WORDSIZE], int number_of_words)
{
	//to hold the address of str before the address of word_to_delete
	//scan the text word by word
	char str[WORDSIZE];
	if(fscanf(infid,"%s",str) == EOF)
	{
		return;
	}
	else
	{
		int cmp_result = compare_list(word_to_delete,str);
		if(cmp_result == -1)
		{
			//the rest of text (without the word from list)
			fprintf(outfid,"%s ",str);
			number_of_words -= 1;
		}
		if(number_of_words == 0)
		{
			fprintf(outfid,"\n");
			number_of_words = WORD_COUNT;
		}
		//recursively call the function
		delete_words(infid, outfid, word_to_delete, number_of_words);
	}
}

//to wide the delete_words to whole file
void clean_file(char* infile, char* outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
	char word[WORDSIZE];
	FILE* infid = fopen(infile,"r");
	FILE* outfid = fopen(outfile,"w");
	if(infid == NULL || outfid == NULL)
	{
		printf("Opening Error\n");
		exit(1);
	}
	else
	{
		delete_words(infid,outfid,words_to_delete,number_of_words);
	}
	fclose(infid);
	fclose(outfid);
}



// recursive array search function
int maze_runner(cell_type maze[][8] , cell_type player, int row, int column)
{
	// when column equal to 8, finish recursive
	if (column == 8)
		return -1;
	if (maze[column][row] == player)
	{
		// if found value, convert for uisng in 2d array
		return (column * 8) + row;
	}
	else
	{
		if (row != 7)
			maze_runner(maze, player, row+1, column);
		else if (row == 7) 
		{
			row = 0;
			maze_runner(maze, player, row, column + 1);
		}
	}
}

// works like, maze_runner function. but prints maze.
int print_maze(cell_type maze[][8], int row, int column)
{
	if (column == 8)
		return -1;

	printf("%d |", maze[column][row]);


	if (row != 7)
		print_maze(maze, row+1, column);
	else if (row == 7) 
	{
		printf("\n");
		row = 0;
		print_maze(maze, row, column + 1);
	}

}

// checks next position. If valid or game finished.
int move_helper(cell_type maze[][8], int x, int y, int move_x, int move_y, cell_type player)
{

	// if not valid move. Inform user.
	if (y + move_y < 0 || y + move_y > 7 || x + move_x < 0 || x + move_x > 7)
	{
		printf("Out of borders. Invalid. Move Again\n");
		return -1;
	}
	// if won the game return 0
	if (maze[y + move_y][x + move_x] == cell_target)
	{
		printf("You won player%d\n", player);
		return 0;
	}
	// if cell is free. change values
	if (maze[y + move_y][x + move_x] == cell_free)
	{
		// printf("Moved from %d [%d][%d] to %d  [%d][%d]\n",maze[y][x], y, x , maze[y + move_y][x + move_x], y + move_y,x + move_x);
		printf("You moved. But not the target.\n");
		maze[y + move_y][x + move_x] = player;
		cell_type temp = cell_free;
		maze[x][y] = temp;
		return 1;
	}
	// equal to wall
	if (maze[y + move_y][x + move_x] == cell_wall)
	{
		printf("Invalid move. You bumped to wall. Move again\n");
		return -1;
	}

}

int maze_move(cell_type maze[][8], cell_type player, move_type move)
{
	// determine next player.
	cell_type next_player;
	if (player == cell_p1) next_player = cell_p2;
	if (player == cell_p2) next_player = cell_p1;

	// determine next move
	move_type next_move;
	int temp;

	// get location given player
	int player_location = maze_runner(maze, player, 0, 0);
	// convert location to use in array
	int x = player_location % 8;
	int y = player_location / 8;

	printf("Total yerim = %d, array oalrak [%d][%d]\n", player_location, y, x);

	if (move == move_up)
	{
		int if_flag = move_helper(maze, x, y, 0, -1, player);
		if (if_flag == 0) return 0;
		if (if_flag == -1) next_player = player;
	}
	if (move == move_down)
	{
		int if_flag = move_helper(maze, x, y, 0, 1, player);
		if (if_flag == 0) return 0;
		if (if_flag == -1) next_player = player;
	}
	if (move == move_right)
	{
		int if_flag = move_helper(maze, x, y, 1, 0, player);
		if (if_flag == 0) return 0;
		if (if_flag == -1) next_player = player;
	}
	if (move == move_left)
	{
		int if_flag = move_helper(maze, x, y, -1, 0, player);
		if (if_flag == 0) return 0;
		if (if_flag == -1) next_player = player;
	}
	else
	{
		printf("Invalid move = %d\n", move);
	}
	// print maze recursively
	print_maze(maze, 0, 0);

	printf("Player%d's turn\n", next_player);
	printf("Enter your move\nleft = 0\tright = 1\nup = 2\tdown = 3\nInput:");
	scanf(" %d", &temp);
	next_move = temp;

	// call this function recursively. Till find a winner
	maze_move(maze, next_player, next_move);
	return 0;
}



// can not implemented hocam :)
void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n)
{
    printf("TO BE IMPLEMENTED\n");
}
