/* Suppose there will never be more than one character of pushback. 
 * Modify getch and ungetch accordingly. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1       // buffer for a single character

// Function prototypes
int getch(void);        // get a character
void ungetch(int c);    // push character back into stack

// Global variables
char buffer[BUFSIZE];   // buffer for ungetch
int buffer_p = 0;       // next free position in buffer

// Driver code
int main(void)
{
    int c;              // character

    printf("Enter a string: ");

    while ((c = getch()) != EOF)    // get characters until EOF
    {
        putchar(c);
        if (isdigit(c))             // if character is a digit
            ungetch(c);             // push character back
    }
    printf("\n");

    // Print value stored in buffer
    printf("Buffer contents: %i the ASCII value of %i\n", buffer[0], atoi(buffer));

    return (0);
}

// getch - get a character from the keyboard
int getch(void)
{
    return (buffer_p > 0) ? buffer[0] : getchar();
}

// ungetch - push a character back on the input stream
void ungetch(int c)
{
    if (buffer_p >= BUFSIZE)
        printf("ungetch: overflowed the single character stack\n");
    else
        buffer[0] = c;
}
