#include <stdio.h>

void expand(char s1[], char s2[]);

int main(void)
{
    char t[] = {'r', '-', 'y', 'u', '\\', 't', '\n', 'x', '-', 'p', '\\', 'b', '\0'};
    char s[50];
    
    expand(t, s);
    
    printf("%s", s);
    
    return 0;
}


/* expand: Expand shorthand notations in s1 into s2 */
void expand(char s1[], char s2[])
{
    int i, j;
    char c;
    
    i = j = 0;
    while((c = s1[i++]) != '\0')
    {
        if(s1[i]=='-' && s1[i+1]>=c)
        {
            i++;
            while(c < s1[i])
                s2[j++] = c++;
        }
        else
            s2[j++] = c;
    }
    
    s2[j] = '\0';
}

