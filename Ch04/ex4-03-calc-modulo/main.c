/* Exercise 4-3. Given the basic framework, it’s straightforward 
 * to extend this reverse Polish calculator. Add the modulus (%) 
 * operator and provisions for negative numbers. */
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

/* External Variables */
int stack_pos = 0;			/* stack position */
double val[MAXVAL];			/* value stack */
char buf[BUFSIZE];			/* buffer for ungetch */
int buf_pos = 0;			/* buffer position */

/* Reverse Polish Calculator */
int main()
{
	int type;
	double op2;
	char s[MAXOP];

	/* Render Calculator's Header */
	printf(SEP "\tReverse Polish Calculator\n" SEP);
	printf("Available Operatiors: + - * / \%%\n" SEP);
	printf("Usage: <operand> <operand> <operator>\n" SEP);

	while ((type = getop(s)) != EOF)
	{
		switch (type)
		{
			case NUMBER:
				push(atof(s));
				break;
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
			case '\n':
				printf("= %.8g\n", pop());
				break;
			default:
				printf("error: unknown command '%s'\n" SEP, s);
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
	int next;				/* next char */

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!IS_DIGIT(c) && c != '.')
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
	if (stack_pos < MAXVAL)		/* is the stack full? */
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
		printf("error: stack empty\n");
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
