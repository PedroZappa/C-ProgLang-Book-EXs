/* Exercise 4-11. Modify getop so that it doesn’t need 
 * to use ungetch. Hint: use an internal static variable. */
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define SEP		    "======================================\n"
#define SEP2	    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
#define MAXVAL	    128
#define MAXOP	    128
#define BUFSIZE	    128
#define NUMBER 	    0

/* Macros */
#define IS_SPACE(c)	((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')
#define IS_DIGIT(c)	((c) >= '0' && (c) <= '9')

/* Function Prototypes */
int getop(char str[]);        /* get next operator or numeric operand */
void push(double f);          /* push f onto value stack */ 
double pop(void);             /* pop and return top value from stack */
int getch(void);              /* get a (possibly pushed) character */
void view_stack(void);        /* print the whole stack */

/* External Variables */
int stack_p = 0;            /* stack position */
double stack[MAXVAL];       /* value stack */
char buffer[BUFSIZE];	        /* buffer for ungetch */
int buffer_p = 0;    		/* buffer position */

// Driver code
int main()
{
    int type;             /* current operand/operator */
    char str[MAXOP];      /* buffer for user input */
    double op2;           /* second operand (for '-' & '/') */

    	/* Render Calculator's Header */
	printf(SEP "\tReverse Polish Calculator\n" SEP);
	printf("Basic Ops\t + - * / \%%\n" SEP);
	printf("Usage: <operand> <operand> <operator>\n" SEP);
    
    /* Get user input */
    while ((type = getop(str)) != EOF)
    {
        view_stack();         /* print the whole stack */
        switch (type)
        {
            /* Operands */
            case NUMBER:
                push(atof(str));
                break;

            /* Operators */
            case '+':
		    	printf("Sum\t%.8f + %.8f\n", stack[stack_p-2], stack[stack_p-1]);
                push(pop() + pop());
                break;
            case '*':
			    printf("Multiply\t%.8f + %.8f\n", stack[stack_p-2], stack[stack_p-1]);
                push(pop() * pop());
                break;
            case '-':
			    printf("Subtract\t%.8f + %.8f\n", stack[stack_p-2], stack[stack_p-1]);
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
			    printf("Divide\t%.8f + %.8f\n", stack[stack_p-2], stack[stack_p-1]);
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf(SEP "error: zero divisor\n");
                break;

            /* Print result of operation when '\n' */
            case '\n':
                printf(SEP "= %.8g\n" SEP, pop());
                break;

            default:
                printf(SEP "error: unknown command %s\n", str);
                break;
        }
    }
    return (0);
}


/* getop - get next operation or numeric operand */
int getop(char str[])
{
    int i;                  /* iterates through str */
    /* 'c' and 'next_c' are set as a static variables to limit their scope to getop */
    static int c = ' ';     /* current character */
    static int buffer;

    /* Ignore leading whitespace */
    while ((str[0] = c = getch()) == ' ' || c == '\t')
        ;
    str[1] = '\0';      /* terminate string in case input not number */

    /* Handle number */
    i = 0;
    if (!IS_DIGIT(c) && c != '.' && c != '-')
    {
        buffer = c;     /* save input */ 
        c = ' ';        /* reset c */
        return (buffer);
    }
    if (c == '-' || IS_DIGIT(c))    /* check for digit OR minus sign */
        while (IS_DIGIT(str[++i] = c = getch()))
            ;
    if (c == '.')                   /* collect fractional part */
        while (IS_DIGIT(str[++i] = c = getch()))
            ;
    str[i] = '\0';                    /* null terminate */ 

    printf(SEP2);
    return (NUMBER);
}

/* push - push f onto value stack */
void push(double f)
{
    if (stack_p < MAXVAL)
        stack[stack_p++] = f;
    else
        printf(SEP "error: stack full, can't push %f\n", f);
}

/* pop - pop and return top value off the value stack */
double pop(void)
{
    if (stack_p > 0)
        return stack[--stack_p];  /* take top value from the stack */
    else
    {
        printf(SEP "Stack is empty.\n");
        return 0.0;
    }
}

/* getch - get a (possibly pushed) character */
int getch(void)
{
    return (buffer_p > 0) ? buffer[--buffer_p] : getchar();
}

/* view_stack - print the whole stack */
void view_stack(void)
{
    int i;
    printf("Stack:\t");
    for (i = stack_p-1; i >= 0; i--)
        printf("%g ", stack[i]);
    printf("\n");
}
