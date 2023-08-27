/* Exercise 2-5. Write the function any(s1,s2), which returns the first location in the string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk() does the same job but returns a pointer to the location.) */
#include <stdio.h>		// for printf & NULL
#include <string.h>

#define	ASCII_SIZE	256
 
int any(char s1[], char s2[]);
 
int main(void)
{
	char *s1[] = 
	{
		"",
		"Z",
		"zedro",
		"Zedr0",
	};
	char *s2[] = 
	{
		"",
		"Z",
		"zedro",
		"Zedr0",
	};
	char *check = NULL;
	size_t n_s1 = sizeof(s1) / sizeof(s1[0]);
	size_t n_s2 = sizeof(s2) / sizeof(s2[0]);
	size_t l , r;
	int passed, failed;
	int pos;

	pos = -1;
	passed = failed = 0;
	for (l = 0; l < n_s1; l++)
	{
		for (r = 0; r < n_s2; r++)
		{
			pos = any(s1[l], s2[r]);
			check = strpbrk(s1[l], s2[r]);
			
			if (pos == -1)
			{
				if (check != NULL)
				{
					printf("Test %ld/%ld FAILED!\n", l, r);
					failed++;
				} 
				else
				{
					printf("Test %ld/%ld PASSED!\t", l, r);
					printf("Match at position %d\n", pos);
					passed++;
				}
			}
			else
			{
				if (check == NULL)
				{
					printf("Test %ld/%ld FAILED!\n", l, r);
					failed++;
				}
				else
				{
					if ((check - s1[l]) == pos)
					{
						printf("Test %ld/%ld PASSED!\n", l, r);
						passed++;
					}
					else
					{
						printf("Test %ld/%ld FAILED!\n", l, r);
						failed++;
					}
				}
			}
		}
	}
	printf("\nTEST RESULTS:\n");
	printf("Passed: %d,\nFailed: %d\n", passed, failed);

	return 0;	
}

// any()
int any(char s1[], char s2[])
{
	char arr[ASCII_SIZE];
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
