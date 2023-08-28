/* bitwise hexadecimal manipulation of color */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int color = 0x123456;	// 24-bit rgb representation of color
	int red, green, blue;

	// Extract color components
	red = (color & 0xff0000) >> 16;	// Extract red component
	green = (color & 0x00ff00) >> 8;	// Extract green component
	blue = (color & 0x0000ff);	// Extract blue component
	
	// Render UI
	printf("Color\t= %6x\n", color);	// Print color in hex
	printf("Red\t= %02x\n", red);	// Print Red component
	printf("Green\t= %02x\n", green);	// Print Green component
	printf("Blue\t= %02x\n", blue);	// Print Blue component

	// Clear green bits
	color &= 0xff00ff;
	green = 0xdc;

	color |= (green << 8);	// Set new green bits in place
	
	printf("Color without green\t= %06x\n", color);

	// Color state = 0x12dc56
	// In Binary =		00010010 11011100 01010110
	// Invert red bits  11101101 = 0xed
	
	color ^= 0xff0000;
	
	// Print new color
	printf("Color with inverted red\t= %06x\n", color);

	return (0);
}
