#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void reverser(char s[], int left, int len);

int main(void)
{
    char s[] = "Reverse";
    
    reverse(s);
    
    printf("%s\n", s);
    
    return 0;
}


void reverse(char s[])
{
    reverser(s, 0, strlen(s));
}

void reverser(char s[], int left, int len)
{
    int right, temp;
    
    right = len - (left + 1);
    if(left < right)
    {
        temp = s[right];
        s[right] = s[left];
        s[left] = temp;
        
        reverser(s, ++left, len);
    }
}
