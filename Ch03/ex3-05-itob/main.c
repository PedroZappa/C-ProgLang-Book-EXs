/* Exercise 3-5. Write the function itob(n,s,b) that converts the 
 * integer n into a base b character representation in the string s. 
 * In particular, itob(n,s, 16) formats n as a hexadecimal integer in s. */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SEP				"===============================\n"
#define V_SEP			"\t=\t"
#define TAB				"\t"
#define MAX_LEN			256
#define MIN_BASE		2
#define MAX_BASE		36

#define WHITESPACE(N)	((N) == ' ' || (N) == '\t' || (N) == '\n')
#define IS_SIGN(N)		((N) == '-' || (N) == '+')

void	itob(int n, char s[], int b);
void	reverse(char str[]);
int		ft_strlen(char *str);
int		ft_atoi(char *str);

int	main(int argc, char **argv)
{
	char	str[MAX_LEN];		// String to store result
	int		base;				// Base
	int		n;					// User input integer
	int		i;					// Iterator
	int		mid_base;			// Mid base		

	// Get user input
	n = 42;
	if (argc > 1)
		n = ft_atoi(argv[1]);
	
	// Render UI
	printf("itob( n, s, b )\n");
	printf(SEP);
	printf(TAB "n = %d\n", n);
	printf(SEP);

	// Convert 'n' into strings in all possible bases 'b'
	for (base = MIN_BASE; base <= MAX_BASE; base++)
	{
		itob(n, str, base);
		printf("Base %2d: = %s\n", base, str);
	}
	printf(SEP);

	return 0;
}


// itob: stores a string represenationof integer 'n' (ASCII values) 
// in the given numerical base 'b'. 
// Limitations: only works for (2 <= b <= 36)
void itob(int n, char s[], int b)
{
	static char base_table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";	// 36 = 26 + 10
	int i, sign;
	
	// Handle invalid base values
	if (b < MIN_BASE || b > MAX_BASE)
	{
		fprintf(stderr, "Invalid base: %d\n", b);
		exit(EXIT_FAILURE);
	}

	// Check 'n's sign
	if ((sign = n) < 0)
		n = -n;
	// Process 'n's digits in reverse order
	i = 0;
	do {
		s[i++] = base_table[n % b];	// Convert to ASCII and get next digit
	} while ((n /= b) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	// Reverse string to the correct order
	reverse(s);
}

// reverse: reverse a string
void reverse(char s[])
{
	int start, end;		// Iterators
	char tmp;			// Temporary buffer
	
	for (start = 0, end = ft_strlen(s)-1; start < end; start++, end--)
	{
		tmp = s[start];
		s[start] = s[end];
		s[end] = tmp;
	}
}

// ft_strlen: returns the length of a string
int ft_strlen(char *s)
{
	int i;
	
	for (i = 0; s[i] != '\0'; i++)
		;
	return i;
}

// ft_atoi: returns the integer value of a string
int ft_atoi(char *str)
{
	int i;
	int n;
	int sign;
	
	i = 0;
	while (WHITESPACE(str[i]))	// Skip whitespace
		i++;

	sign = 1;
	if (IS_SIGN(str[i]))		// Handle sign
	{	
		if (str[i] == '-')
			sign *= -1;
		i++;
	}

	n = 0;	// Convert string to integer
	for (i = 0; str[i] != '\0'; i++)
	{
		n = n * 10 + (str[i] - '0');
	}

	return (n * sign);
}
