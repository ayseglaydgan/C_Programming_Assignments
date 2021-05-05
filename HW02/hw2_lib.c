/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/

#include <stdio.h>
#include "hw2_lib.h"
#include<math.h>

/*Helper functions that i wrote own my own*/
int IsLeap(int year);
int count_to_year_zero(int day, int month, int year);
void print_border(char border);
int my_absolute(int num);

int find_weekday_of_data(int day, int month, int year)
{
    return count_to_year_zero(day,month,year) % 7;
}

int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
    return count_to_year_zero(end_day,end_month,end_year) - count_to_year_zero(start_day,start_month,start_year);
}

int count_to_year_zero(int day, int month, int year)
{
    int num_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int count_day = 0;
    int day_per_year = 0;
    int max_avaible = num_days[month - 1];
    int i;
    if((day > max_avaible) || (day <= 0) || (month <= 0) || (month > 12) || (year <= 0))
    {
        return -1;
    }

    if (IsLeap(year))
        num_days[1] = 29;

    for (i = 1; i < year; i++)
    {
        if (IsLeap(i))
            day_per_year = 366;
        else
            day_per_year = 365;
        count_day += day_per_year;
    }

    for (i = 0; i < month - 1; i++)
        count_day += num_days[i];

    count_day += day;
    return count_day;
}

double find_angle(double a, double b, double c)
{
    double Vb = sqrt(((pow(a,2) + pow(c,2)) / 2) - (pow(b,2) / 4));
    double Vc = sqrt(((pow(a,2) + pow(b,2)) / 2) - (pow(c,2) / 4));
    double s1 = Vb*(2.0 / 3.0);
    double s2 = Vc*(2.0 / 3.0);
    double cos_teta = (pow(a,2) - pow(s1,2) - pow(s2,2)) / (-2*s1*s2);
    double teta = acos(cos_teta);
    return teta;
}

void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border)
{
    char sign1 = (r13 > 0) ? '+' : '-';
    char sign2 = (r23 > 0) ? '+' : '-';
    char sign3 = (r33 > 0) ? '+' : '-';
    printf("┌"); 
    print_border(border);
    printf("┐\n");
    printf("|\t\tRow 101\t\t|\t\tRow ABCDEFG\t\t|\t\tRow XYZ123\t\t|\n");
    print_border(border);
    printf("%c%c\n",border,border);
    printf("|\t\t%u\t\t|%.4g\t\t\t\t\t|%c%d%*c\t\t\t\t|\n", r11, r12, sign1, my_absolute(r13), 5, ' ');
    print_border(border);
    printf("%c%c\n",border,border);
    printf("|\t\t%u\t\t|%.4g\t\t\t\t\t|%c%d%*c\t\t\t\t|\n", r21, r22,sign2, my_absolute(r23),5 , ' ');
    print_border(border);
    printf("%c%c\n",border,border);
    printf("|\t\t%u\t\t|%.4g\t\t\t\t\t|%c%d%*c\t\t\t\t|\n", r31, r32, sign3, my_absolute(r33),5, ' ');
    printf("└");
    print_border(border);
    printf("┘\n");
}

int IsLeap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int my_absolute(int num)
{
    if(num < 0)
        num = -1*num;
    return num;
}

void print_border(char border)
{
    int i;
    for(i = 0; i < 111; i++)
        printf("%c",border);
}

