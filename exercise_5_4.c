#include <stdio.h>

int strend(char *s, char *t);

int main(void)
{
    char s[100] = "Hello";
    char t[100] = "lo";

    printf("%d", strend(s, t));
}

// Returns 1 if t occurs at the end of s, 0 otherwise
int strend(char *s, char *t)
{
    int lenS = 1, lenT = 1;

    while(*s)
    {
        s++;
        lenS++;
    }

    while(*t)
    {
        t++;
        lenT++;
    }

    while(lenS==1 || lenT==1)
        return 0;

    while(lenS>0 && lenT>0 && (*s-- == *t--))
    {
        lenS--;
        lenT--;
    }

    return (lenT==0);
}
