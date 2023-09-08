/* Exercise 4.12 : Adapt the ideas of printd to write a recursive 
 * version of itoa ; that is, convert an integer into a string by 
 * calling a recursive routine. */
#include <limits.h>     /* INT_MAX & INT_MIN */
#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* abs() */
#include <string.h>     /* strlen() */

/* Constants */
#define SEP         "===================================\n"
#define MAX_LEN    128

/* Function Prototypes */
void itoa_recursive(int n, char *str, int base);

int main(void)
{
    char str[MAX_LEN];                            /* to store converted strings */
    int ints[] = { 1, -7, 42, INT_MAX, INT_MIN };                     /* integers to convert */
    int ints_n = sizeof(ints) / sizeof(ints[0]);    /* number of integers in array */
    int i;                                          /* loop counter */

    /* Render Tests*/
    printf("\tatoi_recursive()\n" SEP); 
    printf("Integers converted into strings:\n");
    for (i = 0; i < ints_n; ++i)
    {
        itoa_recursive(ints[i], str, 10);
        printf("%11d\t->\t%s \n", ints[i], str);
    }
    printf(SEP);
    printf("\tUps: Can't print MIN_INT\n");

    return (0); 
}

/* itoa_recursive : convert an integer into a string recursively */
void itoa_recursive(int n, char *str, int base)
{
    static int i;
    //static int sign;

    i = 0;
    if (n < 0)
    {
        str[i++] = '-';     /* append minus sign */
        n = -n;             /* reset sign in anticipation of next non-recursive call */
    }
    if ((n / base) != 0)     /* recursive call */
        itoa_recursive((n / base), str, base);
    
    str[i++] = abs(n % base) + '0';     /* append digit */
    str[i] = '\0';                      /* terminate string */
}

