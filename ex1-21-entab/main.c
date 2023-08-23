/* Entab: replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing. */
#include <stdio.h>

#define MAX_LINES	512
#define MAX_LEN		512
#define BLANK		' '
#define NEWLINE		'\n'
#define TAB			'\t'
#define TAB_SIZE	8

int	main()
{
	char lines[MAX_LINES][MAX_LEN];
	//char temp_line[MAX_LEN];
	char tabs_per_line[MAX_LEN];
	char blanks_per_line[MAX_LEN];
	char chars_per_line[MAX_LEN];
	int c, i, j;				// Iterators
	int line_id, line_len;		// Line Stats
	int tab_c, space_c, char_c;	// Counters
	int entab_len, space2tab;	// Entabbed Line Length

	printf("Input to entab:\n");

	// Get each 'line' w/ stats
	line_id = tab_c = space_c = line_len = 0;
	while ((line_len < MAX_LEN - 1) && (c = getchar()) != EOF)
	{
		if (c == BLANK)
		{
			lines[line_id][line_len] = c;	
			++space_c;
			++line_len;
		}
		else
		{
			if (c == NEWLINE)
			{
				lines[line_id][line_len] = '\0';
				tabs_per_line[line_id] = tab_c;
				blanks_per_line[line_id] = space_c;
				chars_per_line[line_id] = line_len;
				++line_id;
				line_len = tab_c = space_c = 0;
				continue;
			}
			if (c == TAB)
				++tab_c;
			lines[line_id][line_len] = c;
			++line_len;
		}
	}

	// Print pre-entab lengths
	printf("Pre-entab:\n");
	for (i = 0; i < line_id; ++i)
		printf("Length = %d\n", chars_per_line[i]);

	// Convert TABs to BLANKS
	line_len = space_c = char_c = space2tab = 0;
	for (i = 0; i < line_id; ++i)
	{
		for (c = 0; c < chars_per_line[i]; ++c)
		{
			if (lines[i][c] == NEWLINE)
			{
				lines[i][char_c] = '\0';
				chars_per_line[i] = char_c;
				continue;
			}
			
			if (lines[i][c] == BLANK)
			{
				++space2tab;
				++space_c;
			}
			else space2tab = 0;
			
			if (space2tab == TAB_SIZE)
			{
				c -= TAB_SIZE - 1;
				char_c -= TAB_SIZE - 1;
				lines[i][char_c] = TAB;

				// Move chars to the right into the places removed
				for (j = i + 1; j < chars_per_line[i]; ++j)
					lines[i][char_c + j] = lines[i][char_c + j + 1];
				space2tab = 0;
				lines[i][char_c] = '\0';
			}
			++char_c;
		}
	}

	printf("-----------------\nOutput from entab:\n");

	// Print each 'line' w/ stats
	space_c = i = 0;
	for (i = 0; i < line_id; ++i)
	{
		line_len = 0;

		printf("%s$\t", lines[i]);
		printf("\\t = %d;\t", tabs_per_line[i]);
		printf("' ' = %d;\t", blanks_per_line[i]);
		printf("Length = %d;\n", chars_per_line[i]);
	}

	return 0;
}
