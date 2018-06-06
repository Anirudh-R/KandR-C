#include <stdio.h>

void escape(char s[], char t[]);

int main(void)
{
    char t[] = {'r', 'y', '\n', 'u', '\t', 'w', '\0'};
    char s[50];
    
    escape(s, t);
    
    printf("%s", s);
    
    return 0;
}


/* escape: copy t to s expanding escape characters */
void escape(char s[], char t[])
{
    int i, j;
    
    for(i = j = 0; t[i] != '\0'; i++)
        switch(t[i])
        {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
                
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
                
            default:
                s[j++] = t[i];
                break;
        }
        
    s[j] = '\0';
}

