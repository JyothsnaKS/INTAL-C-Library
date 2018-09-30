//Demo program for the "intal" library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stdio.h>
#include "intal.h"

int main() {
	intal* i1 = create_intal();
	intal* i2 = create_intal();
	
	intal* prod = create_intal();
	intal* diff = create_intal();
	intal* sum = create_intal();
	intal* quotient = create_intal();	
	intal* exp = create_intal();
	
	read_intal(i1, "53");
	read_intal(i2, "2");

	printf("i1 = ");
	print_intal(i1);
	printf("\n");

	printf("i2 = ");
	print_intal(i2);
	printf("\n");

	sum=add_intal(i1,i2);
	printf("sum = ");
	print_intal(sum);
	printf("\n");
	
	diff=subtract_intal(i1,i2);
	printf("diff = ");
	print_intal(diff);
	printf("\n");
	
	//quotient=divide_intal(i1,i2); //brute-force approach
	printf("quotient = ");
	print_intal(quotient);
	printf("\n");
	
	prod=multiply_intal(i1,i2);  //complete implemnatation of karatsuba algorithm
	printf("product = ");
	print_intal(prod);
	printf("\n");

	exp=pow_intal(i1,i2); //divide and conquer approach & brute force approach
	printf("exp = ");
	print_intal(exp);
	printf("\n");
	
	delete_intal(&exp);
	delete_intal(&sum);
	delete_intal(&diff);
	delete_intal(&prod);
	delete_intal(&i2);
	delete_intal(&i1);
	return 0;
}
