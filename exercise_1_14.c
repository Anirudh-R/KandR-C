#include <stdio.h>
#include <ctype.h>

#define MAXHIST 15      //max length of histogram bar
#define MAXCHAR 128

/* horizontal histogram of input word counts. */
int main()
{
    int len, c, i;
    int maxvalue;               //max value in counts[]
    int counts[MAXCHAR];

    for(i = 0; i < MAXCHAR; i++)
        counts[i] = 0;

    while((c = getchar()) != EOF)
        if(c < MAXCHAR)
            counts[c]++;

    maxvalue = 0;
    for(i = 1; i < MAXCHAR; i++)
        if(counts[i] > maxvalue)
            maxvalue = counts[i];

    //print histogram
    for(i = 1; i < MAXCHAR; i++)
    {
        if(isprint(i))
            printf("%-3d  %c  %-5d", i, i, counts[i]);
        else
            printf("%-3d     %-5d", i, counts[i]);
        
        len = (counts[i]*MAXHIST)/maxvalue;   //normalize to MAXHIST
        while(len--)
            printf("* ");

        putchar('\n');
    }

    return 0;
}
