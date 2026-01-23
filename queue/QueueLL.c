#include <stdlib.h>
#include <stdio.h>

struct Node
{
    int mdata;
    struct Node *next;
} *front = NULL, *rear = NULL; // global pointers for front and rear

void enqueue(int x) // insert at rear
{
    struct Node *t;
    t = (struct Node *)malloc(sizeof(struct Node));
    if (t == NULL)
    {
        printf("Queue is Full\n");
    }
    else
    {
        t->mdata = x;
        t->next = NULL;
        if (front == NULL) // Queue is empty
        {
            front = rear = t;
        }
        else
        {
            rear->next = t;
            rear = t;
        }
    }
}

int dequeue() // delete from front
{
    int x = -1;
    struct Node *t;
    if (front == NULL)
    {
        printf("Queue is Empty\n");
    }
    else
    {
        t = front;
        front = front->next;
        x = t->mdata;
        free(t);
    }
    return x;
}

void Display()
{
    struct Node *p = front; // Initialize to front of queue

    while (p)
    {
        printf("%d ", p->mdata);
        p = p->next;
    }
    printf("\n");
}

int main()
{fffrt
    enqueue(10);
    enqueue(20);
    enqueue(30);
    printf("Queue after enqueuing 10, 20, 30:\n");
    Display();

    printf("\nDequeued: %d\n", dequeue());
    printf("Queue after dequeue:\n");
    Display();

    return 0;
}

/*
    benraiss@MacBookAir queue %  clang -std=c17 -Wall -Wextra -o _c QueueLL.c
    benraiss@MacBookAir queue % ./_c
    Queue after enqueuing 10, 20, 30:
    10 20 30

    Dequeued: 10 ( First element removed (FIFO))
    Queue after dequeue:
    20 30
    benraiss@MacBookAir queue %

*/