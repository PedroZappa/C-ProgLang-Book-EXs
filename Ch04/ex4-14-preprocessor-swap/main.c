/*  */
#include <stdio.h>

#define swap(type, x, y) \
{                         \
    type temp;             \
    temp = x;               \
    x = y;                   \
    y = temp;                 \
}

int main(void) {
	int ix, iy;
	double dx, dy;
	char *px, *py;

    printf("Preprocessor swap()\n");

	ix = 42;
	iy = 69;
	printf("integers before swap: %d and %d\n", ix, iy);
	swap(int, ix, iy);
	printf("integers after swap: %d and %d\n", ix, iy);
	
	dx = 123.0;
	dy = 321.0;
	printf("doubles before swap: %g and %g\n", dx, dy);
	swap(double, dx, dy);
	printf("doubles after swap: %g and %g\n", dx, dy);
	
	px = "Zedro";
	py = "42";
	printf("pointers before swap: %s and %s\n", px, py);
	swap(char *, px, py);
	printf("integers after swap: %s and %s\n", px, py);

	return 0;
}
