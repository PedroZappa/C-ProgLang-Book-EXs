#include <stdio.h>

int main(void)
{
	int c, bl_c, tab_c, nl_c;

	nl_c = tab_c = bl_c = 0;
	while ((c = getchar()) != EOF)
	{	
		if (c == ' ')
			++bl_c;
		if (c == '\n')
			++nl_c;
		if (c == '\t')
			++tab_c;
	}
	printf("Blanks: %d\n", bl_c);
	printf("Tabs: %d\n", tab_c);
	printf("Newlines: %d\n", nl_c);
}
