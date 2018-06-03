#include <stdio.h>

#define WTSP 0   //Whitespace
#define CHAR 1   //Character

/* print input one word per line */
int main()
{
    int curr, prev, c;

    prev = WTSP;
    while((c = getchar()) != EOF)
    {
        curr = (c==' ' || c=='\t' || c=='\n') ? WTSP : CHAR;

        if(curr == CHAR)
            putchar(c);
        else if(prev==CHAR && curr==WTSP)
            putchar('\n');

        prev = curr;
    }

    return 0;
}
