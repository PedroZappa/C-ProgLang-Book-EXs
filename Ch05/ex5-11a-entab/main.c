/* Exercise 5.11a : Entab with custom tab stops
 * The args interpreted as a squence of tab stop lengths */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define SEP             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
#define DEF_TABSTOP     8
#define MAX_TABS        1024
#define MAX_LEN         512
#define SPACE		    ' '
#define TAB			    '\t'
#define NEW_LINE	    '\n'

/* Function prototypes */
void sort_args(int[], int n);

/* Entab Driver */
int main(int argc, char *argv[])
{
    int c;  
    int i;                  /* Tab Index Iterator */ 
    int nxt_ts;             /* Next tab stop */
    int nxt_def_ts;         /* Next default tab stop */
    int col;                /* Column index */
    int spaces;             /* Number of spaces ... */
    int tab_c[MAX_TABS];



    return 0;
}
