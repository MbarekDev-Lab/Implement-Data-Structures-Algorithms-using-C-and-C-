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

int main()
{
    int A[] = {10, 20, 30, 40, 50};
    int n = sizeof(A) / sizeof(A[0]);
    createCircularLinkedList(A, n);
    // DisplayCircularLinkedList(Head);

    RDisplayCircularLinkedList(Head);
    printf("\n");

    return 0;
}