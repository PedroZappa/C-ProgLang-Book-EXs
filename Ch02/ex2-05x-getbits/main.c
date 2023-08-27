#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);
unsigned extended_getbits(unsigned x, int p, int n);

int main(void)
{
	unsigned x = 42;
	int n;			// 'n' bit field to get
	int p;			// Beginning at position 'p'
	int i, j;		// Loop Thresholds
	int z;

	printf("\tgetbits(x, p, n)\n");

	z = 0;
	i = j = sizeof(x) + 1;
	for (p = 0; p < i; p++)
    {
		for (n = 0; n < j; n++)
		{
			z = getbits(x, p, n);
			printf("getbits(%u, %d, %d) = %u (0x%X)\n", x,  p, n, z, z);	
		}
		printf("======================================\n");
    }

	return 0;
}

/* get 'n' bits from position 'p' */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p + 1 - n)) & (~0 << n);
}


unsigned extended_getbits(unsigned x, int p, int n)
{
	unsigned x_right = (x >> (p + 1 - n));	// shift right to make required bits right-justified
	unsigned mask = (~0 << n);				// create 'n'-bit mask
	return (x_right & mask);				// return required bits
}
