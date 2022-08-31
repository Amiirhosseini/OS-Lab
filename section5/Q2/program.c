//Amirreza Hosseini 9820363
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#define MAXCHILD 5

int main()
{
    pid_t child[MAXCHILD];
    //char child_id[256];
    //bzero(child_id, 256);
    int child_id;
    int inChild = 0;
    int status = 0;
    int pipe;
    char path[20];
    sprintf(path, "6.pipe");
    //making the named-pipe
    mkfifo(path, 0777);
    char buffer[256];
    bzero(buffer, 256);
    //int buffer=154;

    for (int i = 0; i < MAXCHILD; i++)
    {
        child[i] = fork();
        //sprintf(child_id, "%d", i);
        child_id=i;
        if (child[i] == 0)
        {
            inChild = 1;
            break;
        }
    }

    while (inChild == 1)
    {
        
            //bzero(buffer, 256);
            printf("child %d starts\n", child_id);
            //int t = rand() % 10;
            int t=20;
            sleep(t-(child_id*3));

            pipe = open(path, O_RDONLY | O_NONBLOCK);
            read(pipe, buffer, 255);
            //close(pipe);
           // fscanf(path, "%d", &buffer);
          //  pipe = open(path, O_WRONLY);
           // write(pipe, buffer, strlen(buffer));
            
            // printf("child %d pipevalue: \n", child_id);
            
            
            int buffer_int = atoi(buffer);

            printf("child %d pipevalue: %d\n", child_id, buffer_int);
            
            //if (strcmp(buffer, child_id)==0)
            //char temp[256];
           // sprintf(temp , "%d", child_id);
           // if(strcmp(buffer,temp)==0)
            if(child_id==buffer_int)
            {
                //bzero(buffer, 256);
                //char temp=child_id[0]-1;
                int temp=child_id-1;
                //sprintf(buffer , "%d",temp);
               // printf("temp %d\n",temp);
                sprintf(buffer, "%d", temp);
                printf("child %d reach the point\n", child_id);
                 pipe = open(path, O_RDWR | O_NONBLOCK);
                write(pipe, buffer, strlen(buffer));
                // do
                // {
                //     read(pipe, buffer, 255);
                //     if (buffer_int==0)
                //     {
                //         pipe = open(path, O_WRONLY | O_NONBLOCK);
                //         write(pipe, buffer, strlen(buffer));
                //         //close(pipe);
                         exit(status);
                //     }
                //  //while (strcmp(buffer, "0"));
                // }while(buffer !=0);
            }

            //if (buffer[0]== '0')
            if (buffer_int==0)
            {
                pipe = open(path, O_WRONLY);
                write(pipe, buffer, strlen(buffer));
                //close(pipe);
                exit(status);
            }
            // else 
            // {
            // printf("buffer = %s\n", buffer);
            // printf("stcmp%d\n",strcmp(buffer, child_id));
            // }
            
            //bzero(buffer, 256);
            
        
    }
    if (inChild == 0)
    {
        printf("in parent\n");

        int temp = MAXCHILD - 1;
        sprintf(buffer, "%d", temp);
        //printf("to buffer 1 %d\n",buffer);
        //buffer=temp;
        //printf("to buffer 1 %d\n",buffer);
        pipe = open(path,  O_RDWR );
        write(pipe, buffer, strlen(buffer));
        //close(pipe);
       // printf("to buffer %s\n", buffer);
        bzero(buffer, 256);
        int i;
        for (i = 0; i < MAXCHILD; i++)
        {
            waitpid(child[i], &status, 0);
        }
        

        printf("The program finished successfully\n");
    }
}