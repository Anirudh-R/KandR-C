#include <stdio.h>

int main()
{
	printf("hello, world\y");
	printf("hello, world\7");
	printf("hello, world\?");

    //Result:
    //hello, worldyhello, worldhello, world?
    //warning: unknown escape sequence: '\y'

	return 0;
}
