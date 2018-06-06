#include <stdio.h>

int main()
{
    char s[] = "0x7236342a";
    
    printf("%d", htoi(s));
    
    return 0;
}


/* convert hexadecimal string in s[] to integer */
int htoi(char s[])
{
    int result, digit, numdigits, i;
    
    i = 0;
    if(s[i] == '0')     //skip optional 0x or 0x
    {
        i++;
        if(s[i]=='x' || s[i]=='X')
            i++;
    }
    
    result = 0;
    numdigits = 0;
    while(numdigits < 8)        //maximum hexadecimal digits to represent 32-bit int
    {
        if(s[i]>='0' && s[i]<='9')
            digit = s[i] - '0';
        else if(s[i]>='a' && s[i]<='f')
            digit = s[i] - 'a' + 10;
        else if(s[i]>='A' && s[i]<='F')
            digit = s[i] - 'A' + 10;
        else if(s[i] == '\0')
            break;
        else
            return -1;
        
        result = 16*result + digit;
        numdigits++;
        i++;
    }
    
    return result;
}
