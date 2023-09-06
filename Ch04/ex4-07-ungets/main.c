/* Exercise 4-7.  Write a routine ungets(s) that will 
 * push back an entire string onto the input. */
#include <stdio.h>
#include <string.h>

/* Constants */
#define BUFSIZE 100

/* Function Prototypes */
void ungets(char *s);   // push back a string
int getch(void);        // get a character
void ungetch(int c);    // push a character back

/* Globals */
char buffer[BUFSIZE];   /* buffer for ungetch */
int buf_pos = 0;        /* next free position in buffer */


/* Main Driver */
int main(void) 
{
    int c;              /* character */
    char *str = "Zedro 42 Test C-ProgLang-Book\n";

    ungets(str);
    while ((c = getch()) != EOF)
        putchar(c);
    return 0;
}


/* ungets : push back a string */
void ungets(char *s)
{
    size_t len = strlen(s);     /* get length of string */

    if (BUFSIZE-buf_pos >= len)  /* enough space in buffer */
        while (len > 0)         /* push back characters, LIFO */
            ungetch(s[--len]);
}


/* getch : get a character */
int getch(void)
{
    return (buf_pos > 0) ? buffer[--buf_pos] : getchar();
}

/* ungetch : push a character back on input */
void ungetch(int c)
{
    if (buf_pos >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buffer[buf_pos++] = c;
}
