#include <stdio.h>
#include <stdlib.h>    /* for atof() */
#include <math.h>      /* for fmod() */

#define MAXINPUTLEN 1000    /* max total length of all parameters separated by spaces */
#define MAXOP 100           /* max size of operand or operator */
#define NUMBER '0'          /* signal that a number was found */

char inputstr[MAXINPUTLEN];
int inputstrIndex = 0;

int getop(char s[], int* currIndex);
void push(double f);
double pop(void);

int main(int argc, char* argv[])
{
    int type;
    double op2;
    char s[MAXOP];
    int i;
    char c;
    
    //Concatenate all the input parameters separated by spaces
    for(i = 1; i < argc; i++)
    {
        while( (c = *(argv[i]++)) != '\0' )
            inputstr[inputstrIndex++] = c;
            
        inputstr[inputstrIndex++] = (i==argc-1)? '\n' : ' ';
    }
    inputstr[inputstrIndex] = '\0';
    inputstrIndex = 0;
    
    while ((type = getop(s, &inputstrIndex)) != '\0') 
    {
        switch (type) 
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case 'x':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                {
                    push(pop() / op2);
                }
                else
                {
                    printf("error: zero divisor\n");
                    return -1;
                }
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                {
                    push(fmod(pop(), op2));
                }
                else
                {
                    printf("error: zero divisor\n");
                    return -1;
                }
                break;
            case '\n':
                printf("= %g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                return -1;
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

/* getop: get next character or numeric operand */
int getop(char s[], int* currIndex)
{
    int i;
    char c, c2;

    while ((s[0] = c = inputstr[(*currIndex)++]) == ' ' || c == '\t');

    s[1] = '\0';    
    
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */
        
    if (c == '-') 
    {
        c2 = inputstr[(*currIndex)++];
        if (c2 != '\0')
            (*currIndex)--;
        if (!isdigit(c2) && c2 != '.')
            return c;
    }
    
    i = 0;
    if (isdigit(c) || c == '-') /* collect integer part */
        while (isdigit(s[++i] = c = inputstr[(*currIndex)++]));
            
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = inputstr[(*currIndex)++]));
            
    s[i] = '\0';
    
    if (c != '\0')
        (*currIndex)--;
    
    return NUMBER;
}
