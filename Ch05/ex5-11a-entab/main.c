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

/* Macros */
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

/* Function prototypes */
void sort_args(int[], int n);

/* Entab Driver */
int main(int argc, char *argv[])
{
    int c;                  /* Current input char */
    int col;                /* Column index */
    int blanks_n;             /* Number of spaces ... */
    int tabs[MAX_TABS];     /* Array of tab stop lengths */
    int tabs_i;             /* tabs[] index Iterator Helper */ 
    int tab_base;           /* Base tab stop */
    int nxt_ts;             /* Next tab stop */
    int nxt_def_ts;         /* Next default tab stop */

    //int tabs[MAX_TABS] = { 7, 3, 2, 5, 1, 4, 6 };   /* Array of tab stop lengths */
    //tabs_i = sizeof(tabs) / sizeof(tabs[0]);        /* Get number of elements in the array */ 

    /* Loop through args, convert valid args to ints and store them in tabs[] */
    tabs_i = 0;
    while (--argc > 0)
    {
        if (tabs_i >= MAX_TABS)              /* return if too many args */
            return 1;   
        else if (IS_DIGIT(**++argv))    /* check if the char in arg is a digit */
            tabs[tabs_i++] = atoi(*argv);    /* convert char to int */
        else
            return (2);                 /* invalid arg */
    }
   
    /*Set custom tabstops */
    tab_base = 0;                       /* Will hold fallback tab stop */
    if (tabs_i > 0)                     /* If tabs[] has values */
    {
        sort_args(tabs, tabs_i);        /* Sort input args (tab sizes) */
        tab_base = tabs[tabs_i-1];      /* Get the largest custom tab stop */
        tab_base += DEF_TABSTOP - (tab_base % DEF_TABSTOP); /* gets the next tab stop */    
        tab_base /= DEF_TABSTOP;        /* Gets the base of the number for the operation */ 
    }                                   /*  in the next while loop */
    while (tabs_i < MAX_TABS)
        tabs[tabs_i++] = tab_base * DEF_TABSTOP;     /* Set custom tab stops */
    tabs_i = 0;

    /* Get lines */ 
    while ((c = getchar()) != EOF)
    {
        /* This is the main entab loop*/
        if (c != SPACE)           /* try for every char that is not a space */ 
        {
            while (blanks_n > 0)  /* Loop while there are spaces */
            {
                nxt_def_ts = DEF_TABSTOP - (col % DEF_TABSTOP);     /* Get next default tab stop */
                while (tabs[tabs_i] <= col && tabs_i < MAX_TABS)    /* Find next custom tab */  
                    tabs_i++;
                if (tabs_i < MAX_TABS)              /* if next tabs index doesn't overflow the array */
                    nxt_ts = tabs[tabs_i] - col;    /* subtract current col from custom tab */
                if (nxt_def_ts <= nxt_ts && blanks_n - nxt_def_ts >= 0)
                {   /* if next custom tab is larger than default tab ... */
                    putchar(TAB);                   /* print \t */
                    col += nxt_def_ts;              /* update col with the length of default tab */
                    blanks_n -= nxt_def_ts;         /* update blanks_n wih remaining spaces */
                }
                else    /* if default tab is greater than custom tab */
                {
                    while (blanks_n > 0 && nxt_ts-- > 0)
                    {
                        putchar(SPACE);     /* Print spaces until custom tab is reached */
                        col++;              /* Update col */
                        blanks_n--;         /* Update blanks_n */
                    }
                }   
            }
        }
        /* switch through every input char */
        switch (c)
        {
        case SPACE:           
            blanks_n++;         /* Count blanks_n */
            break;
        case NEW_LINE:         
            col = 0;            /* reset col */
            tabs_i = 0;         /* reset tabs_i */
            putchar(c);         /* print \n */
            break;
        case TAB:
            while (tabs[tabs_i] <= col && tabs_i < MAX_TABS) /* Find next custom tab */
                tabs_i++;
            if (tabs_i < MAX_TABS)              /* if next custum tab is not too big */
                nxt_ts = tabs[tabs_i] - col;    /* subtract current col from custom tab */
            blanks_n += nxt_ts;                   /* add spaces to nxt_ts */
            break;
        default:
            putchar(c);     /* Default, print char */
            col++;
            break;             
        }
    }
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
