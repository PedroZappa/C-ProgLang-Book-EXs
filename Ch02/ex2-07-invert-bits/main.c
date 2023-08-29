/* Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted
(i.e., 1 changed into 0 and vice versa), leaving the the others unchanged. */
#include <stdio.h>

#define BYTES 2

unsigned invert(unsigned x, unsigned p, unsigned n);
void print_binary(unsigned x, int size);

int main(void)
{
	unsigned x = 0b11111111;
	unsigned x_inv = 0b0;
	int p, n;
	int max_offset, max_n;

	printf("\t\tinvert( x, p, n )\n");
	printf("\tx = %u = ", x);
	print_binary(x, BYTES);

	max_offset = 8;
	max_n = 5;
	for (p = 0; p < max_offset; p++) 
	{
		printf("===================================================\n");
		for (n = 1; n < max_n; n++)
		{
			x_inv = invert(x, p, n);
			printf("invert( %u, %d, %d ) = %4u = ", x, p, n, x_inv);
			print_binary(x_inv, BYTES);			
		}
	}
	printf("===================================================\n");
	printf("\tx = %u = ", x);
	print_binary(x, BYTES);
	printf("\t\tinvert( x, p, n )");

	return (0);
}


// invert : inverts 'n' bits from position 'p' of 'x'
unsigned invert(unsigned x, unsigned p, unsigned n)
{
	return (x ^ (~(~0 << n) << p));
}


// getbits : returns 'n' bits from 'x' at position 'p'
unsigned getbits(unsigned x, unsigned p, unsigned n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}


// print_binary : prints 'x' in binary form
// size : number of bytes to print in binary
void print_binary(unsigned x, int size)
{
	int i;

	for (i = (size * 8) - 1; i >= 0; i--)
	{
		if (getbits(x, i, 1) == 1) 
			printf("1");
		else
			printf("0");
		if (i % 4 == 0)
			printf(" ");
	}
	printf("\n");
}
