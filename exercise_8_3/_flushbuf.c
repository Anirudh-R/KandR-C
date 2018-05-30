#include "syscalls.h"

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int x, FILE* fp)
{
	unsigned int nc;
	int bufsize;

	if(fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF;

	if((fp->flag & (_WRITE | _ERR)) != _WRITE)	//should be open for writing
		return EOF;

	bufsize = (fp->flag & _UNBUF) : 1 : BUFSIZ;

	if(fp->base == NULL)						//buffer doesn't exist
	{
		if((fp->base = (char*)malloc(bufsize)) == NULL)
		{
			fp->flag |= _ERR;
			return EOF;
		}
	}
	else
	{
		nc = fp->ptr - fp->base;
		if(write(fp->fd, fp->ptr, nc) != nc)	//write out buf to file
		{
			fp->flag |= _ERR;
			return EOF;
		}
	}

	fp->ptr = fp->base;
	*fp->ptr++ = (char)x;
	fp->cnt = bufsize - 1;
	return x;
}