/* Eercise 5-7. Rewrite readlines to store lines in an array 
 * supplied by main, rather than calling alloc to maintain 
 * storage. How much faster is the pro- gram? */ 
#include <stdio.h>
#include <string.h>

#define MAXLINES    1024
#define MAXLEN      512

/* Global variables */
char *lineptr[MAXLINES];        /* array of pointers to char */
char lines[MAXLINES][MAXLEN];   /* array of lines */

/* Function Prototypes */
int ft_getline(char *s, int i);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);
void swap(char *v[], int left, int right);

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

/* ft_getline() - read a line into s, return length */
int ft_getline(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)    
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* readlines() - read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p;
}
