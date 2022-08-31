//Amirreza Hosseini 9820363

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define Philosophers 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % Philosophers
#define RIGHT (phnum + 1) % Philosophers

int state[Philosophers];
int phil[Philosophers] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[Philosophers];

void test(int phnum)
{
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        // eating state
        state[phnum] = EATING;

        int t=rand()%3;
        sleep(t);

        printf("Philosopher %d takes fork %d and %d\n",
               phnum + 1, LEFT + 1, phnum + 1);

        printf("Philosopher %d is Eating\n", phnum + 1);

        sem_post(&S[phnum]);
    }
}

// take up chopsticks
void take_fork(int phnum)
{

    sem_wait(&mutex);

    // state that hungry
    state[phnum] = HUNGRY;

    printf("Philosopher %d is Hungry\n", phnum + 1);

    // eat if neighbours are not eating
    test(phnum);

    sem_post(&mutex);

    // if unable to eat wait to be signalled
    sem_wait(&S[phnum]);

    int t=rand()%3;
        sleep(t);

}

// put down chopsticks
void put_fork(int phnum)
{

    sem_wait(&mutex);

    // state that thinking
    state[phnum] = THINKING;

    printf("Philosopher %d putting fork %d and %d down\n",
           phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void *philosopher(void *num)
{

    while (1)
    {

        int *i = num;

        sleep(1);

        take_fork(*i);

        int t=rand()%3;
        sleep(t);

        put_fork(*i);
    }
}

int main()
{

    int i;
    pthread_t thread_id[Philosophers];

    // initialize the semaphores
    sem_init(&mutex, 0, 1);

    for (i = 0; i < Philosophers; i++)

        sem_init(&S[i], 0, 0);

    for (i = 0; i < Philosophers; i++)
    {

        // create philosopher processes
        pthread_create(&thread_id[i], NULL,
                       philosopher, &phil[i]);

        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < Philosophers; i++)

        pthread_join(thread_id[i], NULL);
}
