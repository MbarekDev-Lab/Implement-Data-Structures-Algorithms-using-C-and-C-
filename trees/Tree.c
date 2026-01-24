#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

struct Node *root = NULL;

void Treecreate()
{
    struct Node *p, *t;
    int x;
    struct Queue q;
    create(&q, 100);

    printf("Enter root value ");
    scanf("%d", &x);
    root = (struct Node *)malloc(sizeof(struct Node));
    root->data = x;
    root->lChird = root->rChird = NULL;
    enqueue(&q, root);

    while (!isEmpty(q))
    {
        p = dequeue(&q);
        // left child
        printf("Enter left child of %d ", p->data);
        scanf("%d", &x);

        if (x != -1)
        {
            t = (struct Node *)malloc(sizeof(struct Node));
            t->data = x;
            t->lChird = t->rChird = NULL;
            p->lChird = t;
            enqueue(&q, t);
        }

        // right child
        printf("Enter right child of %d ", p->data);
        scanf("%d", &x);
        if (x != -1)
        {
            t = (struct Node *)malloc(sizeof(struct Node));
            t->data = x;
            t->lChird = t->rChird = NULL;
            p->rChird = t;
            enqueue(&q, t);
        }
    }
}

void Preorder(struct Node *p)
{
    if (p)
    {
        printf("%d ", p->data);
        Preorder(p->lChird);
        Preorder(p->rChird);
    }
}

void Inorder(struct Node *p)
{
    if (p)
    {
        Inorder(p->lChird);
        printf("%d ", p->data);
        Inorder(p->rChird);
    }
}

int main()
{

    Treecreate();
    printf("Preorder traversal: ");
    Preorder(root);
    printf("\nInorder traversal: ");
    Inorder(root);
    printf("\n\nTree created successfully.\n");

    return 0;
}

/*
    benraiss@MacBookAir trees % clang -std=c17 -Wall -Wextra -o _tree Tree.c
    benraiss@MacBookAir trees % ./_tree
    Enter root value 30
    Enter left child of 30 10
    Enter right child of 30 20
    Enter left child of 10 -1
    Enter right child of 10 -1
    Enter left child of 20 -1
    Enter right child of 20 -1
    Preorder traversal: 30 10 20
    Inorder traversal: 10 30 20

    Tree created successfully.
    benraiss@MacBookAir trees %

             30
            /  \
          10   20

*/