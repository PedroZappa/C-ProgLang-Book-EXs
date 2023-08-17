#include <stdio.h>

/* Print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300
 */
int main(void)
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Celcius to Fahrenheit\n");
    printf("Fahrenheit\tCelcius\n");

    fahr = lower;
    while (fahr <= upper) {
	celsius = (5.0 / 9.0) * (fahr - 32.0);
	printf("\t%3.0f\t%6.1f\n", fahr, celsius);
	fahr = fahr + step;
    }
}
