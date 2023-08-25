#include <stdio.h>

int ft_strlen(char str[]);

int main(int argc, char **argv)
{
	char *str;

	if (argc == 2)
		str = argv[1];
	else
		str = "Zedro";

	printf("'%s' is %d chars long.\n", str, ft_strlen(str));

	return 0;
}


// ft_strlen() : returns the length of a string
int ft_strlen(char str[])
{
	int i;

	i= 0;
	while (str[i] != '\0')
		++i;
	return (i);
} 
