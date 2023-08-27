/* Exercise 2-4. Write an alternate version of squeeze(s1,s2) that deletes each character in s1 that matches any character in the string s2. */
#include <stdio.h>
#include <string.h>

int squeeze(char s1[], char s2[]);

int main(void)
{
	char *l_str[] =			// Array o'test strings
	{			
		"Zedro", 
		"Pappa", 
		"42"
	};
	char *r_str[] =			// Array o'test matches
	{
		"a", 
		"e", 
		"4"
	};
	char buffer [42];
	size_t l_str_i = sizeof(l_str) / sizeof(l_str[0]);	// Get number of elements
	size_t r_right_i = sizeof(r_str) / sizeof(r_str[0]);// ...
	size_t l, r;	// Iterators
	
	printf("Squeeze strings:\n");
		printf("==========================\n");
	 
	for (l = 0; l < l_str_i; l++)			// Loop through l_str array
	{
		for (r = 0; r < r_right_i; r++)		// Loop through r_str array
		{
			strcpy(buffer, l_str[l]);		// Copy l_str into buffer
			squeeze(buffer, r_str[r]);		// squeeze buffered copy
			printf("'%s' - '%s' = '%s'\n", l_str[l], r_str[r], buffer);
		}
		printf("==========================\n");
	}
	return 0;
}


/* squeeze() : delete matching chars */
int squeeze(char s1[], char s2[])
{
	int i, j, k;		// Iterators
	int match;			// Match toggle

	for (i = k = 0; s1[i] != '\0'; i++)				// Loop through s1
	{
		match = 0;
		for (j = 0; s2[j] != '\0' && !match; j++)	// Loop through s2
		{
			if (s1[i] == s2[j])		// Look for match
				match = 1;			// Toggle match FOUND
		}
		if (!match)					// If no match found
			s1[k++] = s1[i];		// Copy char
	}
	s1[k] = '\0';					// null-terminate
	return 0;
}

