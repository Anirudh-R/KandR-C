#include <stdio.h>

int main()
{
    //This gives an error because the '\' nullifies the meaning of the terminating double quote.
    //The compiler complains that the matching quote is missing.
	printf("hello, world\");

	return 0;
}
