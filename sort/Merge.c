#include <stdio.h>
#include <stdlib.h>

// Print array helper function
void printArray(int A[], int n, const char *msg)
{
    printf("%s: ", msg);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Copy array helper function
void copyArray(int src[], int dest[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

// Merge two sorted subarrays A[l..mid] and A[mid+1..h]
void Merge(int A[], int l, int mid, int h)
{
    int i = l;       // starting index for left subarray
    int j = mid + 1; // starting index for right subarray
    int k = l;       // starting index in temp array
    int B[100];      // temporary array to hold merged result

    // Merge while both subarrays have elements
    while (i <= mid && j <= h)
    {
        if (A[i] <= A[j])  // Use <= for stable sort
        {
            B[k++] = A[i++];
        }
        else
        {
            B[k++] = A[j++];
        }
    }
    
    // Copy remaining elements from left subarray (if any)
    while (i <= mid)
    {
        B[k++] = A[i++];
    }

    // Copy remaining elements from right subarray (if any)
    while (j <= h)
    {
        B[k++] = A[j++];
    }

    // Copy merged result back to original array
    for (i = l; i <= h; i++)
    {
        A[i] = B[i];
    }
}

// Iterative Merge Sort (Bottom-Up approach)
void IMergeSort(int A[], int n)
{
    int p, l, h, mid, i;

    // Start with pairs (p=2), then groups of 4, 8, 16, etc.
    for (p = 2; p <= n; p = p * 2)
    {
        // Merge adjacent groups of size p/2
        for (i = 0; i + p - 1 < n; i += p)
        {
            l = i;
            h = i + p - 1;
            mid = (l + h) / 2;
            Merge(A, l, mid, h);
        }
    }
    
    // Merge any remaining elements (handles non-power-of-2 array sizes)
    if (p / 2 < n)
    {
        Merge(A, 0, (p / 2) - 1, n - 1);
    }
}

// Recursive Merge Sort (Top-Down approach)
void RMergeSort(int A[], int l, int h)
{
    if (l < h)
    {
        int mid = (l + h) / 2;        // Find middle point
        RMergeSort(A, l, mid);        // Sort left half
        RMergeSort(A, mid + 1, h);    // Sort right half
        Merge(A, l, mid, h);          // Merge sorted halves
    }
}

int main()
{
    int original[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};
    int n = sizeof(original) / sizeof(original[0]);
    int A[n];
    
    printArray(original, n, "Original array");
    printf("\n");

    // Test 1: Iterative Merge Sort (Bottom-Up)
    printf("=== ITERATIVE MERGE SORT (Bottom-Up) ===\n");
    copyArray(original, A, n);
    IMergeSort(A, n);
    printArray(A, n, "Sorted (Iterative)");
    printf("\n");

    // Test 2: Recursive Merge Sort (Top-Down)
    printf("=== RECURSIVE MERGE SORT (Top-Down) ===\n");
    copyArray(original, A, n);
    RMergeSort(A, 0, n - 1);
    printArray(A, n, "Sorted (Recursive)");
    printf("\n");

    return 0;
}

/*

    benraiss@Mbareks-MacBook-Air sort % clang -std=c17 -Wall -Wextra -o _msort Merge.c
    benraiss@Mbareks-MacBook-Air sort % ./_msort
    3 5 7 9 10 11 12 13 16 24
    benraiss@Mbareks-MacBook-Air sort %


        Initial: [11, 13, 7, 12, 16, 9, 24, 5, 10, 3]

        Pass p=2 (merge pairs):
        Merge(0-1):   [11, 13] → [11, 13]
        Merge(2-3):   [7, 12]  → [7, 12]
        Merge(4-5):   [16, 9]  → [9, 16]
        Merge(6-7):   [24, 5]  → [5, 24]
        Merge(8-9):   [10, 3]  → [3, 10]

        Result: [11, 13, 7, 12, 9, 16, 5, 24, 3, 10]

        Pass p=4 (merge groups of 4):
        Merge(0-3):   [11, 13] + [7, 12]   → [7, 11, 12, 13]
        Merge(4-7):   [9, 16] + [5, 24]    → [5, 9, 16, 24]
        Merge(8-9):   [3, 10] (only 2 left)

        Result: [7, 11, 12, 13, 5, 9, 16, 24, 3, 10]

        Pass p=8 (merge groups of 8):
        Merge(0-7):   [7, 11, 12, 13] + [5, 9, 16, 24] → [5, 7, 9, 11, 12, 13, 16, 24]

        Result: [5, 7, 9, 11, 12, 13, 16, 24, 3, 10]

        Final merge (remaining elements):
        Merge(0-9):   [5, 7, 9, 11, 12, 13, 16, 24] + [3, 10]

        Result: [3, 5, 7, 9, 10, 11, 12, 13, 16, 24] ✓


*/