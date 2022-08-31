//Amirreza Hosseini 9820363
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// void childWork(pid_t pid)
// {

//     srand(getpid());
//     int r = rand() % (100 + 1 - 1) + 1; //random number 1 to 10000
//     //int r =rand()%10;
//     printf("message from child %d waited for %d seconds\n", getpid(), r);
//     sleep(r);
//     inChild = -1;
//     exit(pid);
// }

int main(int argc, char *argv[])
{
    int MAXCHILD=atoi(argv[3]);
    //sprintf(MAXCHILD,"%d",argv[3]);

    pid_t child[MAXCHILD];
    int inChild = 0;
    int status = 0;

    char buf[32];

    for (int i = 0; i < MAXCHILD; i++)
    {
        child[i] = fork();
        if (child[i] == 0)
        {
            inChild = 1;
            break;
        }
    }

    while (inChild == 1)
    {
        sleep(2);
        //childWork(getpid());
        //sprintf(buf, "%s %s", argv[1], argv[2]);

        execlp("/usr/bin/xterm", "xterm", "-e", "./client", argv[1],argv[2], NULL);
    }
    while (inChild == 0)
    {
       // sprintf(buf, "%s %s %s", argv[1], argv[2], argv[3]);

        execlp("/usr/bin/xterm", "xterm", "-e", "./server", argv[1],argv[2],argv[3], NULL);
    }

    return 0;
}