#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORDLEN 100
#define HASHTABSIZE 101

struct nlist
{
  char* name;   //defined name
  char* defn;   //replacement text
  struct nlist* next;
};

struct nlist* hashtab[HASHTABSIZE];     //array of pointers to linked lists

unsigned int hash(char* s);
struct nlist* lookup(char* s);
struct nlist* install(char* name, char* defn);
void undef(char* name);

void getdef(void);
void error(int c, char* s);
void skipblanks(void);
char* strdup(char* s);
int getword(char* word, int limit);
int comment(void);
int getch(void);
void ungetch(int c);
void ungets(char s[]);

/* simple C #define & #undef processor */
int main()
{
    char word[MAXWORDLEN];
    struct nlist* p;
    
    while(getword(word, MAXWORDLEN) != EOF)
    {
        if(strcmp(word, "#") == 0)
            getdef();
        else if(!isalpha(word[0]))
            printf("%s", word);
        else if((p = lookup(word)) == NULL)     //keywords, variable names etc
            printf("%s", word);
        else
            ungets(p->defn);        //push definition
    }
    
    return 0;
}


/* hash: return hash value for string s */
unsigned int hash(char* s)
{
    unsigned int hashval;
    
    for(hashval = 0; *s!='\0'; s++)
        hashval = *s + 31*hashval;
        
    return hashval%HASHTABSIZE;
}

/* lookup: look for s in hashtab */
struct nlist* lookup(char* s)
{
    struct nlist* ptr;
    
    for(ptr = hashtab[hash(s)]; ptr!=NULL; ptr = ptr->next)
        if(strcmp(s, ptr->name) == 0)       //match found
            return ptr;
            
    return NULL;        //not found
}

/* install: Add name,defn to hashtab. Update if already existing. */ 
struct nlist* install(char* name, char* defn)
{
    struct nlist* ptr;
    unsigned int hashval;
    
    if((ptr = lookup(name)) == NULL)    //new entry
    {
        ptr = (struct nlist*)malloc(sizeof(struct nlist));
        
        if(ptr==NULL || (ptr->name = strdup(name))==NULL)
            return NULL;
        
        hashval = hash(name);
        ptr->next = hashtab[hashval];
        hashtab[hashval] = ptr;
    }
    else        //update old definition
    {
        free(ptr->defn);
    }
    
    if((ptr->defn = strdup(defn)) == NULL)
        return NULL;
        
    return ptr;
}

/* undef: remove name,defn from hashtab */
void undef(char* name)
{
    struct nlist *ptr, *prev;
    unsigned int hashval;
    
    if((ptr = lookup(name)) != NULL)
    {
        free(ptr->name);    
        free(ptr->defn);
        
        hashval = hash(name);
        for(prev = hashtab[hashval]; prev->next!=ptr && prev!=ptr; prev = prev->next);       //find the previous node
        
        if(prev == ptr)                     //it is the first node in the chain
            hashtab[hashval] = ptr->next;
        else
            prev->next = ptr->next;
            
        free(ptr);
    }
}

/* getdef: get definition and install it */
void getdef(void)
{
    int c, i;
    char dir[MAXWORDLEN], name[MAXWORDLEN], def[MAXWORDLEN];
    
    skipblanks();
    
    if(!isalpha(getword(dir, MAXWORDLEN)))
    {
        error(dir[0], "getdef: expecting a directive after #.");
    }
    else if(strcmp(dir, "define") == 0)
    {
        skipblanks();
        
        if(!isalpha(getword(name, MAXWORDLEN)))
        {
            error(name[0], "getdef: define name should start with an alphabet.");
        }
        else
        {
            skipblanks();
            
            for(i = 0; i < MAXWORDLEN-1; i++)
                if((def[i] = getch())==EOF || def[i]=='\n')
                    break;                                      //End of definition
            
            def[i] = '\0';
            
            if(i <= 0)
                error('\n', "getdef: incomplete define.");
            else
                install(name, def);
        }
    }
    else if(strcmp(dir, "undef") == 0)
    {
        skipblanks();
        
        if(!isalpha(getword(name, MAXWORDLEN)))
            error(name[0], "getdef: undef name should start with an alphabet.");
        else
            undef(name);
    }
    else
    {
        error(dir[0], "expecting a directive after #.");
    }
}

/* error: print error message and skip rest of the line */
void error(int c, char* s)
{
    printf("Error: %s\n", s);
    
    while(c!=EOF && c!='\n')
        c = getch();
}

/* skipblanks: skip blank and tab characters. */
void skipblanks(void)
{
    int c;
    
    while((c = getch())==' ' || c=='\t');
    
    ungetch(c);
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
    
    //while(isspace(c = getch()));
    
    if((c = getch()) != EOF)
        *word++ = c;
        
    if(isalpha(c) || c=='_')
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
        {
            c = comment();
            c = ' ';            //to return a blank instead of '/'
            *(word-1) = ' ';    //blank out the first '/' to prevent it being printed
        }
        else
            ungetch(d);
    }

    *word = '\0';
    
    return c;
}

/* comment: skip over comment and return the next character */
int comment(void)
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


#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

void ungets(char s[])
{
    int len;
    
    len = strlen(s);
    
    while(len > 0)
        ungetch(s[--len]);
}

int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
