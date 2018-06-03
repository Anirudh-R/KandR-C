#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH 1024

void fsize(char* name);
void dirwalk(char* dirname, void (*fcn)(char*));

/* print file sizes */
int main(int argc, char* argv[])
{
    if(argc == 1)       //current directory if no args
        fsize(".");
    else
        while(--argc)
            fsize(*++argv);

    return 0;
}


/* fsize: print size and other properties of the file 'name' */
void fsize(char* name)
{
    struct stat stbuf;

    if(stat(name, &stbuf) == -1)
    {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }

    if((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);

    printf("%8u  %6o %3u %8ld  %s\n", stbuf.st_ino, stbuf.st_mode, stbuf.st_nlink, stbuf.st_size, name);
}

/* dirwalk: apply fcn to all file in the directory dirname */
void dirwalk(char* dirname, void (*fcn)(char*))
{
    char name[MAX_PATH];

    DIR* dp;
    struct dirent* de;

    if((dp = opendir(dirname)) == NULL)
    {
        fprintf(stderr, "dirwalk: can't open %s\n", dirname);
        return;
    }

    while((de = readdir(dp)) != NULL)
    {
        if(strcmp(de->d_name, ".")==0 || strcmp(de->d_name, "..")==0)   //skip self and parent
            continue;

        if(strlen(dirname)+strlen(de->d_name)+2 > sizeof(name))   //+2 for '/' and '\0'
            fprintf(stderr, "dirwalk: %s/%s too long.\n", dirname, de->d_name);
        else
        {
            sprintf(name, "%s/%s", dirname, de->d_name);
            (*fcn)(name);
        }
    }

    closedir(dp);
}
