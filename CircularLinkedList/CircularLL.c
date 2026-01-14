#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;

} *Head;

void createCircularLinkedList(int A[], int n)
{
    int i;
    struct Node *t, *last;

    Head = (struct Node *)malloc(sizeof(struct Node));
    Head->data = A[0];
    Head->next = Head; // Point to itself to make it circular
    last = Head;

    for (i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = last->next; // Point new node to head
        last->next = t;       // Link last node to new node
        last = t;             // Update last to new node
    }
}

int LengthLL(struct Node *p)
{
    int len = 0;

    if (p == NULL)
        return 0;

    do
    {

        len++;
        p = p->next;
    } while (p != Head);

    /*
    struct Node *temp = p;
    do
        {
            len++;
            temp = temp->next;
        } while (temp != p);


    */
    return len;
}

void DisplayCircularLinkedList(struct Node *h)
{
    struct Node *p = h;
    if (h == NULL)
        return;

    do
    {
        printf("%d -> ", p->data);
        p = p->next;
    } while (p != h);
    printf("(head: %d)\n", h->data);
}

void RDisplayCircularLinkedList(struct Node *h)
{
    static int flag = 0;

    if (h != NULL)
    {
        if (h != Head || flag == 0)
        {
            flag = 1;
            printf("%d -> ", h->data);
            RDisplayCircularLinkedList(h->next);
        }
    }

    flag = 0; // Reset flag for future calls
}

void InsertAtGivenPosition(struct Node *p, int index, int x)
{
    struct Node *t = NULL;

    if (index < 0 || index > LengthLL(p))
        return;

    // Inserting at head (index 0)
    if (index == 0)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = x;

        if (Head == NULL)
        {
            Head = t;
            Head->next = Head;
        }
        else
        {
            while (p->next != Head)
            {
                p = p->next;
            }
            p->next = t;
            t->next = Head;
            Head = t;
        }
    }

    for (int i = 0; i < index - 1; i++)
    {
        p = p->next;
    }

    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;
    t->next = p->next;
    p->next = t;
}

int main()
{
    int A[] = {10, 20, 30, 40, 50};
    int n = sizeof(A) / sizeof(A[0]);
    createCircularLinkedList(A, n);
    // DisplayCircularLinkedList(Head);

    RDisplayCircularLinkedList(Head);
    printf("\n");

    InsertAtGivenPosition(Head, 2, 500);
    DisplayCircularLinkedList(Head);

    return 0;
}

/*
benraiss@MacBookAir CircularLinkedList % clang -std=c17 -Wall -Wextra -o circular_ll CircularLL.c
benraiss@MacBookAir CircularLinkedList % ./circular_ll
10 -> 20 -> 30 -> 40 -> 50 ->
500 -> 10 -> 20 -> 30 -> 40 -> 50 -> 500 -> (head: 500)
benraiss@MacBookAir CircularLinkedList % clang -std=c17 -Wall -Wextra -o circular_ll CircularLL.c
benraiss@MacBookAir CircularLinkedList % ./circular_ll
10 -> 20 -> 30 -> 40 -> 50 ->
10 -> 20 -> 30 -> 40 -> 50 -> 500 -> (head: 10)
benraiss@MacBookAir CircularLinkedList % clang -std=c17 -Wall -Wextra -o circular_ll CircularLL.c
benraiss@MacBookAir CircularLinkedList % ./circular_ll
10 -> 20 -> 30 -> 40 -> 50 ->
10 -> 20 -> 500 -> 30 -> 40 -> 50 -> (head: 10)
benraiss@MacBookAir CircularLinkedList %
*/