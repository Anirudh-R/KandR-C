#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORDLEN 100      //Max length of a word
#define MAXWORDS 1000       //Max number of distinct words in input

struct tnode 
{
  char* word;
  int count;
  struct tnode* left;
  struct tnode* right;
};

struct tnode* addnode(struct tnode* p, char* w, struct tnode* structarr[], int* numwords);
void sortarr(struct tnode* structarr[], int numwords);
void printarr(struct tnode* structarr[], int numwords);
struct tnode* talloc(void);
char* strdup(char* s);
int getword(char* word, int limit);
int getch(void);
void ungetch(int c);

/* list words in input according to decreasing frequency of occurence */
int main()
{
    struct tnode* root;
    char word[MAXWORDLEN];
    struct tnode* structarr[MAXWORDS];      //array holding pointer to all tnodes
    int numwords = 0;                       //number of distinct words in input
    
    root = NULL;
    while(getword(word, MAXWORDLEN) != EOF)
        if(isalpha(word[0]))
            root = addnode(root, word, structarr, &numwords);
    
    sortarr(structarr, numwords);
            
    printarr(structarr, numwords);
    
    return 0;
}


/* addnode: Add a node with w at or below p */
struct tnode* addnode(struct tnode* p, char* w, struct tnode* structarr[], int* numwords)
{
    int cond;
	
	if(p == NULL)
	{
		p = talloc();
		
		if(*numwords < MAXWORDS)
		    structarr[(*numwords)++] = p;       //add pointer to the new node into structarr
		
		p->word = strdup(w);
		p->count = 1;
		p->left = NULL;
		p->right = NULL;
	}
	else if((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if(cond < 1)
		p->left = addnode(p->left, w, structarr, numwords);
	else
		p->right = addnode(p->right, w, structarr, numwords);
	
	return p;
}

/* sortarr: bubble sort structarr in decreasing order of counts */
void sortarr(struct tnode* structarr[], int numwords)
{
    int i, j;
    struct tnode* temp;
    
    for(i = 0; i < numwords-1; i++)
        for(j = 0; j < numwords-1-i; j++)
            if(structarr[j]->count < structarr[j+1]->count)
            {
                temp = structarr[j];
                structarr[j] = structarr[j+1];
                structarr[j+1] = temp;
            }
}

/* printarr: print the words and their counts */
void printarr(struct tnode* structarr[], int numwords)
{
    int i;
    
    for(i = 0; i < numwords; i++)
        printf("%4d    %s\n", structarr[i]->count, structarr[i]->word);
}

/* talloc: make a tnode */
struct tnode* talloc(void)
{
	return (struct tnode*)malloc(sizeof(struct tnode));
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
    
    while(isspace(c = getch()));
    
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
