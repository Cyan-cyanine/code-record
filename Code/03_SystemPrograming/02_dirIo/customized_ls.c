#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("error format.\n");
        exit(-1);
    }
    DIR *dir_p = opendir(argv[1]);
    if (dir_p == NULL)
    {
        perror("opendir error");
        exit(-1);
    }
    struct dirent *dirent_p; // define dirctory entry
    while ((dirent_p = readdir(dir_p)) != NULL)
    {
        if (strcmp(dirent_p->d_name, ".") == 0)
            continue;
        else if (strcmp(dirent_p->d_name, "..") == 0)
            continue;
        printf("%s\t", dirent_p->d_name);
    }
    putchar(10);
    closedir(dir_p);
    return 0;
}