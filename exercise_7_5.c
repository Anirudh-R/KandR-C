#include <stdio.h>
#include <stdlib.h>    /* for atof() */
#include <math.h>      /* for fmod() */

#define MAXOP 100      /* max size of operand or operator */
#define NUMBER '0'     /* signal that a number was found */

int getop(char s[]);
void push(double f);
double pop(void);

int main(void)
{
    int type, done;
    double op2;
    char s[MAXOP];

    done = 0;
    while (!done && (type = getop(s))!=EOF) 
        switch(type) 
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
            case '=':
                printf("ans = %g\n", pop());
                done = 1;
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
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
int getop(char s[])
{
    int c, c2, ret;
    float f;
    
    while((ret = scanf("%c", &c)) != EOF)
        if((s[0] = c)!=' ' && c!='\t')
            break;
    s[1] = '\0';
    
    if(ret == EOF)
        return EOF;
    
    c = (int)((char)c);  //without typecasting, isdigit() and comparisions do not give desired output
        
    if(c == '-')
    {
        ret = scanf("%c", &c2);          //see next character
        if(ret == EOF)
            return c;                    //cannot be a number
        ungetc(c2, stdin);
            
        c2 = (int)((char)c2);
        
        if(isdigit(c2) || c2=='.')      //a negative number
            ungetc(c, stdin);
        else                            //the '-' operator
            return c;
    }
    else if(!isdigit(c) && c!='.')      //an operator
        return c;
            
    else                                //non-negative number
        ungetc(c, stdin);   
        
    scanf("%f", &f);
    sprintf(s, "%f", f);
    return NUMBER;
}
