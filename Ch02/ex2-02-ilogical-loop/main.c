/* 
 * for(i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
       s[i] = c;

Write a loop equivalent to the for loop above without using && or || operators. */
#include <stdio.h>

#define MAX_LEN		124

int main(void)
{
	int c, i;
	char s[MAX_LEN];
	
	printf("Get input:\n");
	i = 0;
	while (i < (MAX_LEN - 1))
	{
		if ((c = getchar()) != '\n')
		{
			if (c != EOF)
				s[i++] = c;		// Store char
		}
		else
			break;
	}
	s[i] = '\0';				// Null-terminate string
	
	printf("Output:\n%s\n", s);

	return 0;
}
