#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINELEN 1000

void fpat(FILE* fp, char* fname, char* pattern, int except, int numbering);
int isblankline(char* line);

/* find: print lines that match a pattern */
int main(int argc, char* argv[])
{
	char pattern[MAXLINELEN];
	int c, except, numbering;
	FILE* fp;

	except = 0;
	numbering = 0;
	while(--argc>0 && *(*++argv)=='-')
        while(c = *++(*argv))
            switch(c)
            {
                case 'x': except = 1;
                          break;

                case 'n': numbering = 1;
                          break;

                default: printf("find: illegal option %c\n", c);
                         argc = 0;
                         break;
            }

    if(argc >= 1)
        strcpy(pattern, *argv);
    else
    {
        printf("find: Usage: find [-x] [-n] pattern [file1 ...]\n");
        exit(1);
    }

    if(argc == 1)   //standard input
        fpat(stdin, "", pattern, except, numbering);
    else
        while(--argc > 0)
            if((fp = fopen(*++argv, "r")) == NULL)
            {
                fprintf(stderr, "find: can't open %s\n", *argv);
                exit(1);
            }
            else
            {
                fpat(fp, *argv, pattern, except, numbering);
                fclose(fp);
            }

    exit(0);
}


/* fpat: find pattern in file fp */
void fpat(FILE* fp, char* fname, char* pattern, int except, int numbering)
{
    char line[MAXLINELEN];
    int linenum, fnameprnt, n;

    linenum = 0;
    fnameprnt = 0;  //flag set once matching fname has been printed
    while(fgets(line, MAXLINELEN, fp) != NULL)
    {
        linenum++;
        if((strstr(line, pattern) != NULL) != except)
        {
            if(isblankline(line))   //don't print blank lines
                continue;

            n = strlen(line);
            if(line[n-1] == '\n')   //remove trailing newline
                line[n-1] = ' ';

            if(*fname && !fnameprnt)
            {
                printf("%s\n", fname);
                fnameprnt = 1;
            }
            if(numbering)
                printf("%d: ", linenum);
            printf("%s\n", line);
        }
    }

    if(fnameprnt)
        printf("\n");
}

/* isblank: returns 1 if line consists only of ' ', '\t' or '\n' */
int isblankline(char* line)
{
    int c;

    while(c = *line++)
        if(!isspace(c))
            return 0;

    return 1;
}