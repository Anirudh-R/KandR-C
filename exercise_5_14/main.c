#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char* lineptr[MAXLINES];

int readlines(char* lineptr[], int lim);
int getline(char s[], int lim);
void writelines(char* lineptr[], int nlines);

void quickSort(void *lineptr[], int left, int right, int (*comp)(void*, void*), int reverse);
void swap(void* v[], int i, int j);
int numcmp(char*, char*);

/* Sorts input lines */
int main(int argc, char* argv[])
{
    int nlines;         //number of input lines read
    int numeric = 0;    //1 for numeric sort
    int reverse = 1;    //-1 for sorting in decreasing order
    char c;
    
    while(--argc>0 && *(*++argv)=='-')
        while(c = *(++(*argv)))
            switch(c)
            {
                case 'n': 
                numeric = 1;
                break;
                
                case 'r':
                reverse = -1;
                break;
                
                default:
                printf("find: illegal option %c\n", c);
                return 1;
                break;
            }
    
    if(argc != 0)
    {
        printf("Usage: sort [-n] [-r]\n");
        return 1;
    }
        
    if((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        quickSort((void**)lineptr, 0, nlines-1, (int (*)(void*, void*))(numeric? numcmp : strcmp), reverse);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("Input too big to sort.\n");
        return 1;
    }
}


/* readlines: read upto lim lines from the input */
int readlines(char* lineptr[], int lim)
{
    int len, nlines=0;
    char *p, line[MAXLEN];

    while( (len = getline(line, MAXLEN)) > 0 )
    {
        if( nlines>=lim || (p=alloc(len))==NULL )
        {
            return -1;
        }
        else
        {
            line[len-1] = '\0';     //delete newline
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
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

/* writelines: put nlines lines to the output */
void writelines(char* lineptr[], int nlines)
{
    while(nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* quickSort: sort v[left]...v[right] into increasing order */
void quickSort(void *v[], int left, int right, int (*comp)(void*, void*), int reverse)
{
    int last, i;
    
    if(left >= right)
        return;
        
    swap(v, left, (left+right)/2);
    last = left;
    
    for(i=left+1; i<=right; i++)
        if(reverse*comp(v[i], v[left]) < 0)
            swap(v, ++last, i);
            
    swap(v, left, last);
    quickSort(v, left, last-1, comp, reverse);
    quickSort(v, last+1, right, comp, reverse);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    
    v1 = atof(s1);
    v2 = atof(s2);
    
    if(v1 < v2)
        return -1;
    else if(v1 > v2)
        return 1;
    else
        return 0;
}

/* swap: swap the contents of v[i] and v[j] */
void swap(void* v[], int i, int j)
{
    void* temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
