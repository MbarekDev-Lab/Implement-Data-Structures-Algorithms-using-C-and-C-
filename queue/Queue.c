#include <stdio.h>
#include <stdlib.h>

struct Queue
{
    /* data */
    int size;
    int front;
    int rear;
    int *Q;
};

void create(struct Queue *q, int size)
{
    q->size = size;
    q->front = q->rear = -1;
    q->Q = (int *)malloc(q->size * sizeof(int));
}

void enqueue(struct Queue *q, int x)
{
    if (q->rear == q->size - 1)
    { // we cannot insert more elements
        printf("Queue is Full\n");
    }
    else
    { // Increment rear and add element insertion
        q->rear++;
        q->Q[q->rear] = x;
    }
}

int dequeue(struct Queue *q)
{
    int x = -1;
    if (q->front == q->rear)
    {
        printf("Queue is Empty\n");
    }
    else
    {
        q->front++;
        x = q->Q[q->front];
    }
    return x;
}

void Display(struct Queue q)
{
    int i;

    for (i = q.front + 1; i <= q.rear; i++)
    {
        printf("%d ", q.Q[i]);
    }
    printf("\n");
}

int main()
{
    struct Queue q;

    create(&q, 5); // creating Queue of size 5 using Array

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    Display(q);

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));

    Display(q);

    return 0;
}
/*
    benraiss@MacBookAir queue %  clang -std=c17 -Wall -Wextra -o _c Queue.c
    benraiss@MacBookAir queue % ./_c
    10 20 30 40 50
    Dequeued: 10
    Dequeued: 20
    30 40 50
    benraiss@MacBookAir queue %


*/
