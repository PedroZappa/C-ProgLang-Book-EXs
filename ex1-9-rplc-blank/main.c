#include <stdio.h>

int main(void)
{
	int c, bl_c;

	bl_c = 0;
	while ((c = getchar()) != EOF)
	{
		while (c == ' ')
		{
		    ++bl_c;
		    c = getchar();
		}
		if (bl_c > 0)
		{
			putchar(' ');
			bl_c = 0;
		}
		putchar(c);
	}
}
