#include <stdio.h>

int lower(int c);

int main()
{
    char c = 'S';
    
    putchar(lower(c));
    
    return 0;
}


/* lower: convert ASCII chars to lower case */
int lower(int c)
{
    return (c>='A' && c<='Z') ? c-'A'+'a' : c;
}
