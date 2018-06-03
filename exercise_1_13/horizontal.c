#include <stdio.h>

#define MAXHIST 15  //max length of histogram bar
#define MAXWORD 11  //max length of word
#define IN 1
#define OUT 0

/* horizontal histogram of input word counts. */
int main()
{
    int state, nc, len, c, i;
    int maxvalue;               //max value in wordlen[]
    int overflow;               //number of words > MAXWORD
    int wordlen[MAXWORD];

    state = OUT;
    nc = 0;
    overflow = 0;

    for(i = 0; i < MAXWORD; i++)
        wordlen[i] = 0;

    while((c = getchar()) != EOF)
    {
        if(c==' ' || c=='\t' || c=='\n')
        {
            state = OUT;
            if(nc > 0)              //a word has completed
                if(nc < MAXWORD)
                    wordlen[nc]++;
                else
                    overflow++;

            nc = 0;
        }
        else if(state == OUT)       //a new word has started
        {
            state = IN;
            nc = 1;
        }
        else                        //inside a word
            nc++;
    }

    maxvalue = 0;
    for(i = 1; i < MAXWORD; i++)
        if(wordlen[i] > maxvalue)
            maxvalue = wordlen[i];

    //print histogram
    for(i = 1; i < MAXWORD; i++)
    {
        len = wordlen[i]*MAXHIST/maxvalue;      //normalize to MAXHIST

        printf("%2d  ", i);
        while(len--)
            putchar('*');

        putchar('\n');
    }

    if(overflow > 0)
        printf("There are %d words >= %d\n", overflow, MAXWORD);

    return 0;
}
