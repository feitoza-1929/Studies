#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "mutex.h"

#define NUM_CHILDREN 5

typedef struct
{
    int counter;
    Mutex *mutex;
} Shared;

void perror_exit(char* message)
{
    perror(message);
    exit(-1);
}

void *check_malloc(int size)
{
    void *result = malloc(size);

    if(result == NULL)
        perror_exit("malloc failed");

    return result;
}

void child_code(Shared *shared)
{
    mutex_lock(shared->mutex);
    printf("counter = %d\n", shared->counter);
    shared->counter++;
    mutex_unlock(shared->mutex);
}

Shared *make_shared()
{
    Shared *result = check_malloc(sizeof(Shared));
    result->mutex = make_mutex();
    result->counter = 0;
    return result;
}

void* entry(void* arg)
{
    Shared *shared = (Shared *)arg;
    child_code(shared);
    pthread_exit(NULL);
}

pthread_t make_thread(void* (*entry)(void*), Shared* shared)
{
    pthread_t result;

    if (pthread_create(&result, NULL, entry, (void*)shared) != 0)
    {
        perror_exit("pthread_create failed");
    }
    return result;
}

void join_thread(pthread_t thread)
{
    if(pthread_join(thread, NULL) == -1)
    {
        perror("pthread_join failed");
        exit(-1);
    }
}

int main()
{
    int i;
    pthread_t children[NUM_CHILDREN];
    Shared *shared = make_shared(1000000);

    for (i = 0; i < NUM_CHILDREN; i++)
    {
        children[i] = make_thread(entry, shared);
    }

    for(i = 0; i < NUM_CHILDREN; i++)
    {
        join_thread(children[i]);
    }
    return 0;
}