/* write a program to print all input lines that are longer than THRESHOLD */
#include <stdio.h>
#define MAXLINE 1000
#define THRESHOLD 7

int main(void)
{
	int c, i, line_len, sub_lines;
	char lines[MAXLINE][MAXLINE];

	c = line_len = sub_lines = 0;
	while ((c = getchar()) != EOF)
    {		
		lines[sub_lines][line_len] = c;
		if (c == '\n')
		{
		    lines[sub_lines][line_len] = 0;  /* Null-terminate the string */
		    if (line_len >= THRESHOLD)
				sub_lines++;
		    line_len = 0;
		}
		else
			++line_len;
	}
		
	printf("=========================\n");
	for (i = 0; i < sub_lines; i++)
		printf("%s\n", lines[i]);
	return 0;
}

