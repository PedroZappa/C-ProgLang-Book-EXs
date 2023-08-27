/* Write the function htoi(s), which converts a string 
 * of hexadecimal digits (including an optional 0x or 0X) 
 * into its equivalent integer value. The allowable digits 
 * are '0' through '9', 'a' through 'f', and 'A' through 'F'. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long htoi(char hexstr[]);					// converts a string of hex bits into integer.
long hexchartoi(char hexdigit, int pos);	// converts a hex char to its integer value.

int main(void)
{
	char *endptr = NULL;
	char *tests[] =
	{
	    "2A",
	    "0x2A",
		"0X2A",
		"0X0C0BE",
		"abcdef",
		"123456",
		"0x123456",
		"zedro",
		"230x234",
		"230"
	};

	long int result;
	long int check;
	size_t total_tests = sizeof(tests) / sizeof(tests[0]);
	size_t curr_test;

	for (curr_test = 0; curr_test < total_tests; curr_test++)
	{
		result = htoi(tests[curr_test]);				// call htoi for convertion.
		check = strtol(tests[curr_test], &endptr, 16);	// compare with library function.

		if ((*endptr != '\0' && result != -1) || result == check)
			printf("Testing: '%s'.\tValid Conversion!\t%ld : %ld\n", tests[curr_test], result, check);
		else
			printf("Testing: '%s'.\tInvalid Conversion!\t%ld : %ld\n", tests[curr_test], result, check);
	}

	return 0;
}

// htoi() : converts a string of hexadecimal digits to an integer value.
long htoi(char *hexstr)
{
	char *ptr = &hexstr[strlen(hexstr) - 1];		// point to last char in hexstr.
	long decimal, digit;
	int pos;

	// Skip '0x' or '0X'
	if (hexstr[0] == '0' && (hexstr[1] == 'x' || hexstr[1] == 'X'))
		hexstr += 2;

	decimal = digit = pos = 0;
	while (ptr >= hexstr)
	{
		if ((digit = hexchartoi(*ptr, pos)) < 0)	// invalid hex digit.
		{
			printf("Invalid hex digit: '%c' at position %d\n", *ptr, pos);
			return (-1);
		}
		decimal += digit;
		--ptr;
		++pos;
	}
	return decimal;
}

// hexchartoi() : converts a hex char to its integer value.
long hexchartoi(char hexdigit, int pos)
{
	char hextable[] = "0123456789ABCDEF";	// valid hex digits
	char *ptr = &hextable[0];				// point to first char in hextable.
	long decimal;
	int i;

	decimal = 0;
	while (*ptr != toupper(hexdigit) && decimal < 16)
	{
		++ptr;								// go to next char in hextable.
		++decimal;							// increment decimal
	}
	if (*ptr == toupper(hexdigit))
	{
		for (i = 0; i < pos; i++)
			decimal *= 16;
		return decimal;
	}
	return -1;
}
