/* Exercise 5.11a : Entab with custom tab stops
 * The args interpreted as a squence of tab stop lengths */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define SEP             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
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
int  entab(char line[], int tab_base, int len);

/* Entab Driver */
int main(int argc, char *argv[])
{
    int i;                  /* Loop index */
    int c;                  /* Current input char */
    int tabs[MAX_TABS];     /* Array of tab stop lengths */
    int tabs_i;             /* tabs[] index Iterator Helper */ 
    int tab_base;           /* Base tab stop */
    /* Testing Vars */
    char lines[MAX_LEN][MAX_LEN];   /* Array of lines */
    int lines_len[MAX_LEN];         /* Array of line lengths */
    int lines_spaces[MAX_LEN];      /* Array of line spaces */
    int lines_tabs[MAX_LEN];       /* Array of line tabs */
    int sub_line, len;              /* Line Stat Counters */
    int tabs_c;                     /* Keep track of number of tabs in line */
    int space_c;                    /* Keep track of number of spaces in line */

    /* Loop through args, convert valid args to ints and store them in tabs[] */
    tabs_i = 0;
    for (i = 1; i < argc && tabs_i < MAX_TABS; i++)
    {
        if (IS_DIGIT(*argv[i]))                 /* check if the char in arg is a digit */
            tabs[tabs_i++] = atoi(argv[i]);     /* convert char to int */
        else
        {
            printf(SEP "Invalid argument: '%s', must be integer.\n", argv[i]);
            printf("Usage: %s [tabstop-1] [tabstop-2] ... [tabstop-n]\n" SEP, argv[0]);
            return (1);                         /* invalid args */
        }
    }

    /* Render Header */
    printf(SEP "Entab w/ ");

    /* Print parsed custom tab stops */
    printf("Custom Tab Stops: ");
    for (i = 0; i < tabs_i; i++)
    {
        printf("%d", tabs[i]);
        if (i < tabs_i - 1)
            printf(", ");
    }
    printf(";\n" SEP);
   
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
        tabs[tabs_i++] = tab_base++ * DEF_TABSTOP;     /* Set custom tab stops */

    /* Get lines from user */
    c = len = sub_line = 0;
    while ((c = getchar()) != EOF)
    {
        lines[sub_line][len] = c;
        if (c == '\n')
        {
            lines[sub_line][len] = '\0';    /* Null-terminate line */
            lines_len[sub_line] = len;      /* Store line length */
            sub_line++;                     /* Get next line */
            len = 0;                        /* Reset line length */
        }
        else ++len;
    }

    /* Get lines */ 
    printf("Type text to entab:\n");
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

/* entab : Entab with custom tab stops */
int entab(char line[], int tab_base, int len)
{
    int i;                  /* Loop index */
    int col;                /* Column index */
    int blanks_n;           /* Number of spaces ... */
    int tabs_i;             /* tabs[] index Iterator Helper */ 
    int nxt_ts;             /* Next tab stop */
    int nxt_def_ts;         /* Next default tab stop */

    tabs_i = blanks_n = 0;
    while (line[len] != '\0')
    {
        /* This is the main entab loop*/
        if (line[i] != SPACE)           /* try for every char that is not a space */ 
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
            blanks_n++;         /* Increment blanks_n */
            space_c++;          /* Invcrement space_c */
            break;
        case NEW_LINE:         
            col = 0;            /* reset col */
            tabs_i = 0;         /* reset tabs_i */
            tabs_c = 0;          /* reset tab_c */
            space_c = 0;        /* reset space_c */
            putchar(c);         /* print \n */
            print_stats();      /* print stats: spaces, tabs before and after entab */
            break;
        case TAB:
            tabs_c++;          /* Increment tabs_c */
            while (tabs[tabs_i] <= col && tabs_i < MAX_TABS) /* Find next custom tab */
            tabs_i++;
            if (tabs_i < MAX_TABS)              /* if next custum tab is not too big */
                nxt_ts = tabs[tabs_i] - col;    /* subtract current col from custom tab */
            blanks_n += nxt_ts;                 /* add spaces to nxt_ts */
            break;
        default:
            putchar(c);     /* Default, print char */
            col++;
            break;             
        }
    }
}
