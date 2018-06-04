#include <stdio.h>

#define MAXLINE	 1000   //Maximum input line size

int getline(char s[], int lim);
void copy(char to[], char from[]);

/* Print longest input line */
int main()
{
	char line[MAXLINE];     
	char longest[MAXLINE];  
	int max, len;
	
	max = 0;
    while((len = getline(line, MAXLINE)) > 0)
    {
        printf("%d, %s", len, line);
        if(len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
	
	if(max > 0)     //there was a line
	    printf("\n%s", longest);

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

/* copy from[] into to[] assuming its big enough */
void copy(char to[], char from[])
{
    int i;
    
    i = 0;
    while((to[i] = from[i]) != '\0')
        i++;
}

