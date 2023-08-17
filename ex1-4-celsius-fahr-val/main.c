#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float celsius;
    
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

    printf("%fº Celcius = %fº Fahrenheit\n", celsius, (9.0 / 5.5) * (celsius + 32));
    return 0;
}
