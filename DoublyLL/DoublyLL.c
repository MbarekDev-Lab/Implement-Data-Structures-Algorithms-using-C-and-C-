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
void insertNode(struct Node *p, int index, int x);
int deleteNode(struct Node *p, int index);
void reverseDoublyLinkedList(struct Node *p);
void Display(struct Node *p);
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
// INSERTION NEW NODE AT GIVEN POSITION
// ============================================================================
/*
 * Insert node at specific index (0-based)
 *
 * Example: Insert 25 at index 2 in [10, 20, 30]
 * Before: NULL <-> 10 <-> 20 <-> 30 <-> NULL
 * After:  NULL <-> 10 <-> 20 <-> 25 <-> 30 <-> NULL
 *                               ↑ (index 2)
 *
 * Time: O(n), Space: O(1)
 */
void insertNode(struct Node *p, int index, int x)
{
    struct Node *t;
    int i;

    if (index < 0 || index > length(first))
    {
        printf("Invalid index!\n");
        return;
    }

    // Case 1: Insert at beginning (index 0)
    if (index == 0)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = x;
        t->prev = NULL;
        t->next = first;

        if (first != NULL) // Check if list is not empty
        {
            first->prev = t;
        }
        first = t;
    }
    // Case 2: Insert at middle or end
    else
    {
        p = first; // Start from first, not using parameter p

        // Move to node before insertion point
        for (i = 0; i < index - 1; i++)
        {
            p = p->next;
        }

        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = x;

        // Link new node
        t->next = p->next; // t points forward to p's next
        t->prev = p;       // t points back to p

        if (p->next != NULL) // If not inserting at end
        {
            p->next->prev = t; // Update forward node's back pointer
        }

        p->next = t; // p now points forward to t
    }
}

// ============================================================================
//  DELETE NODE AT GIVEN POSTION DOUBLY LINKED LIST
// ============================================================================

int deleteNode(struct Node *p, int index)
{
    // struct Node *q = NULL;
    int i, x = -1;

    if (index < 1 || index > length(first))
    {
        printf("Invalid index!\n");
        return -1;
    }

    // Delete first node
    if (index == 1)
    {
        p = first;
        first = first->next;
        if (first != NULL)
        {
            first->prev = NULL;
        }

        x = p->data;
        free(p);
        return x;
    }
    // Delete at middle or end
    else
    {
        p = first;
        for (i = 0; i < index - 1; i++)
        {
            p = p->next;
        }

        p->prev->next = p->next;

        if (p->next != NULL)
        {
            p->next->prev = p->prev;
        }

        x = p->data;
        free(p);
        return x; // retturn deleted value
    }
}

// ============================================================================
// REVERSE DOUBLY LINKED LIST
// ============================================================================

void reverseDoublyLinkedList(struct Node *p)
{
    struct Node *temp = NULL;
    // struct Node *current = p;

    // Swap next and prev for all nodes
    while (p != NULL)
    {
        // Swap prev and next
        temp = p->next;
        p->next = p->prev;
        p->prev = temp;
        p = p->prev;

        if (p != NULL && p->next == NULL)
        {
            first = p;
        }

        /*temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        // Move to next node (which is previous before swap)
        current = current->prev;*/
    }

    // Update first to new head
    // if (temp != NULL)first = temp->prev;
}

// ============================================================================
// DISPLAY REVERSED LL
// ============================================================================
void Display(struct Node *p)
{
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
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

    printf("═══ DISPLAY FORWARD ═══\n");
    displayForward(first);
    printf("\n");

    printf("Inserting 25 at index 3 and 5:\n");
    insertNode(first, 3, 25);
    insertNode(first, 5, 25);

    printf("After inserting 25 at index 3 and 5:\n");
    Display(first);
    printf("\n");

    printf("══ deleting node at a given position ══\n");
    printf("deleting nodes at index 2 and 4:\n");
    printf("\n");

    deleteNode(first, 2);
    deleteNode(first, 4);

    printf("\nLenght is : %d\n", length(first));
    printf("═══ reverse doubly linked list═══\n");
    reverseDoublyLinkedList(first);
    Display(first);
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
        Program completed successfully!
        benraiss@MacBookAir DoublyLL % clang -std=c17 -Wall -Wextra -o doubly_ll DoublyLL.c
        benraiss@MacBookAir DoublyLL % ./doubly_ll
        ═══════════════════════════════════════════════════════
        DOUBLY LINKED LIST - OPERATIONS DEMO
        ═══════════════════════════════════════════════════════

        Creating doubly linked list from array: 10 20 30 40 50

        ═══ DISPLAY FORWARD ═══
        Forward: NULL <-> 10 <-> 20 <-> 30 <-> 40 <-> 50 <-> NULL

        Inserting 25 at index 3 and 5:
        10 20 30 25 40 25 50
        ══ deleting node at a given position ══
        deleting nodes at index 2 and 4:


        Lenght is : 5
        ═══ reverse doubly linked list═══
        50 25 25 30 10
        ═══ DISPLAY BACKWARD ═══
        Backward: NULL <-> 10 <-> 30 <-> 25 <-> 25 <-> 50 <-> NULL

        ═══ LIST LENGTH ═══
        Length: 5

        ═══ MEMORY STRUCTURE (Conceptual) ═══
        NULL <-> [10] <-> [20] <-> [30] <-> [40] <-> [50] <-> NULL
            ↑                                          ↑
            first                                      last

        ═══════════════════════════════════════════════════════
        Program completed successfully!
*/
