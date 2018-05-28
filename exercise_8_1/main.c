#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include "syscalls.h"

void fcopy(int fd1, int fd2);
void error(char* fmt, ...);

/* cat: concatenate files to output. */
int main(int argc, char* argv[])
{
    int fd;
    
    if(argc == 1)       //no args; copy stdin to stdout
        fcopy(1, 0);
    else
        while(--argc)
        {
            if((fd = open(*++argv, O_RDONLY, 0)) == -1)
                error("cat: couldn't open %s", *argv);
            else
            {
                fcopy(1, fd);
                close(fd);
            }
        }

    return 0;
}


/* fcopy: copy fd1 to fd2 */
void fcopy(int fd2, int fd1)
{
    char buf[BUFSIZ];
    int n;
    
    while((n = read(fd1, buf, BUFSIZ)) > 0)
        if(write(fd2, buf, n) != n)
            error("cat: write error.");
}


/* print error message and exit */
void error(char* fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    
    exit(1);
}