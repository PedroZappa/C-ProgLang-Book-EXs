/* Extend atof to handle scientific notation of the form 123.45e-6 
 * where a floating-point number may be followed by e or E and an 
 * optionally signed exponent. */
#include <stdio.h>

#define SEP "=======================0\n"
#define IS_DIGIT(c)	((c) >= '0' && (c) <= '9')
#define IS_SPACE(c)	((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')
#define IS_SIGN(c)	((c) == '-' || (c) == '+')

double atofex(char *s);

int main(int argc, char *argv[])
{
	char *s = "123.45e-6";
	char *strs[] = { "123.45", "-123.456E2", "123e-6", "123e+2", NULL};
	double val;			// converted value of 's'
	int i;

	// Get user input
	if (argc > 1)
		s = argv[argc - 1];

	printf("atofex(char *s)\n");
	printf(SEP);

	printf("Input:  %s\n", s);

	val = atofex(s);
	printf("Output: %3.3f\n", val);
	printf(SEP);

	for (int i = 0; strs[i]; i++)
	{
		printf("Input:  %s\n", strs[i]);
		val = atofex(strs[i]);
		printf("Output: %f\n", val);
		printf(SEP);
	}

	return 0;
}

double atofex(char *s)
{
	double val;			// converted value of 's'
	double power;		// power of 'base'
	double base;		// base of 10	
	double p;			// power
	int exp;			// exponent 
	int sign;			// 1 for positive, -1 for negative
	int i;				// index into string

	for (i = 0; IS_SPACE(s[i]); i++)		// Skip leading whitespace
		;
	sign = (s[i] == '-') ? -1 : 1;			// Set sign
	if (s[i] == '-' || s[i] == '+')			// Increment if sign
		++i;
	for (val = 0.0; IS_DIGIT(s[i]); i++)	// convert integer part to val
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')						// Handle decimal point
		i++;
	for (power = 1.0; IS_DIGIT(s[i]); i++)	// convert fractional part to power
	{
		val = 10.0 * val + (s[i] - '0');	// convert fractional part to val
		power *= 10.0;						// update power
	}
	if (s[i] == 'e' || s[i] == 'E')			// Handle exponent
		i++;
	else
		return sign * val / power;

	base = (s[i] == '-') ? 0.1 : 10.0;		// Set base
	if (IS_SIGN(s[i]))						// Handle sign & increment
		i++;
	for (exp = 0; IS_DIGIT(s[i]); i++)	
		exp = 10.0 * exp + (s[i] - '0');	// convert exponent to digits
	for (p = 1; exp > 0; --exp)
		p *= base;

	return ((sign * (val / power)) * p);
}
