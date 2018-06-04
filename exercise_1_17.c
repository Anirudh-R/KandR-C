#include <stdio.h>

#define MAXLINE	 1000   //Maximum input line size
#define THRESHLEN   80

int getline(char s[], int lim);

/* Print input lines above THRESHLEN */
int main()
{
	char line[MAXLINE];     
	int len;
	
    while((len = getline(line, MAXLINE)) > 0)
        if(len > THRESHLEN)
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
