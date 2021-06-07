#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc ,char* argv[])
{
    DIR *dir;
    struct dirent *ptr;

    dir = opendir("/home/weihuan/WorkSpace/OSExp");

    while(ptr = readdir(dir))
        printf("directory name:%s\n", ptr->d_name);

    closedir(dir);

    return 0;
}
