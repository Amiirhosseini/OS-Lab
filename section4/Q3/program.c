//Amirreza Hosseini 9820363
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h> //gettimeofday
#include <time.h>     //time
#include <fcntl.h>

char buffer_date[80];

char *Date() //returning date
{
    time_t rawtime;
    struct tm *timeinfo;
    //char buffer_date [80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer_date, 80, "20%y-%d-%m    %H:%M", timeinfo);
    return buffer_date;
    // printf("%s",buffer_date);
}

int main()
{
    for (;;)
    {
        char buffer_file[256];
        strcat(buffer_file, Date());
        //printf("%s", buffer_file);
        // puts(buffer_date);
        // Date();

        char path[64];
        char argv[64];

        printf("enter path:");
        scanf("%s", &path);
        printf("enter argumant:");
        scanf("%s", &argv);

        struct timeval start, stop;
        srand(time(NULL));
        long elapsed = 0;

        /*Spawn a child to run the program.*/
        pid_t pid = fork();

        if (pid == 0)
        { /* child process */

            sleep(rand() % 10);
            execv(path, argv);
            //execv("/home/amir/Desktop/oslab4/Q3/helloworld", NULL);

            // printf("11111");
            exit(pid); /* only if execv fails */
        }
        else
        { /* pid!=0; parent process */
            gettimeofday(&start, NULL);
            waitpid(pid, 0, 0); /* wait for child to exit */
            gettimeofday(&stop, NULL);
            long sec = stop.tv_sec - start.tv_sec;
            float m1 = start.tv_usec;
            float m2 = stop.tv_usec;
            elapsed = sec * 1000 + (m2 - m1) / 1000;
        }

        //printf("%ld\n", elapsed);

        sprintf(buffer_file, "%s   %ld    %s\n", buffer_date, elapsed, path);
        // printf("%s", buffer_file);

        int openFile = open("./log.txt", O_CREAT | O_APPEND | O_RDWR, 00777);
        write(openFile, buffer_file, strlen(buffer_file));

        //char buffer_Line[32]="---------------------------\n";
        //write(openFile, buffer_Line, strlen(buffer_Line));
        printf("done\n");
    }
}