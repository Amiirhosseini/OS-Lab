//Amirreza Hosseini 9820363

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define SIZE 6

int stride = SIZE / 2;
int A[SIZE] = {90,35,70, 80,30, 40};
sem_t sem1;

void *routine1(void *x)
{
    int *t = (int *)malloc(sizeof(int));
    int d = *(int *)x;
    //sleep(d);
    sem_wait(&sem1);
    //beginning of critical section

    if (A[d] > A[d + stride]) //swaping
    {
        //int temp = MIN(A[d],A[d+stride]);
        int temp = A[d + stride];
        A[d + stride] = A[d];
        A[d] = temp;
    }

    printf("thread %d A[0]=%d\n", d, A[0]);

    printf("stride =%d\n", stride);

     stride = ceil(stride / 2);
    //end of critical section
    sem_post(&sem1);
    // pthread_exit(NULL);
    *t=A[0];
    pthread_exit((void *)t);
}

int main()
{
    sem_init(&sem1, 0, 1);
    pthread_t threads[stride];
    int thread_id[stride];
    int x=stride+1;
    for (int i = 0; i < x; i++)
    {
         printf("stride in main =%d\n", stride);

        thread_id[i] = i;
        pthread_create(&threads[i], NULL, routine1, (void *)&thread_id[i]);
        //replace two above lines with the below line
        //pthread_create(&threads[i], NULL, routine1, (void *)&i );
        //sleep(1);
     
    }
    int *retval = (int *)malloc(sizeof(int));
    for (int i = 0; i < x; i++)
    {
          
        pthread_join(threads[i], (void **)&retval);
        printf("threadIdx %d finished, return_value = %d \n", i, *retval);
        // if (stride==0)
        // {
        //     printf("finished...\n");
        // }
    }
    return 0;
}