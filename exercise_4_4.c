#include <stdio.h>
#include <stdlib.h>    /* for atof() */
#include <math.h>      /* for fmod() */

#define MAXOP 100      /* max size of operand or operator */
#define NUMBER '0'     /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
void clear(void);

/* Reverse polish calculator */
/*  Commands:
    +, -, *, / and % operators
    ? prints top element of the stack
    c clears the stack
    d duplicates top element of the stack
    s swap top 2 elements of the stack
*/
int main(void)
{
    int type;
    double op1, op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) 
    {
        switch (type) 
        {
            case NUMBER:
                push(atof(s));
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
            case '?':
                op2 = pop();
                printf("%f\n", op2);
                push(op2);
                break;
            case 'c':
                clear();
                break;
            case 'd':
                op2 = pop();
                push(op2);
                push(op2);
                break;
            case 's':
                op1 = pop();
                op2 = pop();
                push(op1);
                push(op2);
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

/* Clears the stack */
void clear(void)
{
	sp = 0;
}


#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c, c2;

    while ((s[0] = c = getch()) == ' ' || c == '\t');

    s[1] = '\0';    
    
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */
        
    if (c == '-') 
    {
        c2 = getch();
        if (c2 != EOF)
            ungetch(c2);
        if (!isdigit(c2) && c2 != '.')
            return c;
    }
    
    i = 0;
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
