/* Exercise 5.11a : Entab with custom tab stops
 * The args interpreted as a squence of tab stop lengths */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define SEP             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
#define DEF_TABSTOP     8           /* Default tab stop */
#define MAX_TABS        12          /* Max number of tabs */
#define MAX_LEN         512         /* Max length of line */
#define SPACE		    ' '         /* Space Character */
#define TAB			    '\t'        /* Tab Character */
#define NEW_LINE	    '\n'        /* New Line Character */

/* Function prototypes */
void sort_args(int[], int n);

/* Entab Driver */
int main(int argc, char *argv[])
{
    int i;                  /* Loop index */
    int c;                  /* Current input char */
    int col;                /* Column index */
    int spaces;             /* Number of spaces ... */
    //int tabs[MAX_TABS];     /* Array of tab stop lengths */
    int tabs_i;             /* tabs[] index Iterator */ 
    int tab_base;           /* Base tab stop */
    int nxt_ts;             /* Next tab stop */
    int nxt_def_ts;         /* Next default tab stop */

    int tabs[MAX_TABS] = { 7, 3, 2, 5, 1, 4, 6 };
    sort_args(tabs, MAX_TABS);

    /* Read number of elements in the array */ 
    tabs_i = sizeof(tabs) / sizeof(tabs[0]);

    /* Print array */ 
    for (i = 0; i < tabs_i; i++)
        printf("%d ", tabs[i]);
    printf("\n");

    /* Parse user input */
    /* Loop through args */
        /* return if too many args */
        /* filter for ints with atoi() */
            /* store args in tabs[] */
    
    /* If tabs[] has values */
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

/* sort_args : Sorts args in ascending order
 * using the shell sort algorithm */
void sort_args(int args[], int n)
{
    int i;
    int j;      
    int split;    /* split index */
    int temp;     /* temp variable fr swapping */

    /* Partition the array in half while each
     * element is greater than 0 */
    for (split = n / 2; split > 0; split /= 2) {
        /* Loop through left half of array */
        for (i = split; i < n; i++) 
        {
            /* Loop through right half of array */
            for (j = i - split; j >= 0 && args[j] > args[j + split]; j -= split) 
            {
                temp = args[j];
                args[j] = args[j + split];
                args[j + split] = temp;
            } 
        }
    }
}
