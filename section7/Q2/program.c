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
#define MAXCHILD 4
#define MAXIMUM 20

int total = 0;
pid_t pid[MAXCHILD];

void handler1(int signo)
{
    int pipe;
    char path[20];
    sprintf(path, "./1.pipe");

    char buffer[256];
    bzero(buffer, 256);

    switch (signo)
    {
    // handling SIGUSR1 takes one second
    //during this time if SIGUSR2 will be blocked on delivery.
    case SIGUSR1:
        // sleep(1);

        pipe = open(path, O_RDONLY | O_NONBLOCK);
        read(pipe, buffer, 255);

        int buffer_int = atoi(buffer);
        bzero(buffer, 256);

        printf("SIGUSR1 received buffer:%d \n", buffer_int);
        total += buffer_int;
        break;
        // case SIGUSR2:
        //     printf("SIGUSR2 received \n");
        //     break;
    }
    if (total >= MAXIMUM)
    {
        for (int i = 0; i < MAXCHILD; i++)
        {
            kill(pid[i], SIGKILL);
        }
        kill(getpid(), SIGKILL);
        //exit(1);
    }
}

int main()
{
    int child_id;
    int pipe;
    char path[20];
    sprintf(path, "./1.pipe");
    //making the named-pipe
    mkfifo(path, 0777);
    char buffer[256];
    bzero(buffer, 256);

    //initializing sigaction structures, action1 and action2 both use handler1
    struct sigaction action1;
    //struct sigaction action2;
    sigset_t set1;             //define signal set named "set1"
    sigemptyset(&set1);        //making set1 empty
    sigaddset(&set1, SIGUSR2); //adding SIGUSR2 to set1
    //set1 includes SIGUSR2, it means if SIGUSR2 will be blocked on delivery.
    sigprocmask(SIG_SETMASK, &set1, NULL);
    action1.sa_handler = handler1;
    //action2.sa_handler = handler1;
    int inchild = 0;
    //initializng parent process before fork()
    sigaction(SIGUSR1, (struct sigaction *)&action1, NULL);
    //sigaction(SIGUSR2, (struct sigaction *)&action2, NULL);
    pid_t parent = getpid();

    for (int i = 0; i < MAXCHILD; i++)
    {
        pid[i] = fork();
        child_id = i;
        if (pid[i] == 0)
        {
            inchild = 1;
            break;
        }
    }

    while (inchild == 0) //parent
        ;
    while (inchild == 1)
    {

        //int t = rand()%10;
        int t = (child_id * 2) + 1;
        sprintf(buffer, "%d", t);
        sleep(t);

        printf("child %d starts\n", child_id);

        pipe = open(path, O_RDWR | O_NONBLOCK);
        write(pipe, buffer, strlen(buffer));
        bzero(buffer, 256);
        //child sends SIGUSR1 and immediately SIGUSR2 to parent every one second
        kill(parent, SIGUSR1);
        //kill(parent, SIGUSR2);
        sleep(10);
    }
    return 0;
}