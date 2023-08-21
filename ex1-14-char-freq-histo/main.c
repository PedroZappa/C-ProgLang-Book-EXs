#include <stdio.h>

/* Program to print histogram of ASCII char frequencies */
int main(void)
{
	int c, cn, i; // Init Iterators
	int ascii[128] = {0}; // Init Array to store range of ASCII Values

	while ((c = getchar()) != EOF)
	{
		++cn;
		ascii[c] += 1;
	}

	printf("Input Char Frequency: %d\n", cn);
	// Print Histogram
	for (i = 0; i < 128; ++i)
	{
		if (ascii[i] != 0)
		{
			// Print counted ASCII Values
			if (i == '\t')
				printf("\\t: %d\n", ascii[i]);
			if (i == '\n')
				printf("\\n: %d\n", ascii[i]);
			if (i == ' ')
				printf("SPACE: %d\n", ascii[i]);
			if (i > 32 && i <= 126)
				printf("%c: %d\n", i, ascii[i]);
			if (i == 127)
				printf("DEL: %d\n", ascii[i]);
		}
	}
}
