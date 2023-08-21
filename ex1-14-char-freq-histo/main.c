#include <stdio.h>

/* Program to print histogram of ASCII char frequencies */
int main(void)
{
	int c, cn, i, star; // Init Iterators
	int ascii[128] = {0}; // Init Array to store range of ASCII Values

	cn = 0;
	while ((c = getchar()) != EOF)
	{
		++cn;
		ascii[c] += 1;
	}

	printf("Input Char Frequency\n");
	printf("Total: %d\n", cn);
	// Print Histogram
	for (i = 0; i < 128; ++i)
	{
		if (ascii[i] != 0)
		{
			// Print counted ASCII Values
			if (i == '\t')
		    {
				printf("\\t: ");
			    for (star = 0; star < ascii[i]; ++star)
				    printf("*");
		    }
		    if (i == '\n')
		    {
				printf("\\n: ");
				for (star = 0; star < ascii[i]; ++star)
					printf("*");
			}
		    if (i == ' ')
		    {
				printf("' ': ");
				for (star = 0; star < ascii[i]; ++star)
					printf("*");
			}
			if (i > 32 && i <= 126) 
		    {
				printf("%c: ", i);
				for (star = 0; star < ascii[i]; ++star)
					printf("*");
			}
		    if (i == 127)
			{
				printf("DEL: ");
				for (star = 0; star < ascii[i]; ++star)
					printf("*");
			}	
		    printf("\n");						
		}
	}
}
