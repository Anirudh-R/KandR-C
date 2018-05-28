#include <stdio.h>

#define MAXLINE 1000

int strindex(char s[], char t[]);
int getline(char s[], int lim);

int main(void) 
{
    char line[MAXLINE];
    char term[] = "ould";
    int lastOcc;
    
    while(getline(line, MAXLINE) > 0)
        if((lastOcc=strindex(line, term)) > 0)
            printf("%s %d\n", line, lastOcc);

	return 0;
}


/* Find the first occurence of string t in s, -1 if none*/
int strindex(char s[], char t[])
{
    int i, j, k;
    int lastOcc;
    
    lastOcc = -1;
    for(i=0; s[i]!='\0'; i++)
    {
        for(j=i, k=0; s[j]==t[k] && t[k]!='\0'; j++, k++);
        
        if(k>0 && t[k]=='\0')
            lastOcc = i;
    }
    
    return lastOcc;
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
