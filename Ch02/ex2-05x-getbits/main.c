#include <stdio.h>
#include <stdlib.h>

unsigned getbits(unsigned x, int p, int n);
unsigned extended_getbits(unsigned x, int p, int n);

int main(int argc, char *argv[])
{
	unsigned x = 42;
	int n;				// 'n' bit field to get
	int p;				// Beginning at position 'p'
	int max_p, max_n;	// Loop Thresholds
	int z;				// to store extracted bits

	// Handle command-line arguments
	if (argc > 1)
		x = atoi(argv[1]);

	// Print UI
	printf("getbits(	x	p	n	)\n");
	printf("====================================================\n");

	z = 0;	
	max_p = 9; 
	max_n = 9;
	for (p = 0; p < max_p; p++)
    {
		for (n = 1; n < max_n; n++)
		{
			z = getbits(x, p, n);
			printf("getbits(	%u,	%d,	%d	) = %u (0x%X)\n", x,  p, n, z, z);	
		}
		printf("====================================================\n");
		printf("getbits(	x	p	n	)\n");
    }

	return 0;
}

/* get 'n' bits from position 'p' */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}


unsigned extended_getbits(unsigned x, int p, int n)
{
	unsigned x_right = (x >> (p+1-n));	// shift right to make required bits right-justified
	unsigned mask = ~(~0 << n);			// create 'n'-bit mask
	return (x_right & mask);			// return required bits
}
