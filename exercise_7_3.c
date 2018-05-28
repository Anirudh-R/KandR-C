#include <stdio.h>
#include <stdarg.h>

#define LOCALFMTLEN 100

void minprintf(char* fmt, ...);

int main()
{
    minprintf("integer = %.5d\ndouble = %10.4f\nstring = %s\nrandom = %r\n", 543, 5.678, "Hello Anirudh!", 4.5656756);   

    return 0;
}


/* minprintf: minimal printf with variable argument list. */
void minprintf(char* fmt, ...)
{
    va_list ap;
    char *p, *sval;
    char localfmt[LOCALFMTLEN];
    unsigned int uval;
    int ival, i;
    double dval;
    
    va_start(ap, fmt);
    
    for(p = fmt; *p; p++)
    {
        if(*p != '%')
        {
            putchar(*p);
            continue;
        }
        
        i = 0;
        localfmt[i++] = '%';
        while(*(p+1) && !isalpha(*(p+1)))     //copy format string till you find the format specifier
            localfmt[i++] = *++p;
        
        localfmt[i++] = *++p;   //format specifier
        localfmt[i] = '\0';
        
        switch(*p)
        {
            case 'i':
            case 'd': ival = va_arg(ap, int);
                      printf(localfmt, ival);
                      break;
                      
            case 'x':
            case 'X':
            case 'u':
            case 'o': uval = va_arg(ap, unsigned int);
                      printf(localfmt, uval);
                      break;
                        
            case 'f': dval = va_arg(ap, double);
                      printf(localfmt, dval);
                      break;
                      
            case 's': sval = va_arg(ap, char*);
                      printf(localfmt, sval);
                      break;
                      
            default: printf(localfmt);
                     break;
        }
    }
    
    va_end(ap);
}
