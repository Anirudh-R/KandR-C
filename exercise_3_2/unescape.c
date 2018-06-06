#include <stdio.h>

void unescape(char s[], char t[]);

int main(void)
{
    char t[] = {'r', 'y', '\n', 'u', '\\', 't', 'x', '\\', 'b', '\0'};
    char s[50];
    
    unescape(s, t);
    
    printf("%s", s);
    
    return 0;
}


/* unescape: Covert escape sequences into real chars while copying from t to s */
void unescape(char s[], char t[])
{
    int i, j;
    
    for(i = j = 0; t[i] != '\0'; i++)
        if(t[i] != '\\')
            s[j++] = t[i];
        else
            switch(t[++i])
            {
                case 'n':
                    s[j++] = '\n';
                    break;
                    
                case 't':
                    s[j++] = '\t';
                    break;
                    
                default:
                    s[j++] = '\\';
                    s[j++] = t[i];
                    break;
            }
    
    s[j] = '\0';
}

