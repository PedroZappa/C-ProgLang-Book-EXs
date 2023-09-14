/* Exercise 4-1. Write the function strrindex(s,t), 
 * which returns the position of the rightmost 
 * occurrence of t in s, or -1 if there is none. */
#include <ctype.h>		// isspace()
#include <stdio.h>

#define SEP "0=====================================================0\n"

#define IS_DIGIT(c)	((c) >= '0' && (c) <= '9')
#define IS_SPACE(c)	((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')
#define IS_SIGN(c)	((c) == '-' || (c) == '+')

int		strindex(char *s, char *t);
int		strrindex(char *s, char *t);
int 	ft_atoi(char *s);

int main(int argc, char *argv[])
{
	char *s = "Zedro Pappa 42++ is the best Zedro!";	// Source string
	char *t[] = { "Z", "p", "+", "o", };		// Substrings to find in 's'
	int n = sizeof(t) / sizeof(t[0]);					// Number of substrings

	// Get user input
	if (argc > 1)
		s = argv[argc - 1];
	
	// Render Source String
	printf("\t\tString to Search:\n");
	printf(SEP);
	printf("\t\"%s\"\n", s);
	printf("\t 0         1         2         3         4\n");
	printf("\t 01234567890123456789012345678901234567890\n");
	printf(SEP);
	printf(" strindex( s, t )\t  ||\tstrrindex( s, t )\n");
	printf(SEP);
	
	// Search for each substring
	printf("Substring | Found @ Index || Substring | Found @ Index\n");
	printf(SEP);
	for (int i = 0; i < n; i++)
	{
		printf("\"%s\"\t    %d", t[i], strindex(s, t[i]));
		printf("\t\t  || \"%s\"\t %d\n", t[i], strrindex(s, t[i]));
	}
	printf(SEP);

	return 0;
}

// strindex : returns first index of t in s
int strindex(char *s, char *t)
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++)	// Loop through 's'
	{								// Compare 's' with 't'
		for (j = i, k = 0; t[j]!='\0' && s[j] == t[k]; j++, k++)	// Loop through 't'
			;						// while 's' and 't' match
		if (k > 0 && t[k] == '\0')
			return i;				// Return first index where 's' and 't' match
	}
	return -1;						// Return -1 if no match was found
}

// strrindex : returns last index of t in s
int strrindex(char *s, char *t)
{
	int i, j, k;
	int m = -1;					// Return -1 if no match was found
	for (i = 0; s[i] != '\0'; i++)	// Loop through 's'
	{								// Compare 's' with 't'
		for (j = i, k = 0; t[j]!='\0' && s[j] == t[k]; j--, k++)	// Loop through 't'
			;
		if (k > 0 && t[k] == '\0')
			m = i;				// Return last index where 's' and 't' match
	}
	return m;
}


// ft_atoi : converts a string to an integer
int ft_atoi(char *s)
{
	int i, n, sign;

	for (i = 0; IS_SPACE(s[i]); i++)	/* Skip leading spaces */
		;
	sign = (s[i] == '-') ? -1 : 1;		/* Set sign */
	if (IS_SIGN(s[i]))					/* Skip sign */
		i++;
	for (n = 0; IS_DIGIT(s[i]); i++)
		n = 10 * n + (s[i] - '0');		/* Convert to integer */
	return (n * sign);
}
