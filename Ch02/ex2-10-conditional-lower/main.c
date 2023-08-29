// Exercise 2-10. Rewrite the function lower, 
// which converts upper case letters to lowercase, 
// with a conditional expression instead of if-else. 
#include <stdio.h>
#include <stdlib.h>

#define SEP "=================\n"

int lower(int c);

int main(int argc, char *argv[])
{
	char c = 'Z';			// Convert to lowercase
	char *str = "Z3DR0";	// String to convert
	int i;					// Iterator

	// Get user input
	if (argc > 1)
		str = argv[1];

	// Render Header
	printf("lower( c )\n");
	printf(SEP);

	// Convert to lowercase
	printf("c = %c\n", c);
	printf("lowercase:\n");
	printf("c = %c\n", lower(c));
	printf(SEP);

	// Print string
	printf("string: %s\n", str);
	printf("Converted string:\n");
	for (i = 0; str[i] != '\0'; i++)
		printf("%c", lower(str[i]));
	printf("\n");

	return (0);
}

/* lower(): converts upper case letters to lowercase */
int lower(int c)
{
	return (c >= 'A' && c <= 'Z') ? c += 'a' - 'A' : c;		// 'a' - 'A' = 32
}

