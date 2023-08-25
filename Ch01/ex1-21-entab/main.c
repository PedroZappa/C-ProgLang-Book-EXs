/* Entab: replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing. */
#include <stdio.h>

#define MAXLINE		256
#define MAX			128
#define TAB_SIZE	8
#define TAB			'\t'

int entab(char line[], int len);

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
		lines[sub_line][len] = c;		// Store char
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
	for (i = 0; i < sub_line; ++i)
	{
		entab(lines[i], lines_len[i]);
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

int entab(char line[], int len)
{
	int i, j, k;			// Iterators 
	int t;					// Toggle
	int space_c;			// Space Counters 

		space_c = 0;
		if (line[i] == ' ')
			space_c++;				// Increment space Counter
		if (line[i] != ' ')
			space_c = 0;			// Reset space Counter
		if (space_c == TAB_SIZE)
		{
			
			i -= (TAB_SIZE - 1);	// Count back to the first blank
			line[i] = '\t';			// Replace first blank with TAB

			for (j = (i + 1); j < len; j++)
				line[j] = line[j + (TAB_SIZE - 1)];		// Remove trailing spaces
			len -= (TAB_SIZE - 1);						// Update line length
			line[len] = '\0';							// Null-terminate line
			space_c = 0;								// Reset space counter
		}
		++i;
	

	return (i);
}
