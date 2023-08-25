/* detab: replace tabs in the input with proper 
 * number of blanks to space to next tab stop.
 * Assume a fixed set of tab stops, every 'n' cols.
 * 'n' should be variable to allow for modification 
 * of the value at runtime */
#include <stdio.h>

#define MAX_NUM		100
#define MAX_LEN		512
#define SPACE		' '
#define TAB			'\t'
#define NEW_LINE	'\n'


int main(void)
{
	printf("To deTAB:\n");
	
	int c, i;
	int offset, lineId, line_len;
	int space_c;
	char lines[MAX_NUM][MAX_LEN];

	// Get lines
	lineId = line_len = 0;
	while ((line_len < MAX_LEN - 1) && (c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			lines[lineId][line_len] = '\0';			// Null-terminate
			lineId++;								// Get next line
			line_len = 0;
		}
		else if (c == '\t') 
		{
		    offset = TAB - (line_len % TAB);		// Get offset
		    while(offset-- != 0) 
		    {
				lines[lineId][line_len] = SPACE;	// Replace tab with space
				++line_len;
			}
		}
		else
		{
			lines[lineId][line_len] = c;			// Store char
			++line_len;
		}
	}

	// Print converted lines
	printf("DeTAB\'ed:\n");
	
	// Testing: Get STATS
	// Loop through lines and count amount of spaces per line
	space_c = 0;
	for (i = 0; i < lineId; ++i)
	{
		line_len = 0;
		while (lines[i][line_len] != '\0')
		{
			if (lines[i][line_len] == SPACE)
				++space_c;					// Increment space Counter
			++line_len;
		}
		printf("%s$\t", lines[i]);
		printf("SPACES: %d\n", space_c);
		space_c = 0;
	}	

	return 0;
}


