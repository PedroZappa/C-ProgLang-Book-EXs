// Exercise 3-1. Our binary search makes two tests inside the loop, when one
// would suffice (at the price of more tests outside). Write a version with only one
// test inside the loop and measure the difference in run-time. 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS	42000
#define TIMEOUT			100000
#define SEP				"================================\n"

int binsearch_og(int x, int v[], int n);
int binsearch(int x, int v[], int n);

int main(int argc, char *argv[])
{
	unsigned long ul_clocks, og_ul_clocks;	// Track clock cycles
	clock_t time_diff;						// Track elapsed time
	int found, found_og;					// Search results
	int v[MAX_ELEMENTS];					// Array to search
	int x;									// Search key
	int i;									// Iterator

	// Get user input
	x = 42;
	if (argc > 1)
		x = atoi(argv[1]);

	// Init array with test data
	for (i = 0; i < MAX_ELEMENTS; i++)
		v[i] = i;

	// Render UI
	printf("binsearch( x, v, n )\n");
	printf(SEP);
	printf("x = %d | v[n] | n = %d\n", x, MAX_ELEMENTS);
	printf(SEP);

	// Tests
	// binsearch_og : Measure time taken to search for x in v
	for (i = 0, time_diff = clock(); i < TIMEOUT; ++i)
		found_og = binsearch_og(x, v, MAX_ELEMENTS);
	time_diff = clock() - time_diff;
	ul_clocks = (unsigned long) time_diff;
	printf("binsearch_og()\ttook\t%fs = %ld clocks\n", (double)time_diff / CLOCKS_PER_SEC, ul_clocks);
	if (found_og == -1)
		printf("'%d' not found in 'v[%d]'\n", x, MAX_ELEMENTS);
	else
		printf("To find '%d' at index %d\n", x, found_og);
	printf(SEP);

	// binsearch : Measure time taken to search for x in v
	for (i = 0, time_diff = clock(); i < TIMEOUT; ++i)
		found = binsearch(x, v, MAX_ELEMENTS);
	time_diff = clock() - time_diff;
	ul_clocks = (unsigned long) time_diff;
	printf("binsearch()\ttook\t%fs = %ld clocks\n", (double)time_diff / CLOCKS_PER_SEC, ul_clocks);
	if (found == -1)
		printf("'%d' not found in 'v[%d]'\n", x, MAX_ELEMENTS);
	else
		printf("To find '%d' at index %d\n", x, found);
	printf(SEP);

	return (0);
}


// binsearch:  Reference implementation
int binsearch_og(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;		// Calculate array´s midpoint
		if (x < v[mid])
			high = mid - 1;			// Search in lower half
		else if (x > v[mid])
			low = mid + 1;			// Search in upper half
		else				
			return (mid);			// Match found
	}
	return (-1);					// No match found
}


// binsearch: Single test inside the loop
int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	
	low = 0;
	high = n - 1;
	mid = (low + high) / 2;
	while (low <= high && x != v[mid])
	{
		if (x < v[mid])
			high = mid - 1;			// Search in lower half
		else
			low = mid + 1;			// Search in upper half
		mid = (low + high) / 2;		// Calculate array´s midpoint
	}
	return ((x == v[mid]) ? mid : -1);
}
