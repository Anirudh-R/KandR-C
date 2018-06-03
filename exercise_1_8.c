#include <stdio.h>

/* count blank, tabs, and newlines */
int main()
{
    int nblanks, ntabs, nnewlines, c;

    nblanks = ntabs = nnewlines = 0;
    while((c = getchar()) != EOF)
    {
        if(c == ' ')
            nblanks++;
        else if(c == '\t')
            ntabs++;
        else if(c == '\n')
            nnewlines++;
    }

    printf("blanks = %d, tabs = %d, newlines = %d\n", nblanks, ntabs, nnewlines);

    return 0;
}
