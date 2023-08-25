#include <stdio.h>

#define IN 1
#define OUT 0

// Count lines, words, and characters in input.
int main(void)
{
	int c, nl, nw, nc, state;

	state = OUT;
	nl = nw = nc = 0;
	while ((c = getchar()) != EOF)
	{
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			++nw;
		}
	}
	printf("New Lines = %d\n", nl);
	printf("Words = %d\n", nw);
	printf("Chars = %d\n", nc);
}
