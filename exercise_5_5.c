#include <stdio.h>

void mystrcpy(char* s, char* t, int n);
void mystrcat(char* s, char* t, int n);
int strcmp(char *s, char *t, int n);

int main(void)
{
    char s[100] = "Hello ";
    char t[100] = "World!";

	mystrcat(s, t, 3);

    printf("%s", s);
}

// Copies at most n chars of string t to s
void mystrcpy(char* s, char* t, int n)
{
    while(n-->0 && (*s++ = *t++));

    if(*--s != '\0')
        *++s = '\0';
}

// Concatenates at most n chars of string t to end of s
void mystrcat(char* s, char* t, int n)
{
    while(*s)
        s++;

    while(n-->0 && (*s++ = *t++));
}

// compare at most n chars of s & t
int strcmp(char *s, char *t, int n)
{
    for( ; n>0 && (*s == *t); s++, t++, n--)
        if(*s == '\0' || n==1)
            return 0;

    return *s - *t;
}
