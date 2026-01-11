#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ============================================================================
// NODE STRUCTURE
// ============================================================================
struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;

} *first = NULL;

// ============================================================================
// CREATE LINKED LIST
// ============================================================================
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

// ============================================================================
// DISPLAY FUNCTIONS
// ============================================================================
void display(struct Node *p)
{
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// ============================================================================
// DISPLAY FUNCTIONS
// ============================================================================
void RDisplay(struct Node *p)
{
    if (p != NULL)
    {
        printf("%d ", p->data);
        RDisplay(p->next);
    }
}

// ============================================================================
// COUNT FUNCTIONS
// ============================================================================
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

// ============================================================================
// SUM FUNCTIONS
// ============================================================================
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

// ============================================================================
// MAX FUNCTIONS
// ============================================================================
int Max(struct Node *p)
{
    int max = INT_MIN;

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

    if (p == NULL)
    {
        return INT_MIN;
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

// ============================================================================
// MIN FUNCTIONS
// ============================================================================
int Min(struct Node *p)
{
    int min = INT_MAX;

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

    if (p == NULL)
    {
        return INT_MAX;
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

// ============================================================================
// LINEAR SEARCH WITH MOVE TO FRONT OPTIMIZATION
// ============================================================================
struct Node *LSearch(struct Node *p, int key)
{
    struct Node *q = NULL;

    while (p != NULL)
    {
        // q = p; // previous node
        if (key == p->data)
        {
            // Move to front optimization (only if not already first)
            if (q != NULL)
            {
                q->next = p->next;
                p->next = first;
                first = p;
            }
            return p;
        }

        q = p;
        p = p->next;
    }
    return NULL;
}

// ============================================================================
// RECURSIVE SEARCH (NO MOVE TO FRONT)
// ============================================================================
struct Node *RSearch(struct Node *p, int key)
{
    if (p == NULL)
    {
        return NULL;
    }
    if (key == p->data)
    {
        return p;
    }
    return RSearch(p->next, key);
}

// ============================================================================
// INSERT AT GIVEN INDEX
// ============================================================================

void Insert(struct Node *p, int index, int value)
{
    struct Node *t;
    int i;

    // Validate index (must be between 0 and length)
    if (index < 0 || index > count(first))
    {
        printf("Invalid index!\n");
        return;
    }

    // Create new node
    t = (struct Node *)malloc(sizeof(struct Node));
    if (t == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    t->data = value;

    // ========== Insert at beginning (index 0) ==========
    if (index == 0)
    {
        t->next = first;
        first = t;
    }
    // ========== Insert at middle or end ==========
    else
    {
        p = first; // Start from first node

        // Traverse to the node BEFORE insertion point
        for (i = 0; i < index - 1; i++)
        {
            p = p->next;
        }

        // Link new node into list
        t->next = p->next;
        p->next = t;
    }
}

void SortedInsert(struct Node *p, int x)
{

    struct Node *t, *q = NULL;

    t = (struct Node *)malloc(sizeof(struct Node));

    // cpp->  Node* t = new Node;

    t->data = x;
    t->next = NULL;

    // Insert at beginning
    if (first == NULL)
    {
        first = t;
    }
    else
    {
        while (p != NULL && p->data < x)
        {
            q = p;
            p = p->next;
        }
        // Insert at beginning
        if (p == first)
        {
            t->next = first;
            first = t;
        }
        else
        {
            t->next = q->next;
            q->next = t;
        }
    }
}

int Delete(struct Node *p, int index)
{
    struct Node *q = NULL;
    int x = -1;
    int i;

    // Validate index (1 based: valid range is 1 to count)
    if (index < 1 || index > count(first)) // checking with count function as length is not stored
    {
        printf("Invalid index!\n");
        return -1;
    }

    // ========== Delete first node (index 1) ==========
    if (index == 1)
    {
        q = first;
        x = first->data;
        first = first->next;
        free(q);
        return x;
    }
    // ========== Delete at middle or end ==========
    else
    {
        p = first;

        // Traverse to the node BEFORE the one to delete
        for (i = 0; i < index - 1; i++)
        {
            // q points to the node before the one to delete
            // p points to the node to delete
            
            q = p;
            p = p->next;
        }

        // Unlink and delete
        q->next = p->next;
        x = p->data;
        free(p); // Free memory
        return x;
    }
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

    struct Node *temp;
    temp = LSearch(first, 30);
    temp = LSearch(first, 10);
    // temp = RSearch(first, 10);
    if (temp)
    {
        printf("Element %d found in Linked List.\n", temp->data);
    }
    else
    {
        printf("Element not found in Linked List.\n");
    }

    // Display list after search with move to front
    printf("Linked List after Search (with Move to Front): ");
    display(first);
    printf("\n");

    // Insert at index 0
    printf("Inserting 50 at index 0.\n");
    Insert(first, 0, 50);
    printf("Linked List after Insertion at index 0: ");
    display(first);
    printf("\n");

    // Insert at index 3
    printf("Inserting 25 at index 3.\n");
    Insert(first, 3, 25);
    printf("Linked List after Insertion at index 3: ");
    display(first);
    printf("\n");

    // Sorted Insert
    printf("Sorted Inserting 15 into Linked List.\n");
    SortedInsert(first, 15);
    SortedInsert(first, 2);
    SortedInsert(first, 35);
    printf("Linked List after Sorted Insertion of 2 and 15: ");
    display(first); // 2 15 35
    printf("\n");

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