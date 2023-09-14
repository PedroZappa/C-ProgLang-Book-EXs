/* In a Two´s Complement number representation, our version 
 * of itoa() does not handle the largest negative number, 
 * that is, the value of `n` equal to -(2^wordsize-1) . 
 * Explain why not. Modify it to print that value correctly 
 * regardless of the machine on which it runs. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SEP		"===============================\n"
#define MAX		256

void itoa(int n, char s[]);
void nega_itoa(int n, char s[]);
void reverse(char s[]);

int main(void)
{
	int ints[] = { 0, 42, -42, INT_MIN, INT_MAX };
	char strs[MAX][MAX];
	char *new_str;
	int ints_len;			// Length of ints[]
	int i;

	// Convert int[] into strs[] w/ itoa()
	ints_len = sizeof(ints) / sizeof(int);
	for (i = 0; i < ints_len; i++)
		itoa(ints[i], strs[i]);

	// Render UI
	printf("\titoa( n, s )\n");
	printf(SEP);
	for (i = 0; i < ints_len; i++)
		printf("[%d] : %11d = %11s\n", i, ints[i], strs[i]);
	printf(SEP);

	// Convert ints[] into strs[] w/ nega_itoa()
	for (i = 0; i < ints_len; i++)
	{
		nega_itoa(ints[i], strs[i]);
	}

	printf("\tnega_itoa( n, s )\n");
	printf(SEP);
	for (i = 0; i < ints_len; i++)
		printf("[%d] : %11d = %11s\n", i, ints[i], strs[i]);
	printf(SEP);
	return 0;
}


// itoa: convert int to ASCII
void itoa(int n, char s[])
{
	int i, sign;
	
	if ((sign = n) < 0)		// Record the sign
		n = -n;				// Make n positive
	i = 0;
	do {	// Generate digits in reverse order
		s[i++] = (n % 10) + '0';	// Convert to ASCII and get next digit
	} while ((n /= 10) > 0);	// Delete it
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';				// Null terminate
	reverse(s);					// Reverse string
}

// nega_itoa: 
// Same as the above, but where recording the sign, we check for a 
// positive number instead, if so invert 'n's sign. On the do-while loop, 
// we invert the relational operator. For the conversion formula, 
// we convert positive to negative instead, so we can handle INT_MIN.
void nega_itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) > 0)		// Record the sign
		n = -n;				// Invert the sign
	i = 0;
	do {	// Generate digits in reverse order
		s[i++] = '0' - (n % 10);// Convert to ASCII and get next digit
	} while ((n /= 10) < 0);	// Delete it from n
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';				// Null terminate
	reverse(s);					// Reverse string
}


// reverse: reverse a string
void reverse(char s[])
{
	int start, end;
	char buffer;	// Temporary buffer
	for (start = 0, end = strlen(s) - 1; start < end; start++, end--)
	{
		buffer = s[start];
		s[start] = s[end];
		s[end] = buffer;
	}
}
