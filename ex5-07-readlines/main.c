/* Eercise 5-7. Rewrite readlines to store lines in an array 
 * supplied by main, rather than calling alloc to maintain 
 * storage. How much faster is the pro- gram? */ 
#include <stdio.h>
#include <string.h>

#define MAXLINES    1024
#define MAXLEN      512

/* Function Prototypes */
int getline(char *, int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* Global variables */
char *lineptr[MAXLINES];    /* array of pointers to char */

int main()
{
    int nlines;             /* number of input lines */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return (0);
    }
    else
    {
        printf("error: input too big to sort\n");
        return (1);
    }
}
