#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORDLEN 100

struct tnode 
{
  char* word;
  int match;
  struct tnode* left;
  struct tnode* right;
};

struct tnode* addnode(struct tnode* p, char* w, int* found, int num);
int compare(char* w, struct tnode* p, int* found, int num);
void printtree(struct tnode* root);
struct tnode* talloc(void);
char* strdup(char* s);
int getword(char* word, int limit);
char comment(void);
int getch(void);
void ungetch(int c);

/* groups: print groups in alphebetical order whose constituent words have the first 'num' characters identical */
/* Default value of num is 6 */
/* Usage: groups [-num] */
int main(int argc, char* argv[])
{
    struct tnode* root;
    char word[MAXWORDLEN];
    int num = 6;
    int found = 0;  //1 if a match was found to the current tnode
    
    if(argc-- > 1)
    {
        if(argv[1][0] == '-')
        {
            num = atoi(++argv[1]);
        }
        else
        {
            printf("Usage: groups [-num]\n");
            return 1;
        }
    }
    
    if(argc > 1)
    {
        printf("Usage: groups [-num]\n");
        return 1;
    }
    
    root = NULL;
    while(getword(word, MAXWORDLEN) != EOF)
    {
        if(isalpha(word[0]) && strlen(word)>=num)
            root = addnode(root, word, &found, num);
            
        found = 0;  //reset found to 0 for next word
    }
            
    printtree(root);
    
    return 0;
}


/* addnode: Add a node with w at or below p */
struct tnode* addnode(struct tnode* p, char* w, int* found, int num)
{
    int cond;
	
	if(p == NULL)
	{
		p = talloc();
		p->word = strdup(w);
		p->match = *found;
		p->left = NULL;
		p->right = NULL;
	}
	else if((cond = compare(w, p, found, num)) < 0)
		p->left = addnode(p->left, w, found, num);
	else if(cond > 0)
		p->right = addnode(p->right, w, found, num);
	
	return p;
}

/* compare: sets match in p if w is a match to p->word. Returns strcmp(w, p->word) */ 
int compare(char* w, struct tnode* p, int* found, int num)
{
    int i;
    char* t = p->word;
    
    for(i = 0; *w == *t; i++, w++, t++)
        if(*w == '\0')  //reached end of strings; they are equal
            return 0;
    
    if(i >= num)
    {
        *found = 1;
        p->match = 1;
    }
    
    return *w - *t;
}

/* printtree: in-order print of tree p */
void printtree(struct tnode* p)
{
	if(p != NULL)
	{
		printtree(p->left);
		
		if(p->match)
		    printf("%s\n", p->word);
		    
		printtree(p->right);
	}
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
    int c, d;
    
    while(isspace(c = getch()));
    
    if(c != EOF)
        *word++ = c;
        
    if(isalpha(c) || c=='_' || c=='#')
    {
        for( ; --limit > 0; word++)
            if(!isalnum(*word = getch()) && *word!='_')
            {
                ungetch(*word);
                break;
            }
    }
    else if(c=='\'' || c=='"')
    {
        for( ; --limit > 0; word++)
            if((*word = getch()) == '\\')
                *++word = getch();
            else if(*word == c)
            {
                word++;
                break;
            }
            else if(*word == EOF)
                break;
    }
    else if(c=='/')
    {
        if((d = getch()) == '*')
            c = comment();
        else
            ungetch(d);
    }

    *word = '\0';
    
    return c;
}

/* comment: skip over comment and return the next character */
char comment(void)
{
    int c;
    
    while((c = getch()) != EOF)
        if(c = '*')
            if((c = getch()) == '/')
                break;
            else
                ungetch(c);
                
    return c;            
}

int buf = 0;    //single character buffer to hold pushed back input values

/* gets a character from input */
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

/* pushes a character back to input */
void ungetch(int c)
{
    if(buf==0)
        buf = c;
    else
        printf("ungetch: buffer full.\n");
}
