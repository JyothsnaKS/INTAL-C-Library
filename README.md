# INTAL_library
### INTAL is short for integers of arbitrary length

Integers of arbitrary length cannot be represented using built-in integer/real data types. Such integers will result in an overflow. It is important to able to represent and perform mathematical operations on them because they have wide applications in cryptography etc. There is also the neccessity to improve the time efficiency of algorithm to make it generate results faster in a worst case or average case scenario and also make the implemention of the algorithm more efficient.

This repository creates C library for integers of arbitrary length consisting of functions to read and print “intal” and perform mathematical operations on “intal”. The integer could be positive, negative or zero. The following functions have been implemented in “intal” library:
1. Add two integers of arbitrary length
2. Subtract two integers of arbitrary length
3. Multiply two integers of arbitrary length
4. Division limited to integer division
5. Exponentiation limited to positive power.

## Approach

1. Addition : A function is written where starting from the least significant digit the corresponding digits are added and the carry is taken forward. Depending on the sign of the argument, a call to subtract function may be made.

2. Subtraction : A function is written where starting from the least significant digit the corresponding digits are subtracted and the borrow is taken care of. Depending on the sign of the argument, a call to addition function may be made.

3. Multiplication: This operation is performed using the Karatsuba algorithm and separate functions have been written to perform padding of leading zeroes ,extracting a substring and calculation power of 10 in addition to the function performing addition and subtraction.

4. Division: This operation is being performed by using a brute force approach where in the divisor is repeatedly subtracted from the divisor, a copy of the divisor is decremented by one each time till it becomes zero.

5. Exponentiation : This operation has been implemented using both brute force and divide and conquer approach separately. In the divide and conquer approach , power(a,n) =a * power(a,n/2) * power(a,n/2)  if n is odd or power(a,n)= * power(a,n/2) * power(a,n/2) if n is even. The previously written multiplication and division functions are being used to implement this.

## Assumptions
1.	Input should be an signed integer only.
2.	Input contains only digits and no other character.
3.	First character of the integer represents the sign of the number and if it not mentioned, it is assumed to be positive.

## Limitation
Division operation returns only the floor value and not a decimal value
