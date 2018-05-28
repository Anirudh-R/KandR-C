#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DEFPRNTLINES 10
#define MAXPRNTLINES 10000      

#define MAXLINES 100
#define MAXLINELEN 100

char* lineptr[MAXLINES];

int readlines(char* lineptr[]);
int getline(char s[], int limit);

int main(int argc, char* argv[])
{
    int nlinesToPrint=DEFPRNTLINES, nlines, lineLimitWarning=0;
    char c;
    
    nlines = readlines(lineptr);
    
    if(argc > 2)
    {
        printf("Usage: tail [-n]\n");
        return 1;
    }
    else if(argc==2 && *(*++argv)=='-')
    {
        nlinesToPrint = 0;
        while(c = *(++(*argv)))
        {
            if(!isdigit(c))
            {
                printf("Error: Invalid parameter.\n");
                return 1;
            }
            
            nlinesToPrint = nlinesToPrint*10 + (c-'0');
            
            if(nlinesToPrint > MAXPRNTLINES)
                lineLimitWarning = 1;
        }
        
        if(lineLimitWarning==1)
            nlinesToPrint = MAXPRNTLINES;
        if(nlines <= nlinesToPrint)
            lineLimitWarning = 0;
        
        nlinesToPrint = (nlines < nlinesToPrint)? nlines : nlinesToPrint;    
    }
    
    while(nlinesToPrint-->0)
        printf("%s\n", lineptr[nlines-1-nlinesToPrint]);
    
    if(lineLimitWarning==1)
        printf("\nWarning: Limiting the no. of lines displayed!\n");

    return 0;
}


int readlines(char* lineptr[])
{
    char line[MAXLINELEN];
    int lineCnt, len;
    char *p;
    
    lineCnt = 0;
    while( (len = getline(line, MAXLINELEN)) > 0 )
    {
        if(lineCnt<MAXLINES && (p=alloc(len))!=NULL)
        {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[lineCnt++] = p;
        }
        else
        {
            return -1;
        }
    }
    
    return lineCnt;
}

int getline(char s[], int limit)
{
    char c;
    int i;
    
    i = 0;
    while(--limit>0 && (c=getchar())!=EOF && c!='\n')
        s[i++] = c;
        
    if(c=='\n')
        s[i++] = c;
    
    s[i] = '\0';
    
    return i;
}
