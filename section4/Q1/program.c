//Amirreza Hosseini 9820363
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

for (;;)
{
    pid_t pid;
    pid=fork();

    if(pid==0) //in child process
    {
        printf("%d\n",getpid());
        exit(0);
    }

    sleep(2);
}
return 0;
}