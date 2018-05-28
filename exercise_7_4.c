#include <stdio.h>
#include <stdarg.h>

int minscanf(char* fmt, ...);

int main()
{
    int a = 0, b = 0, ret;
    
    ret = minscanf("%d %d", &a, &b);
    
    printf("a = %d b = %d\nret = %d", a, b, ret);

    return 0;
}

/* minscanf: minimal scanf with variable argument list */
int minscanf(char* fmt, ...)
{
    va_list ap;
    int* iptr;
    float* fptr;
    char *cptr, *sptr;
    int c, instr, ret;
    char tempstr[2];
    
    va_start(ap, fmt);
    
    ret = 0;
    instr = 0;
    for( ; *fmt; fmt++)
    {
        if(!isspace(*fmt))
        {
            if(*fmt == '%')
                switch(*++fmt)
                {
                    case 'd': iptr = va_arg(ap, int*);
                              scanf("%d", iptr);
                              ret++;
                              continue;
                              
                    case 'f': fptr = va_arg(ap, float*);
                              scanf("%f", fptr);
                              ret++;
                              continue;
                              
                    case 'c': cptr = va_arg(ap, char*);
                              scanf("%c", cptr);
                              ret++;
                              continue;
                    
                    case 's': sptr = va_arg(ap, char*);
                              scanf("%s", sptr);
                              ret++;
                              continue;
                              
                    default: va_end(ap);
                             return ret;    //unknown format specifier
                }
            
            scanf("%1s", tempstr);      //If the character in the format does not match that in input
            if(tempstr[0] != *fmt);
            {
                va_end(ap);
                return ret;
            }
        }
    }
    
    va_end(ap);
    
    return ret;
}
