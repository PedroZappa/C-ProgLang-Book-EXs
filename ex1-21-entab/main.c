/* Entab: replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing. */
#include <stdio.h>

#define MAXLINE		256
#define MAX			128
#define TAB_SIZE	8

int	main(void)
{
	int c, i, j;					/* Iterators */
	int space_c;					/* Space Counters */
	int len, sub_line;				/* Line Counters */
	int tab_c;						/* Tab Counters */
	int char_c;						/* Char Counter */
	char lines[MAXLINE][MAXLINE];	/* Line Storage */
	int lines_len[MAX];				/* Line Lengths */
	int lines_spaces[MAX];			/* Line's Spaces */
	int lines_tabs[MAX];			/* Line's Tabs */

	// Get lines from standard input
	printf("To entab:\n");
	printf("123456789x123456789x123456789x\n");

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
				space_c++;				// Increment Space Counter
			if (lines[i][j] != ' ')
				space_c = 0;			// Reset Counter
			if (space_c == TAB_SIZE)
			{
				/* Count back (TAB_SIZE - 1) spaces */
				j -= (TAB_SIZE - 1);
				lines_len[i] -= (TAB_SIZE - 1);
				lines[i][j] = '\t';		// Replace with TAB
				space_c = 0;
				
				// Remove trailing spaces
				for (j = (i + 1); j < lines_len[i]; j++)
				{
				    lines[i][j] = lines[i][j + (TAB_SIZE - 1)];
				}
				space_c = 0;
				lines[i][lines_len[i]] = '\0';	// Null-terminate
			}Get
			j++;Get
		}
	}

	// Get Stats & Print lines
	printf("=========================\n");
	printf("123456789x123456789x123456789x\n");
	for (i = 0; i < sub_line; i++)
	{
		j = space_c = tab_c = char_c = 0;
		while (lines[i][j] != '\0')
		{
			if (lines[i][j] == ' ')
				++space_c;
			if (lines[i][j] == '\t')
				++tab_c;
			if (lines[i][j] > ' ' && lines[i][j] <= '~')
				++char_c;
			++j;
		}
		lines_spaces[i] = space_c;
		lines_tabs[i] = tab_c;
		lines_len[i] = j;

		printf("%s$\t", lines[i]);
		printf("Spaces: %d\t", space_c);
		printf("Chars: %d\t", char_c);
		printf("Tabs: %d\t", tab_c);
		printf("\tLength: %d\n", lines_len[i]);
	}	
	printf("123456789x123456789x123456789x\n");

	return (0);
}
