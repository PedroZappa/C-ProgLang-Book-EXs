/* Exercise 5-7. Rewrite readlines to store lines in an array 
 * supplied by main, rather than calling alloc to maintain 
 * storage. How much faster is the pro- gram? */ 
#include <stdio.h>
#include <string.h>

#define SEP         "==============================\n"
#define MAXLINES    1024
#define MAXLEN      512

/* Global variables */
char *lineptr[MAXLINES];        /* array of pointers to char */
char lines[MAXLINES][MAXLEN];   /* array of lines */

/* Function Prototypes */
int ft_getline(char *s, int i);
int ft_readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);
void swap(char *v[], int left, int right);

int main()
{
    int nlines;             /* number of input lines */

    /* Render Title */
    printf(SEP "Lines to sort: \n" SEP);

    if ((nlines = ft_readlines(lineptr, MAXLINES)) >= 0)
    {
        qsort(lineptr, 0, nlines-1);        /* Sort lines */
        printf(SEP "Sorted lines:\n" SEP);  /* Print Header */
        writelines(lineptr, nlines);        /* Print lines */
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
    int c, len;

    len = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[len++] = c;
    if (c == '\n')
        s[len++] = c;
    s[len] = '\0';

    return (len);
}

/* readlines() - read input lines */
int ft_readlines(char *lineptr[], int maxlines)
{
    int i, len, nlines;

    /* Initialize lineptr to NULL */
    for (i = 0; i < MAXLINES; i++)
        lineptr[i] = NULL;

    nlines = 0;
    while ((len = ft_getline(lines[nlines], MAXLEN)) > 0)
    {
        if (nlines >= maxlines)
            return (-1);
        else
        {
            lines[nlines][len-1] = '\0';        /* Delete \n */
            lineptr[nlines] = lines[nlines];    /**/ 
            nlines++;                           /* Increment nlines */
        }
    }
    return (nlines);
}

/* writelines() - write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* qsort() - quick sort 
 * *lineptr[] : is the array of pointers to char;
 * left & right : are the start and end indices of the array
 * to be sorted;
 * */
void qsort(char *lineptr[], int left, int right)
{
    int i, last;

    if (left >= right)  /* do nothing if array is empty */
        return;         
    /* swap the first and middle elements */
    /* ((left+right)/2) selects pivot for quicksort */
    swap(lineptr, left, (left+right)/2);
    last = left;    /* store pivot position */ 
    /* loop through the array */
    for (i = left+1; i <= right; i++)
        /* if the current element is smaller than the pivot */
        if (strcmp(lineptr[i], lineptr[left]) < 0)
            swap(lineptr, ++last, i);
    swap(lineptr, left, last);
    /* Recursively sort the two subarrays */
    qsort(lineptr, left, last-1);
    qsort(lineptr, last+1, right);
}

/* swap() - swap two elements */
void swap(char *v[], int left, int right)
{
    char *temp;
 
    temp = v[left];
    v[left] = v[right];
    v[right] = temp;
}
