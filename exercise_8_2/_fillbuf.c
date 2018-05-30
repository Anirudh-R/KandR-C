#include "syscalls.h"

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

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE* fp)
{
    int bufsize;
    
    if(fp->flag.is_read==0 || fp->flag.is_eof==1 || fp->flag.is_err==1)
        return EOF;
        
    bufsize = (fp->flag.is_unbuf) ? 1 : BUFSIZ;
    
    if(fp->base == NULL)
        if((fp->base = (char*)malloc(bufsize)) == NULL)
            return EOF;
            
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    
    if(--fp->cnt < 0)
    {
        if(fp->cnt == -1)
            fp->flag.is_eof = 1;
        else
            fp->flag.is_err = 1;
        
        fp->cnt = 0;
        return EOF;
    }
    
    return (unsigned char) *fp->ptr++;
}
