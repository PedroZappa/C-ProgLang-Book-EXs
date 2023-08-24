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
	int i;					/* Iterators */
	int len;				/* Length of line */
	char line[MAXLINE];		/* Input Line */

	printf("To fold every %d chars:\n", BREAK);

	/* Get input lines */
	while ((len = ft_getline(line, MAXLINE)) > 0) 
	{
		if (len > BREAK)
		{
			ft_fold(line, 0);
			printf("%s\n=======", line);
		}
		else
			printf("%s", line);
	}

	return 0;
}

/* get line */
int ft_getline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;		/* add '\n' & go to next 'i' */
	s[i] = '\0';		/* null-terminate */
	return i;
}

/* fold lines */
void ft_fold(char line[], int idx)
{
	int i, j;
	int space_c;
	
	/* Loop through chars to find split point within BREAK number o'chars */
	space_c = 0;
	for (i = (idx + BREAK); (i > idx) && (line[i] != ' ') 
		&& (line[i] != '\t'); --i)
	{
		// No split point found : split at SPACE after BREAK
		if (i == idx)
		{
			/* Look for next ' ' and '\t' */
			for (i = idx; line[i] != ' ' && line[i] != '\t'; ++i);
			line[i] = '\n';						/* Insert '\n' */
		}

		/* Split point found within BREAK number o'chars */
		if ((strlen(line) - i) <= BREAK)
			line[i] = '\n';						/* Insert '\n' */
		else if ((i > idx) && (i != idx))
		{
			line[i] = '\n';						/* Insert '\n' */
			ft_fold(line, i);					/* Recursive call */
		}
		return ;
	}
}
