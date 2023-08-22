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

int ft_strlcpy(char to[], char from[], int size);
int calc_spaces(int offset, int tabSize);
int detab(char lines[MAX_NUM][MAX_LEN], int lineId, int tabSize);

int main(void)
{
	printf("To detab:\n");
	
	char lines[MAX_NUM][MAX_LEN];
	int c, lineId, line_len, tabSize;

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

	// Detab and print array of lines
	printf("De-tabbed:\n");
	printf("lineIds = %d\n", lineId);

	detab(lines, lineId, tabSize);

	return 0;
}


int	ft_strlcopy(char *to, char *from, unsigned int size)
{
	unsigned int i;

	i = 0;
	if (size)
	{
		while (from[i] && (i < (size - 1)))
		{
		    to[i] = from[i];
		    ++i;
		}
		to[i] = '\0';
	}
	while (from[i])
		++i;
	return (i);
}

int calc_spaces(int offset, int tabSize)
{
   return tabSize - (offset % tabSize);
}


int detab(char lines[MAX_NUM][MAX_LEN], int lineIds, int tabSize)
{
	int line, line_c, space_c, line_len, cpy_len, i;
	char line_cpy[MAX_LEN];

	cpy_len = 0;
	for (line = 0; line < lineIds; ++line)
	{
		cpy_len = ft_strlcopy(line_cpy, lines[line], MAX_LEN);
		line_c = space_c = line_len = 0;
		while (line_cpy[line_c] != '\0')
		{
			if (line_c == TAB)
			{
				i = 0;
				tabSize = calc_spaces(line_len, tabSize);
				while (i < tabSize)
				{
					lines[line][line_c] = SPACE;
					++line_len;
					++line_c;
				    ++i;
				}
			} 
			else if (line_c == SPACE)
			{
				++line_len;
				++line_c;
				++space_c;
			}
			else
			{
				++line_len;
		        ++line_c;
			}
		    line_cpy[line_c] = '\0';
		}

		printf("%s$", line_cpy);
		printf("	Spaces = %d	Length = %d\n", space_c, cpy_len);
	}

	return line_len;
}
