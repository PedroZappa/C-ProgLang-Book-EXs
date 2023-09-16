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
    int c;                  /* Current input char */
    int col;                /* Column index */
    int spaces;             /* Number of spaces ... */
    int tabs[MAX_TABS];     /* Array of tab stop lengths */
    int tabs_i;             /* tabs[] index Iterator */ 
    int tab_base;           /* Base tab stop */
    int nxt_ts;             /* Next tab stop */
    int nxt_def_ts;         /* Next default tab stop */

    /* Parse user input */
    /* Loop through args */
        /* return if too many args */
        /* filter for ints with atoi() */
            /* store args in tabs[] */
    
    /* If there tabs[] has values */
        /* Sort the array */
        /* Get largest value into tab_base */
        /* Add the TAB formula to tab_base */
        /* Divide tab_base by DEF_TABSTOP */ 


    /* Get lines */ 
        /* for every char that is not a space */
            /* */

        /* switch through every char */
            /* Count spaces */
            /* If \n reset col and tabs_i & print char */
            /* If tab ... */
                /* Find next custom tab */
                /* if next custum tab is not too big */
                    /* subtract current col from custom tab store it in nxt_ts */
                /* add spaces to nxt_ts */
                
            /* Default, print char */


    return 0;
}
