#include <stdio.h>

void mystrcat(char* s, char* t);

int main(void)
{
    char s[100] = "Hello ";
    char t[100] = "World!";

	mystrcat(s, t);
	
    printf("%s", s);
}

// Concatenates string t to end of s
void mystrcat(char* s, char* t)
{
    while(*s)
        s++;

    while(*s++ = *t++);
}
