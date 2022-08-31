//Amirreza Hosseini 9820363

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 4
#define THREADS 4

int product = 0;
sem_t sem1;
int A[SIZE] = {92, 35, 70, 80};
int B[SIZE] = {9, 3, 7, 8};
int step = 0;

void *routine1(void *x)
{
    sem_wait(&sem1);
    for (int i = step; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            product += A[i] * B[j];
        }
    }
    step++;
    sem_post(&sem1);

    pthread_exit(NULL);
}

int main()
{
    sem_init(&sem1, 0, 1);
    pthread_t threads[THREADS];
    int thread_id[THREADS];

    for (int i = 0; i < THREADS; i++)
    {
        thread_id[i] = i;
        pthread_create(&threads[i], NULL, routine1, (void *)&thread_id[i]);
        //replace two above lines with the below line
        //pthread_create(&threads[i], NULL, routine1, (void *)&i );
        //sleep(1);
    }
    int *retval = (int *)malloc(sizeof(int));

    for (int i = 0; i < THREADS; i++)
    {

        pthread_join(threads[i], (void **)&retval);
    }

    printf("product: %d\n", product);
}