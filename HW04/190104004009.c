/*Instructor: Yakup Genc
  Programmer: Aysegul Aydogan 190104004009
  Last Revised Date: 6.04.2021 14.02pm */

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

/*Declaration of functions*/
void print_pretty_poly();
void is_armstrong_palindrome();
void how_many_prime_num();

int main(void)
{
    print_pretty_poly();
    is_armstrong_palindrome();
    how_many_prime_num();
}
/*Definitions of functions*/
void print_pretty_poly()
{
    /*Take the degree of poly*/
    int degree;
    printf("Enter your polynomial:\n");
    scanf("%d",&degree);
    float coefficient;
    printf("p(x) = ");
    /*Take the coefficients as float*/
    for(int i = degree; i >= 0; i--)
    {
        scanf("%f",&coefficient);
        /*First printing condition, if coefficient = 0, dont print it*/
        if(coefficient != 0  &&  fabs(coefficient) >= 0.050999999)
        {
            /*Printing the coefficients if it doesnt round to -1*/
            if (coefficient < -1.05)
            {
                if (i == degree)
                    printf("%.1fx^%d",coefficient, i);  
                else if (i == 1)
                    printf("%.1fx",coefficient);
                else if (i == 0)
                    printf("%.1f",coefficient);
                else
                    printf("%.1fx^%d",coefficient, i);
                }
            /*Printing the coefficients if it rounds to -1*/
            else if(coefficient >= -1.05 && coefficient < -0.95)
            {
                if (i == degree)
                    printf("-x^%d", i);
                else if (i == 1)
                    printf("-x");
                else if (i == 0)
                    printf("-1");
                else
                    printf("-x^%d", i);
                }
            /*Printing the coefficients if it rounds to 1*/
            else if(coefficient > 0.95 && coefficient <= 1.05)
            {
                if (i == degree)
                    printf("x^%d", i);
                else if (i == 1)
                    printf("+x");
                else if (i == 0)
                    printf("+1");
                else
                    printf("+x^%d", i);
                }
            /*Printing the coefficients if it doesnt round to 1*/
            else
            {
                if (i == degree)
                    printf("%.1fx^%d",coefficient, i);
                else if (i == 1)
                    printf("+%.1fx",coefficient);
                else if (i == 0)
                    printf("+%.1f",coefficient);
                else
                    printf("+%.1fx^%d",coefficient, i);
            }
        }
    }
    printf("\n");
}

void is_armstrong_palindrome()
{
    double number;
    int temp1, temp2;
    int digit_num = 0;
    int sum1 = 0;
    int sum2 = 0;
    int digit;
    while(1)
    {
        printf("Please enter an integer number: ");
        scanf("%lf",&number);
        /*checks number is positive or integer*/
        if(number >= 0 && ((int)number == number))
        {
            number = (int)number;
            break;
        }
    }
    /*To compare the original number, create temp values*/
    temp1 = number;
    temp2 = number;
    /*To find the number of digit for armstrong number*/
    while(temp1 != 0)
    {
        temp1 /= 10;
        digit_num++;
    }
    /*To find if it is armstrong number or palindrome number*/
    while(temp2 != 0)
    {
        digit = temp2 % 10;
        /*sum1 is for amstrong number*/
        sum1 += pow(digit, digit_num);
        /*sum2 is for palindrome number*/
        sum2 = sum2*10 + digit;
        temp2 /= 10;
    }
    /*Comparison with original number*/
    if(sum1 == number && sum2 == number)
        printf("This number is both Palindrome and Armstrong number\n");
    else if(sum1 == number && sum2 != number)
        printf("This number is only Armstrong number\n");
    else if(sum1 != number && sum2 == number)
        printf("This number is only Palindrome number\n");
    else
        printf("This number does not satisfy any special cases\n");
}

void how_many_prime_num()
{
    double first;
    double second;
    int i, j;
    int counter;
    int sum = 0;
    /*do..while loop controls the first number is smaller condition*/
    do
    {
        printf("Please enter first integer number: ");
        /*first while controls the first number is positive or integer*/
        while(1)
        {
            scanf("%lf",&first);
            if(first > 0 && ((int)first == first))
            {
                first = (int)first;
                break;
            }
            else
                printf("Please enter a valid number: ");
        }
        printf("Please enter second integer number: ");
        /*second while controls the first number is positive or integer*/
        while(1)
        {
            scanf("%lf",&second);
            if(second > 0 && ((int)second == second))
            {
                second = (int)second;
                break;
            }
            else
                printf("Please enter a valid number: ");
        }
        /*if first number bigger then second gives an error message*/
        if (first > second)
        {
            printf("First number must be smaller than Second number\n");
        }
        /*This process continue untill first number smaller than second*/
    } while (first > second);
    /*After the take correct input finds the prime nums calculates the summation*/
    for(i = first + 1; i < second; i++)
    {
        counter = 0;
        for(j = 2; j < i; j++)
        {
            if(i % j == 0)
            {
                counter++;
                break;
            }
        }
        if(counter == 0)
            sum += i;
    }
        printf("Sum of prime numbers between %.0lf and %.0lf: %d \n", first, second, sum); 
}

