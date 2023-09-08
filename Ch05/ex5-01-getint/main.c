/* Exercise 5-1. As written, getint treats a + or - not followed by a digit as a 
 * valid representation of zero. Fix it to push such a character back on the input. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SEP             "=====================================================\n"
#define BUFFER_SIZE     128
#define MAX_INTS        8

/* Function Prototypes */
int getint(int *pn);
int getch(void);
void ungetch(int c);

/* Global Variables */
int buffer[BUFFER_SIZE];    /* buffer for ungetch */
int buffer_p = 0;

int main(void)
{
    int n, i;
    int ints[MAX_INTS];

    // Render UI
    printf("Exercise 5-1: getint\n");
    printf(SEP);

    printf("Enter up to %d integers:\n", MAX_INTS);
    for (n = 0; n < MAX_INTS && getint(&ints[n]) != EOF; n++)
        ;

    printf("Processed %d integers:\n", n);
    for (i = 0; i < n; i++) 
        printf("ints[%d] = %d\n", i, ints[i]);

    return (0);
}


/* getint_zero: get an integer */
int getint(int *pn)
{
    int c;
    int sign;

    *pn = 0;    /* Set pointer to the beginning of the string */
    while (isspace(c = getch()))    /* skip white space */
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {                   /* not a number */
        ungetch(c);     /* push character back into input stream */
        return (0);
    }

    sign = (c == '-') ? -1 : 1;     /* set sign */
    if (c == '-' || c == '+')
    {
        c = getch();
        if (!isdigit(c) && c != EOF)
        {
            ungetch(c);
            return (0);
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');     /* convert to integer */
   
    *pn *= sign;         /* return sign */

    if (c != EOF)        /* ungetch invalid input */       
        ungetch(c);

    return c;
}


/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return (buffer_p > 0) ? buffer[--buffer_p] : getchar();
}

/* ungetch: push a character back on the input */
void ungetch(int c)
{
    if (buffer_p >= BUFFER_SIZE)
        printf("ungetch error: too many characters\n");
    else
        buffer[buffer_p++] = c;
}
