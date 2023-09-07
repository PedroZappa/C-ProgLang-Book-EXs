/* Exercise 4-6.  */
#include <math.h>		/* fmod() sin() cos() exp() pow() */
#include <stdio.h>
#include <string.h>		/* strcmp() */
#include <stdlib.h>		/* atof() */

/* Constants */
#define SEP		    	"======================================\n"
#define SEP2	    	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
#define MAXOP	    	1000	/* max size of operand or operator */
#define MAXVAL	    	100		/* maximum depth of val stack */
#define BUFSIZE	    	100		/* size of buffer */
#define NUMBER	    	0		/* signal that a number was found */
#define ID 		    	1		/* signal that an identifier was found */
#define EOS             2       /* signal end of string was found */
#define MAX_VARS        32      /* maximum length of string */

/* Macros */
#define IS_SPACE(c)	((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')
#define IS_ALPHA(c)	((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z')
#define IS_DIGIT(c)	((c) >= '0' && (c) <= '9')

/* Struct for variables */
struct variable {
    char name[BUFSIZE];
    double value;
};

/* Function Prototypes */
int getop(char []);			/* get next operator or numeric operand */
void push(double f);		/* push f onto value stack */
double pop(void);			/* pop and return top value from stack */
int getch(void);			/* get a (possibly pushed) character */
void ungetch(int);			/* push character back on input */

void check_id(char *str, struct variable var[]);	/* check if str is a valid identifier */
void check_var(char *str, struct variable var[]);   /* check if str is a valid variable */

void stack_cmds(int cmd);
void view_stack(void);	    	/* print the whole stack */
void print_top(void);	    	/* print top element of stack */
void duplicate(void);	    	/* duplicate top element of stack */
void swap(void);		    	/* swap top two elements of stack */
void clear(struct variable var[]);			/* clear stack */

/* External Variables */
int stack_p = 0;		    	/* stack position */
double val[MAXVAL];		    	/* value stack */
char buf[BUFSIZE];	    		/* buffer for ungetch */
int buf_pos = 0;    			/* buffer position */
double op2;				    	/* second operand (for '-', '/' & 'pow()') */
int noPopPrint = 0;	    		/* Don't pop & print on ENTER after stack ops */

struct variable vars[MAX_VARS];  /* Array to store vars */
struct variable input_var;      /* Variable being read */   
int var_pos = 0;

