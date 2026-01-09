#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;

} *first;

void create(int A[], int n)
{
    int i;
    struct Node *t, *last;
    first = (struct Node *)malloc(sizeof(struct Node));
    first->data = A[0];
    first->next = NULL;
    last = first;

    for (i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

void display(struct Node *p)
{
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void RDisplay(struct Node *p)
{
    if (p != NULL)
    {
        printf("%d ", p->data);
        RDisplay(p->next);
    }
}

int count(struct Node *p)
{
    int l = 0;
    while (p != NULL)
    {
        l++;
        p = p->next;
    }
    return l;
}

int RCount(struct Node *p)
{
    if (p != NULL)
    {
        return RCount(p->next) + 1;
    }
    else
    {
        return 0;
    }
}

int sum(struct Node *p)
{
    int s = 0;
    while (p != NULL)
    {
        s += p->data;
        p = p->next;
    }
    return s;
}

int RSum(struct Node *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return RSum(p->next) + p->data;
    }
}

int Max(struct Node *p)
{
    int max = INT32_MIN;

    while (p != NULL)
    {
        if (p->data > max)
        {
            max = p->data;
        }
        p = p->next;
    }
    return max;
}

int RMax(struct Node *p)
{
    int x = 0;

    if (p == 0)
    {
        return INT32_MIN;
    }
    x = RMax(p->next);

    if (x > p->data)
    {
        return x;
    }
    else
    {
        return p->data;
    }
    // Alternatively, using the conditional operator:
    // return (x > p->data) ? x : p->data;
}

int Min(struct Node *p)
{
    int min = INT32_MAX;

    while (p != NULL)
    {
        if (p->data < min)
        {
            min = p->data;
        }
        p = p->next;
    }
    return min;
}

int RMin(struct Node *p)
{
    int x = 0;

    if (p == 0)
    {
        return INT32_MAX;
    }
    x = RMin(p->next);

    if (x < p->data)
    {
        return x;
    }
    else
    {
        return p->data;
    }
    // Alternatively, using the conditional operator:
    // return (x < p->data) ? x : p->data;
}

int main()
{
    int A[] = {3, 5, 7, 10, 30};
    create(A, 5);
    printf("Linked List Elements: ");
    display(first);
    printf("Recursive Display: ");
    RDisplay(first);
    printf("\n");
    printf("Number of elements in Linked List: %d\n", count(first));
    printf("Recursive Count: %d\n", RCount(first));
    printf("Sum of elements in Linked List: %d\n", sum(first));
    printf("Recursive Sum: %d\n", RSum(first));
    printf("Maximum element in Linked List: %d\n", Max(first));
    printf("Recursive Maximum: %d\n", RMax(first));
    printf("Minimum element in Linked List: %d\n", Min(first));
    printf("Recursive Minimum: %d\n", RMin(first));

    return 0;
}
// Output:
/*
  benraiss@Mbareks-MacBook-Air linkedlist % clang -std=c17 -Wall -Wextra -o ll_display LLDisplay.c
    benraiss@Mbareks-MacBook-Air linkedlist % ./ll_display
    Linked List Elements: 3 5 7 10 30
    Recursive Display: 3 5 7 10 30
    Number of elements in Linked List: 5
    Recursive Count: 5
    Sum of elements in Linked List: 55
    Recursive Sum: 55
    Maximum element in Linked List: 30 //max iterative version works too
    Recursive Maximum: 30 // max recursive version works too
    Minimum element in Linked List: 3 // min iterative version
    Recursive Minimum: 3 // min recursive version
  */