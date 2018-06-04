#include <stdio.h>

#define MAXLINE	 1000   //Maximum input line size

int getline(char s[], int lim);
void reverse(char s[]);

/* Reverse input lines */
int main()
{
	char line[MAXLINE];     
	
    while(getline(line, MAXLINE) > 0)
    {
        reverse(line);
        printf("%s", line);
    }

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

/* reverse: reverse string s[] */
void reverse(char s[])
{
    int i, j;
    char temp;
    
    i = 0;
    while(s[i] != '\0')
        i++;
    
    i--;
    if(s[i] == '\n')    //leave the newline in place
        i--;
        
    j = 0;
    while(j < i)
    {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        
        j++;
        i--;
    }
}

