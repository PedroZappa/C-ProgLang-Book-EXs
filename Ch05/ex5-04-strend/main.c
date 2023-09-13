/* Exercise 5.04 Write the function strend(s,t) , which returns 1 if the 
 * string t occurs at the end of the string s , and zero otherwise. */ 
#include <stdio.h>
#include <string.h>

#define SEP "===================================\n"

int strend(char *s, char *t);

int main(void)
{
    int i;
    char s[] = "Hello, Zedro!";
    char *t[] = { "world", "Zedro!", "!" };
    int strs_n = sizeof(t) / sizeof(char *);

    // Header
    printf("\tstrend( s, t ):\n" SEP);
    printf("s: %s\n", s);

    for (i = 0; i < strs_n; i++)
        printf("t[%d]: %s (%d)\n", i, t[i], strend(s, t[i]));

    return (0);
}


/* strend(s,t) returns 1 if the string 't' occurs at the end of the 
 * string 's', and zero otherwise */
int strend(char *s, char *t)
{
    int len;

    len = 0;
    for ( ; *s; s++)        /* point to end of s */
        ;
    for ( ; *t; t++)        /* point to end of t */
        len++;              /* take t's length */
    while (len-- >= 0)      /* compare s and t from end to begin */
        if (*s-- != *t--) 
            return 0;       /* not equal */
    return 1;               /* equal */
}   
