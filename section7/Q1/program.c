//Amirreza Hosseini 9820363

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#define MAX_TRY 4

int counter = 0;

// "handler1" is handler function for action1
void handler1(int signo)
{
    switch (signo)
    {
    case SIGINT:
        printf("Interrupt Signal received   counter = %d \n", counter + 1);
        counter += 1;
        break;
    }

    if (counter == MAX_TRY)
    {
        kill(getpid(), SIGKILL);
    }
}
int main()
{
    //initializing sigaction structure
    struct sigaction action1;
    action1.sa_handler = handler1;
    action1.sa_flags = 0;
    sigaction(SIGINT, (struct sigaction *)&action1, NULL);
    //runnign forever, while process is sensitive to SIGINT
    while (1)
        ;
    return 0;
}