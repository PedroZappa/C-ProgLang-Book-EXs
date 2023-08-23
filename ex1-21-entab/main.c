/* Entab: replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing. */
#include <stdio.h>

#define MAXLINE		512
#define TAB_SIZE	8

int	main(void)
{
	int c, i, j;					/* Iterators */
	int space_c, space_t;			/* Space Counters */
	int len, sub_line;				/* Line Counters */
	int tab_c;						/* Tab Counter */
	char lines[MAXLINE][MAXLINE];	/* Line Storage */
	int lines_len[MAXLINE];			/* Line Lengths */

	printf("To entab:\n");

	// Get lines from standard input
	c = len = sub_line = 0;
	while ((c = getchar()) != EOF)
	{
		lines[sub_line][len] = c;
		if (c == '\n')
		{
			lines[sub_line][len] = '\0';// Null-terminate
			lines_len[sub_line] = len;	// Store line length
			sub_line++;					// Get next line
			len = 0;
		}
		else
			++len;
	}

	// Entab lines
	for (i = 0; i < sub_line; i++)
	{
		j = space_c = 0;
		while (lines[i][j] != '\0')
		{
		    // Count spaces till count == TAB_SIZE
			if (lines[i][j] == ' ')
				++space_c;				// Increment Counter
			if (lines[i][j] != ' ')
				space_c = 0;			// Reset Counter
			if (space_c == TAB_SIZE)
			{
				/* Count back (TAB_SIZE - 1) spaces */
				j -= (TAB_SIZE - 1);
				lines_len[i] -= (TAB_SIZE - 1);
				lines[i][j] = '\t';		// Replace with TAB
			}
			++j;
		}
	}

	// Count Test Stats
	for (i = 0; i < sub_line; i++)
	{
		j = space_c = tab_c = 0;
		while (lines[i][j] != '\0')
		{
			if (lines[i][j] == ' ')
				++space_c;
			if (lines[i][j] == '\t')
				++tab_c;
			++j;
		}
	}

	// Print lines
	printf("=========================\n");
	for (i = 0; i < sub_line; i++)
	{
		printf("%s$\t", lines[i]);
		printf("Spaces: %d\t", space_c);
		printf("Tabs: %d\t", tab_c);
		printf("Line Length: %d\n", lines_len[i]);
	}	

	return (0);
}

