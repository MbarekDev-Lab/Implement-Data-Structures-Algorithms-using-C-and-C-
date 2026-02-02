#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
struct Node
{
    int data;
    struct Node *next;
};

// Insert node in sorted order into linked list
void SortedInsert(struct Node **H, int x)
{
    struct Node *t, *q = NULL, *p = *H;

    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;
    t->next = NULL;

    if (*H == NULL)
        *H = t;
    else
    {
        while (p && p->data < x)
        {
            q = p;
            p = p->next;
        }
        if (p == *H)
        {
            t->next = *H;
            *H = t;
        }
        else
        {
            t->next = q->next;
            q->next = t;
        }
    }
}

// Search for a key in linked list
struct Node *Search(struct Node *p, int key)
{
    while (p != NULL)
    {
        if (key == p->data)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// Hash function: key % 10
int hash(int key)
{
    return key % 10; // return size of hash table (map key to index 0-9)
}

// Insert key into hash table
void Insert(struct Node *H[], int key)
{
    int index = hash(key);
    SortedInsert(&H[index], key);
}

// Display hash table
void Display(struct Node *H[], int size)
{
    printf("\nHash Table:\n");
    for (int i = 0; i < size; i++)
    {
        printf("HT[%d]: ", i);
        struct Node *p = H[i];
        while (p != NULL)
        {
            printf("%d -> ", p->data);
            p = p->next;
        }
        printf("NULL\n");
    }
}

int main()
{
    struct Node *HT[10];
    struct Node *temp;
    int i;

    // Initialize hash table
    for (i = 0; i < 10; i++)
        HT[i] = NULL;

    // Insert elements
    printf("Inserting: 12, 22, 42\n");
    Insert(HT, 12); // hash(12) = 12 % 10 = 2
    Insert(HT, 22); // hash(22) = 22 % 10 = 2  (collision!)
    Insert(HT, 42); // hash(42) = 42 % 10 = 2  (collision!)

    Display(HT, 10);

    // Search for existing key
    printf("\nSearching for 22: ");
    temp = Search(HT[hash(22)], 22);
    if (temp != NULL)
        printf("Found: %d\n", temp->data);
    else
        printf("Not found\n");

    // Search for non-existing key (was the bug!)
    printf("Searching for 21: ");
    temp = Search(HT[hash(21)], 21);
    if (temp != NULL)
        printf("Found: %d\n", temp->data);
    else
        printf("Not found\n");

    return 0;
}

/*

    benraiss@Mbareks-MacBook-Air hashing %  clang -std=c17 -Wall -Wextra -o _chaining Chaining.c && ./_chaining
    Inserting: 12, 22, 42

    Hash Table:
    HT[0]: NULL
    HT[1]: NULL
    HT[2]: 12 -> 22 -> 42 -> NULL
    HT[3]: NULL
    HT[4]: NULL
    HT[5]: NULL
    HT[6]: NULL
    HT[7]: NULL
    HT[8]: NULL
    HT[9]: NULL

    Searching for 22: Found: 22
    Searching for 21: Not found
    benraiss@Mbareks-MacBook-Air hashing %
    
*/