// Exercise 3-2. Write a function escape(s,t) that converts characters like
// newline and tab into visible escape sequences like \n and \t as it copies 
// the string t to s. Use a switch. Write a function for the other direction 
// as well, converting escape sequences into the real characters. 
#include <stdio.h>
#include <string.h>

#define MAXLINE		100
#define BELL		'\a'
#define BACKSPACE	'\b'
#define TAB			'\t'
#define NEWLINE		'\n'
#define V_TAB		'\v'
#define FORM_FEED	'\f'
#define CARR_RET	'\r'
#define BACKSLASH	'\\'
#define D_QUOTE		'\"'
#define SEP			"============================\n"

int ft_getline(char line[], int maxline);
void escape(char escaped[], char line[]);
void unescape(char s[], char t[]);

int main(void)

{
	char line[MAXLINE];				// Store current line
	char lines[MAXLINE][MAXLINE];	// Store input lines
	char escaped[MAXLINE][MAXLINE];	// Store escaped lines
	int sub_line, line_len, len;	// Line counters
	int n;							// Iterator
	
	printf("Input to be escaped:\n");

	// Get lines of user input into lines[]
	sub_line = line_len = 0;
	while ((len = ft_getline(line, MAXLINE)) > 0)
	{
		for (n = 0; n < len; n++)		
		{
			lines[sub_line][n] = line[n];
		}	
		sub_line++;
	}

	// Loop through and print stored lines[]
	printf(SEP);
	for (n = 0; n < sub_line; n++)
		printf("lines[%d]\t: %s", n, lines[n]);
	printf(SEP);

	// Escape lines[]
	for (n = 0; n < sub_line; n++)
	{
		escape(escaped[n], lines[n]);
		printf("Escaped\t\t: %s\n", escaped[n]);
	}
	printf(SEP);

	// Unescaped lines[]
	for (n = 0; n < sub_line; n++)
	{
		unescape(lines[n], escaped[n]);
		printf("Unescaped\t: %s", lines[n]);
	}
	
	return 0;
}


// escape(s,t) : convert special chars into visible 
// escape sequences as it copies the string t to s.
void escape(char s[], char t[])
{
	int i;		// Iterator for 's' (source)
	int j;		// Iterator for 't' (target)

	i = j = 0;
	while (t[i])
	{
		switch (t[i])
		{
			// If special char, convert to escape sequence
			case BELL:
				s[j++] = '\\';	// Insert escape char & go to next char
				s[j] = 'a';		// Finish escape sequence
				break;
			case BACKSPACE:
				s[j++] = '\\';	// ...
				s[j] = 'b';		// ...
				break;
			case TAB:
				s[j++] = '\\';
				s[j] = 't';	
				break;
			case NEWLINE:
				s[j++] = '\\';
				s[j] = 'n';	
				break;
			case V_TAB:
				s[j++] = '\\';
				s[j] = 'v';
				break;
			case FORM_FEED:
				s[j++] = '\\';
				s[j] = 'f';
				break;
			case CARR_RET:
				s[j++] = '\\';
				s[j] = 'r';
				break;
			case BACKSLASH:
				s[j++] = '\\';
				s[j] = '\\';
				break;
			case D_QUOTE:
				s[j++] = '\\';
				s[j] = '\"';
				break;

			default:	
				s[j] = t[i];	// else if regular char, copy
				break;
		}
		++i;
		++j;
	}
	s[j] = t[i];	// Copy null char
}

// unescape(s,t) : convert escape sequences into the real characters
void unescape(char s[], char t[])
{
	int i;		// Iterator for 's' (source)
	int j;		// Iterator for 't' (target)

	i = j = 0;
	while (t[i])
	{
		switch (t[i])
		{
			case '\\':					// start of escape sequence found
				switch (t[++i])			// get next char of escape sequence
				{							// translate it accordingly
					case 'a':
						s[j] = '\a';
						break;
					case 'b':
						s[j] = '\b';
						break;
					case 't':
						s[j] = '\t';
						break;
					case 'n':
						s[j] = '\n';
						break;
					case 'v':
						s[j] = '\v';
						break;
					case 'f':
						s[j] = '\f';
						break;
					case 'r':
						s[j] = '\r';
						break;
					case '\\':
						s[j] = '\\';
						break;
					case '\"':
						s[j] = '\"';
						break;

					default:				// no valid translation found
						s[j++] = '\\';		// Insert escape char & go to next char
						s[j] = t[i];
				}	
				break;

			default:			// else if regular char
				s[j] = t[i];	// Copy char
		}
		++i;				
		++j;
	}
	s[j] = t[i];				// Copy null char
}


// getline: get a line of user input
int ft_getline(char s[], int lim)
{
	int c, i, j;

	j = 0;
	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
		if (i < lim - 1)
			s[j++] = c;
	if (c == '\n')
	{
		if (i < lim - 1)
			s[j++] = c;
		++i;
	}
	s[j] = '\0';
	return (i);
}
