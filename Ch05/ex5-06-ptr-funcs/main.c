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
#define MAX     	9
#define MAX_STRS   	12
#define MAX_LEN		128
#define BUF_SIZE    128

int     ptr_getline(char *str, int lim);
int     ptr_atoi(char *str);
char   *ptr_itoa(int val, char *str);
void    ptr_reverse(char *str);
int     ptr_strlen(char *str);
int     ptr_strindex(char *str, char *sub);
char   *ptr_strchr(char *str, int ch);
char   *ptr_strcpy(char *dest, char *src);

int main(void)
{
    int i;                                  // Loop counter
    char in_strs[MAX][MAX_LEN] = {0};     // Array of strings
    char strs[MAX][MAX_LEN] = {0};     // Array of strings
    int strs_len;                           // Length of array of strs
    int str_len;                            // Length of input string
	int ints[MAX];
    int ints_len;                           // Length of ints

    /* Render Title */
    printf("\tPointer Funk'z\n" SEP);

    /* Get lines */
    i = strs_len = 0;
    while ((str_len = ptr_getline(in_strs[i++], MAX_LEN)) > 0)
        strs_len++;
    printf(SEP);

    /* Tests */
    /* Print input lines & length */
    for (i = 0; i < strs_len; i++)
    {
        printf("in_strs[%d] : '%s'\t[len: %d]\n", i, in_strs[i], ptr_strlen(in_strs[i]));
        ptr_strcpy(strs[i], in_strs[i]);
    }
    printf(SEP);
    

    /* ptr_atoi() */
    printf("ptr_atoi()\n");
    for (i = 0; i < strs_len; i++)
    {
        ints[i] = ptr_atoi(strs[i]);
    }
    ints_len = strs_len;
    for (i = 0; i < ints_len; i++)
    {
        printf("ints[%d] : '%d'\n", i, ints[i]);
    }
    printf(SEP);


    /* ptr_reverse() */
    printf("ptr_reverse()\n");
    for (i = 0; i < strs_len; i++)
    {
        ptr_reverse(strs[i]);
        printf("strs[%d] : '%s'\n", i, strs[i]);
    }
    printf(SEP);
    
    /* ptr_itoa() */
    printf("ptr_itoa()\n");
    for (i = 0; i < strs_len; i++)
    {
        ptr_itoa(ints[i], strs[i]);
        printf("strs[%d] : '%s'\n", i, strs[i]);
    }
    printf(SEP);

    /* strindex() */
    printf("strindex()\n");
    for (i = 0; i < strs_len; i++)
    {
        printf("ptr_strindex(in_strs[%d], 'z') : %d\n", i, ptr_strindex(in_strs[i], "z"));
    }
    printf(SEP);

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
    char *pstr = str;
    int buf;

    while (*pstr)       // Point pstr to the end of the string
        pstr++;  
    pstr--;             // points p to the last character of the string
    while (str <= pstr)
    {                   // Do the swap
        buf = *str;
        *str = *pstr;
        *pstr = buf;
        str++;
        pstr--;
    }
}

// strlen : return length of string
int ptr_strlen(char *str)
{
    char *pstr = str;

    while (*pstr != '\0')
        pstr++;
    return (pstr - str);
}

// strindex : return first index of substring in string
int ptr_strindex(char *str, char *sub)
{
    char *pstr = str;       // pointer to start of str
    char *psub = sub;       // pointer to start of sub

    if (!*sub)
        return (-1);

    while (*pstr)
    {
        if (*pstr == *psub)
        {
            if (*pstr++ == *psub++)
                return (pstr - str-1);
        }
        pstr++;
    }
    return (-1);
}

/* strcpy : copy string src to dest */
char *ptr_strcpy(char *dest, char *src)
{
    char *backup = dest;
    while ((*dest++ = *src++));
    return (backup);
}

