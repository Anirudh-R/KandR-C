#include <stdio.h>

/* skip repetitive blanks */
int main()
{
    int c, prevc;

    prevc = 'x';    //arbitrary non-blank character
    while((c = getchar()) != EOF)
    {
        if(c == ' ' && c != prevc)
            putchar(c);
        else if(c != ' ')
            putchar(c);

        prevc = c;
    }

    return 0;
}
