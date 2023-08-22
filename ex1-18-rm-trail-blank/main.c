/* Program to remove trailing blanks and tabs from 
 * each input line, and to delete blank lines */
#include <stdio.h>
#define MAXLEN 1000

int ft_getline(char line[], int maxline);

int main(void)
{
	int len, end, i;
	char line[MAXLEN];

	while ((len = ft_getline(line, MAXLEN)) > 0)
	{
		end = len;
		for (i = len - 2; i >= 0; i--)
			if (line[i] == ' ' || line[i] == '\t')
				end = i;
			else
				break;

		if (end < len)
		{
			line[end] = '\n';
			line[end + 1] = '\0';
			len = end + 1;
		}
		if (len == 1)
			continue;

		printf("%2d: %s", end, line);
	}
	return 0;
}

/* getline: read a line into str, return length */
int ft_getline(char str[], int lim)
{
	int c, len;

	len = 0;
	while ((c = getchar()) != EOF)
	{
		if (len == lim) break;
		str[len] = c;
		++len;
		if (c == '\n') break;
	}
	str[len] = '\0';

	return len;
}
