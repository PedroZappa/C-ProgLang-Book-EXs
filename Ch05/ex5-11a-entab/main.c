/* Exercise 5.11a : Entab with custom tab stops
 * The args interpreted as a tab_start and tab_gap.
 * tab_start is an integer that specifies the col for the first tab 
 * tab_gap is the number of cols between each tabs.*/
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define SEP             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
#define RULER           "RLR 123456789x123456789x123456789x\n"
#define TABSTART    2           /* Default tab start */
#define TABGAP      4           /* Default tab gap */
#define MAX_LEN         512         /* Max length of line */
#define SPACE		    ' '         /* Space Character */
#define TAB			    '\t'        /* Tab Character */
#define NEW_LINE	    '\n'        /* New Line Character */

/* Macros */
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

/* Global Vars */
char lines[MAX_LEN][MAX_LEN];   /* Array of lines */
/* User input Vars */
int tab_start;          /* First tab stop position */
int tab_gap;            /* space between tabs */
/* Testing Vars*/
int lines_len[MAX_LEN];         /* Array of line lengths */
int lines_spaces[MAX_LEN];      /* Array of line spaces */
int lines_tabs[MAX_LEN];       /* Array of line tabs */
int sub_line;              /* Line Stat Counters */
int tabs_c;             /* Keep track of number of tabs in line */
int space_c;            /* Keep track of number of spaces in line */
int char_c;             /* Keep track of number of chars in line */

/* Function prototypes */
void ft_getline(char line[], int lim);
void sort_args(int[], int n);
void entab(char *line, int tab_start, int tab_gap);
void print_stats(void);

/* Entab Driver */
int main(int argc, char *argv[])
{
    int i;               /* Loop indexes */

    /* Render Header */
    printf(SEP "Entab w/\n");

    /* Loop through args, convert valid args to ints and store them in tabs[] */
    if (argc == 3)
    {
        if (IS_DIGIT(*argv[1]))     /* check if the first char in arg is a digit */
        {
            tab_start = atoi(argv[1]);      /* convert char to int */
            tab_gap = atoi(argv[2]);
            printf("tab_start = %d\n", tab_start);
            printf("tab_gap = %d\n" SEP, tab_gap);
        }
        else
        {
            printf(SEP "Invalid argument: '%s', must be integer.\n", argv[0]);
            printf(SEP "Usage: %s <tab_start> <tab_gap> \n" SEP, argv[0]);
            return (1);                     /* invalid args */
        }
    }
    else if (argc == 1)
    {
        tab_start = TABSTART;   /* default tab start */
        tab_gap = TABGAP;       /* default tab gap */
        /* Print default entab settings */
        printf("tab_start = %d\n", tab_start);
        printf("tab_gap = %d\n", tab_gap);
    }
    else
    {
        printf(SEP "Invalid number of arguments.\n");
        printf(SEP "Usage: %s <tab_start> <tab_gap> \n" SEP, argv[0]);
        return (1);
    }

    printf("Type text to entab:\n");            /* Get lines from user */
    ft_getline(lines[sub_line], MAX_LEN);

    printf(SEP "Input Lines:\n");               /* Print input lines pre-entab */
    for (i = 0; i < sub_line; ++i)
        printf("%d: '%s'\n", i, lines[i]);
    printf(RULER);
    printf(SEP "\tLine Stats before Entab:\n"); /* Print line stats pre-entab*/
    print_stats();

    for (i = 0; i < sub_line; ++i)              /* Entab lines */ 
        entab(lines[i], tab_start, tab_gap);

    printf(SEP "Entabed Lines:\n");             /* Print input lines post-entab */
    for (i = 0; i < sub_line; ++i)
        printf("%d: '%s'\n", i, lines[i]);
    printf(RULER);
    printf(SEP "\tLine Stats after Entab:\n");  /* Get line stats post-entab & print */
    print_stats();

    return 0;
}

/* entab : Entab with custom tab stops */
void entab(char *line, int tab_start, int tab_gap)
{
    int i, t;                   /* Loop index */
    int tab_sep;                /* Number of cols between tabs */
    int tab_started;            /* True if at tab start */

    i = t = tab_sep = tab_started = 0;
    while (line[i])             /* Loop through chars in line */
    {
        if (i == tab_start)     /* If at tab start */
        {
            line[t] = line[i];  /* Copy char */
            line[t] = TAB;   /* Insert tab */
            tab_started = 1;    /* Set flag */
            tab_sep = 0;        /* Reset column */
        }
        else
            line[t] = line[i];  /* Copy char */

        if (tab_sep == tab_gap+1)   /* handle gaps */
        {
            if (tab_started)
                line[t] = TAB;     /* Insert tab */
            tab_sep = 0;
        }
        tab_sep++;              /* Increment column count */
        i++;   
        t++;                    /* get next char in tabbed */
    }
    line[t] = '\0';         /* Null-terminate line */
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
     * partition is greater than 0 */
    for (split = n / 2; split > 0; split /= 2) {
        /* Loop through left half of array */
        for (i = split; i < n; i++) 
        {
            /* Loop through right half of array */
            for (j = (i - split); j >= 0 && args[j] > args[j + split]; j -= split) 
            {
                temp = args[j];
                args[j] = args[j + split];
                args[j + split] = temp;
            } 
        }
    }
}

/* print_stats : Prints number of spaces, 
 * tabs, and chars per line */
void print_stats(void)
{
    int i, j;

    for (i = 0; i < sub_line; ++i)          /* Loop through lines */
    {
        /* Count spaces, tabs, and chars */
        j = space_c = tabs_c = char_c = 0;
        while (lines[i][j])         /* Loop through chars in line */
        {
            if (lines[i][j] == SPACE)        /* Count spaces */
                ++space_c;
            if (lines[i][j] == TAB)         /* Count tabs */
                ++tabs_c;
            if (lines[i][j] > ' ' && lines[i][j] <= '~') /* Count chars */
                ++char_c;
            ++j;
        }
        lines_spaces[i] = space_c;
        lines_tabs[i] = tabs_c;
        lines_len[i] = j;

        /* Do the stats printing */
        printf("[%d] ", i);
        printf("Chars: %d; ", char_c);
        printf("Spaces: %d; ", lines_spaces[i]);
        printf("Tabs: %d; ", lines_tabs[i]);
        printf("Length: %d\n", lines_len[i]);
    }
}

/* getline : Get a line of input from user */
void ft_getline(char line[], int lim)
{
    int c;
    int len;

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

}
