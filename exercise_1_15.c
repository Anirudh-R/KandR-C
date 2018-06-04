#include <stdio.h>

float fahr2cels(float fahr);

/* Convert Fahrenheit to Celsius using function call */
int main()
{
    int fahr;

    for(fahr = 0; fahr <= 300; fahr = fahr + 20)
        printf("%3d   %6.1f\n", fahr, fahr2cels((float)fahr));

    return 0;
}

/* Convert Fahrenheit to Celsius */
float fahr2cels(float fahr)
{
    return 5*(fahr - 32)/9.0;
}
