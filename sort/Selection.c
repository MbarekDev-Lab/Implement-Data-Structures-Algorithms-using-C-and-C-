#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void SelectionSort(int A[], int n)
{

    int i, j, k;

    for (i = 0; i < n - 1; i++)
    {
        for (j = k = i; j < n; j++)
        {
            if (A[j] < A[k])
                k = j;
        }
        swap(&A[i], &A[k]);
    }
}

int main(int argc, char const *argv[])
{
    int A[] = {11, 13, 7, 2, 6, 9, 4, 5, 10, 3}, n = 10, i;
    SelectionSort(A, n);

    for (i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");

    return 0;
}

/*
    benraiss@Mbareks-MacBook-Air sort % ./_sort
    2 3 4 5 6 7 9 10 11 13
    benraiss@Mbareks-MacBook-Air sort %

Pass i=1: Insert 13 into sorted portion [11]
        x = A[1] = 13
        j = 0
        Check: A[0]=11 > 13? NO
        Place 13 at position j+1=1 (stays in place)

        Result: [11, 13 | 7, 2, 6, 9, 4, 5, 10, 3]
         -------
          sorted

Pass i=2: Insert 7 into sorted portion [11, 13]
        x = A[2] = 7
        j = 1

        While loop:
        j=1: A[1]=13 > 7? YES → A[2]=13, j=0  [11, 13, 13, 2, 6, 9, 4, 5, 10, 3]
        j=0: A[0]=11 > 7? YES → A[1]=11, j=-1 [11, 11, 13, 2, 6, 9, 4, 5, 10, 3]
        j=-1: Stop (j > -1 is false)

        Place x=7 at position j+1=0

        Result: [7, 11, 13 | 2, 6, 9, 4, 5, 10, 3]
                -----------
         sorted

Pass i=3: Insert 2 into sorted portion [7, 11, 13]
    x = A[2] = 7
    j = 1
    x = A[3] = 2
    j = 2

While loop:
  j=2: A[2]=13 > 2? YES → A[3]=13, j=1  [7, 11, 13, 13, 6, 9, 4, 5, 10, 3]
  j=1: A[1]=11 > 2? YES → A[2]=11, j=0  [7, 11, 11, 13, 6, 9, 4, 5, 10, 3]
  j=0: A[0]=7 > 2? YES  → A[1]=7,  j=-1 [7, 7, 11, 13, 6, 9, 4, 5, 10, 3]
  j=-1: Stop

Place x=2 at position j+1=0

Result: [2, 7, 11, 13 | 6, 9, 4, 5, 10, 3]
         --------------
            sorted

**while loop shifts elements to the right** to make space for `x=2`:
- `13` shifts right to position 3
- `11` shifts right to position 2
- `7` shifts right to position 1
- Then `x=2` is placed at position `j+1=0`

**This is the core mechanism of Insertion Sort!**

## **Summary:**

| Algorithm | **Best Case** | **Worst Case** | **Key Idea** |
|-----------|---------------|----------------|--------------|
| **Bubble** | O(n) if optimized | O(n²) | Bubble largest to end, multiple passes |
| **Insertion** | O(n) already sorted | O(n²) | Insert each into sorted portion |
| **Selection** | O(n²) always | O(n²) | Select minimum, place at beginning |
*/