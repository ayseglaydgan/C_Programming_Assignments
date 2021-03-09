/*
** hw1_io.c:
**
** The source file implementing output functions.
**
** Author: Yakup Genc. (c) 2018-2021
** Programmer: Aysegul Aydogan. 190104004009
** Revision: 2021.09.03.16.59
** 
*/


#include <stdio.h>
#include <math.h>
#include "hw1_io.h"


void write_polynomial3(double a0, double a1, double a2, double a3)
{
    double coefficient[4] = {a3, a2, a1, a0};
    for(int i = 3; i >= 0; i--)
    {
        /*To print the last term without x and power*/
        if(i == 0)
        {
            if(coefficient[i] < 0)
                printf("%.1lf",coefficient[i]);
            else if(coefficient[i] > 0)
                printf("+%.1lf",coefficient[i]);
        }
        /*To not print if the coefficient is zero*/
        if(coefficient[i] > 0)
        {
            /*To not print the "1" coefficient*/ 
            if(coefficient[i] == 1)
            {
                /*To not print sign for the first term*/
                if(i == 3)
                    printf("x^%d", i);
                /* To print sign */
                else if(i < 3 && i > 1)
                    printf("+x^%d", i);
                /* To not print power */
                else if(i == 1)
                    printf("+x");
            }
            /*To print the term if the coefficient is not 1*/
            else
            {
                if(i == 3 )
                    printf("%.1lfx^%d", coefficient[i], i);
                else if(i < 3 && i > 1)
                    printf("+%.1lfx^%d", coefficient[i], i);
                else if(i == 1)
                    printf("+%.1lfx", coefficient[i]);
            }
        }
        else if(coefficient[i] < 0)
        {
            if(coefficient[i] == -1)
            {
                if(i > 1)
                    printf("-x^%d", i);
                else if(i == 1)
                    printf("-x");
            }
            else
            {
                if(i > 1)
                    printf("%.1lfx^%d", coefficient[i], i);
                else if(i == 1)
                    printf("%.1lfx", coefficient[i]);
            }
        }
    }
    printf("\n");
}
    
    


void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{
    double coefficient[5] = {a4, a3, a2, a1, a0};
    for(int i = 4; i >= 0; i--)
    {
        /*To print the last term without x and power*/
        if(i == 0)
        {
            if(coefficient[i] < 0)
                printf("%.1lf",coefficient[i]);
            else if(coefficient[i] > 0)
                printf("+%.1lf",coefficient[i]);
        }
        /*To not print if the coefficient is zero*/
        if(coefficient[i] > 0)
        {
            /*To not print the "1" coefficient*/
            if(coefficient[i] == 1)
            {
                /* To not print sign for the first term*/
                if(i == 4)
                    printf("x^%d", i);
                /* To print sign*/
                else if(i < 4 && i > 1)
                    printf("+x^%d", i);
                /* To not print power*/
                else if(i == 1)
                    printf("+x");
            }
            /*To print the term if the coefficient is not 1*/
            else
            {
                if(i == 4 )
                    printf("%.1lfx^%d", coefficient[i], i);
                else if(i < 4 && i > 1)
                    printf("+%.1lfx^%d", coefficient[i], i);
                else if(i == 1)
                    printf("+%.1lfx", coefficient[i]);
            }
        }
        else if(coefficient[i] < 0)
        {
            if(coefficient[i] == -1)
            {
                if(i > 1)
                    printf("-x^%d", i);
                else if(i == 1)
                    printf("-x");
            }
            else
            {
                if(i > 1)
                    printf("%.1lfx^%d", coefficient[i], i);
                else if(i == 1)
                    printf("%.1lfx", coefficient[i]);
            }
        }
    }
    printf("\n");
}
