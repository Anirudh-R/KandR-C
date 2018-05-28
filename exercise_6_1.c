#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORDLEN 100
#define NKEYS (sizeof(keytab)/sizeof(keytab[0]))

struct key
{
    char* word;
    int count;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"for", 0},
    {"int", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

int getword(char* word, int limit);
char comment(void);
int binsearch(char* target, struct key tab[], int n);
int getch(void);
void ungetch(int c);

/* count C keywords */
int main()
{
    int n, i;
    char word[MAXWORDLEN];
    
    while (getword(word, MAXWORDLEN) != EOF)
        if(isalpha(word[0]))
            if((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    
    for(i = 0; i < NKEYS; i++)
        if(keytab[i].count > 0)
            printf("%4d   %s\n", keytab[i].count, keytab[i].word);
            
    return 0;
}


/* binsearch: find target in tab[0]....tab[n-1] */
int binsearch(char* target, struct key tab[], int n)
{
    int cond;
    int low, mid, high;
    
    low = 0;
    high = n - 1;
    while(low <= high)
    {
        mid = (low + high)/2;
        
        if((cond = strcmp(target, tab[mid].word)) < 0)
            high = mid - 1;
        else if(cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    
    return -1;
}

/* getword: get next word or character from input */
int getword(char* word, int limit)
{
    int c, d;
    
    while(isspace(c = getch()));
    
    if(c != EOF)
        *word++ = c;
        
    if(isalpha(c) || c=='_' || c=='#')
    {
        for( ; --limit > 0; word++)
            if(!isalnum(*word = getch()) && *word!='_')
            {
                ungetch(*word);
                break;
            }
    }
    else if(c=='\'' || c=='"')
    {
        for( ; --limit > 0; word++)
            if((*word = getch()) == '\\')
                *++word = getch();
            else if(*word == c)
            {
                word++;
                break;
            }
            else if(*word == EOF)
                break;
    }
    else if(c=='/')
    {
        if((d = getch()) == '*')
            c = comment();
        else
            ungetch(d);
    }

    *word = '\0';
    
    return c;
}

/* comment: skip over comment and return the next character */
char comment(void)
{
    int c;
    
    while((c = getch()) != EOF)
        if(c = '*')
            if((c = getch()) == '/')
                break;
            else
                ungetch(c);
                
    return c;            
}

int buf = 0;    //single character buffer to hold pushed back input values

/* gets a character from input */
int getch(void)
{
    int c;
    
    if(buf==0)
    {
        c = getchar();
    }
    else 
    {
        c = buf;
        buf = 0;
    }
        
    return c;
}

/* pushes a character back to input */
void ungetch(int c)
{
    if(buf==0)
        buf = c;
    else
        printf("ungetch: buffer full.\n");
}
