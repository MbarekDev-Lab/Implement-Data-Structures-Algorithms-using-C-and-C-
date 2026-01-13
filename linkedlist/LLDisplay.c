// ============================================================================
// LINKED LIST - COMPLETE OPERATIONS (Abdul Bari's Method)
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h> // this library is for boolean data type (true/false)

// ============================================================================
// NODE STRUCTURE
// ============================================================================
struct Node
{
    int data;
    struct Node *next;
} *first = NULL, *second = NULL, *third = NULL;

// ============================================================================
// CREATE LINKED LIST
// ============================================================================
void createFirst(int A[], int n)
{
    int i;
    struct Node *t, *last;

    first = (struct Node *)malloc(sizeof(struct Node));
    if (!first)
        return;

    first->data = A[0];
    first->next = NULL;
    last = first;

    for (i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        if (!t)
            return;

        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

void createSecond(int B[], int n)
{
    int i;
    struct Node *t, *last;

    second = (struct Node *)malloc(sizeof(struct Node));
    if (!second)
        return;

    second->data = B[0];
    second->next = NULL;
    last = second;

    for (i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        if (!t)
            return;

        t->data = B[i];
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
        return RCount(p->next) + 1;
    else
        return 0;
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
        return 0;
    else
        return RSum(p->next) + p->data;
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
            max = p->data;
        p = p->next;
    }
    return max;
}

int RMax(struct Node *p)
{
    int x = 0;
    if (p == NULL)
        return INT_MIN;

    x = RMax(p->next);
    return (x > p->data) ? x : p->data;
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
            min = p->data;
        p = p->next;
    }
    return min;
}

int RMin(struct Node *p)
{
    int x = 0;
    if (p == NULL)
        return INT_MAX;

    x = RMin(p->next);
    return (x < p->data) ? x : p->data;
}

// ============================================================================
// LINEAR SEARCH WITH MOVE TO FRONT OPTIMIZATION
// ============================================================================
struct Node *LSearch(struct Node *p, int key)
{
    struct Node *q = NULL;

    while (p != NULL)
    {
        if (key == p->data)
        {
            // Move to front (only if not already first)
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
// RECURSIVE SEARCH
// ============================================================================
struct Node *RSearch(struct Node *p, int key)
{
    if (p == NULL)
        return NULL;
    if (key == p->data)
        return p;
    return RSearch(p->next, key);
}

// ============================================================================
// INSERT AT GIVEN INDEX (0-BASED)
// ============================================================================
void Insert(struct Node *p, int index, int value)
{
    struct Node *t;
    int i;

    if (index < 0 || index > count(first))
    {
        printf("Invalid index!\n");
        return;
    }

    t = (struct Node *)malloc(sizeof(struct Node));
    if (t == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    t->data = value;

    if (index == 0)
    {
        t->next = first;
        first = t;
    }
    else
    {
        p = first;
        for (i = 0; i < index - 1; i++)
            p = p->next;

        t->next = p->next;
        p->next = t;
    }
}

// ============================================================================
// SORTED INSERT
// ============================================================================
void SortedInsert(struct Node *p, int x)
{
    struct Node *t, *q = NULL;

    t = (struct Node *)malloc(sizeof(struct Node));
    if (t == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    t->data = x;
    t->next = NULL;

    // Empty list
    if (first == NULL)
    {
        first = t;
        return;
    }

    // Find insertion point
    p = first;
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
    // Insert at middle or end
    else
    {
        t->next = q->next;
        q->next = t;
    }
}

// ============================================================================
// DELETE AT GIVEN INDEX (1 BASED)
// ============================================================================
int Delete(struct Node *p, int index)
{
    struct Node *q = NULL;
    int x = -1;
    int i;

    if (index < 1 || index > count(first))
    {
        printf("Invalid index!\n");
        return -1;
    }

    // Delete first node
    if (index == 1)
    {
        q = first;
        x = first->data;
        first = first->next;
        free(q);
        return x;
    }
    // Delete at middle or end
    else
    {
        p = first;
        for (i = 0; i < index - 1; i++)
        {
            q = p;
            p = p->next;
        }

        q->next = p->next;
        x = p->data;
        free(p);
        return x;
    }
}

// ============================================================================
// CHECK IF SORTED
// ============================================================================
int isSorted(struct Node *p)
{
    int x = INT_MIN; // Fixed: Use INT_MIN instead of -65536

    while (p != NULL)
    {
        if (p->data < x)
            return 0;

        x = p->data;
        p = p->next;
    }
    return 1;
}

// ============================================================================
// REMOVE DUPLICATES FROM SORTED LINKED LIST
// ============================================================================
void RemoveDuplicates(struct Node *p)
{
    struct Node *q; // points to current node, q to next node

    if (p == NULL)
        return;

    p = first;       // start from head
    q = first->next; // intialize q to the second node

    // struct Node *p = p->next;
    while (q != NULL)
    {
        if (p->data != q->data)
        {
            p = q;       // move p to q
            q = q->next; // move q to next node
        }
        // if duplicate found delete q
        else
        {
            p->next = q->next; // skip q Unlinking the duplicate node
            // using delete keyword (only in C++) but causes issues in C compilation
            free(q);     // Free memory of duplicate node
            q = p->next; // move q to next node
        }
    }
}

/*
    Initial: first → [3] → [5] → [5] → [7] → [7] → [10] → NULL
                      ↑     ↑
                      p     q

    Step 1: p->data (3) ≠ q->data (5) → Move both forward
            [3] → [5] → [5] → [7] → [7] → [10] → NULL
                   ↑     ↑
                   p     q

    Step 2: p->data (5) == q->data (5) → Delete q
            [3] → [5] ────→ [7] → [7] → [10] → NULL
                   ↑         ↑
                   p         q (after free)

    Step 3: p->data (5) ≠ q->data (7) → Move both forward
            [3] → [5] → [7] → [7] → [10] → NULL
                         ↑     ↑
                         p     q

    Step 4: p->data (7) == q->data (7) → Delete q
            [3] → [5] → [7] ────→ [10] → NULL
                        ↑         ↑
                        p         q

    Step 5: p->data (7) ≠ q->data (10) → Move both forward
            [3] → [5] → [7] → [10] → NULL
                                ↑      ↑
                                p      q

    Step 6: q == NULL → Stop

    Final: [3] → [5] → [7] → [10] → NULL
*/

void RemoveDuplicatesUnsorted(struct Node *p)
{
    struct Node *q, *r;

    if (p == NULL)
        return;

    r = p;
    while (r != NULL && r->next != NULL)
    {
        q = r;
        while (q->next != NULL)
        {
            if (r->data == q->next->data)
            {
                struct Node *temp = q->next;
                q->next = q->next->next;
                free(temp);
            }
            else
            {
                q = q->next;
            }
        }
        r = r->next;
    }
}

// ============================================================================
// REVERSE LINKED LIST // O(N) TIME & O(1) SPACE
// ============================================================================

void ReverseListByData(struct Node *p)
{
    int i = 0;
    int *A;
    int n = count(first);

    A = (int *)malloc(sizeof(int) * n);
    p = first;

    while (p != NULL)
    {
        A[i] = p->data;
        p = p->next;
        i++;
    }

    p = first;
    i--;

    while (p != NULL)
    {
        p->data = A[i--];
        p = p->next;
    }

    free(A);
}

void ReverseListByPointer(struct Node *p)
{
    struct Node *q = NULL, *r = NULL;
    p = first;

    while (p != NULL)
    {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    first = q;
    return;
}

// ============================================================================
// REVERSE LINKED LIST USING SLIDING POINTERS (Iterative)
// ============================================================================
void IReverseList(struct Node *p)
{
    struct Node *q = NULL, *r = NULL;

    p = first;

    while (p != NULL)
    {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    first = q;
}

void IIReverseList(struct Node *p)
{
    struct Node *q = NULL, *r = NULL;
    p = first;

    while (p != NULL)
    {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    first = q;
}

// reverse using recursion
struct Node *RReverseList(struct Node *q, struct Node *p)
{
    if (p != NULL)
    {
        RReverseList(p, p->next);
        p->next = q;
    }
    else
        first = q;

    return first;
}

// Merge and concatenate two sorted linked lists -> concatenation is O(n) but merge is O(m+n)
// ============================================================================
// CONCATENATE   AND MERGE TWO LINKED LISTS O(n) time , O(1) extra space
// ============================================================================
// Concatenate two linked lists and return head of new list
//.lists->             first,        second
void Concat(struct Node *p, struct Node *q)
{
    third = p;

    while (p->next != NULL)
    {
        /* code */
        p = p->next;
    }
    p->next = q;
}

//.lists->    first, second
void Merge(struct Node *p, struct Node *q)
{
    struct Node *last;

    if (p->data < q->data)
    {
        third = last = p;
        p = p->next;
        last->next = NULL;
    }
    else
    {
        third = last = q;
        q = q->next;
        last->next = NULL;
    }

    while (p && q)
    {
        if (p->data < q->data)
        {
            last->next = p;
            last = p;
            p = p->next;
            last->next = NULL;
        }
        else
        {
            last->next = q;
            last = q;
            q = q->next;
            last->next = NULL;
        }
    }

    if (p)
        last->next = p;
    if (q)
        last->next = q;
}

// ============================================================================
// DETECT LOOP IN LINKED LIST Time O(n) , Space O(1)
// ============================================================================
bool isLoop(struct Node *f)
{
    struct Node *p, *q;
    p = q = f;

    do
    {
        p = p->next; // move by one pointer
        q = q->next; // move by two pointers
        q = q ? q->next : q;
    } while (p && q && p != q);

    if (p == q)
    {
        printf("Loop detected in linked list\n");
        return true;
    }
    else
    {
        printf("No loop in linked list\n");
        return false;
    }
}

// ============================================================================
// FREE LINKED LIST
// ============================================================================
void freeList(struct Node *p)
{
    struct Node *temp;
    while (p)
    {
        temp = p;
        p = p->next;
        free(temp);
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    printf("═══════════════════════════════════════════════════════\n");
    printf("  LINKED LIST - COMPLETE OPERATIONS DEMO\n");
    printf("═══════════════════════════════════════════════════════\n\n");

    /*int A[] = {3, 5, 7, 10, 30};
    createFirst(A, 5);

    int B[] = {3, 5, 5, 7, 7, 10, 30, 30};
    createSecond(B, 8);

    printf("Original List: ");
    display(first);
    printf("Recursive Display: ");
    RDisplay(first);
    printf("\n\n");

    // Count & Sum
    printf("═══ COUNT & SUM ═══\n");
    printf("Count (Iterative): %d\n", count(first));
    printf("Count (Recursive): %d\n", RCount(first));
    printf("Sum (Iterative): %d\n", sum(first));
    printf("Sum (Recursive): %d\n\n", RSum(first));

    // Max & Min
    printf("═══ MAX & MIN ═══\n");
    printf("Max (Iterative): %d\n", Max(first));
    printf("Max (Recursive): %d\n", RMax(first));
    printf("Min (Iterative): %d\n", Min(first));
    printf("Min (Recursive): %d\n\n", RMin(first));

    // Search with Move-to-Front
    printf("═══ SEARCH OPERATIONS ═══\n");
    struct Node *temp;
    temp = LSearch(first, 30);
    printf("After searching 30: ");
    display(first);

    temp = LSearch(first, 10);
    if (temp)
        printf("Element %d found!\n", temp->data);
    printf("After searching 10 (Move-to-Front): ");
    display(first);
    printf("\n");

    // Insert Operations
    printf("═══ INSERT OPERATIONS ═══\n");
    Insert(first, 0, 50);
    printf("After inserting 50 at index 0: ");
    display(first);

    Insert(first, 3, 25);
    printf("After inserting 25 at index 3: ");
    display(first);
    printf("\n");

    // Sorted Insert
    printf("═══ SORTED INSERT ═══\n");
    SortedInsert(first, 15);
    printf("After sorted insert 15: ");
    display(first);

    SortedInsert(first, 2);
    printf("After sorted insert 2: ");
    display(first);

    SortedInsert(first, 35);
    printf("After sorted insert 35: ");
    display(first);
    printf("\n");

    // Delete Operation
    printf("═══ DELETE OPERATIONS ═══\n");
    int deletedValue = Delete(first, 4);
    printf("Deleted value at index 4: %d\n", deletedValue);
    printf("After deletion: ");
    display(first);
    printf("\n");

    // Check if sorted
    printf("═══ IS SORTED? ═══\n");
    printf("Is list sorted? %s\n\n", isSorted(first) ? "YES" : "NO");

    // remove duplicates test (uncomment to test)

    printf("List with duplicates: ");
    display(first);
    RemoveDuplicates(first);
    printf("After removing duplicates: "); // 3 5 7 10 30
    display(first);
    printf("\n");

    // Reverse List
    printf("═══ REVERSE LIST By POINTER & DATA ═══\n");
    printf("Original List: ");
    display(first);
    ReverseListByPointer(first);
    printf("After reversing by pointer: ");
    display(first);
    printf("\n");

    // Reverse List by Data
    ReverseListByData(first);
    printf("After reversing by data: ");
    display(first);
    printf("\n");

    // Reverse List using Sliding Pointers
    printf("═══ REVERSE LIST USING SLIDING POINTERS ═══\n");
    IReverseList(first);
    printf("After reversing by sliding pointers: ");
    display(first);
    printf("\n");

    // Reverse List using Iterative Sliding Pointers 2
    IIReverseList(first);

    printf("After reversing by sliding pointers II: ");
    display(first);
    printf("\n");

    // Reverse List using Recursion
    RReverseList(NULL, first);
    printf("After reversing by recursion: ");
    display(first);
    printf("\n");*/

    // merge two lists test
    /*int A[] = {3, 5, 7, 10, 30};
    createFirst(A, 5);

    int B[] = {3, 5, 5, 7, 7, 10, 30, 30};
    createSecond(B, 8);

    printf("First List: ");
    display(first);
    printf("\n \n");
    printf("Second List: ");
    display(second);
    printf("\n");


    Concat(first, second);
    printf("After Concatenation: ");
    display(third);
    printf("\n");
        First List: 3 5 7 10 30
        Second List: 3 5 5 7 7 10 30 30
        After Concatenation: 3 5 7 10 30 3 5 5 7 7 10 30 30

    Merge(first, second);
    printf("After Merge: ");
    display(third);
    printf("\n");*/

    /*
        First List: 3 5 7 10 30
        Second List: 3 5 5 7 7 10 30 30
        After Merge: 3 3 5 5 5 7 7 7 10 10 30 30 30
    */

    // Detect Loop
    // Create a loop for testing
    int L[] = {1, 2, 3, 4, 5};
    createFirst(L, 5); // 1 2 3 4 5

    struct Node *t1, *t2;
    t1 = first->next->next;             // 3rd node
    t2 = first->next->next->next->next; // 5th node
    t2->next = t1;                      // Create loop for testing 5 -> 3

    printf("═══ DETECT LOOP IN LINKED LIST ═══\n");
    printf("Checking for loop in linked list... %s\n", isLoop(first) ? "Loop detected" : "No loop detected");

    printf("\n");

    /*
            Loop detected in linked list
            Checking for loop in linked list... Loop detected
    */

    // Cleanup
    t2->next = NULL; // Break the loop before freeing
    freeList(first);
    printf("═══════════════════════════════════════════════════════\n");
    printf("Memory freed successfully!\n");

    return 0;
}

/**
benraiss@MacBookAir linkedlist % clang -std=c17 -Wall -Wextra -o ll_display LLDisplay.c
benraiss@MacBookAir linkedlist % ./ll_display
═══════════════════════════════════════════════════════
  LINKED LIST - COMPLETE OPERATIONS DEMO
═══════════════════════════════════════════════════════

Original List: 3 5 7 10 30
Recursive Display: 3 5 7 10 30

═══ COUNT & SUM ═══
Count (Iterative): 5
Count (Recursive): 5
Sum (Iterative): 55
Sum (Recursive): 55

═══ MAX & MIN ═══
Max (Iterative): 30
Max (Recursive): 30
Min (Iterative): 3
Min (Recursive): 3

═══ SEARCH OPERATIONS ═══
After searching 30: 30 3 5 7 10
Element 10 found!
After searching 10 (Move-to-Front): 10 30 3 5 7

═══ INSERT OPERATIONS ═══
After inserting 50 at index 0: 50 10 30 3 5 7
After inserting 25 at index 3: 50 10 30 25 3 5 7

═══ SORTED INSERT ═══
After sorted insert 15: 15 50 10 30 25 3 5 7
After sorted insert 2: 2 15 50 10 30 25 3 5 7
After sorted insert 35: 2 15 35 50 10 30 25 3 5 7

═══ DELETE OPERATIONS ═══
Deleted value at index 4: 50
After deletion: 2 15 35 10 30 25 3 5 7

═══ IS SORTED? ═══
Is list sorted? NO

List with duplicates: 3 5 5 7 7 10 30 30
After removing duplicates: 3 5 7 10 30

═══ REVERSE LIST By POINTER & DATA ═══
Original List: 3 5 7 10 30
After reversing by pointer: 30 10 7 5 3

After reversing by data: 3 5 7 10 30

═══ REVERSE LIST USING SLIDING POINTERS ═══
After reversing by sliding pointers: 30 10 7 5 3

After reversing by sliding pointers II: 3 5 7 10 30

After reversing by recursion: 30 10 7 5 3

═══════════════════════════════════════════════════════
Memory freed successfully!
benraiss@MacBookAir linkedlist %
 */