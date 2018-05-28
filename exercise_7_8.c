#include <stdio.h>
#include <stdlib.h>

#define MAXBOT  3
#define MAXHDR  5
#define MAXLINELEN  100
#define MAXPAGE  25

void fileprint(FILE* fp, char* fname);
int heading(char* fname, int pagenum);

/* print: print files - each new one on a new page */
int main(int argc, char* argv[])
{
	FILE* fp;

    if(argc == 1)   //no input files, print stdin
        fileprint(stdin, " ");
    else
        while(--argc > 0)
            if((fp = fopen(*++argv, "r")) == NULL)
            {
                fprintf(stderr, "find: can't open %s\n", *argv);
                exit(1);
            }
            else
            {
                fileprint(fp, *argv);
                fclose(fp);
            }

    exit(0);
}


/* fileprint: print file fp */
void fileprint(FILE* fp, char* fname)
{
    char line[MAXLINELEN];
    int linenum, pagenum;

    pagenum = 1;
    linenum = heading(fname, pagenum++);
    while(fgets(line, MAXLINELEN, fp) != NULL)
    {
        if(linenum == 1)    //start of a new page
        {
            fprintf(stdout, "\f");
            linenum = heading(fname, pagenum++);
        }
        fputs(line, stdout);

        if(++linenum > MAXPAGE - MAXBOT)    //reset line number
            linenum = 1;
    }

    fprintf(stdout, "\f");  //page eject after the file
}

/* heading: put heading and enough blank lines */
int heading(char* fname, int pagenum)
{
    int ln = MAXBOT;

    fprintf(stdout, "\n\n");
    fprintf(stdout, "** %s    page %d **", fname, pagenum);

    while(ln++ < MAXHDR)
        fprintf(stdout, "\n");

    return ln;
}
