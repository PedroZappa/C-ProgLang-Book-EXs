// Exercise 3-3. Write a function expand(s1,s2) that expands shorthand 
// notations like a-z in the string s1 into the equivalent complete list 
// abc...xyz in s2. Allow for letters of either case and digits, and be 
// prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that 
// a leading or trailing - is taken literally.
#include <ctype.h>
#include <stdio.h>

#define UPPER(N) ((N) >= 'A' && (N) <= 'Z')		// Uppercase check
#define LOWER(N) ((N) >= 'a' && (N) <= 'z')		// Lowercase check
#define NUMBER(N) ((N) >= '0' && (N) <= '9')		// Digit check
#define ALPHA_NUM(N) (UPPER(N) || LOWER(N) || NUMBER(N))	// Alpha-numeric check

#define SEP			"============================\n"
#define MAXLINE		512
#define DASH		'-'

void expand(char *s1, char *s2);

int main(int argc, char *argv[])
{
	char *strs[] = { "a-z", "-a-z", "a-z-", "0-9a-z", 
					"-0-9", "A-Z", "-A-Z", "A-Z-", NULL };
	char expanded[MAXLINE];
	int i;

	// Get user input though args
	if (argc > 1)
		strs[0] = argv[1];

	// Render Header
	printf("\texpand()\n");
	printf(SEP); 
	
	// Expand shorthand notation in strings
	i = 0;
	while (strs[i])
	{
		expand(strs[i], expanded);
		printf("Unexpanded\t:\t%s\n", strs[i]);
		printf("Expanded\t:\t%s\n", expanded);
		++i;
	}
	printf(SEP);

	return 0;
}

//	expand: shorthand strings
void expand(char *s1, char *s2)
{
	int i;		// Counter for source string length
	int j;		// Counter for expanded string length
	int buffer;	// Temporary buffer

	j = 0;
	for (i = 0; s1[i]; i++)		// Loop through s1
	{
		if (i == 0 || s1[i] != DASH)	// If anthing but dash or first char
		{
			s2[j++] = s1[i];			// Copy char
			continue;
		}
		// if dash, but not a full shorthand expression
		if (s1[i] == DASH && (!ALPHA_NUM(s1[i-1]) || !ALPHA_NUM(s1[i+1])))
		{
			s2[j++] = s1[i];			// Copy char
			continue;
		}
		// if shorthand expression
		if (s1[i] == DASH && (
					// Check for Uppercase
					(UPPER(s1[i-1]) && UPPER(s1[i+1]) && (s1[i-1] < s1[i+1])) ||
					// Check for Lowercase
					(LOWER(s1[i-1]) && LOWER(s1[i+1]) && (s1[i-1] < s1[i+1])) ||
					// Check for Numbers
					(NUMBER(s1[i-1]) && NUMBER(s1[i+1]) && (s1[i-1] < s1[i+1]))))
		{
			buffer = s1[i-1]+1;			// save next ASCII in buffer
			while (buffer < s1[i+1])	// while chars till last ASCII
				s2[j++] = buffer++;		// Copy char, go to next ASCII
			continue;
		}
		s2[j++] = s1[i];		// Copy char
	}
	s2[j] = '\0';				// null-terminate
}

