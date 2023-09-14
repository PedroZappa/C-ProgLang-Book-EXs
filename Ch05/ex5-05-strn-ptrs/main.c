/* Write versions of the library functions strncpy , strncat , and strncmp , 
 * which operate on at most the first n characters of their argument strings. 
 * For example, strncpy(s,t,n) copies at most n characters of t to s . 
 * Full descriptions from Appendix B:
 *
 * 	char *strncpy(s,ct,n)	copy at most n characters of string ct
 *				to s, return s. Pad with '\0's is ct
 *				has fewer than n characters.
 *	
 *	char *strncat(s,ct,n)	concatenate at most n characters of
 *				string ct to string s, terminate s with
 *				'\0'; return s.
 *
 *	int strncmp(cs,ct,n)	compare at most n characters of string
 *				cs to string ct; return <0 if cs<ct,
 *				0 if cs==ct, or >0 if cs>ct. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SEP     "==============================\n"
#define MAXBUFF 100

char *ft_strncpy(char *s, char *ct, int n);
char *ft_strncat(char *s, char *ct, int n);
int ft_strncmp(char *cs, char *ct, int n);

int main(void)
{
    char *source = "Zedro 42!";          // source string
    char target[MAXBUFF];                // target string
    int i;
    int n;

    n = strlen(source);
    for (i = 1; i <= n; i++)
    {
        printf("ft_strncpy: %s\n", ft_strncpy(target, source, i));
        printf("ft_strncat: %s\n", ft_strncat(target, source, i));
        printf("ft_strncmp: %d\n", ft_strncmp("111 42", "111 43", i));
        printf(SEP);
    }

    return (0);
}


// ft_strncpy : copy at most n characters of ct to s
char *ft_strncpy(char *s, char *ct, int n)
{
    char *ps = s;                       // save original pointer location of s

    while (n > 0 && (*s++ = *ct++))     // copy at most n characters of ct to s
        ;
    while (n-- > 0)                     // pad with '\0'
        *s++ = '\0';                   
    *s = '\0';                          // terminate s with '\0'
    return (ps);
}

// ft_strncat : concatenate at most n characters of ct to s
char *ft_strncat(char *s, char *ct, int n)
{
    char *ps = s;                       // save original pointer location of s
    
    while (*s)                          // Loop through s until '\0'
        s++;                           
    while (n-- > 0 && (*s++ = *ct++))   // concatenate at most n characters of ct to s
        ;
    *s = '\0';                          // terminate s with '\0'
    return (ps);

}

// ft_strncmp : compare at most n characters of cs to ct; return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct
int ft_strncmp(char *cs, char *ct, int n)
{
    if (n <= 0)                         // invalid input
        return (1);
    
    while (n-- > 0)                     // compare at most n characters of cs to ct
    {
        if (*cs != *ct || !*cs || !*ct)
            return (*cs - *ct);
        cs++;
        ct++;
    }
    return (0);
}
