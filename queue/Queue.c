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

void circularEnqueue(struct Queue *q, int x)
{
    if ((q->rear + 1) % q->size == q->front)
    {
        printf("Queue is Full\n");
    }
    else
    {
        q->rear = (q->rear + 1) % q->size;
        q->Q[q->rear] = x;
    }
}

int circularDequeue(struct Queue *q)
{
    int x = -1;
    if (q->front == q->rear)
    {
        printf("Queue is Empty\n");
    }
    else
    {
        q->front = (q->front + 1) % q->size;
        x = q->Q[q->front];
    }
    return x;
}

void circularDisplay(struct Queue q)
{
    // Handle empty queue
    if (q.front == q.rear)
    {
        printf("Queue is Empty\n");
        return;
    }

    int i = q.front + 1;
    do
    {
        printf("%d ", q.Q[i]);
        i = (i + 1) % q.size;

    } while (i != (q.rear + 1) % q.size);

    printf("\n");
}

int main()
{
    printf("═══════════════════════════════════════════════════════════\n");
    printf("       QUEUE COMPARISON: LINEAR vs CIRCULAR\n");
    printf("═══════════════════════════════════════════════════════════\n");

    // ========================================================================
    // PART 1: LINEAR QUEUE - Demonstrating Space Wastage Problem
    // ========================================================================
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║  PART 1: LINEAR QUEUE (Problem)      ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");

    struct Queue linearQ;
    create(&linearQ, 5);

    printf("Step 1: Enqueue 5 elements (10, 20, 30, 40, 50)\n");
    enqueue(&linearQ, 10);
    enqueue(&linearQ, 20);
    enqueue(&linearQ, 30);
    enqueue(&linearQ, 40);
    enqueue(&linearQ, 50);
    printf("Queue: ");
    Display(linearQ);

    printf("\nStep 2: Dequeue 3 elements\n");
    printf("Dequeued: %d\n", dequeue(&linearQ));
    printf("Dequeued: %d\n", dequeue(&linearQ));
    printf("Dequeued: %d\n", dequeue(&linearQ));
    printf("Queue: ");
    Display(linearQ);

    printf("\nStep 3: Try to enqueue new element (60)\n");
    printf("Result: ");
    enqueue(&linearQ, 60); // Will show "Queue is Full"
    printf(" PROBLEM: Indices 0, 1, 2 are FREE but we can't use them!\n");
    printf("   This is SPACE WASTAGE in linear queue.\n");

    free(linearQ.Q);

    // ========================================================================
    // PART 2: CIRCULAR QUEUE - Solving the Problem
    // ========================================================================
    printf("\n\n╔═══════════════════════════════════════╗\n");
    printf("║  PART 2: CIRCULAR QUEUE (Solution)   ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");

    struct Queue circularQ;
    create(&circularQ, 5);

    printf("Step 1: Enqueue 5 elements (10, 20, 30, 40, 50)\n");
    circularEnqueue(&circularQ, 10);
    circularEnqueue(&circularQ, 20);
    circularEnqueue(&circularQ, 30);
    circularEnqueue(&circularQ, 40);
    circularEnqueue(&circularQ, 50);
    printf("Queue: ");
    circularDisplay(circularQ);
    printf("State: front=%d, rear=%d\n", circularQ.front, circularQ.rear);

    printf("\nStep 2: Dequeue 3 elements\n");
    printf("Dequeued: %d\n", circularDequeue(&circularQ));
    printf("Dequeued: %d\n", circularDequeue(&circularQ));
    printf("Dequeued: %d\n", circularDequeue(&circularQ));
    printf("Queue: ");
    circularDisplay(circularQ);
    printf("State: front=%d, rear=%d\n", circularQ.front, circularQ.rear);

    printf("\nStep 3: Enqueue new elements (60, 70, 80)\n");
    circularEnqueue(&circularQ, 60);
    printf("After enqueue(60) - Queue: ");
    circularDisplay(circularQ);
    printf("State: front=%d, rear=%d (rear wrapped to 0!)\n", circularQ.front, circularQ.rear);

    circularEnqueue(&circularQ, 70);
    printf("After enqueue(70) - Queue: ");
    circularDisplay(circularQ);
    printf("State: front=%d, rear=%d\n", circularQ.front, circularQ.rear);

    circularEnqueue(&circularQ, 80);
    printf("After enqueue(80) - Queue: ");
    circularDisplay(circularQ);
    printf("State: front=%d, rear=%d\n", circularQ.front, circularQ.rear);

    printf("\n SUCCESS: Circular queue REUSED the freed space!\n");
    printf("   Elements at indices: 3, 4, 0, 1, 2 (wrapped around)\n");

    printf("\nStep 4: Try to add one more (should be full now)\n");
    printf("Result: ");
    circularEnqueue(&circularQ, 90); // Will show "Queue is Full"
    printf("This is correct - we can store max 4 elements in size-5 array\n");
    printf("(1 slot sacrificed to distinguish empty from full)\n");

    printf("\nStep 5: Dequeue all remaining elements\n");
    while (circularQ.front != circularQ.rear)
    {
        int val = circularDequeue(&circularQ);
        printf("Dequeued: %d - Remaining: ", val);
        circularDisplay(circularQ);
    }

    free(circularQ.Q);

    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("KEY INSIGHT:\n");
    printf("Linear Queue:   Space wastage - can't reuse freed slots\n");
    printf("Circular Queue: Efficient - reuses freed slots via modulo!\n");
    printf("═══════════════════════════════════════════════════════════\n");

    return 0;
}
