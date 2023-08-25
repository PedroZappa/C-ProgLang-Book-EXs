/* Ex1-23: Uncomment: Write a program to remove 
 * all comments from a C program. Don’t forget 
 * to handle quoted strings and character 
 * constants properly. C comments do not nest. */
#include <stdio.h>

#define SEARCH	0
#define SLASH	1
#define COMMENT	2
#define STAR	3


int main(void)
{
    int state;
	char c;

	/* Get user input */
	printf("Enter a C program to uncomment: ");
	state = SEARCH;
	while((c = getchar()) != EOF)
	{
		if (state == SLASH)
	    {
			if (c == '*')
				state = COMMENT;// comment found
			else				// do not print 
			{
				putchar('/');	// comment finished
				state = SEARCH;	// switch back to search mode
			}
		}
		// Look for comments 
		if (state == SEARCH || state == SLASH)
		{
			// Look for comment oepning '/' 
			if (state == SEARCH)
			{
				if (c == "/*"[0])
					state = SLASH;	// opening '/' found 
				else
					putchar(c);		// print current char
			}
		}
		else if (state == COMMENT)
		{
			if (c == "/*"[1])		// closing comment '*' found
				state = STAR;
		}
		else if (state == STAR)
		{
			if (c == '/')
				state = SEARCH;		// comment closed '/' : print again
			else if (c == '*')
				state = COMMENT;	// opening '*' : switch to comment mode
		}
	}
	if (state == SLASH)
		putchar('/');

	return 0;
}


