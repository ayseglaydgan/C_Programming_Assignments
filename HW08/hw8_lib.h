/*
** hw8_lib.h:
**
** The header file declaring library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/
#define WORDSIZE 30
#define WORD_COUNT 10

typedef enum{
    cell_wall,
    cell_p1,
    cell_p2,
    cell_free,
    cell_target
}cell_type;

typedef enum { 
    move_left,
    move_right,
    move_up,
    move_down
}move_type;

int myStrlen(const char *word_one);

int myStrcmp(const char *word_one, const char *word_two);

int compare_list(char *word[WORDSIZE], char *str);

void delete_words (FILE* infid, FILE* outfid, char *word_to_delete[WORDSIZE], int number_of_words);

void clean_file(char* infile, char * outfile, char* words_to_delete[1], int number_of_words);


int maze_move(cell_type maze[][8], cell_type player, move_type move);


void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n);
