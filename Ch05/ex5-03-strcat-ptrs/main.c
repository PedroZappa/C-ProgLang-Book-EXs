/* Exercise 5-3. Write a pointer version of the function 
 * strcat that we showed in Chapter 2: strcat(s,t) copies 
 * the string t to the end of s. */
#include <stdio.h>

#define STRLEN      100

void *ft_strcat(char *s, char *t);

int main(void)
{
    char str1[STRLEN] = "Zedro, ";
    char *str2[] = { "", "42!" };
    int strs_n = sizeof(str2) / sizeof(char *);

    for (int i = 0; i < strs_n; i++)
    {
        ft_strcat(str1, str2[i]);
        printf("%s$\n", str1);

    }

    return 0;
}

void *ft_strcat(char *s, char *t)
{
    if (*s)                 /* if 's' is not null */
        while (*++s)        /* while there is a char in 's' */
            ;
    while ((*s++ = *t++))   /* copy 't' to end of 's' */
        ;
    return s;
}
