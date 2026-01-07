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

struct Sparse *add(struct Sparse *s1, struct Sparse *s2)
{
    struct Sparse *sum;
    int i, j, k;
    i = j = k = 0;

    sum = (struct Sparse *)malloc(sizeof(struct Sparse));
    sum->ele = (struct Element *)malloc((s1->num + s2->num) * sizeof(struct Element));

    while (i < s1->num && j < s2->num)
    {
        if (s1->ele[i].i < s2->ele[j].i)
            sum->ele[k++] = s1->ele[i++];
        else if (s1->ele[i].i > s2->ele[j].i)
            sum->ele[k++] = s2->ele[j++];
        else
        {
            if (s1->ele[i].j < s2->ele[j].j)
                sum->ele[k++] = s1->ele[i++];
            else if (s1->ele[i].j > s2->ele[j].j)
                sum->ele[k++] = s2->ele[j++];
            else
            {
                sum->ele[k] = s1->ele[i];
                sum->ele[k++].x = s1->ele[i++].x + s2->ele[j++].x;
            }
        }
    }

    for (; i < s1->num; i++)
        sum->ele[k++] = s1->ele[i];
    for (; j < s2->num; j++)
        sum->ele[k++] = s2->ele[j];

    sum->m = s1->m;
    sum->n = s1->n;
    sum->num = k;

    return sum;
}

int main(void)
{
    /* code */

    struct Sparse s1, s2, *s;

    CreateSparse(&s1);
    CreateSparse(&s2);

    s = add(&s1, &s2);
    printf("\n");
    printf "First Matrix:\n";
    DisplaySparse(s1);
    printf("\n");
    printf("Second Matrix:\n");
    DisplaySparse(s2);
    printf("\n");
    printf("Sum Matrix:\n");
    DisplaySparse(*s);

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
