#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

typedef struct
{
    int *elements;
    int length;
    int next_in;
    int next_out;
} Queue;

Queue *make_queue(int length)
{
    Queue *queue = malloc(sizeof(Queue));
    queue->length = length + 1;
    queue->elements = malloc(sizeof(int) * length);
    queue->next_in = 0;
    queue->next_out = 0;
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
    if(queue_full(queue))
        perror_exit("queue is full");

    queue->elements[queue->next_in] = item;
    queue->next_in = queue_increment(queue, queue->next_in);
}

int queue_pop(Queue *queue)
{
    if(queue_empty(queue))
        perror_exit("queue is empty");

    int item = queue->elements[queue->next_out];
    queue->next_out = queue_increment(queue, queue->length);
    return item;
}

int main()
{
    return 0;
}