/* “fold” long input lines into two or more shorter lines 
 * after the last non-blank character that occurs before 
 * the n-th column of input. 
 * Do something intelligent with very long lines, and if 
 * there are no blanks or tabs before the specified column. */
#include <stdio.h>

#define MAXLINE		256
#define BREAK		6

int main(void)
{
	int c, i;
	int sub_line, len;
	char lines[MAXLINE][MAXLINE];		// Store folded lines

	// Get lines from standard input
	printf("To fold:\n");

	c = sub_line = len = 0;
	while ((c = getchar()) != EOF)
	{
		lines[sub_line][len] = c;		// Store char
		++len;
		if ((len % BREAK) == 0 || c == '\n')
		{
			lines[sub_line][len] = '\0';// Null-terminate
			++sub_line;
			len = 0;
		}
	}
	lines[sub_line][len + 1] = '\0';

	// Print folded lines
	printf("Fold = %d\n", BREAK);
	printf("123456789x123456789x123456789x\n");
	for (i = 0; i < sub_line; i++)
		printf("%s$\n", lines[i]);

}
