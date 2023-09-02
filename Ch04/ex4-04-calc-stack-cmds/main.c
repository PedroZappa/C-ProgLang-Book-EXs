/* Exercise 4-4. Add commands to print the top element of the stack
 * without popping, to duplicate it, and to swap the top two elements.
 * Add a command to clear the stack. */
#include <math.h>		/* fmod() */
#include <stdio.h>
#include <stdlib.h>		/* atof() */

#define	SEP			"======================================\n"
#define MAXOP		1000	/* max size of operand or operator */
#define MAXVAL		100		/* maximum depth of val stack */
#define BUFSIZE		100		/* size of buffer */
#define NUMBER		'0'		/* signal that a number was found */

#define IS_SPACE(c)	((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')
#define IS_DIGIT(c)	((c) >= '0' && (c) <= '9')

/* Function Prototypes */
int getop(char []);			/* get next operator or numeric operand */
void push(double f);		/* push f onto value stack */
double pop(void);			/* pop and return top value from stack */
int getch(void);			/* get a (possibly pushed) character */
void ungetch(int);			/* push character back on input */

void stack_cmds(int type);
void view_stack(void);		/* print the whole stack */
void print_top(void);		/* print top element of stack */
void duplicate(void);		/* duplicate top element of stack */
void swap(void);			/* swap top two elements of stack */
void clear(void);			/* clear stack */

/* External Variables */
int stack_pos = 0;			/* stack position */
double val[MAXVAL];			/* value stack */
char buf[BUFSIZE];			/* buffer for ungetch */
int buf_pos = 0;			/* buffer position */
int noPopPrint = 0;			/* Don't pop & print on ENTER after stack ops */

/* Reverse Polish Calculator */
int main()
{
	int type;				/* current operand/operator */
	double op2;				/* second operand (for '-' & '/') */
	char s[MAXOP];			/* buffer for user input */

	/* Render Calculator's Header */
	printf(SEP "\tReverse Polish Calculator\n" SEP);
	printf("Math Ops\t: + - * / \%%\n");
	printf("Special Ops\t: ? # ~ ! \n" SEP);
	printf("Usage: <operand> <operand> <operator>\n" SEP);

	while ((type = getop(s)) != EOF)
	{
		view_stack();		/* print the whole stack */
		switch (type)
		{
			/* Operands */
			case NUMBER:
				push(atof(s));
				break;

			/* Special Commands */
			case '?': case '#': case '~': case '!':
				stack_cmds(type);
				break;

			/* Operators */
			case '+':					/* add */
				push(pop() + pop());
				break;
			case '*':					/* multiply */
				push(pop() * pop());
				break;
			case '-':					/* subtract */
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':					/* divide */
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':					/* modulus */
				op2 = pop();
				if (op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("error: zero divisor\n" SEP);
				break;

			/* Terminating Condition */
			case '\n':
				if (!noPopPrint)
					printf("\t= %.8g\n" SEP, pop());
				noPopPrint = 0;
				break;
			default:
				printf("error: unknown command '%s'\n", s);
				break;
		}
	}
	return (0);
}


/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int c;					/* current char */
	int i;					/* iterator */

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!IS_DIGIT(c) && c != '.' && c != '-')
		return c;			/* not a number */

	i = 0;
	if (c == '-')			/* handle negative number */
	{
		s[i++] = '-';
		c = getch();
	}
	if (IS_DIGIT(c))		/* collect integer part */
	{
		while (IS_DIGIT(c))
		{
			s[i++] = c;
			c = getch();
		}
	}
	if (c == '.')			/* collect fractional part */
	{
		s[i++] = c;
		c = getch();
		while (IS_DIGIT(c))
		{
			s[i++] = c;
			c = getch();
		}
		
	}
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}


// push: push 'f' onto the value stack
void push(double f)
{
	if (stack_pos < MAXVAL-1)		/* is the stack full? */
		val[stack_pos++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

// pop: pop and return top value off the value stack
double pop(void)
{
	if (stack_pos > 0)
		return val[--stack_pos];
	else
	{
		printf(SEP "Stack is empty\n");
		return 0.0;
	}
}

// getch: get a (possibly pushed) character
int getch(void)
{
	return (buf_pos > 0) ? buf[--buf_pos] : getchar();
}

// ungetch: push character back on input
void ungetch(int c)
{
	if (buf_pos >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[buf_pos++] = c;
}


/* stack_ops: stack operation commands */
void stack_cmds(int cmd)
{
	int i;
	noPopPrint = 1;
	
	switch (cmd)
	{
		case '?':
			print_top();
			break;
		case '#':
			duplicate();
			break;
		case '~':
			swap();
			break;
		case '!':
			noPopPrint = 0;
			clear();
			break;
		default:
			printf("error: unknown command '%d'\n", cmd);
			break;
	}
}

/* view_stack: print the whole stack */
void view_stack(void)
{
	int i;
	printf("Stack:\n");
	for (i = stack_pos-1; i >= 0; i--)
		printf("%.8g\n", val[i]);
}

/* print_top: print top element of stack */
void print_top(void)
{
	if (stack_pos > 0)
		printf("Stack's top element: %.8g\n", val[stack_pos - 1]);
	else
		printf("error: stack is empty\n");
}

/* duplicate: duplicate top element of stack */
void duplicate(void)
{
	if (stack_pos > MAXVAL-1)
		printf("error: stack full, can't duplicate\n");
	else
	{
		double buffer = pop();

		push(buffer);			/* push original */
		push(buffer);			/* push duplicate */
		//++stack_pos;			/* increment stack position */
	}
}

/* swap: swap top two elements of stack */
void swap(void)
{
	double buffer;
	if (stack_pos < 1)		/* if stack has less than 2 elements */
		printf("error: not enough elements\n");
	else
	{
		buffer = val[stack_pos - 1];
		val[stack_pos - 1] = val[stack_pos - 2];
		val[stack_pos - 2] = buffer;
	}
}

/* clear: clear stack */
void clear(void)
{
	stack_pos = 0;
}
