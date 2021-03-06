#include <stdio.h>
#include <stdlib.h>    
#include <math.h>      
#include <string.h>

#define MAXOP 100      /* max size of operand or operator */
#define NUMBER '0'     /* signal that a number was found */
#define MATHOP '1'
#define VARIABLE '2'

int getop(char []);
void push(double);
double pop(void);

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

    while ((type = getop(s)) != EOF) 
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



#include <ctype.h>

void ungets(char s[]);
int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c, c2;

    while ((s[0] = c = getch()) == ' ' || c == '\t');

    s[1] = '\0';    
    
    i = 0;
    if(isalpha(c))
    {
        while(isalpha(s[++i] = c = getch()));
        
        s[i] = '\0';
        
        if(c != EOF)
            ungetch(c);
            
        return MATHOP;
    }
    
    if (!isdigit(c) && c != '.' && c != '-')
    {
        if(c=='=')
        {
            if(isalpha(c2 = getch()))
            {
                s[0] = c2;
                return VARIABLE;
            }
            else if(c2 != EOF)
            {
                ungetch(c2);
            }
        }
        
        return c; /* not a number */
    }
        
    if (c == '-') 
    {
        c2 = getch();
        if (c2 != EOF)
            ungetch(c2);
        if (!isdigit(c2) && c2 != '.')
            return c;
    }
    
    if (isdigit(c) || c == '-') /* collect integer part */
        while (isdigit(s[++i] = c = getch()));
            
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()));
            
    s[i] = '\0';
    
    if (c != EOF)
        ungetch(c);
        
    return NUMBER;
}


#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

void ungets(char s[])
{
    int len;
    
    len = strlen(s);
    
    while(len > 0)
        ungetch(s[--len]);
}

int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
