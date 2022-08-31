//Amirreza Hosseini 9820363
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#define MAXCHILD 4
#define MAXIMUM 10

int main()
{

    pid_t child[MAXCHILD];
    int inChild = 0;
    int status = 0;

    int fd[2];
    //char buffer[256];
    int buffer;
    int x = pipe(fd);

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
        // printf("in child\n");
        close(fd[0]);
        //int i;
        // for(i=0;i<MAXCHILD;i++)
        // {
        int t = rand() % 10;
        sleep(t);
        buffer = rand() % 10;
        //sprintf(buffer,"hello");
        write(fd[1], &buffer, sizeof(buffer));
        // }
    }
    while (inChild == 0)
    {
        close(fd[1]);
        int total = 0;
        // printf("in parent\n");
        while (total <= MAXIMUM)
        {
            printf("%d\n", total);

            sleep(3);

            if (read(fd[0], &buffer, sizeof(buffer)) > 0)
                total = total + buffer;
            //printf("%s",buffer);
            else
                printf("pipe is not available\n");
        }

        kill(0, SIGKILL);
    }
}