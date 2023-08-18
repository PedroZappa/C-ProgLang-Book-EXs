#include <stdio.h>

int main(void)
{
	int c;

	while ((c = getchar()) != EOF)
	{
		printf("%d ", (c != EOF));
		putchar(c);
	}
	printf("\n%d\n", (c != EOF));
}
