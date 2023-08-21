#include <stdio.h>

int power(int base, int n);

/* Test power() */
int main(void)
{
	int i = 0;

	printf("2^i		2^i		-3^i\n");
	printf("------------------------------------\n");
	for (i = 0; i < 10; ++i)
		printf("%3d		%3d	      %6d\n", i, power(2, i), power(-3, i));
	return 0;
}

/* power() : x^n for n >= 0 */
int power(int base, int n)
{
	int i, p;

	p = 1;
	for (i = 1; i <= n; ++i)
		p = p * base;
	return p;
}
