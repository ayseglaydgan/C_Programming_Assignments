/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/


#include <stdio.h>
#include <stdlib.h>
#include "hw8_lib.h"





void test_clean_file () 
{
	char *word[4] = {"provider", "use", "apps", "cloud"};
	clean_file("input.txt","output.txt",word,WORD_COUNT);
	return;
}


void test_maze_move ()
{
	cell_type maze[8][8] = {
		{cell_p1, cell_free, cell_free, cell_free, cell_free, cell_wall, cell_wall, cell_wall},
		{cell_free, cell_free, cell_wall, cell_wall, cell_free, cell_wall, cell_wall, cell_wall},
		{cell_wall, cell_free, cell_wall, cell_wall, cell_free, cell_free, cell_free, cell_free},
		{cell_wall, cell_free, cell_free, cell_target, cell_free, cell_free, cell_wall, cell_wall},
		{cell_wall, cell_wall, cell_free, cell_wall, cell_wall, cell_free, cell_free, cell_free},
		{cell_wall, cell_free, cell_free, cell_free, cell_wall, cell_wall, cell_wall, cell_free},
		{cell_free, cell_free, cell_wall, cell_free, cell_wall, cell_free, cell_free, cell_free},
		{cell_p2, cell_free, cell_wall, cell_free, cell_free, cell_free, cell_free, cell_wall}
	};
	printf("-----------Welcome perfect Maze game mate <3 -----------\n");
	printf("Player1 Starting location = 0,0\n");
	printf("Player2 Starting location = 0,7\n");
	printf("Your turn Player1\n");
	move_type move;
	int temp;
	printf("Enter your move\nleft = 0\tright = 1\nup = 2\tdown = 3\nInput:");
	scanf(" %d", &temp);
	move = temp;
	maze_move(maze, cell_p1, move);
}


void test_towers_of_hanoi ()
{
	printf("TO BE IMPLEMENTED\n");
}

int domates(cell_type player)
{
	printf("%d",player);
	return -1;
}

/*
** main function for testing the functions...
**
*/
int main(void) {
	test_clean_file ();
	test_maze_move ();
	// test_towers_of_hanoi ();
	return (0);
} /* end main */
