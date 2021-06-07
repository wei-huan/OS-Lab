#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_BUFFER 100

char msg1[] = "child process 1 is sending a message\n";
char msg2[] = "child process 2 is sending a message\n";
char buffer[MAX_BUFFER];

int main()
{
    pid_t child1, child2;
    int fd[2];
    int msglength1, msglength2;

    // 获取写入管道数据的msg长度
    msglength1 = strlen(msg1);
    msglength2 = strlen(msg2);

    char readbuffer[msglength1 + msglength2];

    // 创建管道
    if(pipe(fd) == -1)
    {
        perror("Failed to create the pipe\n");
        exit(1);
    }    

    // 创建子进程1
    child1 = fork();

    // 创建失败
    if(child1 == -1)
    {
        printf("fork1_error\n");
        exit(1);
    }
    // 在子进程1中
    else if(child1 == 0)
    {
        // 子进程1关闭管道读入端
        close(fd[0]);
        // 子进程1向管道写数据
        write(fd[1], msg1, msglength1);
        // 结束子进程1 
        exit(1);
    }
    // 在父进程中
    else
    { 
        // 创建子进程2
        child2 = fork();
        // 创建失败
        if(child2 == -1)
        {
            printf("fork2_error\n");
            exit(1);
        }
        // 在子进程2中
        else if(child2 == 0)
        {        
            printf("儿子进程2\n");
       
            // 子进程2关闭管道读入端
            close(fd[0]);
            // 子进程2向管道写数据
            write(fd[1], msg2, msglength2);
            // 结束子进程2
            exit(1);
        }
        else
        {
            sleep(1);
            printf("爹第进程\n");
        
            // 父进程关闭管道写入端
            close(fd[1]);
            // 父进程读管道数据
            read(fd[0], readbuffer, msglength1 + msglength2);
            printf("%s", readbuffer);

            // 父进程关闭管道
            //close(fd[0]);
            // close(fd[1]);
        }
    }
    return 0;
}
