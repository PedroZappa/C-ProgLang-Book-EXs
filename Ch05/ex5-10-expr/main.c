/* Exercise 5-10. Write the program expr, which evaluates a 
 * reverse Polish expression from the command line, where each 
 * operator or operand is a separate argument. For example, 
 * expr 2 3 4 + #* evaluates 2 x (3+4). */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define MAX_SIZE   1024

/* Global Variables */
int stack[MAX_SIZE];
int stack_top = 0;

/* Function prototypes */
void push(double val);
double pop(void);

int main(int argc, char *argv[])
{
    int i;
    double val;

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
        printf("Stack underflow!\n");
}
