#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELEN 1000

/* diff : print the first line where 2 files differ */
int main(int argc, char* argv[])
{
    FILE *fp1, *fp2;
    char line1[MAXLINELEN], line2[MAXLINELEN];
    int linenum, n, empty, c1, c2;

    if(argc != 3)
    {
        fprintf(stderr, "%s: Usage: diff file1 file2\n", argv[0]);
        exit(1);
    }

    if((fp1 = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "%s: can't open %s\n", argv[0], argv[1]);
        exit(1);
    }
    if((fp2 = fopen(argv[2], "r")) == NULL)
    {
        fprintf(stderr, "%s: can't open %s\n", argv[0], argv[2]);
        exit(1);
    }

    if((c1 = getc(fp1)) != EOF)
        putc(c1, fp1);

    if((c2 = getc(fp2)) != EOF)
        putc(c2, fp2);

    empty = c1==EOF && c2==EOF;    //If both files are empty

    linenum = 1;
    while( fgets(line1, MAXLINELEN, fp1)!=NULL && fgets(line2, MAXLINELEN, fp2)!=NULL )
    {
        if(strcmp(line1, line2) != 0)
            break;

        n = strlen(line1);
        if(line1[n-1] == '\n')  //if line was not cut off because of length limit
            linenum++;
    }

    if(empty)
        printf("Nothing to compare. Both files are empty.\n");
    else if(!(feof(fp1) && feof(fp2)))
        printf("%d\n", linenum);
    else
        printf("Both files are equal.\n");

    if(ferror(stdout))
    {
        fprintf(stderr, "%s: Error writing to stdout.\n", argv[0]);
        exit(2);
    }

    fclose(fp1);
    fclose(fp2);

    exit(0);
}
