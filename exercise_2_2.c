#include <stdio.h>

int okloop = 1;

i = 0;
while(okloop == 1)
{
    if(i >= lim-1)
        okloop = 0;
    else if((c = getchar()) == '\n' || c==EOF)
        okloop = 0;
    else
        s[i++] = c;
}


