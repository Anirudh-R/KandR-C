#include <stdio.h>
#include <ctype.h>

int getfloat(double *pn);
int getch(void);
void ungetch(int c);

int main(void) 
{
    double result;
    int ret;
    
    ret = getfloat(&result);
    
    if(ret!=0)
        printf("%f\n", result);
    else
        printf("Error: Not a number.\n");

	return 0;
}


int getfloat(double *pn)
{
    int c, sign, pwr;
    
    while(isspace(c = getch()));    //skip whitespace characters
    
    if(!isdigit(c) && c!=EOF && c!='+' && c!='-' && c!='.')   //not a number
    {
        ungetch(c);
        return 0;
    }
    
    sign = (c == '-')? -1 : 1;
    
    if(c=='+' || c=='-')
    {
        c = getch();                //see the next character
        if(!isdigit(c) && c!=EOF && c!='.')
        {
            ungetch(c);
            return 0;
        }
    }
        
    for(*pn=0; isdigit(c); c=getch())
        *pn = 10*(*pn) + (c - '0');
        
    if(c=='.')
    {
        c = getch();
        if(!isdigit(c) && c!=EOF)
        {
            ungetch(c);
            return 0;
        }
    }
    
    for(pwr=1; isdigit(c); c=getch())
    {
        *pn = 10*(*pn) + (c - '0');
        pwr *= 10;
    }
        
    (*pn) = sign*(*pn)/pwr;
    
    if(c!=EOF)
        ungetch(c);
    
    return c;
}


int buf = 0;    //single character buffer to hold pushed back input values

int getch(void)
{
    int c;
    
    if(buf==0)
        c = getchar();
    else 
    {
        c = buf;
        buf = 0;
    }
        
    return c;
}

void ungetch(int c)
{
    if(buf==0)
        buf = c;
    else
        printf("ungetch: buffer full.\n");
}
