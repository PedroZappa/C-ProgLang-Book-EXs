/* Exercise 2-1. Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned, by printing appropriate values from standard headers and by direct computation. Harder if you compute them: determine the ranges of the various floating-point types. */
#include <float.h>
#include <limits.h>
#include <math.h>	// for pow() and powl()
#include <stdio.h>

int main(void)
{
	printf("\tC Data Type Ranges:\n\n");

	/* unsigned char */
	unsigned char uchar_min, uchar_max;
	uchar_min = uchar_max = 0;
	--uchar_max;	//cause max3 to underflow to get 'unsigned char' max
	printf("'unsigned char' range:\t\t%hu - %hu\n", uchar_min, uchar_max);
	printf("from <limits.h>:\t\t%d - %d\n\n", 0, UCHAR_MAX);

	/* char */
	char char_min, char_max;
	char_min = char_max = (uchar_max / 2);		/* int division gets max */
	char_min *= -1;		// get min by multiplying by -1
	--char_min;			// and subtracting 1
	printf("'char' range:\t\t\t%hi - %hi\n", char_min, char_max);
	printf("from <limits.h>:\t\t%i - %i\n\n", SCHAR_MIN, SCHAR_MAX);

	/* signed char */
	signed char schar_min, schar_max;
	schar_min = schar_max = (uchar_max / 2);	/* int division gets max */
	schar_min *= -1;		// get min by multiplying by -1
	--schar_min;			// and subtracting 1
	printf("'signed char' range:\t\t%hd - %hd\n", schar_min, schar_max);
	printf("from <limits.h>:\t\t%i - %i\n\n", SCHAR_MIN, SCHAR_MAX);

	printf("===================================\n\n");

	/* unsigned short */
	unsigned short ushort_min, ushort_max;
	ushort_min = ushort_max = 0;
	--ushort_max;	//cause underflow to get 'unsigned short' max
	printf("'unsigned short' range:\t\t%hu - %hu\n", ushort_min, ushort_max);
	printf("from <limits.h>:\t\t%d - %d\n\n", 0, USHRT_MAX);

	/* unsigned short int */
	unsigned short int ushort_int_min, ushort_int_max;
	ushort_int_min = ushort_int_max = 0;
	--ushort_int_max;	//cause underflow to get 'unsigned short int' max
	printf("'unsigned short int' range:\t%hu - %hu\n", ushort_int_min, ushort_int_max);
	printf("from <limits.h>:\t\t%d - %d\n\n", 0, USHRT_MAX);

	/* short */
	short short_min, short_max;
	short_min = short_max = (ushort_max / 2);	/* int division gets max */
	short_min *= -1;		// get min by multiplying by -1
	--short_min;			// and subtracting 1
	printf("'short' range:\t\t\t%hi - %hi\n", short_min, short_max);
	printf("from <limits.h>:\t\t%i - %i\n\n", SHRT_MIN, SHRT_MAX);

	/* signed short */
	signed short sshort_min, sshort_max;
	sshort_min = sshort_max = (ushort_max / 2);	/* int division gets max */
	sshort_min *= -1;		// get min by multiplying by -1
	--sshort_min;			// and subtracting 1
	printf("'signed short' range:\t\t%hd - %hd\n", sshort_min, sshort_max);
	printf("from <limits.h>:\t\t%i - %i\n\n", SHRT_MIN, SHRT_MAX);

	/* signed short int */
	signed short int sshort_int_min, sshort_int_max;
	sshort_int_min = sshort_int_max = (ushort_int_max / 2);
	sshort_int_min *= -1;	// get min by multiplying by -1
	--sshort_int_min;		// and subtracting 1
	printf("'signed short int' range:\t%hd - %hd\n", sshort_int_min, sshort_int_max);
	printf("from <limits.h>:\t\t%i - %i\n\n", SHRT_MIN, SHRT_MAX);

	printf("===================================\n\n");

	/* unsigned */
	unsigned unsigned_min, unsigned_max;
	unsigned_min = unsigned_max = 0;
	--unsigned_max;		// cause underflow to get 'unsigned' max
	printf("'unsigned' range:\t\t%u - %u\n", unsigned_min, unsigned_max);
	printf("from <limits.h>:\t\t%u - %u\n\n", 0, UINT_MAX);

	/* unsigned int */
	unsigned int uint_min, uint_max;
	uint_min = uint_max = 0;
	--uint_max;			// cause underflow to get 'unsigned int' max
	printf("'unsigned int' range:\t\t%u - %u\n", uint_min, uint_max);
	printf("from <limits.h>:\t\t%u - %u\n\n", 0, UINT_MAX);

	/* signed */
	signed signed_min, signed_max;
	signed_min = signed_max = (unsigned_max / 2);	/* int division gets max */
	signed_min *= -1;	// get min by multiplying by -1
	--signed_min;
	printf("'signed' range:\t\t\t%d - %d\n", signed_min, signed_max);
	printf("from <limits.h>:\t\t%d - %d\n\n", INT_MIN, INT_MAX);

	/* int */
	int int_min, int_max;
	int_min = int_max = (unsigned_max / 2);			/* int division gets max */
	int_min *= -1;	// get min by multiplying by -1
	--int_min;		// and subtracting 1
	printf("'int' range:\t\t\t%d - %d\n", int_min, int_max);
	printf("from <limits.h>:\t\t%d - %d\n\n", INT_MIN, INT_MAX);

	/* signed int */
	signed int sint_min, sint_max;
	sint_min = sint_max = (uint_max / 2);			/* int division gets max */
	sint_min *= -1;	// get min by multiplying by -1
	--sint_min;		// and subtracting 1
	printf("'signed int' range:\t\t%d - %d\n", sint_min, sint_max);
	printf("from <limits.h>:\t\t%d - %d\n\n", INT_MIN, INT_MAX);

	printf("===================================\n\n");

	/* unsigned long */
	unsigned long ulong_min, ulong_max;
	ulong_min = ulong_max = 0;
	--ulong_max;		// cause underflow to get 'unsigned long' max
	printf("'unsigned long' range:\t\t%lu - %lu\n", ulong_min, ulong_max);
	printf("from <limits.h>:\t\t%i - %lu\n\n", 0, ULONG_MAX);

	/* unsigned long int */
	unsigned long int ulong_int_min, ulong_int_max;
	ulong_int_min = ulong_int_max = 0;
	--ulong_int_max;	// cause underflow to get 'unsigned long int' max
	printf("'unsigned long int' range:\t%lu - %lu\n", ulong_int_min, ulong_int_max);
	printf("from <limits.h>:\t\t%i - %lu\n\n", 0, ULONG_MAX);

	/* long */
	long long_min, long_max;
	long_min = long_max = (ulong_max / 2);			/* int division gets max */
	long_min *= -1;	// get min by multiplying by -1
	--long_min;		// and subtracting 1
	printf("'long' range:\t\t\t%ld - %ld\n", long_min, long_max);
	printf("from <limits.h>:\t\t%ld - %ld\n\n", LONG_MIN, LONG_MAX);

	/* long int */
	long int long_int_min, long_int_max;
	long_int_min = long_int_max = (ulong_int_max / 2);
	long_int_min *= -1;	// get min by multiplying by -1
	--long_int_min;		// and subtracting 1
	printf("'long int' range:\t\t%ld - %ld\n", long_int_min, long_int_max);
	printf("from <limits.h>:\t\t%ld - %ld\n\n", LONG_MIN, LONG_MAX);
	
	/* signed long */
	signed long slong_min, slong_max;
	slong_min = slong_max = (ulong_max / 2);		/* int division gets max */
	slong_min *= -1;	// get min by multiplying by -1
	--slong_min;		// and subtracting 1
	printf("'signed long' range:\t\t%ld - %ld\n", slong_min, slong_max);
	printf("from <limits.h>:\t\t%ld - %ld\n\n", LONG_MIN, LONG_MAX);

	/* signed long int */
	signed long int slong_int_min, slong_int_max;
	slong_int_min = slong_int_max = (ulong_int_max / 2);
	slong_int_min *= -1;	// get min by multiplying by -1
	--slong_int_min;		// and subtracting 1
	printf("'signed long int' range:\t%ld - %ld\n", slong_int_min, slong_int_max);
	printf("from <limits.h>:\t\t%ld - %ld\n\n", LONG_MIN, LONG_MAX);

	printf("===================================\n\n");

	/* unsigned long long */
	unsigned long long ullong_min, ullong_max;
	ullong_min = ullong_max = 0;
	--ullong_max;		// cause underflow to get 'unsigned long long' max
	printf("'unsigned long long' range:\t%llu - %llu\n", ullong_min, ullong_max);
	printf("from <limits.h>:\t\t%i - %llu\n\n", 0, ULLONG_MAX);

	/* unsigned long long int */
	unsigned long long int ullong_int_min, ullong_int_max;
	ullong_int_min = ullong_int_max = 0;
	--ullong_int_max;	// cause underflow to get 'unsigned long long int' max
	printf("'unsigned long long int' range:\t%llu - %llu\n", ullong_int_min, ullong_int_max);
	printf("from <limits.h>:\t\t%i - %llu\n\n", 0, ULLONG_MAX);

	/* long long */
	long long ll_min, ll_max;
	ll_min = ll_max = (ullong_max / 2);			/* int division gets max */
	ll_min *= -1;	// get min by multiplying by -1
	--ll_min;		// and subtracting 1
	printf("'long long' range:\t\t%lld - %lld\n", ll_min, ll_max);
	printf("from <limits.h>:\t\t%lld - %lld\n\n", LLONG_MIN, LLONG_MAX);

	/* long long int */
	long long int ll_int_min, ll_int_max;
	ll_int_min = ll_int_max = (ullong_int_max / 2);
	ll_int_min *= -1;	// get min by multiplying by -1
	--ll_int_min;		// and subtracting 1
	printf("'long long int' range:\t\t%lld - %lld\n", ll_int_min, ll_int_max);
	printf("from <limits.h>:\t\t%lld - %lld\n\n", LLONG_MIN, LLONG_MAX);

	/* signed long long */
	signed long long sll_min, sll_max;
	sll_min = sll_max = (ullong_max / 2);		/* int division gets max */
	sll_min *= -1;	// get min by multiplying by -1
	--sll_min;		// and subtracting 1
	printf("'signed long long' range:\t%lld - %lld\n", sll_min, sll_max);
	printf("from <limits.h>:\t\t%lld - %lld\n\n", LLONG_MIN, LLONG_MAX);

	/* signed long long int */
	signed long long int sll_int_min, sll_int_max;
	sll_int_min = sll_int_max = (ullong_int_max / 2);
	sll_int_min *= -1;	// get min by multiplying by -1
	--sll_int_min;		// and subtracting 1
	printf("'signed long long int' range:\t%lld - %lld\n", sll_int_min, sll_int_max);
	printf("from <limits.h>:\t\t%lld - %lld\n\n", LLONG_MIN, LLONG_MAX);

	printf("===================================\n\n");

	/* float */
	float float_min, float_max;
	float mantissa = 1.0;
	float_min = pow(2, -126);			// get float min
	for (int i = 1; i < 23; ++i)
		mantissa += pow(2, -i);			// calculate mantissa
	float_max = mantissa * pow(2, 127);	// get float max
	printf("'float' range:\t\t%.1f - %.1f\n", float_min, float_max);
	printf("from <float.h>:\t\t%.1f - %.1f\n\n", FLT_MIN, FLT_MAX);

	return 0;
}
