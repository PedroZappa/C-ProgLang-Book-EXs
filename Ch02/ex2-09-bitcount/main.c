// Ex2-09: In a two's complement number system, 'x &= (x-1)' deletes the rightmost 1-bit in x.
// Explain why. Use this observation to write a faster version of bitcount.
#include <stdio.h>
#include <stdlib.h>

#define BYTES 2

int bitcount_og(unsigned x);
int bitcount(unsigned x);
void print_binary(unsigned x, int size);

int main (int argc, char *argv[])
{
	unsigned x, x_og = 0b01110101;
	int n_1bits;

	// get user input
	if (argc > 1)
		x = x_og = atoi(argv[1]);
	
	// Render UI
	printf("\t\tbitcount( x ) =\n");
	printf("\tx = %u = ", x);
	print_binary(x, BYTES);
	printf("==================================================\n");

	// Calculate
	// Count number of 1s
	n_1bits = bitcount_og(x);

	while (x != 0)		// while bits != 0
	{
		// Set x to new value
		x &= (x - 1);	// clear rightmost 1-bit
		printf("bitcount( %2d ) = has (%2x ) = ", x, n_1bits);
		print_binary(x, BYTES);
	}
	printf("==================================================\n");
	printf("\tx = %d; has (%d) 1-bits.\n", x_og, n_1bits);


	return (0);
}

int bitcount_og(unsigned x)
{
	int n_1bits;

	for (n_1bits = 0; x != 0; x >>= 1)	// Shift right while != 0
		if (x & 01)						// Check if bit at LSb is 1
			n_1bits++;					// Count number of 1s
	return n_1bits;
}

int bitcount(unsigned x)
{
	int n_1bits;

	while (x != 0)		// while bits != 0
	{
		x &= (x - 1);	// clear rightmost 1-bit
		n_1bits++;		// count number of 1s
	}
	return n_1bits;
}


// Visualization Helpers
// getbits : returns 'n' bits from 'x' at position 'p'
unsigned getbits(unsigned x, unsigned p, unsigned n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

// print_binary : prints 'x' in binary form
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


