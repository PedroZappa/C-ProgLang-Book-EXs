/* Exercise 2-6. Write a function setbits(x,p,n,y) that returns 'x' 
 * with the 'n' bits that begin at position 'p' set to the rightmost 
 * 'n' bits of 'y', leaving the other bits unchanged. */
#include <stdio.h>
#include <stdlib.h>

#define BYTES	2

void print_binary(unsigned long x, size_t size);
unsigned long getbits(unsigned long x, int p, int n);
unsigned long setbits(unsigned long x, int p, int n, unsigned long y);

int main(int argc, char *argv[])
{
	unsigned long y = 0b1010101010101010;	
	unsigned long x = 0x0;			// 0
	unsigned char n;				// 'n' bit fields to get
	unsigned char offset;			// LSb offset
	unsigned long z;				// to store extracted bits
	int max_p, max_n;				// Loop Thresholds
	int i;							// Iterator

	// Handle command-line arguments
	if (argc == 2)
		y = atoi(argv[argc-1]);
	else if (argc == 3)
	{
		x = atoi(argv[argc-2]);
		y = atoi(argv[argc-1]);
	}
	else
	{
		printf("Usage: %s <y>\n", argv[0]);
		printf("y = %3lu= ", y);
		print_binary(y, BYTES);
		printf("=============================================================\n");
	}

	// Print Tests
	printf("setbits( x, p, n, y )\n");
	printf("x = %4lu = ", x);
	print_binary(x, BYTES);
	printf("y = %4lu = ", y);
	print_binary(y, BYTES);
	printf("=============================================================\n");

	max_p = 9;
	i = max_p - 4;
	for (offset = 0; offset < max_p; offset++)
	{
		max_n = 8 - i;
		for (n = 1; n < max_n; n++)
		{
			z = setbits(x, offset, n, y);
			printf("setbits( %lu, %d, %2d, %lu ) =>\tx = %3lu = ", x, offset, n, y, z);
			print_binary(setbits(x,	offset, n, y), BYTES);
		}
		printf("=============================================================\n");
		--i;
	}
	printf("x = %4lu = ", x);
	print_binary(x, BYTES);
	printf("y = %4lu = ", y);
	print_binary(y, BYTES);

	return (0);
}


// getbits :
unsigned long getbits(unsigned long x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

// setbits :
unsigned long setbits(unsigned long x, int p, int n, unsigned long y)
{
	// Extract 'n'-bits
	y = getbits(y, p, n);

	// Create 'n'-bit mask & filters
	unsigned mask = ~(~0 << n);	 // 'n' right-adjusted 1s 
	unsigned filterX = ((~0 << (p+1)) | (~(~0 << (p+1-n))));
	unsigned filterY = ((y & mask) << (p+1-n));

	// Set bits
	x = (x & filterX) | filterY;

	return (x);
}


// print_binary : Print the binary representation of a number
void print_binary(unsigned long x, size_t size)
{
	int i;			// Iterator
	
	// Starting at MSB (leftmost-bit) get each bit to print
	// Print size in bytes
	for (i = (size * 8) - 1; i >= 0; i--)
	{
		if (getbits(x, i, 1) == 1)
			printf("1");
		else
			printf("0");

		if (i % 4 == 0)		// every 4 bits print a space (for readability)
			printf(" ");
	}
	printf("\n");
}
