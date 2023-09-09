/* Exercise 5.02 Write getfloat , the floating-point analog of 
 * getint . What type does getfloat return as its function val */
#include <ctype.h>
#include <math.h>
#include <stdio.h>

/* Constants */
#define SEP             "=====================================================\n"
#define BUFFER_SIZE     128

/* Funcion Prototypes */
int getfloat(double *pf);
int getch(void);
void ungetch(int c);

/* Global Variables */
int buffer[BUFFER_SIZE];    /* buffer for ungetch */
int buffer_p = 0;           /* next free position in buffer */


/* Driver Code */
int main(void)
{
    double return_float;
    double f;

    // Render UI
    printf("Exercise 5-2: getfloat()\n");
    printf(SEP);

    do {
        fputs("Enter number: ", stdout);
        fflush(stdout);
        return_float = getfloat(&f);
        printf("You entered: %.3f (%g)\n", f, return_float);
    } while (return_float > 0);

    if (return_float == EOF)
        printf("EOF\n");
    else 
        printf("not a number\n");

    return (0);
}


/* getfloat: get a (possibly pushed back) floating-point number */
int getfloat(double *pf)
{
    int c;
    int sign;
    int digits;     
    int fraction;

    /* skip white space */
    while (isspace(c = getch()))
        ;

    /* Handle invalid characters */
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
    {
        ungetch(c);
        return (0);
    }

    /* Handle sign */
    sign = (c == '-') ? -1 : 1;         /* set sign */
    if (c == '-' || c == '+')           /* minus or plus sign? */
    {
        c = getch();                    /* get next character */
        if (!isdigit(c) && c != '.')    /* not a number? */
        {
            if (c == EOF)               /* end of file? */
                return (EOF);
            else                        /* not a number */
            {
                ungetch(c);              /* push character back */
                return (0);
            }
        }
    }

    /* Handle valid number */
    *pf = 0;
    digits = 0;
    fraction = 0;
    for ( ; isdigit(c) || c == '.'; c = getch())
    {
        if (c == '.')
            fraction = 1;
        else
        {
            if (!fraction)
                *pf = 10 * *pf + (c - '0');
            else
            {
                *pf = *pf + ((c - '0') / pow(10, fraction));
                fraction++;        
            }
            digits++;
        }
    }
   
    *pf *= sign;             /* apply sign */

    if (c != EOF)         
        return EOF;          /* return EOF */
    else                   
    {
        ungetch(c);          /* ungetch invalid input */
        return (digits) ? c : 0;
    }
}


/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return (buffer_p > 0) ? buffer[--buffer_p] : getchar();
}

/* ungetch: push a character back on input */
void ungetch(int c)
{
    if (buffer_p >= BUFFER_SIZE)
        printf("ungetch: too many characters\n");
    else
        buffer[buffer_p++] = c;
}
