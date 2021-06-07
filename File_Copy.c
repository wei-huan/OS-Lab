#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc ,char* argv[])
{
    FILE *sfp, *ofp;
    char *path, *temp, *sourcefile, *objectfile; 
    char flow, delim = '/';

    /* 检查输入参数 */
    for(int i = 0; i < argc; i++)
        printf("main函数的参数%d为%s\n",i,argv[i]);

    /* 得到源文件文件指针 */
    sfp = fopen(argv[1], "r");
    if(sfp == NULL){
        printf("源文件%s不存在, 程序退出\n",argv[1]);
        exit(0);
    }

    /* 得到源文件名 */
    strtok(argv[1], &delim);

    while((temp = strtok(NULL, &delim)))
        sourcefile = temp; 

    // printf("source file:%s\n", sourcefile);

    /* 得到带目标路径的目标文件 */
    objectfile = strcat(argv[2], sourcefile);
    // printf("object file:%s\n", objectfile);

    /* 得到目标文件文件指针 */
    ofp = fopen(objectfile, "w");
    if(ofp == NULL){
        printf("目标文件%s不存在或创建失败， 程序退出\n",argv[2]);
        exit(0);
    }

    /* 复制文件 */
    while((flow = fgetc(sfp))!= EOF )
        fputc(flow, ofp);
    
    // printf("charformfile=%c\n", flow);
    // lseek();
    /* 关闭文件 */
    fclose(sfp);
    fclose(ofp);

    return 0;
}