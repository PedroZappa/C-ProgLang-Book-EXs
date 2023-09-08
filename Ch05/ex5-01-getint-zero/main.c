/* */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SEP             "=====================================================\n"
#define BUFFER_SIZE     128

/* Function Prototypes */
int getint_zero(char *pn);
int getch(void);
void ungetch(int c);

/* Global Variables */
int buffer[BUFFER_SIZE];
int buffer_p;

int main(void)
{
    int ints[6] = { -7, 42, INT_MIN, INT_MAX };
    int ints_n = sizeof(ints) / sizeof(ints[0]);
   
    // Render UI
    printf("Exercise 5-1: getint_zero\n");
    printf(SEP);
    for (int i = 0; i < ints_n; i++)
    {
        printf("ints[%d] = %d\n", i, ints[i]);
    }

    return (0);
}


/* getint_zero: get an integer */
int getint_zero(char *pn)
{
    int c;
    int sign;

    while (isspace(c = getch()))    /* skip white space */
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);     /* push character back into input stream */
        return (0);
    }

    sign = (c == '-') ? -1 : 1;     /* set sign */

    while (c == '+' || c == '-')
    {
        c = getch();
        if (!isdigit(c))
        {
            ungetch(sign == -1 ? '-' : '+');
            return (0);
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = *pn * 10 + (c - '0');     /* convert to integer */

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return 0;
}


/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return ((buffer_p > 0) ? buffer[--buffer_p] : getchar());
}

/* ungetch: push a character back on the input */
void ungetch(int c)
{
    if (buffer_p >= BUFFER_SIZE)
        printf("ungetch error: too many characters\n");
    else
        buffer[buffer_p++] = c;
}
