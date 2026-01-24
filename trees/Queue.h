#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    /* data */
    struct Node *lChird;
    struct Node *rChird;
    int data;
};

struct Queue
{
    int size;
    int front;
    int rear;
    struct Node **Q; // one poiter point to another pointer of type Node
};

void create(struct Queue *q, int size)
{
    q->size = size;
    q->front = q->rear = -1;
    q->Q = (struct Node **)malloc(q->size * sizeof(struct Node *)); // allocating memory for array of pointers of type Node it a double pointer matrix of pointers
}

void enqueue(struct Queue *q, struct Node *x)
{
    if ((q->rear + 1) % q->size == q->front)
        printf("Queue is Full\n");
    else
    {
        q->rear = (q->rear + 1) % q->size;
        q->Q[q->rear] = x;
    }
    // struct Node *next;
};

struct Node *dequeue(struct Queue *q)
{
    struct Node *x = NULL;

    if (q->front == q->rear)
        printf("Queue is Empty\n");
    else
    {
        q->front = (q->front + 1) % q->size; // circular increment to next index saving space
        x = q->Q[q->front];
    }
    return x;
};

int isEmpty(struct Queue q)
{
    return q.front == q.rear; // true if empty
}

#endif // QUEUE_H