/* Reverse Polish Calculator */
int main()
{
	int type;			    	/* current operand/operator */
	char s[MAXOP];	    		/* buffer for user input */

	/* Render Calculator's Header */
	printf(SEP "\tReverse Polish Calculator\n" SEP);
	printf("Basic Ops\t + - * / \%%\n");
    printf("Advanced Ops\t sin cos exp pow\n");
	printf("Special Ops\t ? # ~ ! \n");
	printf("User Variables\n" SEP);
	printf("Usage: <operand> <operand> <operator>\n" SEP);

    clear(vars);                 /* clear the var array */

	while ((type = getop(s)) != EOF)
	{
		view_stack();		/* print the whole stack */
		switch (type)
		{
			/* Operands */
			case NUMBER:
				push(atof(s));
				break;

			/* String Handling for math.h functions */
			case ID:
				check_id(s, vars);
				break;

			/* Special Commands */
			case '?': case '#': case '~': case '!':
				stack_cmds(type);
				break;

			/* Operators */
			case '+':					/* add */
				printf("Sum\t%.8f + %.8f\n", val[stack_p-2], val[stack_p-1]);
				push(pop() + pop());
				break;
			case '*':					/* multiply */
				printf("Multiply\t%.8f * %.8f\n", val[stack_p-2], val[stack_p-1]);
				push(pop() * pop());
				break;
			case '-':					/* subtract */
				printf("Subtract\t%.8f - %.8f\n", val[stack_p-2], val[stack_p-1]);
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':					/* divide */
				printf("Divide\t%.8f / %.8f\n", val[stack_p-2], val[stack_p-1]);
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':					/* modulus */
				printf("Modulus\t%.8f \%% %.8f\n", val[stack_p-2], val[stack_p-1]);
				op2 = pop();
				if (op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("error: zero divisor\n" SEP);
				break;

			/* Terminating Condition */
			case '\n':
				if (!noPopPrint)
					printf(SEP "\t= %.8g\n" SEP, pop());
				noPopPrint = 0;
				break;

            /* Handle vars */
            case EOS:
                break;
            case '=':
                pop();
                vars[var_pos].value = pop();
                input_var.value = vars[var_pos].value;
                push(input_var.value);
                break;
            case '<':
                printf("last variable: %s = %g\n", input_var.name, input_var.value);
                break;

			default:
				printf("error: unknown command '%s'\n", s);
				break;
		}
	}
	return (0);
}


/* getop: parse next operator, operand or identifier */
int getop(char s[])
{
	int c;					    /* current char */
    int next_c;                 /* next char */
	int i = 0;				    /* iterator */

	/* Skip whitespace */
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

    /* Handle alphabetical identifiers */
	if (IS_ALPHA(c))			/* Check for a math.h or var identifier */
	{
		i = 0;
		do 
		{
			s[i++] = c;         /* collect identifier */
			c = getch();
		}
		while (IS_ALPHA(c));    /* while alphabetical */
		s[i] = '\0';

		if (c != EOF)           /* If not end of file */
			ungetch(c);         /* Put non-alphabetical char back */
		return ID;
	}

    /* Handle assignment operator '=' */
	if (!IS_DIGIT(c) && c != '.')
    {
        /* Check if next char is '=' AND next char is '\n' */
        if (c == '=' && (next_c = getch()) == '\n')    
        {
            ungetch('\0');  /* put '\0' back */
            return c;       /* return '=' */
        }
        if (c == '\0')      /* If end of file */
            return EOS;     /* return EOS signal */
		return c;
    }

    /* Handle number */
	i = 0;
	if (c == '-')			/* handle negative number */
	{
		s[i++] = '-';
		c = getch();
	}
	if (IS_DIGIT(c))		/* handle integer part */
	{
		while (IS_DIGIT(c))
		{
			s[i++] = c;     /* collect integer part */
			c = getch();
		}
	}
	if (c == '.')			/* handle fractional part */
	{
		s[i++] = c;         /* collect '.' */
		c = getch();
		while (IS_DIGIT(c))
		{
			s[i++] = c;     /* collect fractional part */
			c = getch();
		}
	}
	s[i] = '\0';
	
    if (c != EOF)           /* If not end of file */
		ungetch(c);         /* Put non-digit char back */

	printf(SEP2);
	return NUMBER;
}


// push: push 'f' onto the value stack
void push(double f)
{
	if (stack_p < MAXVAL)		/* is the stack full? */
		val[stack_p++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

// pop: pop and return top value off the value stack
double pop(void)
{
	if (stack_p > 0)            /* is the stack not empty? */
		return val[--stack_p];  /* take top value from the stack */
	else
	{
		printf(SEP "Stack is empty.\n");
		return 0.0;
	}
}

// getch: get a (possibly pushed) character
int getch(void)
{
    /* If buffer is not empty read a character from it 
     * else return the next character from stdin */
	return (buf_pos > 0) ? buf[--buf_pos] : getchar();
}

// ungetch: push character back on input
void ungetch(int c)
{
	if (buf_pos >= BUFSIZE)     /* is the buffer full? */
		printf("ungetch: too many characters\n");
	else                        /* otherwise push character */
		buf[buf_pos++] = c;
}


/* check_id: check if str is a valid identifier
 * valid IDs: sin, cos, exp, pow */
void check_id(char *str, struct variable var[])
{
	if (0 == strcmp(str, "sin")) 		/* Validate sin() */
	{
		if (stack_p < 1)
			printf("error: stack underflow, can't call sin\n");
		else
        {
			printf("Sin\t %.8f\n", val[stack_p-1]);
			push(sin(pop()));
        }
    }
	else if (0 == strcmp(str, "cos"))	/* Validate cos() */
	{
		if (stack_p < 1)
			printf("error: stack underflow, can't call cos\n");
		else
        {
            printf("Cosine\t %.8f\n", val[stack_p-1]);
			push(cos(pop()));
        }
    }
	else if (0 == strcmp(str, "exp"))	/* Validate exp() */
	{
		if (stack_p < 1)
			printf("error: stack underflow, can't call exp\n");
		else
        {
			printf("Exponent\t %.8f\n", val[stack_p-1]);
			push(exp(pop()));
        }
    }
	else if (0 == strcmp(str, "pow"))		/* Validate pow() */
	{
		if (stack_p < 2)
			printf("error: stack underflow, can't call pow\n");
		else
		{
			op2 = pop();
            printf("Power\t%.8f ^ %.8f\n", val[stack_p-1], val[stack_p]);
			push(pow(pop(), op2));
		}
	}
	else          /* if not math function str is a variable */
        check_var(str, var);
}

/* check_var : check if 'str' matches any of the variable.names
 * If found updates global array of variable's value
 * If no match is found add the variable to the stack */
void check_var(char *str, struct variable var[])
{
    int i;      /* String Iterator */

    for (i = 0; i < MAX_VARS-1 && var[i].name[0] != '\0'; i++)
    {
        /* Check if 'str' doesn' match any of var[i].name */
        if (!strcmp(str, var[i].name))
        { 
            strcpy(input_var.name, str);        /* Save input_var name */
            input_var.value = var[i].value;     /* Save input_var value */
            push(var[i].value);                 /* Push input_var value into stack */
            var_pos = i;		                /* Update var_pos */
            return;
        }
    }

    strcpy(var[i].name, str);       /* If var name not found, add it */
    strcpy(input_var.name, str);    /* Save input_var name */
    push(var[i].value);             /* Push input_var value into stack */
    var_pos = i;                    /* Update var_pos */
 }

/* stack_ops: handle stack operation commands */
void stack_cmds(int cmd)
{
	int i;
	noPopPrint = 1;
	
	switch (cmd)
	{
		case '?':           /* print top element of stack */
			print_top();
			break;
		case '#':           /* duplicate top element of stack */
			duplicate();
			break;
		case '~':           /* swap top two elements of stack */
			swap();
			break;
		case '!':           /* clear stack */
			noPopPrint = 0;
			clear(vars);
			break;
        default:           /* handle unknown command */
			printf("error: unknown command '%d'\n", cmd);
			break;
	}
}

/* view_stack: print the whole stack */
void view_stack(void)
{
	int i;

    /* print stack from top to bottom */
	printf("Stack:\t");
	for (i = stack_p-1; i >= 0; i--)
		printf("%.8g ", val[i]);
	printf("\n");
}

/* print_top: print top element of stack */
void print_top(void)
{
	if (stack_p > 0)
		printf("Stack's top element: %.8g\n", val[stack_p - 1]);
	else
		printf("error: stack is empty\n");
}

/* duplicate: duplicate top element of stack */
void duplicate(void)
{
	if (stack_p > MAXVAL-1)
		printf("error: stack full, can't duplicate\n");
	else
	{
		double buffer = pop();

		push(buffer);			/* push original */
		push(buffer);			/* push duplicate */
	}
}

/* swap: swap top two elements of stack */
void swap(void)
{
	double buffer;
	if (stack_p < 1)		/* if stack has less than 2 elements */
		printf("error: not enough elements\n");
	else
	{
		buffer = val[stack_p - 1];
		val[stack_p - 1] = val[stack_p - 2];
		val[stack_p - 2] = buffer;
	}
}

/* clear: clear stack */
void clear(struct variable var[])
{
	stack_p = 0;        /* clear stack by setting pointer to index 0 */

    /* Clear variables array by setting the first element to NULL */
    for (int i = 0; i < MAX_VARS; i++)
    {
         var[i].name[0] = '\0';
         var[i].value = 0.0;
    }
}
