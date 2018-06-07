#include <stdio.h>

#define ABS(x) ((x)<0 ? -(x) : (x))

void itoa(int n, char s[], int w);
void reverse(char s[]);

int main(void)
{
    int n = -214647;
    char s[50];
    
    itoa(n, s, 11);
    
    printf("%s", s);
    
    return 0;
}


/* itoa: convert n to characters in s, padded on the left to width w */
void itoa(int n, char s[], int w)
{
    int i, sign;
    
    sign = n;    
    i = 0;
    do {
        s[i++] = ABS(n % 10) + '0';
    } while((n /= 10) != 0);
    
    if(sign < 0)
        s[i++] = '-';
    
    while(i < w)
        s[i++] = ' ';
    
    s[i] = '\0';
    
    reverse(s);
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

