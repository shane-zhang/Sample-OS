#include <stdio.h>

int main(void)
{
    int fd[2];
    if(pipe(fd)!=-1)
    {
        printf("pipe Creating\t\t[OK]!\n");
    }
    else
    {
        printf("pipe Creating\t\t[FAIL]!\n");
        return (1);
    }
    int pid=fork();
    char InBuf[100],OutBuf[100];
    if(pid>0)
    {
        wait();
        sleep(5);
        system("ps -l|grep pipe");
        printf("This is parent process!PID %d\n",pid);
        read(fd[0],InBuf,100);
        printf("%s",InBuf);
        exit(0);
    }
    if(pid==0)
    {
        system("ps -l|grep pipe");
        printf("This is child process!PID %d\n",pid);
        lockf(fd[1],1,0);
        sprintf(OutBuf,"\nSome Thing Write To his father\n");
        write(fd[1],OutBuf,100);
        lockf(fd[1],0,0);
        exit(0);
    }
    if(pid<0)
    {
        printf("Fork Error\n");
        exit(0);
    }
}
