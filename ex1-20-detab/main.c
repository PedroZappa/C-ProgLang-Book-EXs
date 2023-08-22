/* detab: replace tabs in the input with proper 
 * number of blanks to space to next tab stop.
 * Assume a fixed set of tab stops, every 'n' cols.
 * 'n' should be variable to allow for modification 
 * of the value at runtime */
#include <stdio.h>

#define MAX_NUM		100
#define MAX_LEN		1024
#define SPACE		' '
#define TAB			'\t'

int calc_spaces(int offset, int tabSize);
int ft_getline(char line[], int maxline);
void copy(char to[], char from[]);


int main(void)
{
	printf("To detab:\n");
	
	char lines[MAX_NUM][MAX_LEN];
	//char line[MAX_LEN], result[MAX_LEN];
	int c, lineId, line_len, i;

	lineId = line_len = 0;
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

	printf("De-tabbed:\n");
	for (i = 0; i < lineId; ++i)
		printf("%s\n", lines[i]);

	return 0;
}


int calc_spaces(int offset, int tabSize)
{
	return tabSize - (offset % tabSize);
}
