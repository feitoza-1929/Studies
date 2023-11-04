#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

typedef struct
{
    int counter;
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
    printf("counter = %d\n", shared->counter);
    shared->counter++;
}

Shared *make_shared()
{
    Shared *result = check_malloc(sizeof(Shared));
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

void main()
{
    
}