#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

class Node
{
    /* data */
public:
    Node *lChird;
    Node *rChird;
    int data;
};

class Queue
{

private:
    int size;
    int front;
    int rear;
    Node **Q; // one poiter point to another pointer of type Node

public:
    Queue()
    {
        front = rear = -1;
        size = 0;
        Q = new Node *[size];
    };

    Queue(int s)
    {
        size = s;
        front = rear = -1;
        Q = new Node *[size];
    };

    friend void create(Queue *q, int size);
    friend void enqueue(Queue *q, Node *x);
    friend Node *dequeue(Queue *q);
    friend int isEmpty(Queue q);
    friend void Display(Queue q);
};
void create(Queue *q, int size)
{
    q->size = size;
    q->front = q->rear = -1;
    q->Q = (Node **)malloc(q->size * sizeof(Node *)); // allocating memory for array of pointers of type Node it a double pointer matrix of pointers
}

void enqueue(Queue *q, Node *x)
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

Node *dequeue(Queue *q)
{
    Node *x = nullptr;

    if (q->front == q->rear)
        printf("Queue is Empty\n");
    else
    {
        q->front = (q->front + 1) % q->size; // circular increment to next index saving space
        x = q->Q[q->front];
    }
    return x;
};

void Display(Queue q)
{
    for (int i = q.front + 1; i <= q.rear; i++)
    {
        printf("%d ", q.Q[i]->data);
    }
    printf("\n");
}

int isEmpty(Queue q)
{
    return q.front == q.rear; // true if empty
}

#endif // QUEUE_H