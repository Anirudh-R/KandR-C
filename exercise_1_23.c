#include <stdio.h>

void rcomment(int c);
void in_comment(void);
void echo_quote(int c);

/* Remove comments from a valid C program */
int main()
{
    int c, d;
    
    while((c = getchar()) != EOF)
        rcomment(c);
    
    return 0;
}


/* rcomment: remove comments starting from c */
void rcomment(int c)
{
    int d;
    
    if(c == '/')
    {
        if((d = getchar()) == '*')      //beginning of a comment
            in_comment();
        else if(d == '/')               //just another slash
        {
            putchar(c);
            rcomment(d);
        }
        else                            //not a comment
        {
            putchar(c);
            putchar(d);
        }
    }
    else if(c == '\'' || c == '"')       //beginning of a quote
        echo_quote(c);
    else
        putchar(c);
}

/* in_comment: skip comment */
void in_comment(void)
{
    int prev, curr;
    
    prev = getchar();
    curr = getchar();
    while(!(prev=='*' && curr=='/'))
    {
        prev = curr;
        curr = getchar();
    }
}

/* echo_quote: echo chars within the quote starting from c */
void echo_quote(int c)
{
    int d;
    
    putchar(c);
    while((d = getchar()) != c)
    {
        putchar(d);
        if(d == '\\')
            putchar(getchar());     //skip the next character
    }
    putchar(d);
}

