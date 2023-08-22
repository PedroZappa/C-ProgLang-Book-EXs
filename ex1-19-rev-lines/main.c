/* Program that reverses input line by line */
#include <stdio.h>
#define MAX_LEN 1000

int ft_getline(char line[], int maxlen);
void ft_revstr(char str[], int len);

int main(void)
{
	int len;
	char line[MAX_LEN];
	
	while ((len = ft_getline(line, MAX_LEN)) > 0)
		if (len >= 1)
		{
			ft_revstr(line, len);
			printf("%s\n", line);
		}

	return 0;
}

// getline: read a line into str, return length
int ft_getline(char str[], int maxlen)
{
	int c, len;

	len = 0;
	while ((c = getchar()) != EOF)
	{
		if (len == maxlen || c == '\n') break;
		str[len] = c;
		++len;
	}
	str[len] = '\0';

	return len;
}

// revstr: reverse a string
void ft_revstr(char str[], int len)
{
	int i, end, tmp;

	for (i = 0, end = len - 1; i < end; i++, end--)
	{
		tmp = str[i];
		str[i] = str[end];
		str[end] = tmp;
	}
	return ;
}
