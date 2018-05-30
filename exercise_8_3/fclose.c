/* fclose: close file fp */
int fclose(FILE* fp)
{
	if(fp->flag & _WRITE)
		if(fflush(fp) != 0)		//write out anything left in the buffer
			return EOF;

	fp->cnt = 0;			//reset all parameters
	fp->ptr = NULL;
	fp->base = NULL;
	fp->flag = 0;
	fp->fd = 0;

	return 0;
}