#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    
    DIR *dir;
    struct dirent *sourcedir;
    FILE *sfp, *ofp;
    char *sourcefile, *objectfile, *copyfile; 
    char sourcepath[80], objectpath[80], temppath[80];  // temppath 是strcat的参数, strcat 会改变传入的第一个参数， 如果直接传 sourcepath 第二次的参数就是错的
    char flow;

    /* 检查输入参数 */
    for(int i = 1; i < argc; i++)
        printf("\nmain函数的参数%d为%s\n",i,argv[i]);

    /* 得到源路径和目标路径 */
    strcpy(&sourcepath, argv[1]);
    strcpy(&objectpath, argv[2]);

    /* 得到文件夹下的文件名 */
    dir = opendir(argv[1]);
    
    /* 遍历文件夹 */
    while (sourcedir = readdir(dir)){
        if (sourcedir->d_name[0] != '.'){

            /* 得到当前要复制的文件 */
            copyfile = sourcedir->d_name;
            printf("\ncopy file:%s\n", copyfile);

            /* 得到源路径加文件 */
            strcpy(&temppath, &sourcepath);
            sourcefile = strcat(temppath, copyfile);
            printf("\nsource file:%s\n", sourcefile);

            /* 得到源文件文件指针 */
            sfp = fopen(sourcefile, "r");
            if(sfp == NULL){
                printf("\n源文件%s不存在, 程序退出\n", sourcefile);
                exit(0);
            }
            
            /* 得到带目标路径的目标文件 */
            strcpy(&temppath, &objectpath);
            objectfile = strcat(temppath, copyfile);
            printf("\nobject file:%s\n", objectfile);

            /* 得到目标文件文件指针 */
            ofp = fopen(objectfile, "w");
            if(ofp == NULL){
                printf("\n目标文件%s不存在或创建失败， 程序退出\n", objectfile);
                exit(0);
            }

            /* 复制文件 */
            while((flow = fgetc(sfp)) != EOF)
                fputc(flow, ofp);
            
            /* 关闭文件 */
            fclose(sfp);
            fclose(ofp);
        }
    }

    /* 关闭文件夹 */    
    closedir(dir);

    return 0;
}