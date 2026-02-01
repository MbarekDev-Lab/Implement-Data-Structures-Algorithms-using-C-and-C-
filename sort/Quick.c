#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int A[], int l, int h)
{
    int pivot = A[l]; // pivot element is first element
    int i = l;        // start from left index
    int j = h;        // start from right index

    do
    {
        do
        {
            i++;
        } while (A[i] <= pivot); // move i to right until A[i] > pivot found find such element from left

        do
        {
            j--;
        } while (A[j] > pivot); // move j to left until A[j] ≤ pivot found from right

        if (i < j)
            swap(&A[i], &A[j]); // swap A[i] and A[j] if i < j
    } while (i < j);

    swap(&A[l], &A[j]); // put pivot in correct position
    return j;           // return pivot index
}

void QuickSort(int A[], int l, int h)
{
    int j;
    if (l < h)
    {
        j = partition(A, l, h); // partitioning index returned
        QuickSort(A, l, j);
        QuickSort(A, j + 1, h);
    }
}

int main(int argc, char const *argv[])
{
    int i;
    int A[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3, INT32_MAX}, n = 11;

    QuickSort(A, 0, n - 1);

    for (i = 0; i < 10; i++)
    {
        printf("%d ", A[i]);
    }

    printf("\n");

    return 0;
}

/*
Quick Sort is a divide-and-conquer algorithm - much faster than Bubble/Insertion/Selection!
Initial: [11, 13, 7, 12, 16, 9, 24, 5, 10, 3, INT32_MAX]
    benraiss@Mbareks-MacBook-Air sort % ./_qsort
    3 5 7 9 10 11 12 13 16 24
    benraiss@Mbareks-MacBook-Air sort %

        Initial: [11, 13, 7, 12, 16, 9, 24, 5, 10, 3, INT32_MAX]
        pivot = 11 (A[0])
        i = 0, j = 10

        Step 1:
        i++ until A[i] > 11 → i=1 (A[1]=13 > 11) ✓
        j-- until A[j] ≤ 11 → j=9 (A[9]=3 ≤ 11) ✓
        i < j? YES → swap(A[1], A[9]) → swap(13, 3)
        Result: [11, 3, 7, 12, 16, 9, 24, 5, 10, 13, INT32_MAX]

        Step 2:
        i++ until A[i] > 11 → i=3 (A[3]=12 > 11) ✓
        j-- until A[j] ≤ 11 → j=8 (A[8]=10 ≤ 11) ✓
        i < j? YES → swap(A[3], A[8]) → swap(12, 10)
        Result: [11, 3, 7, 10, 16, 9, 24, 5, 12, 13, INT32_MAX]

        Step 3:
        i++ until A[i] > 11 → i=4 (A[4]=16 > 11) ✓
        j-- until A[j] ≤ 11 → j=7 (A[7]=5 ≤ 11) ✓
        i < j? YES → swap(A[4], A[7]) → swap(16, 5)
        Result: [11, 3, 7, 10, 5, 9, 24, 16, 12, 13, INT32_MAX]

        Step 4:
        i++ until A[i] > 11 → i=6 (A[6]=24 > 11) ✓
        j-- until A[j] ≤ 11 → j=5 (A[5]=9 ≤ 11) ✓
        i < j? NO (i=6, j=5) → STOP

        Final: Swap pivot A[0] with A[j=5] → swap(11, 9)
        Result: [9, 3, 7, 10, 5, 11, 24, 16, 12, 13, INT32_MAX]
                                ↑
                            pivot in correct position!

        Return j=5

*/