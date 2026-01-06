#include <stdio.h>
#include <stdlib.h>

struct Element
{
    /* data */
    int i;
    int j;
    int x;
};

struct Sparse
{
    /* data */

    int m;
    int n;
    int num;
    struct Element *ele;
};

void CreateSparse(struct Sparse *s)
{
    int i;

    printf("Enter Dimensions: ");
    scanf("%d%d", &s->m, &s->n);
    printf("Enter Number of Non-Zero Elements: ");
    scanf("%d", &s->num);

    s->ele = (struct Element *)malloc(s->num * sizeof(struct Element));

    printf("Enter all non-zero elements (row column value): \n");
    for (i = 0; i < s->num; i++)
    {
        scanf("%d%d%d", &s->ele[i].i, &s->ele[i].j, &s->ele[i].x);
    }
}

void DisplaySparse(struct Sparse s)
{
    int i, j, k = 0;

    printf("The Sparse Matrix is: \n");

    // to print the matrix
    for (i = 0; i < s.m; i++)
    {
        for (j = 0; j < s.n; j++)
        {
            if (k < s.num && i == s.ele[k].i && j == s.ele[k].j)
            {
                printf("%d ", s.ele[k++].x); // print non-zero element and move to next
            }
            else
            {
                printf("0 "); // print zero for non-stored elements
            }
        }
        printf("\n");
    }
}

int main(void)
{
    /* code */

    struct Sparse s;

    CreateSparse(&s);
    DisplaySparse(s);

    return 0;
}
/**
 * 
 * benraiss@MacBookAir Matrices % ./sparse_abdo
Enter Dimensions: 5 5
Enter Number of Non-Zero Elements: 5
Enter all non-zero elements (row column value): 
0 0 1
1 0 1
2 0 1
3 0 1
4 0 1
The Sparse Matrix is: 
1 0 0 0 0 
1 0 0 0 0 
1 0 0 0 0 
1 0 0 0 0 
1 0 0 0 0 
benraiss@MacBookAir Matrices % 
 * 
 * 
 * 
 */
