#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define EMPTY -1 // Marker for empty slot

// Hash function
int hash(int key)
{
    return key % SIZE;
}

// Generic probe function , finds empty slot or key location
// Returns: index if found/empty slot available, -1 if table full
// Abdul Bari’s words Never allow hash table to become full rehash before that.
int probe(int HT[], int key, int *probes)
{
    int index = hash(key);
    int i = 0;

    *probes = 0; // Track number of probes

    // Linear probe until empty slot or matching key found
    while (HT[(index + i) % SIZE] != EMPTY)
    {
        (*probes)++;

        // If we find the key, return its index
        if (HT[(index + i) % SIZE] == key)
            return (index + i) % SIZE;

        i++;
        if (i == SIZE)
        {
            return -1; // Table full
        }
    }

    (*probes)++;
    return (index + i) % SIZE; // Return empty slot index
}

// Linear Probing Insert (refactored to use probe())
void Insert(int HT[], int key)
{
    int initial_hash = hash(key);
    int probes = 0;

    printf("Inserting %d (hash = %d):\n", key, initial_hash);

    int index = probe(HT, key, &probes);

    if (index == -1)
    {
        printf("  Hash table is FULL!\n");
        return;
    }

    // Check if key already exists
    if (HT[index] == key)
    {
        printf("  Key %d already exists at index %d\n", key, index);
        return;
    }

    if (probes > 1)
        printf("  Collision! Probed %d times\n", probes);

    HT[index] = key;
    printf("  Inserted at index %d\n", index);
}

// Linear Probing Search (refactored to use probe())
int Search(int HT[], int key)
{
    int probes = 0;
    int index = probe(HT, key, &probes);

    // If we found an empty slot, key doesn't exist
    if (index != -1 && HT[index] == EMPTY)
        return -1;

    return index;
}

int Search2(int H[], int key)
{
    int inedx = hash(key);
    int i = 0;
    while (H[(inedx + i) % SIZE] != EMPTY)
    {
        i++;
        return (inedx + i) % SIZE;
    }
}

// Display hash table
void Display(int HT[])
{
    printf("\nHash Table:\n");
    for (int i = 0; i < SIZE; i++)
    {
        if (HT[i] == EMPTY)
            printf("HT[%d]: EMPTY\n", i);
        else
            printf("HT[%d]: %d\n", i, HT[i]);
    }
    printf("\n");
}

int main()
{
    int HT[SIZE];

    // Initialize hash table with EMPTY markers
    for (int i = 0; i < SIZE; i++)
        HT[i] = EMPTY;

    printf("=== LINEAR PROBING HASH TABLE ===\n\n");

    // Insert elements
    Insert(HT, 12); // hash(12) = 2
    Insert(HT, 25); // hash(25) = 5
    Insert(HT, 35); // hash(35) = 5  (collision! probe to 6)
    Insert(HT, 26); // hash(26) = 6  (collision! probe to 7)
    Insert(HT, 15); // hash(15) = 5  (collision! probe to 8)

    Display(HT);

    // Search for keys
    printf("=== SEARCHING ===\n");

    int key = 35;
    int index = Search(HT, key);
    if (index != -1)
        printf("Key %d found at index: %d\n", key, index);
    else
        printf("Key %d not found.\n", key);

    key = 22;
    index = Search(HT, key);
    if (index != -1)
        printf("Key %d found at index: %d\n", key, index);
    else
        printf("Key %d not found.\n", key);

    key = 26;
    index = Search(HT, key);
    if (index != -1)
        printf("Key %d found at index: %d\n", key, index);
    else
        printf("Key %d not found.\n", key);

    return 0;
}

/*

    benraiss@Mbareks-MacBook-Air hashing % clang -std=c17 -Wall -Wextra -o _lhashing LinearProbing.c
    benraiss@Mbareks-MacBook-Air hashing % ./_lhashing
    === LINEAR PROBING HASH TABLE ===

    Inserting 12 (hash = 2):
    Inserted at index 2
    Inserting 25 (hash = 5):
    Inserted at index 5
    Inserting 35 (hash = 5):
    Collision! Probed 2 times
    Inserted at index 6
    Inserting 26 (hash = 6):
    Collision! Probed 2 times
    Inserted at index 7
    Inserting 15 (hash = 5):
    Collision! Probed 4 times
    Inserted at index 8

    Hash Table:
    HT[0]: EMPTY
    HT[1]: EMPTY
    HT[2]: 12
    HT[3]: EMPTY
    HT[4]: EMPTY
    HT[5]: 25
    HT[6]: 35
    HT[7]: 26
    HT[8]: 15
    HT[9]: EMPTY

    === SEARCHING ===
    Key 35 found at index: 6
    Key 22 not found.
    Key 26 found at index: 7
    benraiss@Mbareks-MacBook-Air hashing %


    Insert 15 (hash = 5):
  Try index 5: occupied (25) → probe 1
  Try index 6: occupied (35) → probe 2
  Try index 7: occupied (26) → probe 3
  Try index 8: EMPTY!        → probe 4

Total: 4 probes!

*/