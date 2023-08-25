#include <stdio.h>

int main(void)
{
	int c, state;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\t' || c == '\n')
		{
			putchar(c);
			putchar('\n');
			c = getchar();
		}
		putchar(c);
	}
}
