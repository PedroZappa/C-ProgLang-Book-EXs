#include <stdio.h>

#define IN 1
#define OUT 0

int main(void)
{
	int c, i, j, c_count, w_count, status;
	int n_words[100];	
	
	c_count = w_count = status = i = 0;
	while ((c = getchar()) != EOF) 
	{
		++c_count;
		if (c == ' ' || c == '\n' || c == '\t')
			status = OUT;
		else if (status == OUT)
		{
			status = IN;
		    ++w_count;
		    n_words[i] = c_count;
		    c_count = 0;
		}
		++i;
	}
	
	for (i = 0; i < w_count; ++i)
		n_words[i] = c_count;

	printf("words to print = %d\n", w_count);
	printf("word length = \n");

	/*for (i = 0; i < n_words[w_count]; ++i)
	{						
		printf("%2d ", n_words[i]);
		for (j = 0; j < c_count; ++j)
		    printf("*");
		printf("\n");
	}*/
}
