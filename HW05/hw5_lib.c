/*
** hw5_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/

#include <stdio.h>
#include <math.h>
#include "hw5_lib.h"


void helper_take_poly(double *cof0, double *cof1, double *cof2, double *cof3)
{
	int i, deg;
	double cof;
	printf("Enter format like this: (deg, cof), (deg, cof), (deg, cof), (deg, cof)\n");
	for (i = 0; i < 4; i++)
	{
		scanf(" (%d, %lf),%*c",&deg, &cof);
		/*printf("degree = %d, cof = %lf\n", deg, cof);*/

		if (deg == 0) *cof0 = cof;
		else if (deg == 1) *cof1 = cof;
		else if (deg == 2) *cof2 = cof;
		else if (deg == 3) *cof3 = cof;
	}
}

void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op)
{
	
	switch (op)	
	{
	case '+':
		*a3 = *a3 + *b3;
		*a2 = *a2 + *b2;
		*a1 = *a1 + *b1;
		*a0 = *a0 + *b0;
		break;
	case '-':
		*a3 = *a3 - *b3;
		*a2 = *a2 - *b2;
		*a1 = *a1 - *b1;
		*a0 = *a0 - *b0;
		break;
	case '*':
		*a3 = *a3 * *b3;
		*a2 = *a2 * *b2;
		*a1 = *a1 * *b1;
		*a0 = *a0 * *b0;
		break;

	default:
		printf("INVALID OPERATOR\n");
		break;
	} 

	

}

void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N)
{
	double d0, d1, d2, d3, euclidian_distance = 0, calc_d0, calc_d1, calc_d2, calc_d3;
	double temp0 = *mean_a0, temp1 = *mean_a1, temp2 = *mean_a2, temp3 = *mean_a3;
	double total0 = 0, total1 = 0, total2 = 0, total3 = 0;
	int i;

	for (i = 0; i < N; i++)
	{
		scanf("%lf",&d0);
   		scanf("%lf",&d1);
   		scanf("%lf",&d2);
   		scanf("%lf",&d3);

		total0 += d0;
		total1 += d1;
		total2 += d2;
		total3 += d3;

		calc_d0 = fabs(d0 - temp0) * fabs(d0 - temp0);
		calc_d1 = fabs(d1 - temp1) * fabs(d1 - temp1);
		calc_d2 = fabs(d2 - temp2) * fabs(d2 - temp2);
		calc_d3 = fabs(d3 - temp3) * fabs(d3 - temp3);

		distance_between_4d_points (calc_d0, calc_d1, calc_d2, calc_d3, &euclidian_distance);
		
		if (*longest_distance < euclidian_distance)
		{
			*longest_distance = euclidian_distance;
		}
		
		temp0 = d0;
		temp1 = d1;
		temp2 = d2;
		temp3 = d3;
	}

	*mean_a0 = total0 / N;
	*mean_a1 = total1 / N;
	*mean_a2 = total2 / N;
	*mean_a3 = total3 / N;
}

void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance)
{
   
   *euclidian_distance = sqrt((d0 + d1 + d2 + d3));
}

void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats)
{

	int seatsA = 0, seatsB = 0, seatsC = 0, seatsD = 0, seatsE = 0, total_seats = 0;

	double A = *partyA, B = *partyB, C = *partyC, D = *partyD, E = *partyE;
	double tempA = A, tempB = B, tempC = C, tempD = D, tempE = E;

	while(total_seats != numberOfSeats)
	{
		/* A wins */
		if (tempA >= tempB & tempA >= tempC & tempA >= tempD & tempA >= tempE)
			tempA = A / ++seatsA;  
		/* B wins */
		else if (tempB >= tempA & tempB >= tempC & tempB >= tempD & tempB >= tempE)
			tempB = B / ++seatsB;  
		/* C wins */
		else if (tempC >= tempA & tempC >= tempB & tempC >= tempD & tempC >= tempE)
			tempC = C / ++seatsC;  
		/* D wins */
		else if (tempD >= tempA & tempD >= tempC & tempD >= tempB & tempD >= tempE)
			tempD = D / ++seatsD;  
		/* E wins */
		else if (tempE >= tempA & tempE >= tempB & tempE >= tempC & tempE >= tempD)
			tempE = E / ++seatsE;  

		total_seats = seatsA + seatsB + seatsC + seatsD + seatsE;

		/* printf("toto: %d A: %d B: %d C: %d D: %d E: %d\n", total_seats, seatsA, seatsB, seatsC, seatsD, seatsE); */
	}

	/* set values to seats values */
	*partyA = seatsA;
	*partyB = seatsB;
	*partyC = seatsC;
	*partyD = seatsD;
	*partyE = seatsE;
	
}

