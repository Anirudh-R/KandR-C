#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABSIZE 101

struct nlist
{
  char* name;           //defined name
  char* defn;           //replacement text
  struct nlist* next;
};

struct nlist* hashtab[HASHTABSIZE];     //array of pointers to linked lists

unsigned int hash(char* s);
struct nlist* lookup(char* s);
struct nlist* install(char* name, char* defn);
void undef(char* name);

int main()
{
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
