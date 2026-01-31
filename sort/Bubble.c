#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void Bubble(int A[], int n)
{
    int i, j, flag = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(&A[j], &A[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0) // no swaps means array is already sorted so we can exit early
            break;
        else
            flag = 0;
    }
}

int main()
{
    // int A[] = {3, 7, 9, 10, 6, 5, 12, 4, 11, 2}, n = 10, i;
    int A[] = {3, 7, 9, 10}, n = 4, i;
    Bubble(A, n);
    for (i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}

/*
init  int A[] = {3, 7, 9, 10}, n = 4, i;
sorted ->  3 7 9 10
benraiss@Mbareks-MacBook-Air sort %

benraiss@Mbareks-MacBook-Air sort % clang -std=c17 -Wall -Wextra -o _sort Bubble.c
benraiss@Mbareks-MacBook-Air sort % ./_sort
2 3 4 5 6 7 9 10 11 12
benraiss@Mbareks-MacBook-Air sort % ./_sort


Initial: [3, 7, 9, 10, 6, 5, 12, 4, 11, 2]

After Pass 1: [3, 7, 9, 6, 5, 10, 4, 11, 2, | 12]
                                              ↑ already in place

Pass 2 (i=1, inner loop j < n-1-1 = 8):
  j=0: 3 < 7   → no swap
  j=1: 7 < 9   → no swap
  j=2: 9 > 6   → SWAP! [3, 7, 6, 9, 5, 10, 4, 11, 2, | 12]
  j=3: 9 > 5   → SWAP! [3, 7, 6, 5, 9, 10, 4, 11, 2, | 12]
  j=4: 9 < 10  → no swap
  j=5: 10 > 4  → SWAP! [3, 7, 6, 5, 9, 4, 10, 11, 2, | 12]
  j=6: 10 < 11 → no swap
  j=7: 11 > 2  → SWAP! [3, 7, 6, 5, 9, 4, 10, 2, 11, | 12]
                                              ↑ 11 bubbled!

After Pass 2: [3, 7, 6, 5, 9, 4, 10, 2, | 11, 12]
                                         ↑  ↑
                                    2 largest in place

*/