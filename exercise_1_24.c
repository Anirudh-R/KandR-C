#include <stdio.h>

int brace, brack, paren;    //respective counts

void checkSyntax(int c);
void in_comment(void);
void in_quote(int c);

/* Rudimentary C syntax checker */
int main()
{
    int braceDone, brackDone, parenDone;    //respective errors have already been printed
    int c;
    
    braceDone = 0; 
    brackDone = 0; 
    parenDone = 0;
    while((c = getchar()) != EOF)
    {
        if(c == '/')
        {
            if((c = getchar()) == '*')      //inside comment
                in_comment();
            else
                checkSyntax(c);
        }
        else if(c == '\'' || c == '"')      //inside quote or string constant
            in_quote(c);
        else
            checkSyntax(c);
            
        if(!braceDone && brace < 0)
        {
            printf("Unbalanced braces\n");
            braceDone = 1;
        }
        else if(!brackDone && brack < 0)
        {
            printf("Unbalanced brackets\n");
            brackDone = 1;
        }
        else if(!parenDone && paren < 0)
        {
            printf("Unbalanced parantheses\n");
            parenDone = 1;
        }
    }
    
    if(!braceDone && brace != 0)
        printf("Unbalanced braces\n");
    if(!brackDone && brack != 0)
        printf("Unbalanced brackets\n");
    if(!parenDone && paren != 0)
        printf("Unbalanced parantheses\n");
        
    return 0;
}


/* checkSyntax: look for rudimentary syntax errors */
void checkSyntax(int c)
{
    if(c == '{')
        brace++;
    else if(c == '}')
        brace--;
    else if(c == '[')
        brack++;
    else if(c == ']')
        brack--;
    else if(c == '(')
        paren++;
    else if(c == ')')
        paren--;
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

/* in_quote: skip chars within the quote starting from c */
void in_quote(int c)
{
    int d;
    
    while((d = getchar()) != c)
        if(d == '\\')
            getchar();     //skip the next character
}