int helper_find_quadrant(double* x, double*y)
{
	/* determine which quadrant */
	if (*x > 0 && *y > 0)
		return 1;
	else if (*x < 0 && *y > 0)
		return 2;
	else if (*x < 0 && *y < 0)
		return 3;
	else if (*x > 0 && *y < 0)
		return 4;
}

int helper_sort (double *x1, double *y1, double *x2, double *y2)
{
	/* comparing slopes and points according to quadrants*/
	/* if first value bigger than last value return 1 */
	int quadrant1, quadrant2;
	double slop_diff;
	quadrant1 =  helper_find_quadrant(x1, y1);
	quadrant2 =  helper_find_quadrant(x2, y2);
	slop_diff = fabs(*y1 / *x1) - fabs(*y2 / *x2);

	if (quadrant1 > quadrant2)
		return 1;
	else if (quadrant1 < quadrant2)
		return 0;
	else /* if equals */
	{
		if (quadrant1 == 1 || quadrant1 == 3)
		{
			if (slop_diff > 0)
				return 1;
			else
				return 0;
		}
		else /* if quadrant == 2 or quadrant == 4 */
		{
			if (slop_diff < 0)
				return 1;
			else
				return 0;
		}
	}
}

void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3)
{
	/* first find max value 
	** than compare other two 
	*/ 
	int check1, check2, check3;
	double mX1, mY1, mX2, mY2, mX3, mY3;
	check1 = helper_sort(x1, y1, x2, y2);
	check2 = helper_sort(x1, y1, x3, y3);
	check3 = helper_sort(x2, y2, x3, y3);
	if (check1 == 1 && check2 == 1)
	{
		/* find max value */
		mX1 = *x1; mY1 = *y1;
		if (check3 == 1)
		{
			mX2 = *x2; mY2 = *y2;
			mX3 = *x3; mY3 = *y3;
		}
		else
		{
			mX2 = *x3; mY2 = *y3;
			mX3 = *x2; mY3 = *y2;
		}
	}

	check1 = helper_sort(x2, y2, x1, y1);
	check2 = helper_sort(x2, y2, x3, y3);
	check3 = helper_sort(x1, y1, x3, y3);
	if (check1 == 1 && check2 == 1)
	{
		mX1 = *x2; mY1 = *y2;
		if (check3 == 1)
		{
			mX2 = *x1; mY2 = *y1;
			mX3 = *x3; mY3 = *y3;
		}
		else
		{
			mX2 = *x3; mY2 = *y3;
			mX3 = *x1; mY3 = *y1;
		}

	}
	check1 = helper_sort(x3, y3, x1, y1);
	check2 = helper_sort(x3, y3, x2, y2);
	check3 = helper_sort(x1, y1, x2, y2);
	if (check1 == 1 && check2 == 1)
	{
		mX1 = *x3; mY1 = *y3;
		if (check3 == 1)
		{
			mX2 = *x1; mY2 = *y1;
			mX3 = *x2; mY3 = *y2;
		}
		else
		{
			mX2 = *x2; mY2 = *y2;
			mX3 = *x1; mY3 = *y1;
		}
	}

	*x1 = mX1;
	*y1 = mY1;
	*x2 = mX2;
	*y2 = mY2;
	*x3 = mX3;
	*y3 = mY3;

}


void number_encrypt (unsigned char* number)
{
	char b7='-', b6='-', b5='-', b4='-', b3='-', b2='-', b1='-', b0='-';
	get_number_components (*number, &b7, &b6, &b5, &b4, &b3, &b2, &b1, &b0);
	reconstruct_components (number, b7, b6, b5, b4, b3, b2, b1, b0);
	printf("TO BE IMPLEMENTED\n");
	
}

/* can not implemented hocam :( */
void get_number_components (unsigned char num, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0)
{
	/*
	int number = num - 'a';
	*b0 = '0', *b1 = '0', *b2 = '0', *b3 = '0', *b4 = '0', *b5 = '0', *b6 = '0', *b7 ='0';

	*b0 = (number % 2) + 'a';
	number /= 2; if (number == 0) return;
	*b1 = (number % 2) + 'a';
	number /= 2; if (number == 0) return;
	*b2 = (number % 2) + 'a';
	number /= 2; if (number == 0) return;
	*b3 = (number % 2) + 'a';
	number /= 2; if (number == 0) return;
	*b4 = (number % 2) + 'a';
	number /= 2; if (number == 0) return;
	*b5 = (number % 2) + 'a';
	number /= 2; if (number == 0) return;
	*b6 = (number % 2) + 'a';
	number /= 2; if (number == 0) return;
	*b7 = (number % 2);
	number /= 2; if (number == 0) return;
	*/
}


void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0)
{
	printf("TO BE IMPLEMENTED\n");
}
