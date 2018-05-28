#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORDLEN 100

struct linkedlist           //linked list of line numbers
{
  int ln;                   //line no.
  struct linkedlist* ptr;   //pointer to next element in the linked list
};

struct tnode 
{
  char* word;
  struct linkedlist* lines;     //pointer to its list of line numbers
  struct tnode* left;
  struct tnode* right;
};

struct tnode* addnode(struct tnode* p, char* w, int linenum);
void addln(struct tnode* p, int linenum);
void printtree(struct tnode* root);
int isnoiseword(char* word);
struct tnode* talloc(void);
struct linkedlist* lalloc(void);
char* strdup(char* s);
int getword(char* word, int limit);
int getch(void);
void ungetch(int c);

/* list of line numbers for all the words in input */
int main()
{
    struct tnode* root;
    char word[MAXWORDLEN];
    int linenum = 1;
    
    root = NULL;
    while(getword(word, MAXWORDLEN) != EOF)
        if(isalpha(word[0]) && isnoiseword(word)==-1)
            root = addnode(root, word, linenum);
        else if(word[0] == '\n')
            linenum++;
            
    printtree(root);
    
    return 0;
}


/* addnode: Add a node with w at or below p */
struct tnode* addnode(struct tnode* p, char* w, int linenum)
{
    int cond;
	
	if(p == NULL)               //new node
	{
		p = talloc();
		p->word = strdup(w);
		p->lines = lalloc();
		p->lines->ln = linenum;
		p->lines->ptr = NULL;
		p->left = NULL;
		p->right = NULL;
	}
	else if((cond = strcmp(w, p->word)) == 0)
		addln(p, linenum);
	else if(cond < 1)
		p->left = addnode(p->left, w, linenum);
	else
		p->right = addnode(p->right, w, linenum);
	
	return p;
}

/* addln: Add a line no. to the linked list if not already recorded */
void addln(struct tnode* p, int linenum)
{
    struct linkedlist* t = p->lines;
    
    while(t->ptr!=NULL && t->ln!=linenum)
        t = t->ptr;
    
    if(t->ln != linenum)
    {
        t->ptr = lalloc();
        t->ptr->ln = linenum;
        t->ptr->ptr = NULL;
    }
}

/* printtree: in-order print of tree p */
void printtree(struct tnode* p)
{
    struct linkedlist* t;
    
	if(p != NULL)
	{
		printtree(p->left);
		
		printf("%s    ", p->word);
		
		t = p->lines;
		while(t != NULL)
		{
		    printf("%d ", t->ln);
		    t = t->ptr;
		}
		printf("\n");
		
		printtree(p->right);
	}
}

/* isnoiseword: Returns -1 if word is not a noiseword, >= otherwise */
int isnoiseword(char* word)
{
    static char* nw[] = {
        "a",
        "an",
        "and",
        "are",
        "in",
        "is",
        "of",
        "or",
        "that",
        "the",
        "this",
        "to"
    };
    int low, mid, high, cond, n;
    
    n = sizeof(nw)/sizeof(nw[0]);
    
    low = 0;
    high = n-1;
    while(low <= high)
    {
        mid = (low + high)/2;
        if((cond = strcmp(word, nw[mid])) < 0)
            high = mid - 1;
        else if(cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    
    return -1;
}

/* talloc: make a tnode */
struct tnode* talloc(void)
{
	return (struct tnode*)malloc(sizeof(struct tnode));
}

/* lalloc: make a new linked list element */
struct linkedlist* lalloc(void)
{
    return (struct linkedlist*)malloc(sizeof(struct linkedlist));
}

/* strdup: return a duplicate of s */
char* strdup(char* s)
{
	char* p;
	
	p = (char*)malloc((strlen(s) + 1)*sizeof(char));
	
	if(p != NULL)
		strcpy(p, s);
	
	return p;
}

/* getword: get next word or character from input */
int getword(char* word, int limit)
{
    int c;
    
    while((c=getch())==' ' || c=='\t');
    
    if(c != EOF)
        *word++ = c;
        
    if(!isalpha(c))
    {
        *word = '\0';
        return c;
    }
    
    for( ; --limit > 0; word++)
        if(!isalnum(*word = getch()))
        {
            ungetch(*word);
            break;
        }
        
    *word = '\0';
    
    return word[0];
}

int buf = 0;    //single character buffer to hold pushed back input values

/* getch: gets a character from input */
int getch(void)
{
    int c;
    
    if(buf==0)
    {
        c = getchar();
    }
    else 
    {
        c = buf;
        buf = 0;
    }
        
    return c;
}

/* ungetch: pushes a character back to input */
void ungetch(int c)
{
    if(buf==0)
        buf = c;
    else
        printf("ungetch: buffer full.\n");
}
