#include <stdio.h>
#include <stdlib.h>

void printArray(int A[], int n, const char *msg)
{
    printf("%s: ", msg);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void ShellSort(int A[], int n) // nlogn time complexity on average and worst case
{
    int gap, i, j, temp;

    for (gap = n / 2; gap >= 1; gap /= 2) // reduce gap by half each iteration
    {
        for (i = gap; i < n; i++) // perform gapped insertion sort
        {
            temp = A[i];
            j = i - gap;
            while (j >= 0 && A[j] > temp) // shift elements until correct position is found
            {
                A[j + gap] = A[j]; // shift element up by gap
                j = j - gap;       // move to next element in gap sequence
            }
            A[j + gap] = temp; // place temp in correct position
        }
    }
}

// n(nlogn) time complexity on average and worst case
// Shell Sort - Improved Insertion Sort with gaps
void ShellSort2(int A[], int n)
{
    int gap, i, j, temp;

    // Start with large gap, then reduce
    for (gap = n / 2; gap >= 1; gap = gap / 2)
    {
        printf("\n--- Gap = %d ---\n", gap);

        // Perform gapped insertion sort
        for (i = gap; i < n; i++)
        {
            temp = A[i];
            j = i - gap;

            // Shift elements until correct position is found
            while (j >= 0 && A[j] > temp)
            {
                A[j + gap] = A[j];
                j = j - gap;
            }
            A[j + gap] = temp;
        }

        printArray(A, n, "After gap");
    }
}

int main()
{
    int A[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3}, n = 10;

    printArray(A, n, "Original");
    ShellSort(A, n);
    printf("\n");
    printArray(A, n, "Final Sorted");

    return 0;
}
/*

benraiss@Mbareks-MacBook-Air sort %  cd /Users/benraiss/Documents/data-structures-c-cpp/sort && clang -std=c17 -Wall -Wextra -o _shell ShellSort.c && ./_shell
Original: 11 13 7 12 16 9 24 5 10 3

--- Gap = 5 ---
After gap: 9 13 5 10 3 11 24 7 12 16

--- Gap = 2 ---
After gap: 3 7 5 10 9 11 12 13 24 16

--- Gap = 1 ---
After gap: 3 5 7 9 10 11 12 13 16 24

ShellSort2 Debug Output:
Final Sorted: 3 5 7 9 10 11 12 13 16 24

ShellSort2 Debug Output:
Final Sorted: 3 5 7 9 10 11 12 13 16 24
benraiss@Mbareks-MacBook-Air sort %

*/

