#define BUFSIZE 10000

static char allocbuf[BUFSIZE];
char *allocp = allocbuf;

char* alloc(int len)
{
	if(allocbuf + BUFSIZE - allocp >=  len)
	{
		allocp += len;
		return allocp - len;
	}
	else
		return 0;
}

void afree(char *p)
{
	if(p>=allocbuf && p<allocbuf+BUFSIZE)
		allocp = p;
}
