#include <stdio.h>

int any(char s1[], char s2[]);

int main()
{
    char s1[] = "wadddasd";
    char s2[] = "ds";
    
    printf("%d", any(s1, s2));
    
    return 0;
}


/* any: return first position in s1 where any character from s2 occurs, -1 otherwise */
int any(char s1[], char s2[])
{
    int i, j;
    
    for(i = 0; s1[i] != '\0'; i++)
        for(j = 0; s2[j] != '\0'; j++)
            if(s1[i] == s2[j])
                return i;
                
    return -1;
}