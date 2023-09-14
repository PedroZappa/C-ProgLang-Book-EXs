/* Exercise 5.06 : Rewrite appropriate programs from earlier chapters 
 * and exercises with pointers instead of array indexing. Good 
 * possibilities include getline (Chapters 1 and 4), atoi , itoa , and 
 * their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and 
 * strindex and getop (Chapter 4). */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SEP	    	"===============================\n"
#define NUMBER		0
#define MAX     	12
#define MAX_LEN		128
#define BUF_SIZE    128

int     ptr_getline(char *str, int lim);
int     ptr_atoi(char *str);
char   *ptr_itoa(int val, char *str);
void    ptr_reverse(char *str);
int     ptr_strlen(char *str);
int     ptr_strindex(char *str, char *sub);
char   *ptr_strchr(char *str, int ch);
int     ptr_getop(char *str);
int     getch(void);
void    ungetch(int c);

/* Global Variables */
char buf[BUF_SIZE];     /* buffer for ungetch */
int buf_p = 0;          /* next free position in buf */


int main(void)
{
    int i;                      // Loop counter
    char strs[MAX][MAX] = {0};  // Array of strings
    int strs_len;
	int ints[MAX];
    int ints_len;
    int str_len;                // Length of input string
    // char conv_str[MAX_LEN];     // String to convert
    int conv_int;               // Converted integer

    /* Render UI */
    printf("\tPointer Funk'z\n" SEP);

    /* Get lines */
    i = 0;
    while ((str_len = ptr_getline(strs[i++], MAX)) > 0)
        ;
    printf(SEP);

    /* Convert lines */
    strs_len = sizeof(strs) / sizeof(strs[0]);
    for (i = 0; i < strs_len; i++)
    {
        conv_int = ptr_atoi(strs[i]);
        ints[i] = conv_int;
    }

    ints_len = sizeof(ints) / sizeof(ints[0]);
    for (i = 0; i < ints_len; i++)
    {
        ptr_atoi(strs[i]);
        printf("[%d] : '%d'\n", i, ints[i]);
    }

    /* Print saved lines */
    // conv_int = 0;
    // for (i = 0; strs[i] && i < MAX; i++)
    // {
    //     printf("[%d] : '%s'\n", i, strs[i]);
    //     // if str has digits, convert it to int
    //     if ((conv_int = ptr_atoi(strs[i])) > 0)
    //     {
    //         printf("ptr_atoi : %d\n", conv_int);
    //         ptr_itoa(conv_int, conv_str);
    //         printf("ptr_itoa : '%s'\n", conv_str);
    //     }
    // }

    return (0);
}

// getline : read a line into s, return length
int ptr_getline(char *s, int lim)
{
    int c;              // current character
    char *ps;           // pointer to next character in s

    ps = s;             // start at beginning of s
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *ps++ = c;      // store characters in ps
    if (c == '\n')  
        *ps = '\0';      // overwrite newline with null character

    return (ps - s);
}

// atoi : convert string to integer
int ptr_atoi(char *str)
{
    int n;
    int sign;

    while (isspace(*str))               // skip white space
        str++;
    sign = (*str == '-') ? -1 : 1;      // set sign
    if (*str == '+' || *str == '-')     // skip extra signs
        str++;
    for (n = 0; isdigit(*str); str++)
        n = 10 * n + (*str - '0');      // convert digit
    *str = '\0';                        // null-terminate
    return (n * sign);                  // apply sign to n, return result
}

// itoa : convert integer to string
// and supports INT_MIN
char *ptr_itoa(int num, char *str)
{
    char *pstr = str;              // Point to start of string
    int isNeg = 0;                 // Sign of number   
    
    // Check for negative numnber
    if (num < 0)
    {
        isNeg = 1;
        num = -num;
    }
    // Convert num to string
    do                     
    {   
        *pstr++ = num % 10 + '0';  // convert & get next digit
    } while ((num /= 10) > 0);             // delete it

    // If number is negative, append '-'
    if (isNeg)
        *pstr++ = '-';

    *pstr = '\0';                   // null-terminate string
    ptr_reverse(str);               // reverse string

    return (str);
}

// reverse : reverse a string
void ptr_reverse(char *str)
{
    int start, end;
    char buffer;

    start = 0;
    end = ptr_strlen(str) - 1;
    while (start < end)
    {
        buffer = *(str + start);
        *(str + start) = *(str + end);
        *(str + end) = buffer;
        start++;
        end--;
    }
}

// strlen : return length of string
int ptr_strlen(char *str)
{
    char *pstr;

    pstr = str;
    while (*pstr++)
        ;
    return (pstr - str);
}

// strindex : return first index of substring in string
int ptr_strindex(char *str, char *sub)
{
    char *pstr;       // pointer to start of str
    char *ppstr;      // pointer to pointer to str
    char *psub;       // pointer to start of sub

    if (!*sub)
        return (0);
    pstr = str;
    while ((pstr = ptr_strchr(pstr, *sub)) != NULL)
    {
        psub = sub;
        ppstr = pstr;
        while (*psub && *ppstr == *psub)  // while characters match
        {
            psub++;
            ppstr++;
        }
        if (*psub == '\0')
            return (pstr - str);
        pstr++;
    }
    return (-1);
}

// strchr : return pointer to first occurrence of character in string
char *ptr_strchr(char *str, int c)
{
    char ch = c;

    while (*str++ != ch)    // while current value of str is not equal to ch
        if (*str == '\0')
            return (NULL);
    return (str);           // return pointer to first occurrence
}

// getop : get next operator from string
int ptr_getop(char *str)
{
    int c;

    while ((*str++ = c = getch()) == ' ' || c == '\t')  // skip white space
        ;
    *str = '\0';                            // null-terminate
    
    // Handle Operators
    if (!isdigit(c) && c != '.')
        return (c);     // return operator
    
    // Handle Numbers
    if (isdigit(c))    
        while (isdigit(*str++ = c = getch()))
            ;           // collect integer part
    if (c == '.')
        while (isdigit(*str++ = c = getch()))
            ;           // collect fractional part
    *--str = '\0';      // null-terminate

    if (c != EOF)       // if not end of file
        ungetch(c);     // Put non-digit back
    return (NUMBER);
}

// getch : get a (possibly pushed back) character
int getch(void)
{
    return (buf_p > 0) ? buf[--buf_p] : getchar();
}

// ungetch : push character back on input
void ungetch(int c)
{
    if (buf_p >= BUF_SIZE)
        printf("ungetch: too many characters\n");
    else
        buf[buf_p++] = c;
}
