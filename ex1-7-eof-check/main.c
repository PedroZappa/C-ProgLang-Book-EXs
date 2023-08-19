#include <stdio.h>

int main(int argc, char *argv[])
{
	int c;

	while ((c = getchar()) != EOF)
	{
		putchar(c);
		printf(" EOF = %d \n", (c != EOF));
	}
	printf(" EOF = %d \n", (c == EOF));
}
