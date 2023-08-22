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
#define NULL_CHAR	'\0'

int detab(char *lines[MAX_LEN], int lineId, int tabSize);
void copy(char to[], char from[]);


int main(void)
{
	printf("To detab:\n");
	
	char lines[MAX_NUM][MAX_LEN];
	int c, i, lineId, line_len, tabSize;

	lineId = line_len = 0, tabSize = 8;
	while ((c = getchar()) != EOF)
	{
		lines[lineId][line_len] = c;
		if (c == '\n')
		{
			lines[lineId][line_len] = '\0';
			lineId++;
			line_len = 0;
		}
		else ++line_len;
	}

	// Detab array of lines


	printf("De-tabbed:\n");
	for (i = 0; i < lineId; ++i)
		printf("%s\n", lines[i]);

	return 0;
}


void copy(char to[], char from[])
{
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}


int detab(char *lines[MAX_LEN], int lineId, int tabSize)
{
	int line, line_c, line_len, tab_c;
	char line_cpy[MAX_LEN];

	for (line = 0; line < lineId; ++line)
	{
		line_cpy = copy(line_cpy, lines[line]);
		line_c = line_len = 0;
		while (line_cpy[line_c] != '\0')
		{
			if (line_c == TAB)
			{
				tab_c = 0, tabSize = 8;
				while (tab_c < tabSize)
				{
					lines[line][line_c] = SPACE;
					++line_len;
				    ++tab_c;
				}
				++line_c;
			} else
				++line_len
		        ++line_c;
			    
		}
	}

	return
}
