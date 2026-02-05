#include <stdio.h>
#include <stdlib.h>

/**
 * Max Heap Implementation in C
 * Using 1-based indexing (index 0 is unused)
 * 
 * Parent of i: i/2
 * Left child:  2*i
 * Right child: 2*i+1
 */

/**
 * Insert element into Max Heap (Heapify Up / Bubble Up)
 * Time Complexity: O(log n)
 * 
 * @param H  Heap array (1-indexed, index 0 unused)
 * @param n  Index where new element is to be inserted
 */
void Insert(int H[], int n)
{
    int i = n;      // Current position of new element
    int temp = H[i]; // Store the element to insert

    // Bubble up: Compare with parent and shift parents down if needed
    while (i > 1 && temp > H[i / 2])
    {
        H[i] = H[i / 2]; // Move parent down
        i = i / 2;        // Move to parent's position
    }
    H[i] = temp; // Place element at final position
}

/**
 * Delete (Extract Max) from Max Heap (Heapify Down / Bubble Down)
 * Time Complexity: O(log n)
 * 
 * Removes the root (maximum element) and reorganizes the heap
 * 
 * @param H  Heap array
 * @param n  Current size of heap
 * @return   The deleted maximum element
 */
int Delete(int H[], int n)
{
    int i, j, temp;
    int deletedValue = H[1]; // Store max element (root)
    int lastElement = H[n];   // Last element to be moved

    H[1] = lastElement; // Move last element to root
    i = 1;              // Start at root
    j = 2 * i;          // Left child

    // Bubble down: Compare with children and swap with larger child
    while (j <= n - 1)
    {
        // Pick the larger child
        if (j < n - 1 && H[j + 1] > H[j])
        {
            j = j + 1; // Right child is larger
        }

        // If parent is smaller than larger child, swap 
        if (lastElement < H[j])
        {
            H[i] = H[j]; // Move child up
            i = j;        // Move to child's position
            j = 2 * i;    // Next level children
        }
        else
        {
            break; // Heap property satisfied
        }
    }
    H[i] = lastElement; // Place last element at final position
    return deletedValue;
}

/**
 * Print heap array
 */
void printHeap(int H[], int n)
{
    printf("Heap: [");
    for (int i = 1; i <= n; i++)
    {
        printf("%d", H[i]);
        if (i < n)
            printf(", ");
    }
    printf("]\n");
}

/**
 * Print heap as tree structure (simple visualization)
 */
void printTree(int H[], int n)
{
    printf("\nHeap Tree Structure:\n");
    int level = 0;
    int elementsInLevel = 1;
    int index = 1;

    while (index <= n)
    {
        // Print spacing
        for (int i = 0; i < (4 - level); i++)
            printf("  ");

        // Print elements at this level
        for (int i = 0; i < elementsInLevel && index <= n; i++)
        {
            printf("%d ", H[index++]);
        }
        printf("\n");

        level++;
        elementsInLevel *= 2;
    }
    printf("\n");
}

/**
 * Build heap from array using repeated insertions
 */
void buildHeap(int H[], int n)
{
    printf("Building heap by inserting elements one by one...\n\n");
    for (int i = 2; i <= n; i++)
    {
        printf("Inserting H[%d] = %d\n", i, H[i]);
        Insert(H, i);
        printHeap(H, i);
    }
}

/**
 * Heap Sort (sorts in ascending order)
 * Repeatedly delete max and place at end
 */
void heapSort(int H[], int n)
{
    printf("\n=== HEAP SORT ===\n");
    printf("Extracting elements in descending order:\n\n");

    int originalSize = n;

    // Extract max repeatedly
    for (int i = n; i > 1; i--)
    {
        int max = Delete(H, i);
        H[i] = max; // Place deleted max at end
        printf("Extracted: %d\n", max);
        printHeap(H, i - 1);
    }

    printf("\nSorted array (ascending): ");
    for (int i = 1; i <= originalSize; i++)
    {
        printf("%d ", H[i]);
    }
    printf("\n");
}

int main()
{
    printf("==========================================\n");
    printf("  MAX HEAP IMPLEMENTATION (1-indexed)\n");
    printf("==========================================\n\n");

    // Example 1: Building a heap
    printf("Example 1: Building Heap\n");
    printf("-------------------------\n");
    int H1[] = {0, 10, 20, 30, 25, 5, 40, 35}; // Index 0 unused
    int n1 = 7;

    printf("Initial array (excluding index 0): ");
    for (int i = 1; i <= n1; i++)
        printf("%d ", H1[i]);
    printf("\n\n");

    buildHeap(H1, n1);
    printTree(H1, n1);

    // Example 2: Insert and Delete operations
    printf("\n==========================================\n");
    printf("Example 2: Insert and Delete Operations\n");
    printf("==========================================\n\n");

    int H2[] = {0, 50, 30, 20, 15, 10, 8, 16}; // Already a heap
    int n2 = 7;

    printf("Initial heap:\n");
    printHeap(H2, n2);
    printTree(H2, n2);

    printf("Deleting maximum element...\n");
    int max = Delete(H2, n2);
    n2--;
    printf("Deleted: %d\n", max);
    printHeap(H2, n2);
    printTree(H2, n2);

    // Example 3: Heap Sort
    printf("\n==========================================\n");
    printf("Example 3: Heap Sort\n");
    printf("==========================================\n\n");

    int H3[] = {0, 14, 15, 5, 20, 30, 8, 40};
    int n3 = 7;

    printf("Original array: ");
    for (int i = 1; i <= n3; i++)
        printf("%d ", H3[i]);
    printf("\n\n");

    // Build heap
    buildHeap(H3, n3);

    // Perform heap sort
    heapSort(H3, n3);

    printf("\n==========================================\n");
    printf("  DEMONSTRATION COMPLETE!\n");
    printf("==========================================\n");

    return 0;
}

/*
Expected Output:

==========================================
  MAX HEAP IMPLEMENTATION (1-indexed)
==========================================

Example 1: Building Heap
-------------------------
Initial array (excluding index 0): 10 20 30 25 5 40 35 

Building heap by inserting elements one by one...

Inserting H[2] = 20
Heap: [20, 10]
Inserting H[3] = 30
Heap: [30, 10, 20]
Inserting H[4] = 25
Heap: [30, 25, 20, 10]
Inserting H[5] = 5
Heap: [30, 25, 20, 10, 5]
Inserting H[6] = 40
Heap: [40, 25, 30, 10, 5, 20]
Inserting H[7] = 35
Heap: [40, 25, 35, 10, 5, 20, 30]

Heap Tree Structure:
        40 
      25 35 
    10 5 20 30 

*/