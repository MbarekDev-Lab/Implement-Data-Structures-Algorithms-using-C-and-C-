#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *lchild;
    struct Node *rchild;
    int data;
    int height;
} *root = NULL;

int NodeHeight(struct Node *p)
{
    int hl, hr;
    hl = p && p->lchild ? p->lchild->height : 0; // if p exists and p has left child get its height else 0
    hr = p && p->rchild ? p->rchild->height : 0; // if p exists and p has right child get its height else 0
    return hl > hr ? hl + 1 : hr + 1;            // return max of left height and right height plus 1 for current node
}

int BalanceFactor(struct Node *p)
{
    int hl, hr;                                  // hl height left child hr height right child
    hl = p && p->lchild ? p->lchild->height : 0; // if p exists and p has left child get its height else 0
    hr = p && p->rchild ? p->rchild->height : 0; // if p exists and p has right child get its height else 0
    return hl - hr;                              // balance factor is left height - right height
}

struct Node *LLRotation(struct Node *p)
{
    struct Node *pl = p->lchild;   // pl means p left child
    struct Node *plr = pl->rchild; // plr means p left right child

    pl->rchild = p;  // rotate
    p->lchild = plr; // rotate

    p->height = NodeHeight(p);   // update heights
    pl->height = NodeHeight(pl); // update heights

    if (root == p) // update root if necessary
        root = pl; // if p was root now pl is root
    return pl;     // new root after rotation
}

struct Node *RRRotation(struct Node *p)
{
    struct Node *pr = p->rchild;   // pr means p right child
    struct Node *prl = pr->lchild; // prl means p right left child

    pr->lchild = p;  // rotate
    p->rchild = prl; // rotate

    p->height = NodeHeight(p);   // update heights
    pr->height = NodeHeight(pr); // update heights

    if (root == p) // update root if necessary
        root = pr; // if p was root now pr is root
    return pr;
}

struct Node *RLRotation(struct Node *p)
{
    struct Node *pr = p->rchild;   // pr means p right child
    struct Node *prl = pr->lchild; // prl means p right left child

    pr->lchild = prl->rchild;
    p->rchild = prl->lchild;

    prl->rchild = pr;
    prl->lchild = p;

    pr->height = NodeHeight(pr);
    p->height = NodeHeight(p);
    prl->height = NodeHeight(prl);

    if (root == p)
        root = prl;
    return prl;
}

struct Node *LRRotation(struct Node *p)
{
    struct Node *pl = p->lchild;
    struct Node *plr = pl->rchild;

    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;

    plr->lchild = pl;
    plr->rchild = p;

    pl->height = NodeHeight(pl);
    p->height = NodeHeight(p);
    plr->height = NodeHeight(plr);

    if (root == p)
        root = plr;
    return plr;
}
struct Node *RInsert(struct Node *p, int key)
{

    struct Node *t = NULL;
    if (p == NULL) // tree is empty first time crearionof node
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = key;
        t->height = 1; // new node is initially added at leaf
        t->lchild = t->rchild = NULL;
        return t;
    }

    if (key < p->data) // insert in left subtree
    {
        p->lchild = RInsert(p->lchild, key); // recursive call
    }
    else if (key > p->data) // insert in right subtree
    {
        p->rchild = RInsert(p->rchild, key); // recursive call
    }

    p->height = NodeHeight(p); // update height of current node

    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) // LL Rotation
        return LLRotation(p);
    else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1) // LR Rotation
        return LRRotation(p);
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1) // RR Rotation
        return RRRotation(p);
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1) // RL Rotation
        return RLRotation(p);

    return p;
}

int main(void)
{
    root = RInsert(root, 10);
    root = RInsert(root, 5);
    root = RInsert(root, 2);
    printf("AVL Tree created successfully.\n");
    return 0;
}

/*
    benraiss@MacBookAir avl % clang++ -std=c++17 -Wall -Wextra -o _treeavl AVL.c
    clang++: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated [-Wdeprecated]
    benraiss@MacBookAir avl % ./_treeavl
    AVL Tree created successfully.
*/