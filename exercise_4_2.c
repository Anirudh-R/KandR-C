#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 1000

double atof(char s[]);
int getline(char s[], int lim);

int main(void) 
{
    char line[MAXLINE];
    
    while(getline(line, MAXLINE) > 0)
        printf("%f\n", atof(line));

	return 0;
}

/* Read input real numbers in normal/scientific form */
double atof(char s[])
{
    double val;
    int sign, expsign, power, exponent, i;
    
    for(i=0; isspace(s[i]); i++);    //Skip white space
    
    //Mantessa part
    sign = (s[i]=='-')? -1 : 1;
    
    if(s[i]=='-' || s[i]=='+')
        i++;
        
    for(val=0; isdigit(s[i]); i++)
        val = val*10 + (s[i]-'0');
        
    if(s[i]=='.')
        i++;
        
    for(power=0; isdigit(s[i]); i++)
    {
        val = val*10 + (s[i]-'0');
        power++;
    }
    
    //Exponent part
    if(s[i]=='e' || s[i]=='E')
        i++;
    
    expsign = (s[i]=='-')? -1 : 1;
    
    if(s[i]=='-' || s[i]=='+')
        i++;
    
    for(exponent=0; isdigit(s[i]); i++)
        exponent = exponent*10 + (s[i]-'0');
        
    return sign*val*pow(10, expsign*exponent - power);
}

/* Read a new line of maximum MAXLINE-1 characters */
int getline(char s[], int lim)
{
    int i;
    char c;
    
    i = 0;
    while(--lim>0 && (c=getchar())!=EOF && c!='\n')
        s[i++] = c;
        
    if(c == '\n')
        s[i++] = c;
        
    s[i] = '\0';
    
    return i;
}
