/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
** Programmer: Aysegul Aydogan. 190104004009
** Revision: 2021.09.03.16.59
** 
*/


#include <stdio.h>
#include<math.h>

#include "hw1_lib.h"
#include "hw1_io.h"



/*
** Testing root finding..
**
*/
void test_root_finder3() 
{
	double root_known = 1.0;
	double root_found;
	root_found = root3(1.2,0.0,-1.0,-1.2, root_known - 0.1, root_known + 0.1);
	printf("Ground truth root: %f vs found root: %f\n", root_known, root_found);
}

void test_root_finder4() 
{
	double root_known = -0.8;
	double root_found;
	root_found = root4(1.0,-1.0,2.0,0.0,-4.0, root_known - 0.1, root_known + 0.1);
	printf("Ground truth root: %f vs found root: %f\n", root_known, root_found);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	printf("******RESULTS FOR 3-DEGREE POLYNOMIALS******\n");
	printf("The Polynomial: ");
	write_polynomial3(1.2,0.0,-1.0,-1.2); 
	test_root_finder3();
	printf("Integral of 3-Degree Polynomial: %f\n",integral3(1.2,0.0,-1.0,-1.2,1.0,5.0,1.0));
	printf("\n");
	printf("******RESULTS FOR 4-DEGREE POLYNOMIALS******\n");
	printf("The Polynomial: ");
	write_polynomial4(1.0,-1.0,2.0,0.0,-4.0);
	test_root_finder4();
	printf("Integral of 4-Degree Polynomial: %f\n",integral4(1.0,-1.0,2.0,0.0,-4.0,1.0,5.0,1.0));
	
	

	return (0);
} /* end main */
