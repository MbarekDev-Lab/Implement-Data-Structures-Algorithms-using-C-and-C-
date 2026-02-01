#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
// Merge two sorted subarrays A[l..mid] and A[mid+1..h]
void Merge(int A[], int l, int mid, int h)
{
    int i = l;       // starting index for left subarray
    int j = mid + 1; // starting index for right subarray
    int k = l;       // starting index to be sorted
    int B[100];      // temporary array to hold merged result

    while (i <= mid && j <= h)
    {
        if (A[i] < A[j])
        {
            B[k++] = A[i++];
        }
        else
        {
            B[k++] = A[j++];
        }
    }
    for (; i <= mid; i++)
    {
        B[k++] = A[i];
    }

    for (; j <= h; j++)
    {
        B[k++] = A[j];
    }

    // Copy merged result back to original array
    for (i = l; i <= h; i++)
    {
        A[i] = B[i];
    }
}

// Iterative Merge Sort
void IMergeSort(int A[], int n)
{
    int p, l, h, mid, i;

    for (p = 2; p <= n; p = p * 2)
    {
        for (i = 0; i + p - 1 < n; i += p)
        {
            l = i;
            h = i + p - 1;
            mid = (l + h) / 2;
            Merge(A, l, mid, h);
        }
    }
    if (p / 2 < n)
    {
        Merge(A, 0, (p / 2) - 1, n - 1);
    }
}

int main()
{
    int A[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3}, n = 10, i;

    IMergeSort(A, n);

    for (i = 0; i < 10; i++)
        printf("%d ", A[i]);

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