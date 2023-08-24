#include <stdio.h>

int isComment(void);
int isEndComment(void);

int c;

int main(void)
{
    extern int c;
	while ((c = getchar()) != EOF)
	{
		if (isComment())				// If a comment is found
		{
		    while (!(isEndComment()))	// Look for end comment
				putchar(' ');				// Print spaces
			printf("    ");				// Make up for skipped comment tags
		}
		else
			putchar(c);					// Print char
	}
	return (0);
}

/* isComment: return 1 if c is a comment, 0 otherwise */
int isComment(void)
{
    extern int c;
    if (c == '/')			// Check for comment opening '/'
	{
		c = getchar();		// Get next char
		if (c == '*')		// Check for comment opening '*'
			return (1);
		else
			putchar('/');	
	}
	return  (0);
}

/* isEndComment: return 1 if c is a end comment, 0 otherwise */
int isEndComment(void)
{
    extern int c;
    c = getchar();
    if (c == '*')
	{
		c = getchar();
		if (c == '/')
			return (1);
	}
	return  (0);
}

