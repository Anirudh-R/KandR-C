#include <stdio.h>

#define ABS(x) ((x)<0 ? -(x) : (x))

void itoa(int n, char s[], int b);
void reverse(char s[]);

int main(void)
{
    int n = -214745;
    char s[50];
    
    itoa(n, s, 16);
    
    printf("%s", s);
    
    return 0;
}


/* itoa: convert n to base b representation in s */
void itoa(int n, char s[], int b)
{
    int i, sign, temp;
    
    sign = n;    
    i = 0;
    do {
        temp = ABS(n % b);
        s[i++] = (temp <= 9) ? temp+'0' : temp+'A'-10;
    } while((n /= b) != 0);
    
    if(sign < 0)
        s[i++] = '-';
    
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

