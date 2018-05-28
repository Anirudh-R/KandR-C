#include <stdio.h>
#include <string.h>

#define MAXLINE 5000
#define MAXLEN 1000

extern char* alloc(int len);
extern void afree(char *p);

char* lineptr[MAXLINE];

int readlines(char* lineptr[]);
void writelines(char* lineptr[], int nlines);

void qsort(char* lineptr[], int left, int right);
void swap(char* v[], int i, int j);

int getline(char s[], int lim);

// Program to sort input lines
int main(void)
{
    int nlines;

    if((nlines = readlines(lineptr)) >= 0)
    {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("Error: Input size too large.\n");
        return 1;
    }
}


int readlines(char* lineptr[])
{
    int len, nlines=0;
    char *p, line[MAXLEN];

    while( (len = getline(line, MAXLEN)) > 0 )
    {
        if( nlines>=MAXLINE || (p=alloc(len))==NULL )
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

void writelines(char* lineptr[], int nlines)
{
    while(nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void qsort(char* v[], int left, int right)
{
    int i, last;

    if(left>=right)
        return;

    swap(v, left, (left+right)/2);
    last = left;

    for(i=left+1; i<=right; i++)
        if(strcmp(v[i], v[left]) < 0)
            swap(v, i, left);

    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(char* v[], int i, int j)
{
    char* temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
