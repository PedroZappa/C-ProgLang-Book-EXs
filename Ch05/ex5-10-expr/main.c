/* Exercise 5-10. Write the program expr, which evaluates a 
 * reverse Polish expression from the command line, where each 
 * operator or operand is a separate argument. For example, 
 * expr '2 3 4 + *' evaluates '2 x (3+4)' */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define SEP         "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
#define MAX_SIZE   1024

/* Global Variables */
int stack[MAX_SIZE];
int stack_top = 0;

/* Function prototypes */
void push(double val);
double pop(void);

int main(int argc, char *argv[])
{
    int i;          /* Index Iterator */
    int op2;        /* Second operand for '-' & '/' ops */
    char *p_arg;    /* to point to args */

    printf(SEP "\tEXPR Solver\n" SEP);
    for (i = 1; i < argc; i++)   /* Read arguments starting from last */
    {
        p_arg = argv[i];
        printf("argv[%d] = %s\n", i, argv[i]);
        while (*p_arg && isdigit(*p_arg))    /* Is operand? */
            p_arg++;
        printf("*p_arg = %d, (%c)\n", *p_arg, *p_arg);

        switch(*p_arg)
        {
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: Division by zero!\n");
                break;
            case '\0':
                push(atoi(argv[i]));
                break;
        }
    }
    printf(SEP "Result = %lf\n" SEP, pop());

    return (0);
}

/* push - push a value onto the stack */
void push(double val)
{
    if (stack_top < MAX_SIZE)
        stack[stack_top++] = val;
    else
        printf("Stack overflow!\n");
}

/* pop - pop a value from the stack */
double pop(void)
{
    if (stack_top > 0)
        return (stack[--stack_top]);
    else
    {
        printf("Stack underflow!\n");
        return (0.0);
    }
}
