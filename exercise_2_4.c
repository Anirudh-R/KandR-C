#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main()
{
    char s1[] = "wadddasd";
    char s2[] = "ds";
    
    squeeze(s1, s2);
    
    printf("%s", s1);
    
    return 0;
}


/* squeeze: delete chars in s1 which are in s2 */
void squeeze(char s1[], char s2[])
{
    int indx, i, j;
    
    indx = 0;
    for(i = 0; s1[i] != '\0'; i++)
    {
        for(j = 0; s2[j]!='\0' && s2[j]!=s1[i]; j++);
        
        if(s2[j] == '\0')       
            s1[indx++] = s1[i];
    }
    
    s1[indx] = '\0';
}