#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *prev;
    int data;
    struct Node *next;
} *first = NULL;

// Function declarations
void createDoublyLinkedList(int A[], int n);
void displayForward(struct Node *p);
void displayBackward(struct Node *p);
int length(struct Node *p);

// ============================================================================
// CREATE DOUBLY LINKED LIST
// ============================================================================
void createDoublyLinkedList(int A[], int n)
{
    struct Node *t, *last;
    int i;

    first = (struct Node *)malloc(sizeof(struct Node));
    first->data = A[0];
    first->next = first->prev = NULL;

    last = first;

    for (i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        // t->next = last->next;
        t->next = NULL;
        t->prev = last;
        last->next = t;
        last = t;

        /*

           0x1000              0x2000              0x3000              0x4000
        ┌─────────────┐    ┌─────────────┐    ┌─────────────┐    ┌─────────────┐
        │ prev: NULL  │    │ prev: 0x1000│    │ prev: 0x2000│    │ prev: 0x3000│
        │ data: 10    │ ──→│ data: 20    │ ──→│ data: 30    │ ──→│ data: 40    │
        │ next: 0x2000│ ←──│ next: 0x3000│ ←──│ next: 0x4000│ ←──│ next: ???   │
        └─────────────┘    └─────────────┘    └─────────────┘    └─────────────┘
            ↑                                                          ↑
          first                                                      last

        */
    }
}

// ============================================================================
// DISPLAY FORWARD
// ============================================================================
void displayForward(struct Node *p)
{
    printf("Forward: NULL");
    while (p != NULL)
    {
        printf(" <-> %d", p->data);
        p = p->next;
    }
    printf(" <-> NULL\n");
}

// ============================================================================
// DISPLAY BACKWARD
// ============================================================================
void displayBackward(struct Node *p)
{
    if (p == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (p->next != NULL)
    {
        p = p->next;
    }

    printf("Backward: NULL");
    while (p != NULL)
    {
        printf(" <-> %d", p->data);
        p = p->prev;
    }
    printf(" <-> NULL\n");
}

// ============================================================================
// GET LENGTH
// ============================================================================
int length(struct Node *p)
{
    int len = 0;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    printf("═══════════════════════════════════════════════════════\n");
    printf("  DOUBLY LINKED LIST - OPERATIONS DEMO\n");
    printf("═══════════════════════════════════════════════════════\n\n");

    int A[] = {10, 20, 30, 40, 50};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Creating doubly linked list from array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n\n");

    createDoublyLinkedList(A, n);

    printf("\nLenght is : %d\n", length(first));

    printf("═══ DISPLAY FORWARD ═══\n");
    displayForward(first);
    printf("\n");

    printf("═══ DISPLAY BACKWARD ═══\n");
    displayBackward(first);
    printf("\n");

    printf("═══ LIST LENGTH ═══\n");
    printf("Length: %d\n\n", length(first));

    printf("═══ MEMORY STRUCTURE (Conceptual) ═══\n");
    printf("NULL <-> [10] <-> [20] <-> [30] <-> [40] <-> [50] <-> NULL\n");
    printf("       ↑                                          ↑\n");
    printf("     first                                      last\n\n");

    printf("═══════════════════════════════════════════════════════\n");
    printf("Program completed successfully!\n");

    return 0;
}

/*
    benraiss@MacBookAir DoublyLL % clang -std=c17 -Wall -Wextra -o doubly_ll DoublyLL.c
    benraiss@MacBookAir DoublyLL % ./doubly_ll
    ═══════════════════════════════════════════════════════
    DOUBLY LINKED LIST - OPERATIONS DEMO
    ═══════════════════════════════════════════════════════

    Creating doubly linked list from array: 10 20 30 40 50


    Lenght is : 5
    ═══ DISPLAY FORWARD ═══
    Forward: NULL <-> 10 <-> 20 <-> 30 <-> 40 <-> 50 <-> NULL

    ═══ DISPLAY BACKWARD ═══
    Backward: NULL <-> 50 <-> 40 <-> 30 <-> 20 <-> 10 <-> NULL

    ═══ LIST LENGTH ═══
    Length: 5

    ═══ MEMORY STRUCTURE (Conceptual) ═══
    NULL <-> [10] <-> [20] <-> [30] <-> [40] <-> [50] <-> NULL
        ↑                                          ↑
        first                                      last

    ═══════════════════════════════════════════════════════
    Program completed successfully!
*/
