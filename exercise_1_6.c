#include <stdio.h>

int main()
{
    int x;

    while((x = getchar()) != EOF)
        printf("condition = %d\n", x);

    printf("condition = %d\n", x);

    return 0;
}
