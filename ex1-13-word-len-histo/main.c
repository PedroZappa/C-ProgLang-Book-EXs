#include <stdio.h>

#define WORD_MAX 100
#define IN 1
#define OUT 0

int main(void)
{
        int c, i, j; // Init Iterators
        int w_len, w_count, status;
        int n_words[WORD_MAX];

        status = IN;
        w_len = w_count = i = 0;
        while ((c = getchar()) != EOF)
        {
				++w_len;
                if (c == ' ' || c == '\n' || c == '\t')
                {	
				    n_words[w_count] = --w_len;
				    if (w_len > 0)
						++w_count;
				    w_len = 0;
					status = OUT;
                }
				else if (status == OUT)
				    status = IN;
        }

        printf("%d Words\n", w_count);
        printf("_________________\nWord Length\n");

        for (i = 0; i < w_count; ++i)
        {
                printf("%3d\t", n_words[i]);
                for (j = 0; j < n_words[i]; ++j)
                    printf("*");
                printf("\n");
        }
}
