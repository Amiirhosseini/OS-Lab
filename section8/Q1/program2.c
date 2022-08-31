//Amirreza Hosseini 9820363

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define SIZE 6

int stride = SIZE / 2;
int start[SIZE];
int A[SIZE] = {90, 35, 70, 80, 30, 40};
int min_A[SIZE];
pthread_t tid[SIZE/2];

void *routine1(void *arg) //routin func without semaphore and swapping 
{
    int i, s;
    int n, start, stop;
    int result;

    n = SIZE / stride;

    s = *(int *)arg;

    start = s * n;

    if (s != (stride - 1))
    {
        stop = start + n;
    }
    else
    {
        stop = SIZE;
    }

    result = A[start];

    for (i = start + 1; i < stop; i++)
    {

        if (A[i] < result)
            result = A[i];
    }

    min_A[s] = result;
    return (NULL);
}

int main()
{
    int i;
    int result;
    for (i = 0; i < stride; i = i + 1)
    {
        start[i] = i;
       pthread_create(&tid[i], NULL, routine1, (void *)&start[i]);
    }

    for (i = 0; i < stride; i = i + 1)
        pthread_join(tid[i], NULL);

    result = min_A[0];
    for (i = 1; i < stride; i++)
        if (min_A[i] < result)
            result = min_A[i];
    printf("%d\n", result);
}