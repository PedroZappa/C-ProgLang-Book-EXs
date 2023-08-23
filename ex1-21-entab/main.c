/* Entab: replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing. */
#include <stdio.h>

#define MAX_LINES	512
#define MAX_LEN		512
#define NEWLINE		'\n'
#define TAB			'\t'
#define BLANK		' '

int ft_getline(char str[], int lim);

int	main()
{
	printf("Input to entab:\n");
	char lines[MAX_LINES][MAX_LEN];
	char line[MAX_LEN];
	int i;					// Iterators
	int line_id, line_len;	// Line Stats
	int tab_c;

	line_id = tab_c = 0;
	while ((line_len = ft_getline(line, MAX_LEN)) > 0)
	{
		// Copy 'line' into 'lines' & get Stats
		for (i = 0; i < line_len; ++i)
		{
			lines[line_id][i] = line[i];	
			if (line[i] == TAB)
				++tab_c;
		}
		++line_id;
	}

	// Print 'lines' array
	printf("Output from entab:\n");
	for (i = 0; i < line_id; ++i)
	{
		printf("%s$\n", lines[i]);
	}

	return 0;
}

/* ft_getline: read a line into str, return length */
int	ft_getline(char str[], int lim)
{
	int c;		// Iterators
	int len;	// Line length / Index
	int offset;	// Tab offset
	
	len = 0;
	while ((len < lim - 1) && (c = getchar()) != EOF && c != '\n')
	{
		if (c == NEWLINE)
		{
			str[len] = '\0';
			len = 0;
		}
		else if (c == TAB)
		{
			offset = TAB - (len % TAB);
			while (offset-- != 0)
			{
				str[len] = BLANK;
				++len;
			}
		}
		else
		{
			str[len] = c;
			++len;
		}
	}

	return (len);
}
