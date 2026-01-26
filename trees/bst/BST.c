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

struct Node *RInsert(struct Node *p, int key)
{
    struct Node *t = NULL;

    if (p == NULL)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = key;
        t->lchild = t->rchild = NULL;
        return t;
    }

    if (key < p->data)
    {
        p->lchild = RInsert(p->lchild, key);
    }
    else if (key > p->data)
    {
        p->rchild = RInsert(p->rchild, key);
    }
    return p;
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

// Helper function to find height of tree recursively
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
        // key found
        if (Height(p->lchild) > Height(p->rchild)) // left subtree is taller
        {
            q = InorderPredecessor(p->lchild);
            p->data = q->data;
            p->lchild = Delete(p->lchild, q->data);
        }
        else // right subtree is taller
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

    // recursive  Insert nodes
    root = RInsert(root, 10);
    RInsert(root, 5);
    RInsert(root, 20);
    RInsert(root, 20);
    RInsert(root, 8);
    RInsert(root, 30);

    // Delete nodes
    printf("Deleting root 10...\n");
    Delete(root, 10); // delete root

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

benraiss@Mbareks-MacBook-Air bst % clang++ -std=c++17 -Wall -Wextra -o _treenbst BST.c
clang++: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated [-Wdeprecated]
benraiss@Mbareks-MacBook-Air bst % ./_treenbst
Deleting root 10...
Binary Search Tree Operations
==============================

Initial BST (Inorder): 5 8 20 30

Height of BST: 3

Search Results:
  Key 40 not found.
  Key 100 not found.

Deleting 20...
After deletion (Inorder): 5 8 30

Deleting 30...
After deletion (Inorder): 5 8

Deleting 50 (root)...
After deletion (Inorder): 5 8

Height after deletions: 2

BST operations completed successfully.
benraiss@Mbareks-MacBook-Air bst %

                10
                /  \
            5     20
            \      \
                8     30
*/