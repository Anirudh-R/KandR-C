#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXFIELDS 10

char* lineptr[MAXLINES];

int readlines(char* lineptr[], int lim);
int getline(char s[], int lim);
void writelines(char* lineptr[], int nlines);

void quickSort(void* lineptr[], int left, int right, int (*comp)(void*, void*), int reverse, int fold, int direc, int pos1, int pos2);
void swap(void* v[], int i, int j);
void lower(char* s);
char* substr(char* s, int pos1, int pos2);
int min(int a, int b);
int numcmp(char*, char*);

extern char* alloc(int len);
extern void afree(char *p);

/* sort: Sorts input lines
    sort [-nrfd] [-pos1 -pos2]
    n: numeric = 0 (default), 1 for numeric sort
    r: reverse = 1 (default), -1 for sorting in decreasing order
    f: fold = 0 (default), 1 for folding upper and lower cases together
    d: direc = 0 (default), 1 for directory type sort
    pos1 = -1 (default), starting position of the field - starts from 0
    pos2 = -1 (default), Ending position of the field
*/
int main(int argc, char* argv[])
{
    int nlines;         //number of input lines read
    
    int nFields = 0;     //Number of fields to be sorted
    int fieldParams[MAXFIELDS][6];  //Each row contains [numeric, reverse, fold, direc, pos1, pos2] values for the field
    int fieldLimit = 0;  //1 if MAXFIELDS fields have been specified, ignore rest of the fields
    
    int i;
    char posCnt=0, c;
    
    
    fieldParams[0][0]=0; fieldParams[0][1]=1; fieldParams[0][2]=0; fieldParams[0][3]=0; fieldParams[0][4]=-1; fieldParams[0][5]=-1;
    
    while(--argc>0 && *(*++argv)=='-')
    {
        while(c = *(++*argv))
        {
            if(isalpha(c))
            {
                switch(c)
                {
                    case 'n': 
                    fieldParams[nFields][0] = 1;    //numeric = 1;
                    break;
                    
                    case 'r':
                    fieldParams[nFields][1] = -1;   //reverse = -1;
                    break;
                    
                    case 'f':
                    fieldParams[nFields][2] = 1;   //fold = 1;
                    break;
                    
                    case 'd':
                    fieldParams[nFields][3] = 1;    //direc = 1;
                    break;
                    
                    default:
                    printf("find: illegal option %c\n", c);
                    return 1;
                    break;
                }
            }
            else
            {
                fieldParams[nFields][4+posCnt] = atoi(*argv);
                posCnt++;
                if(posCnt==2)   //both pos1 & pos2 have been captured
                {
                    if(fieldParams[nFields][4]>fieldParams[nFields][5] || fieldParams[nFields][4]<0 || fieldParams[nFields][5]<0)       //pos1 > pos2
                    {
                        printf("Error: pos1 and pos2 much be non-negative. pos1 cannot be greater than pos2.\n");
                        return 1;
                    }
                    
                    if(nFields == MAXFIELDS-1)
                    {
                        fieldLimit = 1;
                        break;
                    }
                    
                    nFields++;
                    fieldParams[nFields][0]=0; fieldParams[nFields][1]=1; fieldParams[nFields][2]=0;    //Initialize the next field parameters
                    fieldParams[nFields][3]=0; fieldParams[nFields][4]=-1; fieldParams[nFields][5]=-1;
                    posCnt = 0;
                }
                break;
            }
        }
        if(fieldLimit)
            break;
    }
    
    if(argc != 0)
    {
        printf("Usage: sort [-nrfd] [-pos1 -pos2]\n");
        return 1;
    }
        
    if((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        for(i = 0; i < nFields; i++)    //sort input by each field in the order specified
            quickSort((void**)lineptr, 0, nlines-1, (int (*)(void*, void*))(fieldParams[i][0]? numcmp : strcmp), fieldParams[i][1],
                        fieldParams[i][2], fieldParams[i][3], fieldParams[i][4], fieldParams[i][5]);

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
void quickSort(void* v[], int left, int right, int (*comp)(void*, void*), int reverse, int fold, int direc, int pos1, int pos2)
{
    int last, i, fieldSort;
    char *s1, *s2;
    char *d1, *d2;
    char *f1, *f2;      //field substrings
    
    if(left >= right)
        return;
    
    swap(v, left, (left+right)/2);
    last = left;
    
    fieldSort = !(pos1==-1 && pos2==-1);    //1 if sorting by field is requested
    
    for(i=left+1; i<=right; i++)
    {
        if(fold)
        {
            s1 = (char*)malloc((strlen(v[i])+1)*sizeof(char));
            strcpy(s1, v[i]);
            lower(s1);
            s2 = (char*)malloc((strlen(v[left])+1)*sizeof(char));
            strcpy(s2, v[left]);
            lower(s2);
            
            if(direc)
            {
                if(fieldSort)
                {
                    d1 = substr(s1, pos1, pos2);
                    d2 = substr(s2, pos1, pos2);
                }
                else
                {
                    d1 = s1;
                    d2 = s2;
                }
                
                while(!isalnum(*d1) && *d1!=' ' && *d1!='\0')
                    d1++;
                    
                while(!isalnum(*d2) && *d2!=' ' && *d2!='\0')
                    d2++;
                
                if(reverse*strcmp(d1, d2) < 0)
                    swap(v, ++last, i);
                    
                if(fieldSort)
                {
                    free(d1);
                    free(d2);
                }
            }
            else
            {
                if(fieldSort)
                {
                    f1 = substr(s1, pos1, pos2);
                    f2 = substr(s2, pos1, pos2);
                }
                else
                {
                    f1 = s1;
                    f2 = s2;
                }
                
                if(reverse*strcmp(f1, f2) < 0)
                    swap(v, ++last, i);
                    
                if(fieldSort)
                {
                    free(f1);
                    free(f2);
                }
            }
            
            free(s1);
            free(s2);
        }
        else
        {
            if(direc)
            {
                if(fieldSort)
                {
                    d1 = substr(v[i], pos1, pos2);
                    d2 = substr(v[left], pos1, pos2);
                }
                else
                {
                    d1 = v[i];
                    d2 = v[left];
                }
                
                while(!isalnum(*d1) && *d1!=' ' && *d1!='\0')
                    d1++;
                    
                while(!isalnum(*d2) && *d2!=' ' && *d2!='\0')
                    d2++;
                
                if(reverse*comp(d1, d2) < 0)
                    swap(v, ++last, i);
                    
                if(fieldSort)
                {
                    free(d1);
                    free(d2);
                }
            }
            else
            {
                if(fieldSort)
                {
                    f1 = substr(v[i], pos1, pos2);
                    f2 = substr(v[left], pos1, pos2);
                }
                else
                {
                    f1 = v[i];
                    f2 = v[left];
                }
                
                if(reverse*comp(f1, f2) < 0)
                    swap(v, ++last, i);
                    
                if(fieldSort)
                {
                    free(f1);
                    free(f2);
                }
            }    
        }
    }
            
    swap(v, left, last);
    quickSort(v, left, last-1, comp, reverse, fold, direc, pos1, pos2);
    quickSort(v, last+1, right, comp, reverse, fold, direc, pos1, pos2);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char* s1, char* s2)
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

/* lower: Converts string s to lowercase */
void lower(char* s)
{
    while(*s)
    {
        *s = tolower(*s);
        s++;
    }
}

/* substr: returns the substring s[pos1]...s[pos2] */
char* substr(char* s, int pos1, int pos2)
{
    char* r;
    int n, i;
    
    n = strlen(s) - 1;  //index of last char in s
    
    r = (char*)malloc((n+2)*sizeof(char));
    
    r[0] = '\0';
    if(pos1 > n)
        return r;
    
    for(i = 0; pos1 <= min(n, pos2); pos1++, i++)
        r[i] = s[pos1];
    
    r[i] = '\0';
    
    return r;
}

int min(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}
