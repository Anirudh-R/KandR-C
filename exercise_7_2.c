#include <stdio.h>
#include <ctype.h>

#define MAXLINELEN 15
#define HEXLEN 6        //Total length of " 0xhh "

int inc(int pos, int n);

/* print arbitrary input. Print HEX value of non-graphic chars and blanks */
int main()
{
    int c, pos,     //current position in line
    prevchar;       //1 if previous char was graphic
    
    pos = 0;
    prevchar = 0;
    while((c = getchar()) != EOF)
    {
        if(iscntrl(c) || c==' ')    //non-graphic or blank
        {
            if(prevchar && pos!=0 && c!='\n')            //to prevent 2 consecutive spaces
            {
                putchar(' ');
                pos = inc(pos, 1);
            }
            
            printf("0x%02X ", c);
            pos = inc(pos, HEXLEN-1);
            
            if(c == '\n')
            {
                putchar(c);
                pos = 0;
            }
            
            prevchar = 0;
        }
        else
        {
            putchar(c);
            pos = inc(pos, 1);
            prevchar = 1;
        }
    }
    
    return 0;
}

/* Shift current pos in line by n, provided it did not exceed MAXLINELEN */
int inc(int pos, int n)
{
    if(pos + n < MAXLINELEN)
    {
        return pos + n;
    }
    else
    {
        putchar('\n');
        return n;
    }
}
