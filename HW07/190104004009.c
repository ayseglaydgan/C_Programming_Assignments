/*Student: Aysegul Aydogan*/
/*Student No: 190104004009 */
/*Last Revise: 01.05.2021 23.18*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_WORD 1000
#define WORD_LEN 50


int read_dict(char dict_file[MAX_WORD], char arr[MAX_WORD][WORD_LEN]);
void read_text(char text_file[MAX_WORD], char dict[MAX_WORD][WORD_LEN], int dict_count, int bonus_flag);
void find_best_correction(char dict[MAX_WORD][WORD_LEN], int dict_count, char word[WORD_LEN], int bonus_flag);
void fix_spelling_error(char dict_file[MAX_WORD], char text_file[MAX_WORD], int bonus_flag);
void fix_spelling_error2(char dict_file[MAX_WORD], char text_file[MAX_WORD], int bonus_flag);


int main()
{
    /*calling without bonus part*/
    printf("Welcome to WORLD BEST SPELLING CHECKER\n\n");

    printf("\n*****************************************\n");
    printf("fix_spelling_error(...) running\n");
    printf("*****************************************\n");
    fix_spelling_error("dictionary.txt","text.txt", 0);

    /*calling with bonus part*/
    printf("\n*****************************************\n");
    printf("fix_spelling_error2(...) running\n");
    printf("*****************************************\n");
    fix_spelling_error2("dictionary.txt","text.txt", 1);
}

void fix_spelling_error(char dict_file[MAX_WORD], char text_file[MAX_WORD], int bonus_part)
{
    char dict[MAX_WORD][WORD_LEN];
    int dict_count = read_dict(dict_file, dict);
    read_text(text_file, dict, dict_count, bonus_part);
}

void fix_spelling_error2(char dict_file[MAX_WORD], char text_file[MAX_WORD], int bonus_part)
{
    char dict[MAX_WORD][WORD_LEN];
    int dict_count = read_dict(dict_file, dict);
    read_text(text_file, dict, dict_count, bonus_part);
}

int read_dict(char dict_file[MAX_WORD] ,char arr[MAX_WORD][WORD_LEN])
{
    /*opens the dict file*/
    FILE *fp = fopen(dict_file,"r");
    int word_count = 0, letter_count = 0;
    char ch;
    /*read the dict file to the EOF*/
    while((ch = fgetc(fp)) != EOF)
    {
        /*take only the letters and & assign to a "word"*/
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '&'))
        {
            arr[word_count][letter_count] = ch;
            letter_count++;
        }
        /* if there is any \n stop assigning to word and call new word*/
        if(ch == '\n')
        {
            /*add '\0' to the end of word*/
            arr[word_count][letter_count] = '\0';
            letter_count = 0;
            /*increase the number of word*/
            word_count++;
        }
    }
    return word_count;
}

void read_text(char text_file[MAX_WORD], char dict[MAX_WORD][WORD_LEN], int dict_count, int bonus_part)
{
    /*opens the text file*/
    FILE *fp = fopen(text_file,"r");
    int letter_count = 0;
    /*declare an array to assign the words in text*/
    char str[WORD_LEN];
    char ch;
    while((ch = fgetc(fp)) != EOF)
    {
        /*take the words with punct*/
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '.') || (ch == ',') || (ch == '&') || (ch == '?') || (ch == '\''))
        {
            /*assign the letters and punc to the array one by one*/
            str[letter_count] = ch;
            letter_count++;
        }
        /* "/" exception is for manager/producer*/ 
        else if (ch == ' ' || ch == '\n' || ch == '/')
        {
            /*add '\0' at the end of word*/
            /*reset the array for the next word*/
            str[letter_count] ='\0';
            /*call the find_best_correction function*/
            find_best_correction(dict, dict_count, str, bonus_part);
            printf("%c",ch);
            letter_count = 0;
        }
        else
        {
            printf("%c",ch);
        }
    }
    /*do it the reset again for the last word of the text*/
    str[letter_count] ='\0';
    find_best_correction(dict, dict_count, str, bonus_part);
    printf("\n");
}

void find_best_correction(char dict[MAX_WORD][WORD_LEN], int dict_count, char word[WORD_LEN], int bonus_part)
{
    /*first comparion of text and dict is about length*/
    int len_dict;
    int len_word = strlen(word);
    /*variable to hold differences between words*/               
    int difference = 999;
    /*to compare the number of difference between previous one to find which has min difference*/
    int temp_difference = -1;
    /*assign to 1 to check if the word is not in dict*/
    int index = -1;
    /*word in text is with . , ? to find exact char size*/
    if((word[len_word-1] == '.') || (word[len_word-1] == ',') || (word[len_word-1] == '?' || word[len_word-1] == '\''))
        len_word -= 1;

    /* if the char before the end of word is ' */ 
    if (word[len_word-2] == '\'')
    {
        /*assume that there is no '*/
        word[len_word-2] = word[len_word-1];
        /*takes the word with punct so when it deleted decrease the num of char in word*/
        len_word--;
    }
    /*to search the word in dict (each line)*/    
    for(int i = 0; i < dict_count; i++)
    {
        /*assign -1 for the probability of finding the same word*/
        temp_difference = -1;
        len_dict = strlen(dict[i]);
        /*if the text and dict have the same char num, look the other conditions*/    
        if(len_dict == len_word)
        {
            /*assume that the word in text is the same with dictionary*/
            temp_difference = 0;  
            for(int j = 0; j < len_word; j++)
            {
                /*if there is any difference increase the difference - no matter lowercase or uppercase*/
                if (dict[i][j] != word[j] && (dict[i][j] + 'a' - 'A') != word[j])
                {
                    temp_difference++;
                }
            }
        }
        /* if bonnus part is active */
        if (bonus_part == 1)
        {
            if (temp_difference == 1 || temp_difference == 2)
                index = i;
        }

        /*condition to determine the word which has min difference (optimal word)*/
        if(temp_difference != -1 && temp_difference < difference)
        {
            difference = temp_difference;
            /*to access to the correct word*/
            index = i;
        }

        /*if there is more than one word for best option*/
        if(temp_difference == difference)
        {
            for(int j = 0; j < len_word; j++)
            {
                if(dict[i][j] != dict[index][j])
                {
                    /*choose the word which has vowel letter*/
                    if(dict[i][j] == 'a' || dict[i][j] == 'e' || dict[i][j] == 'i' || dict[i][j] == 'o' || dict[i][j] == 'u')
                    {
                        /*to access to the correct word*/
                        index = i;
                    }
                }
            }
        }
    }
    /*if the word in the text is also in the dict with correct form*/
    if (index != -1)
        printf("%s",dict[index]);
    /*if there is no correct form print the same*/   
    else
        printf("%s",word);
    /*if there is a . , ? at the end of word, dont touch it*/
    if((word[len_word] == '.') || (word[len_word] == ',') || (word[len_word] == '?') || word[len_word] == '\'')
        printf("%c",word[len_word]);
}
