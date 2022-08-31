//Amirreza Hosseini 9820363
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXCHILD 4

pid_t child[MAXCHILD];
int inChild = 0;
int status = 0;

void childWork(pid_t pid)
{

    srand(getpid());
    int r = rand() % (100 + 1 - 1) + 1; //random number 1 to 10000
    //int r =rand()%10;
    printf("message from child %d waited for %d seconds\n", getpid(), r);
    sleep(r);
    inChild = -1;
    exit(pid);
}

int main()
{

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
        childWork(getpid());
    }
    while (inChild == 0)
    {
        sleep(5);
        for (int i = 0; i < MAXCHILD; i++)
        {
            int child_d;
            // //**comment from next line
            // child_d = wait(&status);
            // if (child_d > 0)
            //     printf("child[%d] is dead now \n", child[i]);
            // else if (child_d == -1)
            //     printf("no child to wait for \n");

            child_d = waitpid(child[i], &status, WNOHANG);
            if (child_d == 0)
                printf("child[%d] is still alive\n", child[i]);
            else if (child_d > 0)
            {
                //printf("child[%d] is dead now \n", child[i]);
                child[i] = fork();
                if (child[i] == 0)
                {
                    printf("child[%d] regenerated with new pid %d\n", i, getpid());
                    childWork(getpid());
                }
            }
            else
                printf("no specified child to wait for \n");
        }
    }

    return 0;
}