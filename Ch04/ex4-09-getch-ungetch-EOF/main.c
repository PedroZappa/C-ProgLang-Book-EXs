/* Exercise 4-9. Our getch and ungetch do not handle 
 * a pushed-back EOF correctly. Decide what their 
 * properties ought to be if an EOF is pushed back, 
 * then implement your design. */
#include <stdio.h>

// Function prototypes
int getch(void);
void ungetch(int c);

// Global variables
int buffer = '\0';      // buffer for ungetch
/* As requested by the exercise, ungetch only handles 
 * a single char in the buffer */


int main(void)
{
    ungetch('z');           // push back 'z'
    printf("%c", getch());  // print 'z'

    ungetch(EOF);           // push back EOF
    printf("%c", getch());  // print 1st char of input

    return (0);
}


// getch : if buffer has a char, return it.
// Otherwise, return getchar()
int getch(void)
{
    int c;

    if (buffer != '\0')
    {
        c = buffer;
        buffer = '\0';
        return (c);
    }
    return (getchar());
}

// ungetch : add c to the buffer
void ungetch(int c)
{
    if (c != EOF)
        buffer = c;
}
