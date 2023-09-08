/* Exercise 4.12 : Adapt the ideas of printd to write a recursive 
 * version of itoa ; that is, convert an integer into a string by 
 * calling a recursive routine. */
#include <stdio.h>
#include <string.h>

/* Constants */
#define MAX_STR     100

/* Function Prototypes */
void itoa_recursive(int n, char *str, int base);
void reverse(char *str);

int main(void)
{
    return (0); 
}

void itoa_recursive(int n, char *str, int base)
{
    // static int i;
    // static int sign;

    // if (n < 0)
    // {
    //     n *= -1;
    //     abs = EOF;
    // }

    if (n < base)
        *str++ = n + '0';
    else
    {
        itoa_recursive(n / base, str, base);
        *str++ = n % base + '0';
    }
}

/* reverse : reverse a string */
void reverse(char *str)
{
    int c = 0;
    int start, end;
    
    for (start = 0, end = strlen(str)-1; start < end; start++, end--)
    {
        c = str[start];
        str[start] = str[end];
        str[end] = c;
    }

}
