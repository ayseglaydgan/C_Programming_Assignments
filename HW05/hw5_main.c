/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/


#include <stdio.h>
#include "hw5_lib.h"


void test_operate_polynomials () 
{
	double cofA0, cofA1, cofA2, cofA3, cofB0, cofB1, cofB2, cofB3;
	char op;

	helper_take_poly(&cofA0, &cofA1, &cofA2, &cofA3);
	helper_take_poly(&cofB0, &cofB1, &cofB2, &cofB3);
	
	/* printf("cof0 %lf\ncof1 %lf\ncof2 %lf\ncof3 %lf\n",cofA0, cofA1, cofA2, cofA3); */ 
	/* printf("cof0 %lf\ncof1 %lf\ncof2 %lf\ncof3 %lf\n",cofB0, cofB1, cofB2, cofB3); */

	printf("Choose an Operator (+, -, *):\n");
	scanf(" %c",&op);

	operate_polynomials  (&cofA3, &cofA2, &cofA1, &cofA0, &cofB3, &cofB2, &cofB1, &cofB0, op);

	printf("Result: (3, %.2f), (2, %.2f), (1, %.2f), (0, %.2f)\n",cofA3, cofA2, cofA1, cofA0);
}


void test_four_d_vectors ()
{
	double mean_a0=0.0, mean_a1=0.0, mean_a2=0.0, mean_a3=0.0, longest_distance=0.0;
	int N=5;
	printf("\nEnter your vectors respectively\n\n");
	four_d_vectors (&mean_a0, &mean_a1, &mean_a2, &mean_a3, &longest_distance, N);
	printf("Mean a0: %f\nMean a1: %f\nMean a2: %f\nMean a3: %f\nThe longest distance between two points: %f\n\n\n", mean_a0, mean_a1, mean_a2, mean_a3, longest_distance);
}


void test_dhondt_method ()
{
	int partyA=100000, partyB=80000, partyC=30000, partyD=0, partyE=0, numberOfSeats=8;
	dhondt_method (&partyA, &partyB, &partyC, &partyD, &partyE, numberOfSeats);
	printf("Party A: %d seat(s).\nParty B: %d seat(s).\nParty C: %d seat(s).\nParty D: %d seat(s).\nParty E: %d seat(s).\n\n\n", partyA, partyB, partyC, partyD, partyE);
}


void test_order_2d_points_cc ()
{
	double x1=-2.0, y1=8.0, x2=-3.0, y2=-15.0, x3=4.0, y3=-8.0;
	order_2d_points_cc (&x1, &y1, &x2, &y2, &x3, &y3);
	printf("Counter-Clockwise Order: (%f,%f) - (%f,%f) - (%f,%f)\n\n\n", x1, y1, x2, y2, x3, y3);
}


void test_number_encrypt ()
{
	unsigned char number=0;
	number_encrypt (&number);
	printf("Encrypted number: %d\n\n\n", number);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_operate_polynomials (); 
	test_four_d_vectors (); 
	test_dhondt_method ();
	test_order_2d_points_cc ();
	test_number_encrypt ();
	return (0);
} /* end main */
