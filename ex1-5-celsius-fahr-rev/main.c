#include <stdio.h>

// Symbolic Constants
#define LOWER 0
#define UPPER 300
#define STEP 20

int main(void)
{
	float fahr, celsius;
	
	printf("Celsius to Fahrenheit\n");
	printf("Fahrenheit\tCelsius\n");

	for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
	{
		celsius = (5.0 / 9.0) * (fahr - 32);
		printf("%3.0f\t\t%6.1f\n", fahr, celsius);
	}
	return 0;
}
