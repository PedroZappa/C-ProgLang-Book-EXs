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
double stack[MAX_SIZE];
int stack_top = 0;

/* Function prototypes */
void push(double val);
double pop(void);

void print_stack(void);
void print_ops(double op1, int op, double op2);

int main(int argc, char *argv[])
{
    int i;          /* Index Iterator */
    double op2;        /* Second operand for '-' & '/' ops */
    char *p_arg;    /* to point to args */

    printf(SEP "\tEXPR Solver\n" SEP);
    
    /* Read arguments starting from first */
    for (i = 1; i < argc; i++)  
    {
        p_arg = argv[i];    /* Point to current argument */

        //printf("argv[%d] = %s\n", i, p_arg);
        print_stack();
        while (*p_arg && isdigit(*p_arg))
            p_arg++;
        switch(*p_arg)
        {
            case '+':
                print_ops(stack[stack_top - 2], *p_arg, stack[stack_top - 1]);
                push(pop() + pop());
                printf("%.3lf\n", stack[stack_top - 1]);
                break;
            case '-':
                print_ops(stack[stack_top - 2], *p_arg, stack[stack_top - 1]);
                op2 = pop();
                push(pop() - op2);
                printf("%lf\n", stack[stack_top - 1]);
                break;
            case '*':
                print_ops(stack[stack_top - 2], *p_arg, stack[stack_top - 1]);
                push(pop() * pop());
                printf("%lf\n", stack[stack_top - 1]);
                break;
            case '/':
                print_ops(stack[stack_top - 2], *p_arg, stack[stack_top - 1]);
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: Division by zero!\n");
                printf("%lf\n", stack[stack_top - 1]);
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

/* print_stack - print the stack contents */
void print_stack(void)
{
    int i;
    for (i = 0; i < stack_top; i++)
        printf("%.3lf ", stack[i]);
    printf("\n");
}

/* print_ops - print the stack contents */
void print_ops(double op1, int op, double op2)
{
    printf(SEP "%.3lf %c %.3lf = ", op1, op, op2);
}
