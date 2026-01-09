#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
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

int main()
{
    int A[] = {3, 5, 7, 10, 15};
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

    return 0;
}
// Output:
/*
    benraiss@Mbareks-MacBook-Air linkedlist % clang -std=c17 -Wall -Wextra -o ll_display LLDisplay.c
    benraiss@Mbareks-MacBook-Air linkedlist % ./ll_display
    Linked List Elements: 3 5 7 10 15
    Recursive Display: 3 5 7 10 15
    Number of elements in Linked List: 5
    Recursive Count: 5
    Sum of elements in Linked List: 40
    Recursive Sum: 40
    benraiss@Mbareks-MacBook-Air linkedlist %
  */