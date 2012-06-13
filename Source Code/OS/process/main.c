#include <stdio.h>

int sleep_5(void)
{
    printf("Catch Signal,Sleep\n");
    sleep(5);
}

int pro_up(void)
{
    printf("Some Process is up\n");
    sleep(5);
}

int main(void)
{
    printf("Process Control\n");
    signal(2,sleep_5);
    signal(3,sleep_5);
    signal(1,pro_up);
    int pid=fork();
    if(pid>0)
    {
        wait();
        sleep(5);
        system("ps -l|grep process");
        printf("This is parent process!PID %d\n",pid);
        exit(0);
    }
    if(pid==0)
    {
        system("ps -l|grep process");
        printf("This is child process!PID %d\n",pid);
        exit(0);
    }
    if(pid<0)
    {
        printf("Fork Error\n");
        exit(0);
    }
}
