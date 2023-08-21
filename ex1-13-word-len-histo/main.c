#include <stdio.h>

#define WORD_MAX 100
#define IN 1
#define OUT 0

int main(void)
{
	int c, i, j, w_len, w_count, status, n_words[WORD_MAX];
	
	status = OUT;
	w_len = w_count = i = 0;
	while ((c = getchar()) != EOF) 
	{
		++w_len;
		if (c == ' ' || c == '\n' || c == '\t')
		{
			status = OUT;
		    n_words[i] = w_len;
		    w_len = 0;
		}
		else if (status == OUT)
		{
			status = IN;
		    ++w_count;
		}
		++i;
	}

	printf("words to print = %d\n", w_count);
	printf("Word | Length\n");

	for (i = 0; i < n_words[w_count]; ++i)
	{						
		printf("%3d ", n_words[i]);
		for (j = 0; j < i; ++j)
		    printf("*");
		printf("\n");
	}
}
