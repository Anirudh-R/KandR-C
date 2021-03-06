#include <stdio.h>

/* Convert Fahrenheit to Celsius */
int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("FAH      CEL\n\n");
    while (fahr <= upper)
    {
        celsius = 5 * (fahr-32)/9.0;
        printf("%3.0f   %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
	
	return 0;
}
