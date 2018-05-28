#include <stdio.h>

void printd(int n);
int itoa(char s[], int n, int i);

int main(void)
{
    char s[100] = ""; 
    
    //printd(-347);
    
    itoa(s, -347, 0);
    printf("%s\n", s);
    
    return 0;
}

/* printd(): prints n in decimal. */
void printd(int n)
{
    if(n < 0)
    {
        putchar('-');
        n = -n;
    }
    
    if(n/10 > 0)        // If 2 or more digits remain
        printd(n/10);
    putchar(n%10 + '0');
}

/* itoa(): converts n into a string and puts it in s, starting at index i. Returns length. */
int itoa(char s[], int n, int i)
{
    if(n < 0)
    {
        s[i++] = '-';
        n = -n;
    }
    
    if(n/10 > 0)
        i = itoa(s, n/10, i);
    s[i++] = n%10 + '0';
    
    s[i] = '\0';
    
    return i;
}
