#include <stdio.h>
#include <stdlib.h>

// enter your initial constant size value
#define N 4

enum 
{
    right = 6,
    left = 4,
    up = 8,
    down = 5
};

// create empty array with random values
void create_array(int arr[N][N], int spaceI, int spaceJ);
// generate random values due to table missing value
int generate_random(int arr[N][N]);
// print table to screen nicely
void print_table(int arr[N][N]);
// play game
void play_game(int arr[N][N], int direction, int x, int y, int *spaceI, int *spaceJ);
// checks winner
int check_winner(int arr[N][N]);

/**
 * Fill the given array
 * Use generate_random function to
 * creating unique values
 * @param arr That going to used array
 * @param spaceI Space value I index
 * @param spaceJ Space value J index
 */
void create_array(int arr[N][N], int spaceI, int spaceJ)
{

    for(int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
                // if equal to space  coordinates
            if(i == spaceI && j == spaceJ)
            {
                arr[i][j] = -1;
            }
            else
            {
                arr[i][j] = generate_random(arr);
            }
        }
    }
}

/**
 * generate random number
 * due to array's values
 * @param arr That gonna checked array
 * @return which int value is clear
 */
int generate_random(int arr[N][N])
{
    int digit = (rand() % (N*N-1)) + 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (arr[i][j] == digit)
            {
                digit = (rand() % (N*N-1)) + 1;
                i = -1; 
                j = 0;
                break;
            }
        }
    }               
    return digit;
    
}

/**
 * Print all table values
 * with some beauty 
 * Thanks to the stars (*)
 * @param arr That going to printed
 */
void print_table(int arr[N][N])
{
    
    for (int i = 0; i < 16*N; i++) printf("*");
    for (int i = 0; i < N; i++)
    {
        printf("\n*\t");
        for(int j = 0; j < N; j++)
        {
            if (arr[i][j] != -1)
                printf("%d\t*\t", arr[i][j]);
            else
                printf("\t*\t");
        }
        printf("\n"); 
        for (int i = 0; i < 16*N; i++) printf("*");
    }
    printf("\n");
}

/**
 * use switch case
 * to chose which direction is going to moved
 * and move if valid
 * @param arr That going to use
 * @param direction Which direction [left, right, up, down]
 * @param x Player x coordinate
 * @param y Player y coordinate
 * @param spaceI Space's I coordinate (x)
 * @param spaceJ  Space's J coordinate (y)
 */
void play_game(int arr[N][N],int direction, int x, int y, int *spaceI, int *spaceJ)
{
    int tempI = *spaceI, tempJ = *spaceJ;
    int repeat = 0;
    int repeat_checker = 1;
    while(repeat < repeat_checker)
    {
        switch (direction)
        {
        case up:
            repeat_checker = x - tempI;
            if (repeat_checker < 0)
            {
                printf("Invalid coordinates. Please try again.\n");
                break;
            }
            if (*spaceI + 1 < N)
            {
                int temp = arr[*spaceI][*spaceJ];
                arr[*spaceI][*spaceJ] = arr[*spaceI+1][*spaceJ];
                arr[*spaceI+1][*spaceJ] = temp;
                *spaceI = *spaceI + 1;
            }
            else
                printf("Invalid array size. Can not pass corners\n");
            break;
        case down:
            repeat_checker = tempI - x;
            if (repeat_checker < 0)
            {
                printf("Invalid coordinates. Please try again.\n");
                break;
            }
            if (*spaceI - 1 >= 0)
            {
                int temp = arr[*spaceI][*spaceJ];
                arr[*spaceI][*spaceJ] = arr[*spaceI-1][*spaceJ];
                arr[*spaceI-1][*spaceJ] = temp;
                *spaceI = *spaceI - 1;
            }
            else
                printf("Invalid array size. Can not pass corners\n");
            break;
        case right:
            repeat_checker = tempJ - y;
            if (repeat_checker < 0)
            {
                printf("Invalid coordinates. Please try again.\n");
                break;
            }
            if (*spaceJ - 1 >= 0)
            {
                int temp = arr[*spaceI][*spaceJ];
                arr[*spaceI][*spaceJ] = arr[*spaceI][*spaceJ-1];
                arr[*spaceI][*spaceJ-1] = temp;
                *spaceJ = *spaceJ - 1;
            }
            else
                printf("Invalid array size. Can not pass corners\n");
            break;
        case left:
            repeat_checker = y - tempJ;
            if (repeat_checker < 0)
            {
                printf("Invalid coordinates. Please try again.\n");
                break;
            }
            if (*spaceJ + 1 < N)
            {
                int temp = arr[*spaceI][*spaceJ];
                arr[*spaceI][*spaceJ] = arr[*spaceI][*spaceJ+1];
                arr[*spaceI][*spaceJ+1] = temp;
                *spaceJ = *spaceJ + 1;
            }
            else
                printf("Invalid array size. Can not pass corners\n");
            break;
        default:
            printf("Wrong direction. Please enter valid direction\n");
            break;
        }
        repeat++;
     
    }
}

/**
 * Check array 
 * Look all values
 * If all they continuing after and after
 * Return 1, otherwise 0
 * @param arr Take an array
 * @return 1 if win, 0 if not win
 */
int check_winner(int arr[N][N])
{
    int counter = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (arr[i][j] == counter)
                counter++;
            else if (arr[i][j] == -1)
                continue;
            else
                return 0;
        }  
    }
    return 1;
}


int main()
{
    // for creating different values each time.
    // without using (time(NULL)) parameter.
    // I sended a dummy adress value (which changes all running times)
    
    // since, srand is invalid function for this homework, I leave it with command.

    //int dummy = 0;
    //srand(&dummy);

    int showCheckFunction[4][4] =   {{1,2,3,4},
                                    {5,6,7,8},
                                    {9,10,11,12},
                                    {13,14,-1,15}};
    int showInvalidCheckFunction[4][4] =    {{1,2,3,4},
                                              {5,6,7,8},
                                              {9,10,-1,12},
                                             {13,14,15,11}};
    printf("*****WELCOME TO THE PERFECT PUZZLE GAME*****\nFirstly, I am gonna how is show check_winner function working\n");
    print_table(showCheckFunction);
    printf("This is check_winner return value (for valid) = %d\n",check_winner(showCheckFunction));
    printf("Now here comes an invalid example\n");
    print_table(showInvalidCheckFunction);
    printf("This is check_winner return value (for invalid) = %d\n",check_winner(showInvalidCheckFunction));
    printf("Test is over\n");

    printf("\n\n\nNow, IT IS SHOW TIME\n\n");


    int arr[N][N] = {0};
    int direction;
    int x,y;
    int spaceI = (rand() % N);
    int spaceJ = (rand() % N);
    create_array(arr, spaceI, spaceJ);
    print_table(arr);
    while(1)
    {
        printf("Enter direction > || Right = 6 || Left = 4 || Up = 8 || Down = 5 ||\n");
        scanf(" %d",&direction);
        printf("Enter [x y] > [Like array style, 0 index based]\n");
        scanf(" %d %d",&x,&y);
        if (spaceI - x == 0 || spaceJ - y == 0)
            play_game(arr,direction,x,y, &spaceI, &spaceJ);
        else
            printf("Wrong coordinates. Please try again.\n");
        print_table(arr); 
        if (check_winner(arr) == 1)
        {
            printf("You win!!!\n");
            break;
        }
    }
    printf("Goodbye my frined...\n");
    
}