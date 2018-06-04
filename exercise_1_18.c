#include <stdio.h>

#define MAXLINE	 1000   //Maximum input line size

int getline(char s[], int lim);
int removeblanks(char s[], int len);

/* Remove trailing blanks and tabs of input lines */
int main()
{
	char line[MAXLINE];     
	int len;
	
    while((len = getline(line, MAXLINE)) > 0)
        if(removeblanks(line, len) >= 0)
            printf("%s", line);

    return 0;
}


/* getline: Read a line of max lim chars into s, return length */
int getline(char s[], int lim)
{
    int c, i;
    
    for(i = 0; (c = getchar())!=EOF && c!='\n' && i<lim-1; )
        s[i++] = c;
    
    if(c == '\n' && i < lim-1)
        s[i++] = c;
    
    s[i] = '\0';
    
    return i;
}

/* removeblanks: Remove trailing blanks and tabs */
int removeblanks(char s[], int len)
{
    while(len-->0 && (s[len]==' ' || s[len]=='\t' || s[len]=='\n'));
    
    return len;
}

