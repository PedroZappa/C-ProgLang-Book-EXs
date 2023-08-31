/* Exercise 3.06: Write a version of itoa that accepts three 
 * arguments instead of two. The third argument is a minimum 
 * field width; the converted number must be padded with 
 * blanks on the left if necessary to make it wide enough. */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SEP		"===============================\n"
#define MAX		256
#define TAB		'\t'

#define WHITESPACE(N)	((N) == ' ' || (N) == '\t' || (N) == '\n')
#define IS_SIGN(N)		((N) == '-' || (N) == '+')

void	itoa_width(int n, char str[], int width);
void	reverse(char str[]);
int		ft_atoi(char *str);
int		ft_strlen(char *str);

int main(int argc, char **argv)
{
	int n;				// User input integer
	int i, j;			// Iterators
	char str[MAX];		// Store conversion string
	int ints[] = { 42, 0, INT_MAX, INT_MIN };	
	
	// Get user input
	n = 42;
	if (argc > 1)
		ints[0] = ft_atoi(argv[argc - 1]);

	// Render Header
	printf("itoa_width( n, s, width )\n");
	printf(SEP);
	for (j = 0; j < 4; j++)
	{
		printf("\tn = %d\n", ints[j]);
		printf(SEP);

		for (i = 1; i < 7; i++)
		{
			itoa_width(ints[j], str, i);
			printf("Width = %d: '%s'\n", i, str);
		}
		printf(SEP);
	}
	return 0;
}

// itoa_width: convert int to ASCII
// adds a blanks so that printed number is wide enough
void itoa_width(int n, char s[], int width)
{
	int i, sign;

	// Doing calculations with negative numbers
	if ((sign = n) > 0)
		n = -n;		// Invert the 'n's sign if positive
	
	i = 0;
	do {
		s[i++] = '0' - (n % 10);	// Convert to ASCII and get next digit
	} while ((n /= 10) < 0);		// Delete it from 'n'
	
	if (sign < 0)					// Check original sign of 'n'
		s[i++] = '-';

	while (i < width)				// Fill extra blanks
		s[i++] = ' ';

	s[i] = '\0';					// Null terminate

	reverse(s);						// Reverse string
}

// reverse: reverse a string
void reverse(char s[])
{
	int start, end;		// Iterators
	int c;				// Temporary buffer

	start = 0;
	end = ft_strlen(s) - 1;
	while (start < end)
	{
		c = s[start], s[start] = s[end], s[end] = c;
		++start;
		--end;
	}
}

// ft_strlen: returns the length of a string
int ft_strlen(char *str)
{	
	int i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

// atoi: convert string to int
int ft_atoi(char *str)
{
	int i;
	int n;
	int sign;

	// Skip whitespace
	i = 0;
	while (WHITESPACE(str[i]))
		i++;

	// Handle sign
	sign = 1;
	while (IS_SIGN(str[i]))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}

	// Handle digits
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10 + (str[i++] - '0');

	return (n * sign);
}
