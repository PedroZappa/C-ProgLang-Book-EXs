/* Exercise 2-5. Write the function any(s1,s2), which returns the first location in the string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk() does the same job but returns a pointer to the location.) */
#include <stdio.h>		// for printf & NULL
#include <string.h>

#define	ASCII_SIZE	256
 
int any(char s1[], char s2[]);
 
int main(int argc, char *argv[])
{
    char *s1 = NULL;
    char *s2 = NULL;

	if (argc < 3 || argc > 3)
	{
		printf("Usage: %s <string1> <string2>\n", argv[0]);
		return(1);
	}
	else
	{
		s1 = argv[argc - 2];
		s2 = argv[argc - 1];
	}
    
	printf("'%s' includes '%s'?\n", s1, s2);
	if (any(s1, s2) != -1)
		printf("Match found at index '%d'\n", any(s1, s2));
	else
		printf("No match found\n");

	return 0;	
}

// any()
int any(char s1[], char s2[])
{
	char arr[ASCII_SIZE] = {0};
	int i;

	if (s1 == NULL)			// Check for NULL strings
	{
		if (s2 == NULL) 
			return 0;		// If both are NULL, return 0
		else 
			return -1;		// If only s1 is NULL, return -1
	}

	for (i = 0; i < ASCII_SIZE; i++)
		arr[i] = 0;			// Initialize array with ASCII_SIZE elems to 0

	while (*s2 != '\0')		// While there are chars in s2
	{
		arr[(unsigned char)*s2] = 1;		// Set char state in arr to 1
		s2++;				// Advance s2
	}

	i = 0;					// Reset iterator
	while (s1[i] != '\0')	// While there are chars in s1
	{
		if (arr[(unsigned char) s1[i]] == 1)	// If char in arr is 1
			return (i);							// Return index
		i++;									// Advance s1
	}
	return (-1);			// Return -1 if no match found
}
