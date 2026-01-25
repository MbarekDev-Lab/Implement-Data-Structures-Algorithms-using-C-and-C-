#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *lchild;
    struct Node *rchild;
    int data;
} *root = NULL;

void Insert(int key) // insert key in BST
{
    struct Node *t = root;
    struct Node *r = NULL, *p;

    if (root == NULL) // tree is empty
    {
        p = (struct Node *)malloc(sizeof(struct Node));
        p->data = key;
        p->lchild = p->rchild = NULL;
        root = p;
        return;
    }

    while (t != NULL) // search for the key
    {
        r = t;
        if (key < t->data)
            t = t->lchild;
        else if (key > t->data)
            t = t->rchild;
        else
            return; // key already exists
    }

    p = (struct Node *)malloc(sizeof(struct Node));
    p->data = key;
    p->lchild = p->rchild = NULL;

    if (key < r->data)
        r->lchild = p;
    else
        r->rchild = p;
}

void Inorder(struct Node *p)
{
    if (p)
    {
        Inorder(p->lchild);
        printf("%d ", p->data);
        Inorder(p->rchild);
    }
}

struct Node *Search(int key)
{
    struct Node *t = root;

    while (t != NULL)
    {
        if (key == t->data)
        {
            return t;
        }
        else if (key < t->data)
        {
            t = t->lchild;
        }
        else
        {
            t = t->rchild;
        }
    }
    return NULL;
}

int Height(struct Node *p)
{
    int x, y;
    if (p == NULL)
        return 0;
    x = Height(p->lchild);
    y = Height(p->rchild);
    return x > y ? x + 1 : y + 1;
}

struct Node *InorderPredecessor(struct Node *p)
{
    while (p && p->rchild != NULL)
        p = p->rchild;
    return p;
}

struct Node *InorderSuccessor(struct Node *p)
{
    while (p && p->lchild != NULL)
        p = p->lchild;
    return p;
}

struct Node *Delete(struct Node *p, int key)
{
    struct Node *q;

    if (p == NULL)
        return NULL;

    if (p->lchild == NULL && p->rchild == NULL)
    {
        if (p == root)
            root = NULL;
        free(p);
        return NULL;
    }

    if (key < p->data)
        p->lchild = Delete(p->lchild, key);
    else if (key > p->data)
        p->rchild = Delete(p->rchild, key);
    else
    {
        if (Height(p->lchild) > Height(p->rchild))
        {
            q = InorderPredecessor(p->lchild);
            p->data = q->data;
            p->lchild = Delete(p->lchild, q->data);
        }
        else
        {
            q = InorderSuccessor(p->rchild);
            p->data = q->data;
            p->rchild = Delete(p->rchild, q->data);
        }
    }
    return p;
}

int main()
{
    struct Node *temp;

    // Insert nodes
    Insert(50);
    Insert(30);
    Insert(70);
    Insert(20);
    Insert(40);
    Insert(60);
    Insert(80);

    printf("Binary Search Tree Operations\n");
    printf("==============================\n\n");

    printf("Initial BST (Inorder): ");
    Inorder(root);
    printf("\n\n");

    printf("Height of BST: %d\n\n", Height(root));

    // Search operations
    printf("Search Results:\n");
    temp = Search(40);
    if (temp != NULL)
        printf("  Key 40 found!\n");
    else
        printf("  Key 40 not found.\n");

    temp = Search(100);
    if (temp != NULL)
        printf("  Key 100 found!\n");
    else
        printf("  Key 100 not found.\n");
    printf("\n");

    // Delete operations
    printf("Deleting 20...\n");
    Delete(root, 20);
    printf("After deletion (Inorder): ");
    Inorder(root);
    printf("\n\n");

    printf("Deleting 30...\n");
    Delete(root, 30);
    printf("After deletion (Inorder): ");
    Inorder(root);
    printf("\n\n");

    printf("Deleting 50 (root)...\n");
    Delete(root, 50);
    printf("After deletion (Inorder): ");
    Inorder(root);
    printf("\n\n");

    printf("Height after deletions: %d\n\n", Height(root));

    printf("BST operations completed successfully.\n");

    return 0;
}

/*

benraiss@MacBookAir bst % clang++ -std=c++17 -Wall -Wextra -o _treenbst BST.c
clang++: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated [-Wdeprecated]
benraiss@MacBookAir bst % ./_treenbst
Binary Search Tree Operations
==============================

Initial BST (Inorder): 20 30 40 50 60 70 80

Height of BST: 3

Search Results:
  Key 40 found!
  Key 100 not found.

Deleting 20...
After deletion (Inorder): 30 40 50 60 70 80

Deleting 30...
After deletion (Inorder): 40 50 60 70 80

Deleting 50 (root)...
After deletion (Inorder): 40 60 70 80

Height after deletions: 3

BST operations completed successfully.
benraiss@MacBookAir bst %

                50
            /    \
            30      70
            /  \    /  \
        20   40  60   80
*/