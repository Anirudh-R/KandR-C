#include <stdio.h>
#include <stdlib.h>

#define NALLOC 1024		//minimum no. of units to request
#define MAXBYTES 10240  //max no. of bytes to request

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


static Header base;				    //empty list to get started
static Header* freep = NULL;	    //start of free list
static unsigned int maxalloc = 0;   //max no. of units allocated currently

/* malloc: general-purpose storage allocator */
void* mymalloc(unsigned int nbytes)
{
	Header *p, *prevp;
	unsigned int nunits;

    if(nbytes > MAXBYTES)
    {
        fprintf(stderr, "mymalloc: can't allocate more than %u bytes at a time.\n", MAXBYTES);
        return NULL;
    }

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

	maxalloc = (nu > maxalloc) ? nu : maxalloc;

	myfree((void*)(up+1));

	return freep;
}


/* free: put block ap in free list */
void myfree(void* ap)
{
	Header *bp, *p;

	bp = (Header*)ap - 1;	//point to block header
	if(bp->s.size == 0 || bp->s.size > maxalloc)
    {
        fprintf(stderr, "myfree: can't free %u units.\n", bp->s.size);
        return;
    }

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


/* bfree: free an arbirary block p of n characters. Return no. of units freed. */
unsigned int bfree(char* p, unsigned int n)
{
    Header* hp;

    if(n < sizeof(Header))      //too small to be useful
        return 0;

    hp = (Header*)p;

    hp->s.size = n/sizeof(Header);
    free((void*)(hp+1));

    return hp->s.size;
}

