#include <stdio.h>
#include <stdlib.h>    
#include <math.h>      
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000   /* Maximum input line size */
#define MAXOP 100      /* max size of operand or operator */
#define NUMBER '0'     /* signal that a number was found */
#define MATHOP '1'
#define VARIABLE '2'

int getop(char []);
void push(double);
double pop(void);

char line[MAXLINE];
int lineIndx = 0;

double vars[26];
double last = 0;

/* Reverse polish calculator */
/*  Commands:
    +, -, *, / and % operators
    sin, exp, pow commands
    You can use capital single letter variables
*/
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];
    
    while(getline(line, MAXLINE)!=0)
    {
        lineIndx = 0;
        
        while ((type = getop(s)) != '\0') 
        {
            switch (type) 
            {
                case NUMBER:
                    push(atof(s));
                    break;
                case MATHOP:
                    if(!strcmp(s, "sin"))
                        push(sin(pop()));
                    else if(!strcmp(s, "exp"))
                        push(exp(pop()));
                    else if(!strcmp(s, "pow"))
                    {
                        op2 = pop();
                        push(pow(pop(), op2));
                    }
                    else if(!strcmp(s, "last"))
                    {
                        printf("The most recently printed value is %g\n", last);
                    }
                    else
                        printf("error: unknown command %s\n", s);
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("error: zero divisor\n");
                    break;
                case '%':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(fmod(pop(), op2));
                    else
                        printf("error: zero divisor\n");
                    break;
                case VARIABLE:
                    last = vars[s[0] - 'A'] = pop();
                    push(last);
                    break;
                case '\n':
                    printf("= %g\n", pop());
                    break;
                default:
                    printf("error: unknown command %s\n", s);
                    break;
            }
        }
    }

    return 0;
}


#define MAXVAL 100 /* maximum depth of val stack */

double val[MAXVAL]; /* value stack */
int sp = 0; /* next free stack position */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else 
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}


int getline(char s[], int lim);

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c, c2;

    while ((s[0] = c = line[lineIndx++]) == ' ' || c == '\t');

    s[1] = '\0';    
    
    i = 0;
    if(isalpha(c))
    {
        while(isalpha(s[++i] = c = line[lineIndx++]));
        
        s[i] = '\0';
        
        if(c != '\0')
            lineIndx--;
            
        return MATHOP;
    }
    
    if (!isdigit(c) && c != '.' && c != '-')
    {
        if(c=='=')
        {
            if(isalpha(c2 = line[lineIndx++]))
            {
                s[0] = c2;
                return VARIABLE;
            }
            else if(c2 != '\0')
            {
                lineIndx--;
            }
        }
        
        return c; /* not a number */
    }
        
    if (c == '-') 
    {
        c2 = line[lineIndx++];
        if (c2 != '\0')
            lineIndx--;
        if (!isdigit(c2) && c2 != '.')  //An operator
            return c;
    }
    
    if (isdigit(c) || c == '-') /* collect integer part */
        while (isdigit(s[++i] = c = line[lineIndx++]));
            
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = line[lineIndx++]));
            
    s[i] = '\0';
    
    if (c != '\0')
        lineIndx--;
        
    return NUMBER;
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
