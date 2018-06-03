#include <stdlib.h>

#define NALLOC 1024		//minimum no. of units to request

typedef long Align;		//Alignment to long boundary

union header			//block header
{
	struct
	{
		union header* ptr;		//next block on free list
		unsigned int size;		//size of this block (in units of Header size)
	} s;

	Align x;					//to force alignment
};

typedef union header Header;


void* mymalloc(unsigned int nbytes);
void* mycalloc(unsigned int n, unsigned int size);
static Header* morecore(unsigned int nu);
void myfree(void* ap);
char* sbrk(int size);


static Header base;				//empty list to get started
static Header* freep = NULL;	//start of free list

/* malloc: general-purpose storage allocator */
void* mymalloc(unsigned int nbytes)
{
	Header *p, *prevp;
	unsigned int nunits;

	nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;	//+1 for the block header

	if((prevp = freep) == NULL)		//no free list yet
	{
		base.s.ptr = prevp = freep = &base;
		base.s.size = 0;
	}

	for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
	{
		if(p->s.size >= nunits)		//big enough
		{
			if(p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else
			{
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}

			freep = prevp;
			return (void*)(p + 1);
		}

		if(p == freep)		//wrapped around free list
			if((p = morecore(nunits)) == NULL)
				return NULL;
	}
}


/* morecore: ask system for more memory */
static Header* morecore(unsigned int nu)
{
	char* cp;
	Header* up;

	if(nu < NALLOC)
		nu = NALLOC;

	cp = sbrk(nu * sizeof(Header));
	if(cp == (char*)(-1))			//no space from system
		return NULL;

	up = (Header*)cp;
	up->s.size = nu;
	myfree((void*)(up+1));

	return freep;
}


/* free: put block ap in free list */
void myfree(void* ap)
{
	Header *bp, *p;

	bp = (Header*)ap - 1;	//point to block header
	for(p = freep; !(p < bp && bp < p->s.ptr); p = p->s.ptr)
		if(p >= p->s.ptr && (p < bp || bp < p->s.ptr))			//bp beyond start or end of arena
			break;

	if(bp + bp->s.size == p->s.ptr)		//join to upper neighbour
	{
		bp->s.size += (p->s.ptr)->s.size;
		bp->s.ptr = (p->s.ptr)->s.ptr;
	}
	else
		bp->s.ptr = p->s.ptr;

	if(p + p->s.size == bp)				//join to lower neighbour
	{
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	}
	else
		p->s.ptr = bp;

	freep = p;
}


/* mycalloc: allocate zero-initialized storage of size n*size */
void* mycalloc(unsigned int n, unsigned int size)
{
    char *ret, *p;
    unsigned int nb, i;

    nb = n*size;
    if((ret = p = (char*)mymalloc(nb)) != NULL)
        for(i = 0; i < nb; i++)
            *p++ = 0;

    return ret;
}

