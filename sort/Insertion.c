#include <stdio.h>
#include <stdlib.h>

void Insertion(int A[], int n)
{

    int i, j, x;

    for (i = 1; i < n; i++)
    {
        j = i - 1;
        x = A[i];
        while (j > -1 && A[j] > x)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }
}

int main(int argc, char const *argv[])
{
    int A[] = {11, 13, 7, 2, 6, 9, 4, 5, 10, 3}, n = 10, i;
    Insertion(A, n);

    for (i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");

    return 0;
}

/*
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

    While loop:
    j=1: A[1]=13 > 7? YES → A[2]=13, j=0  [11, 13, 13, 2, 6, 9, 4, 5, 10, 3]
    j=0: A[0]=11 > 7? YES → A[1]=11, j=-1 [11, 11, 13, 2, 6, 9, 4, 5, 10, 3]
    j=-1: Stop (j > -1 is false)

    Place x=7 at position j+1=0

    Result: [7, 11, 13 | 2, 6, 9, 4, 5, 10, 3]
         -----------
    sorted
*/