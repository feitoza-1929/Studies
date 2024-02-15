#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include "mutex.h"

#define QUEUE_LENGTH 5
#define NUM_CHILDREN 2

typedef struct
{
    Queue *queue;
} Shared;

typedef struct
{
    int *elements;
    int length;
    int next_in;
    int next_out;
    Mutex *mutex;
} Queue;

Queue *make_queue(int length)
{
    Queue *queue = malloc(sizeof(Queue));
    queue->length = length + 1;
    queue->elements = malloc(sizeof(int) * length);
    queue->next_in = 0;
    queue->next_out = 0;
    queue->mutex = make_mutex();
    return queue;
}

int queue_empty(Queue *queue)
{
    return queue->next_in == queue->next_out;
}

int queue_full(Queue *queue)
{
    return queue_increment(queue, queue->next_in) == queue->length;
}

int queue_increment(Queue *queue, int i)
{
    return (i + 1) % queue->length;
}

void queue_push(Queue *queue, int item)
{
    mutex_lock(queue->mutex);
    if (queue_full(queue))
    {
        mutex_unlock(queue->mutex);
        perror_exit("queue is full");
    }

    queue->elements[queue->next_in] = item;
    queue->next_in = queue_increment(queue, queue->next_in);
    mutex_unlock(queue->mutex);
}

int queue_pop(Queue *queue)
{
    mutex_lock(queue->mutex);
    if (queue_empty(queue))
    {
        mutex_unlock(queue->mutex);
        perror_exit("queue is empty");
    }

    int item = queue->elements[queue->next_out];
    queue->next_out = queue_increment(queue, queue->length);
    mutex_unlock(queue->mutex);
    return item;
}

void* producer_entry(void *arg)
{
    Shared *shared = (Shared *)arg;

    for (int i = 0; i < QUEUE_LENGTH - 1; i++)
    {
        printf("adding item %d\n", i);
        queue_push(shared->queue, i);
    }
    pthread_exit(NULL);
}

void *consumer_entry(void* arg)
{
    int item;
    Shared *shared = (Shared *)arg;
    for (int i = 0; i < QUEUE_LENGTH - 1; i++)
    {
        item = queue_pop(shared->queue);
        printf("consuming item %d\n", item);
    }
    pthread_exit(NULL);
}

pthread_t make_thread(void*(*entry)(void*), Shared* shared)
{
    pthread_t result;

    if(pthread_create(&result, NULL, entry, (void*)shared) != 0)
        perror_exit("pthread_create failed");

    return result;
}

Shared *make_shared()
{
    Shared *shared = malloc(sizeof(Shared));
    shared->queue = make_queue(QUEUE_LENGTH);
    return shared;
};

int main()
{
    pthread_t child[NUM_CHILDREN];

    Shared *shared = make_shared();

    child[0] = make_thread(producer_entry, shared);
    child[1] = make_thread(consumer_entry, shared);

    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        join_thread(child[i]);
    }
    return 0;
}