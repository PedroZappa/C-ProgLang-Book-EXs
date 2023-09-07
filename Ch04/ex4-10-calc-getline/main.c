/* Exercise 4-10. An alternate organization uses getline to read an entire 
 * input line; this makes getch and ungetch unnecessary. 
 * Revise the calculator to use this approach. */
#include <stdio.h>
#include <stdlib.h>

#define SEP     "========================================\n"
#define SEP2    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
#define MAXLINE 512     /* max length of line */
#define MAXOP   128     /* max size of operand or operator */
#define MAXVAL  128     /* max depth of value stack */     
#define NUMBER  '0'     /* signal that a number was found */

/* Macros */
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

/* Function Prototypes */
int ft_getline(char line[], int maxline);   /* getline */
int getop(char []);     /* get next operator or numeric operand */
void push(double);      /* push operand/operator onto stack */
double pop(void);       /* pop operand/operator from stack */
void view_stack(void);  /* print the value stack */

/* Global Variables */
double val_stack[MAXVAL];   /* value stack */
int stack_p = 0;            /* top of value stack */
char line[MAXLINE];         /* input line */
int line_len = 0;           /* length of input line */

/* Reverse Polish Calculator */
int main(void)
{
    int type;        /* holds the type of last token */
    double op2;      /* second operand (for '-' & '/' operators) */
    char str[MAXOP];

    // Render Calcuator Header
    printf(SEP "\tReverse Polish Calculator\n" SEP);
	printf("Basic Ops\t + - * / \%%\n");
	printf("Usage: <operand> <operand> <operator>\n" SEP);
     
    // Get line from user
    while (ft_getline(line, MAXLINE) != '\0') 
    {
        line_len = 0;   /* reset line length */
        // Read opeartors and operands from line
        while ((type = getop(str)) != '\0') 
        {
            view_stack();
            // Check if it's an operator or operand
            switch (type) 
            {
                case NUMBER:
                    push(atof(str));
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("error: zero divisor\n" SEP);
                    break;
                case '\n':
                    printf(SEP "\t= %.8g\n" SEP, pop());
                    break;
                default:
                    printf("error: unknown command \'%s\'\n", str);
            }
        }
    }
    return (0);
}


/* getline : read a line into s, return length */
int ft_getline(char line[], int maxline) 
{
    int len, c;         /* i counts characters, c gets input */

    len = 0;              
    while (--maxline > 0 && (c = getchar()) != EOF && c != '\n')
        line[len++] = c;    /* store characters */
    if (c == '\n')      
        line[len++] = c;
    line[len] = '\0';       /* null terminate */

    return (len);
}

/* getop : get next operator or numeric operand */
int getop(char str[])
{
    int i, c;         /* i counts characters, c gets input */

    i = 0;
    while ((str[0] = c = line[line_len++]) == ' ' || c == '\t')
        ;               /* skip white space */
    str[1] = '\0';        /* null terminate */
    if (!IS_DIGIT(c) && c != '.' && c != '-')
        return (c);     /* not a number */
    if (IS_DIGIT(c))    /* collect integer part */
        while (IS_DIGIT(str[++i] = c = line[line_len++]))
            ;
    if (c == '.')       /* collect fraction part */
        while (IS_DIGIT(str[++i] = c = line[line_len++]));
    str[i] = '\0';        /* null terminate */
    line_len--;
    
    printf(SEP2);

    return (NUMBER);
}

/* push : push operand/operator onto stack */
void push(double f)
{
    if (stack_p < MAXVAL)           /* Check if there is room on the stack */
        val_stack[stack_p++] = f;   /* push operand/operator onto stack */
    else
        printf("error: stack overflow, can't push %g\n", f);
}

/* pop : pop operand/operator from stack */
double pop(void)
{
    if (stack_p > 0)                /* Check if there is a value to pop from the stack */
        return (val_stack[--stack_p]);
    else
        printf("error: stack underflow, can't pop %g\n", val_stack[stack_p]);

    return (0.0);
}

/* viewstack : print the value stack */
void view_stack(void)
{
    int i;
    printf("Stack:\t");
    for (i = stack_p-1; i >= 0; i--)
        printf("%g ", val_stack[i]);
    printf("\n");
}
