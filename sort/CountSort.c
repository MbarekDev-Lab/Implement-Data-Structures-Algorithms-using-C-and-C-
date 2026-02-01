#include <stdio.h>
#include <stdlib.h>

int findMax(int A[], int n)
{
    int max = INT32_MIN;
    int i;
    for (i = 0; i < n; i++)
    {
        if (A[i] > max)
            max = A[i];
    }
    return max;
}

void CountSort(int A[], int n)
{
    int i, j, max, *C;

    max = findMax(A, n);

    C = (int *)malloc(sizeof(int) * (max + 1));

    for (i = 0; i <= max; i++)
        C[i] = 0;

    for (i = 0; i < n; i++)
        C[A[i]]++;

    i = 0;
    j = 0;

    while (j < max + 1)
    {
        if (C[j] > 0)
        {
            A[i++] = j;
            C[j]--;
        }
        else
        {
            j++;
        }
    }
    free(C);
}

int main(int argc, char const *argv[])
{
    int A[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3}, n = 10, i;

    CountSort(A, n);

    for (i = 0; i < 10; i++)
    {
        printf("%d ", A[i]);
    }

    printf("\n");
    return 0;
}
/*

benraiss@Mbareks-MacBook-Air sort % clang -std=c17 -Wall -Wextra -o _csort CountSort.c
benraiss@Mbareks-MacBook-Air sort % ./_csort
3 5 7 9 10 11 12 13 16 24
benraiss@Mbareks-MacBook-Air sort %

max = findMax(A, n);  // max = 24

C = [0, 0, 0, ..., 0]  // Size: max+1 = 25 elements

For each element in A[], increment C[element]

Original: [11, 13, 7, 12, 16, 9, 24, 5, 10, 3]

C[3] = 1   (3 appears once)
C[5] = 1   (5 appears once)
C[7] = 1   (7 appears once)
C[9] = 1   (9 appears once)
C[10] = 1  (10 appears once)
C[11] = 1  (11 appears once)
C[12] = 1  (12 appears once)
C[13] = 1  (13 appears once)
C[16] = 1  (16 appears once)
C[24] = 1  (24 appears once)


while (j < max + 1) {
    if (C[j] > 0) {
        A[i++] = j;    // Place j in array
        C[j]--;        // Decrement count
    } else {
        j++;           // Move to next number
    }
}

j=0: C[0]=0? Skip
j=1: C[1]=0? Skip
j=2: C[2]=0? Skip
j=3: C[3]=1? YES → A[0]=3, C[3]=0
j=4: C[4]=0? Skip
j=5: C[5]=1? YES → A[1]=5, C[5]=0

Result: [3, 5, 7, 9, 10, 11, 12, 13, 16, 24]


*/