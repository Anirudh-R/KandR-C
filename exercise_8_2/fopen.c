#include <fcntl.h>
#include "syscalls.h"

#define PERMS 0666

/* In stdio.h, the file stucture definition needs to be changed to

typedef struct _iobuf {
    int cnt;
    char* ptr;
    char* base;
    struct flag_field {
        is_read : 1;
        is_write : 1;
        is_unbuf : 1;
        is_buf : 1;
        is_eof : 1;
        is_err : 1;
    } flag;
    int fd;
}   FILE;

*/

/* open and return file pointer to the file 'name' */
FILE* fopen(char* name, char* mode)
{
    int fd;
    FILE* fp;
    
    if(*mode!='r' && *mode!='w' && *mode!='a')
        return NULL;
        
    for(fp = _iob; fp <= _iob + OPEN_MAX; fp++)
        if(fp->flag.is_read==0 && fp->flag.is_write==0)     //free slot found
            break;
            
    if(fp >= _iob + OPEN_MAX)
        return NULL;
        
    if(*mode == 'w')
        creat(name, PERMS);
    else if(*mode == 'a')
    {
        if((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
            
        lseek(fd, 0L, 2);
    }
    else
        fd = open(name, O_RDONLY, 0);
    
    if(fd == -1)
        return NULL;
    
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag.is_unbuf = 0;
    fp->flag.is_buf = 1;
    fp->flag.is_eof = 0;
    fp->flag.is_err = 0;
    if(*mode == 'r')
    {
        fp->flag.is_read = 1;
        fp->flag.is_write = 0;
    }
    else
    {
        fp->flag.is_read = 0;
        fp->flag.is_write = 1;
    }
    
    return fp;
}