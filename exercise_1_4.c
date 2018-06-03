#include <stdio.h>

/* Convert Celcius to Fahrenheit */
int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;
    printf("CEL     FAH\n\n");
    while (celsius <= upper)
    {
        fahr = 9*celsius/5.0 + 32;
        printf("%5.1f   %4.2f\n", celsius, fahr);
        celsius = celsius + step;
    }
	
	return 0;
}
