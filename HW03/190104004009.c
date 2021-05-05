/*  Instructor: Yakup Genc
    Programmer: Aysegul Aydogan
    Revision Date: 25.03.2021 */

#include<stdio.h>
/*WANTED FUNCTIONS*/
void calculate_fibonacci_sequence();
void decide_perfect_harmonic_number();
void difference_max_min();
void bmi_calculation();
/*HELPERS*/
int check_input();
void print_fibonacci(int);
int check_natural_num();
void is_perfect_harmonic(int);

int main()
{
    calculate_fibonacci_sequence();
    printf("\n");
    decide_perfect_harmonic_number();
    printf("\n");
    difference_max_min();
    printf("\n");
    bmi_calculation();
    return 0;
}

/*-------Checks the input for part1 (Is it char, *, negative or pozitive integer)------*/
int check_input()
{
    int input;
    /*to check input is * or another char*/
    if(scanf("%d",&input) == 0)
    {
        char c;
        do
        {
            c = getchar();
            if(c == '*')
            {
                return 0;
            }
        } while (c != '\n');
        printf("Please enter 'numeric' term(s) number:");
        return -1;
    }
    else
    {
        if(input <= 0)
        {
            printf("Please enter 'positive' term(s) number: ");
            return -1;
        }
    /*if the input is correct type */
        else
        {
            return input;
        }
    }
}
/*-------Prints the fibonacci seq according to input------*/
void print_fibonacci(int input)
{
    int i, num1, num2, next_num;
    num1 = 1;
    num2 = 1;
    printf("Fibonacci Sequence:\n");
    for(i = 0; i < input; i++)
    {
        /*fibonacci algorithm*/
        printf("%d\n",num1);
        next_num = num1 + num2;
        num1 = num2;
        num2 = next_num;
    }
}
/*-------General function for the part1" (controls the flow of functions)------*/
void calculate_fibonacci_sequence()
{
    int return_val;
    printf("please enter term(s) number:");
    while(1)
    {
        return_val = check_input();
        if(return_val != -1 && return_val != 0)
        {
            print_fibonacci(return_val);
            printf("please enter term(s) number:");
        }
        else if(return_val == 0)
            break;
    }

}

/*-------Checks the input for part2 (Is it *, float, negative or pozitive integer)------*/
int check_natural_num()
{
    double input;
    /*to check input is * or another char*/
    if(scanf("%lf",&input) == 0)
    {
        char c;
        do
        {
            c = getchar();
            if(c == '*')
            {
                return -1;
            }
        } while (c != '\n');
        printf("Enter a numeric number:");
        return 0;
    }
    else
    {
        if(input <= 0)
        {
            printf("Enter a natural number:");
            return 0;
        }
        else
        {
            /*checking input is integer or not*/
            if((int)input == input)
                return (int)input;
            else
                printf("Enter a natural number:");
                return 0;
        }
    }
}
/*------Some calculations to determine perfect - harmonic number according to input------*/
void is_perfect_harmonic(int input)
{
    int i;
    int j = 0;
    int sum_perf = 0;
    float sum_harm = 0;
    printf("Natural Number Divisors:");
    for(i = 1; i <= input; i++)
    {
        if(input % i == 0)
        {
            j++;
            if(i != input)
                printf(" %d,",i);
            else
                printf(" %d\n",i);
            /*Perfect number and harmonic number algorithm*/
            sum_perf += i;
            sum_harm = sum_harm + ((float)1/(float)i);
        }
    }
    printf("Is perfect number ?: ");
    if(sum_perf == 2*input)
        printf("Yes\n");
    else
        printf("No\n");
    printf("Is harmonic number ?: ");
    if((int)sum_harm == sum_harm)
        printf("Yes\n");
    else
        printf("No\n");
}
/*-------General function for the part2" (controls the flow of functions)------*/
void decide_perfect_harmonic_number()
{
    printf("Please enter input number:");
    while(1)
    {
        int return_val;
        return_val = check_natural_num();
        if(return_val != -1 && return_val != 0)
        {
            is_perfect_harmonic(return_val);
            printf("Please enter input number:");
        }
        else if(return_val == -1)
        {
            break;
        }
    }
}
/*-------Finds the difference between max and min number of 5 number seq------*/
void difference_max_min()
{
    double max;
    double min;
    int i;
    double num;
    printf("Please enter 5 numbers: ");
    scanf("%lg",&num);
    /*assign to first input to compare the other inputs*/
    max = num;
    min = num;
    for(i = 1; i < 5; i++)
    {
        scanf("%lf",&num);
        if(num > max)
        max = num;
        else if(num < min)
        min = num;
    }
    printf("Maximum number is: %g\n", max);
    printf("Minimum number is: %g\n", min);
    printf("Difference between maximum and minimum is %g\n",(max - min));
    }
/*-------Calculates the bmi------*/
void bmi_calculation()
{
    double height, weight, bmi;
    printf("Please enter the weight(kg): ");
    scanf("%lf",&weight);
    printf("Please enter the height(m): ");
    scanf("%lf",&height);
    /*bmi calculation formula*/
    bmi = weight / (height*height);
    printf("Your category: ");
    if(bmi < 16.0)
        printf("Severely Underweight\n");
    else if( bmi >= 16.0 && bmi <= 18.4)
        printf("Underweight\n");
    else if( bmi >= 18.5 && bmi <= 24.9)
        printf("Normal\n");
    else if( bmi >= 25.0 && bmi <= 29.9)
        printf("Overweight\n");
    else
        printf("Obese\n");
}