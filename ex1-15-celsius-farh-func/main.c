#include <stdio.h>
#include <stdlib.h>

float celsius2fahr(float celsius);

int main(int argc, char *argv[])
{
	float celsius = 0.0;

	printf("Celsius to Fahrenheit Conversion\n");

	if (argc != 2)
	{
		do {
			printf("Usage: %s <temperature>\n", argv[0]);
			scanf("%f", &celsius);
		} while (!celsius);
	} else {
		celsius = atof(argv[1]);
	}

	printf("%3.0fº Celcius = %6.2fº Fahrenheit\n", celsius, celsius2fahr(celsius));
}


float celsius2fahr(float celsius)
{
	return (9.0 / 5.0) * (celsius + 32.0);
}
