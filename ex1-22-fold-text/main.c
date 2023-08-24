/* “fold” long input lines into two or more shorter lines 
 * after the last non-blank character that occurs before 
 * the n-th column of input. 
 * Do something intelligent with very long lines, and if 
 * there are no blanks or tabs before the specified column. */
#include <stdio.h>
#include <string.h>

#define MAXLINE		256
#define TAB_SIZE	8
#define BREAK		6

int ft_getline(char line[], int lim);
void ft_fold(char line[], int idx);

int main(void)
{
	int len;				/* Length of line */
	char line[MAXLINE];		/* Input Line */

	printf("Fold input every %d chars:\n", BREAK);

	/* Get input lines */
	while ((len = ft_getline(line, MAXLINE)) > 0) 
	{
		if (len > BREAK)
		{
			ft_fold(line, 0);
			printf("====================\n");
			printf("%s", line);
			printf("123456789x123456789x\n");
			printf("====================\n");
		}
		else printf("%s", line);
	}

	return 0;
}

/* get line */
int ft_getline(char line[], int lim)
{
	int c, i;			/* i = index, c = char */

	for (i = 0; i < (lim - 1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
		line[i] = c;		/* add char to 'line' */
	if (c == '\n')
		line[i++] = c;		/* add '\n' & go to next 'i' */
	line[i] = '\0';			/* null-terminate */
	return i;
}

/* fold lines: recursive */
void ft_fold(char line[], int l_idx)
{
	int i;					/* i = index */	
	
	/* Loop in reverse through 'line's first block of chars
	 * of BREAK length to find split point */
	for (i = (l_idx + BREAK); (i > l_idx) && (line[i] != ' ') && (line[i] != '\t'); --i)
	{
		// No split point found : split at ' ' or \t after BREAKs length
		if (i == l_idx)
		{
			/* Look for next ' ' and '\t' */
			for (i = l_idx; line[i] != ' ' && line[i] != '\t'; ++i);
			line[i] = '\n';						/* Insert '\n' */
		}
		/* Split point found within BREAKs length */
		if ((strlen(line) - i) <= BREAK)
			line[i] = '\n';						/* Insert '\n' */
		else if ((i > l_idx) && (i != l_idx))
		{
		    line[i] = '\n';					/* Insert '\n' */
			ft_fold(line, i);					/* Recursive call */
		}

		return ;
	}
}
