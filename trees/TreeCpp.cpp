#include <iostream>
#include "Queue.hpp"
using namespace std;

class Tree
{
    // automatically private in C++ private by default
    Node *root;

public:
    Tree() { root = nullptr; }
    void Treecreate();

    void Preorder()
    {
        Preorder(root); // start from root calls private function
    };
    void Preorder(Node *p); // Declaration (only) of private function implemented later

    void Inorder()
    {
        Inorder(root);
    };
    void Inorder(Node *p);

    void Postorder()
    {
        Postorder(root);
    };
    void Postorder(Node *p);

    void Levelorder()
    {
        Levelorder(root);
        cout << endl;
    };
    void Levelorder(Node *p);

    int Height()
    {
        return Height(root);
    };
    int Height(Node *p);

    ~Tree();
};

void Tree::Treecreate()
{
    Queue q;
    int x;
    Node *p;
    Node *t;
    cout << "Enter root value: ";
    cin >> x;
    root = new Node();
    root->data = x;
    root->lChird = root->rChird = nullptr;
    enqueue(&q, root);

    while (!isEmpty(q))
    {
        p = dequeue(&q);

        cout << "Enter left child of " << p->data << ": ";
        cin >> x;
        if (x != -1)
        {
            t = new Node();
            t->data = x;
            t->lChird = t->rChird = nullptr;
            p->lChird = t;
            enqueue(&q, t);
        }
        cout << "Enter right child of " << p->data << ": ";
        cin >> x;
        if (x != -1)
        {
            t = new Node();
            t->data = x;
            t->lChird = t->rChird = nullptr;
            p->rChird = t;
            enqueue(&q, t);
        }
    }
}

void Tree::Preorder(Node *p) // private function implementation
{
    if (p)
    {
        cout << p->data << " ";
        Preorder(p->lChird); // recursivly traverse left child
        Preorder(p->rChird);
    }
}
void Tree::Inorder(Node *p)
{
    if (p)
    {
        Inorder(p->lChird);
        cout << p->data << " ";
        Inorder(p->rChird);
    }
}
void Tree::Postorder(Node *p)
{
    if (p)
    {
        Postorder(p->lChird);
        Postorder(p->rChird);
        cout << p->data << " ";
    }
}
void Tree::Levelorder(Node *p)
{
    Queue q;
    cout << p->data << " ";
    enqueue(&q, p);

    while (!isEmpty(q))
    {
        p = dequeue(&q);
        if (p->lChird)
        {
            cout << p->lChird->data << " ";
            enqueue(&q, p->lChird);
        }
        if (p->rChird)
        {
            cout << p->rChird->data << " ";
            enqueue(&q, p->rChird);
        }
    }
}
int Tree::Height(Node *p)
{
    int x = 0, y = 0;
    if (p == nullptr)
        return 0;
    x = Height(p->lChird);
    y = Height(p->rChird);
    if (x > y)
        return x + 1;
    else
        return y + 1;
}
Tree::~Tree()
{
    // Destructor to free memory (not implemented here)
}

int main()
{
    Tree t;
    t.Treecreate();

    cout << "\nPreorder traversal: ";
    t.Preorder();

    cout << "\nInorder traversal: ";
    t.Inorder();

    cout << "\nPostorder traversal: ";
    t.Postorder();

    cout << "\nLevel-order traversal: ";
    t.Levelorder();

    cout << "\nHeight of tree: " << t.Height() << endl;

    return 0;
}

/*

    benraiss@MacBookAir trees % clang++ -std=c++17 -Wall -Wextra -o _treecpp TreeCpp.cpp
    benraiss@MacBookAir trees % ./_treecpp                                              
    Enter root value: 10
    Enter left child of 10: 20
    Enter right child of 10: 30
    Enter left child of 20: -1
    Enter right child of 20: -1
    Enter left child of 30: -1
    Enter right child of 30: -1

    Preorder traversal: 10 30 30 
    Inorder traversal: 30 10 30 
    Postorder traversal: 30 30 10 
    Level-order traversal: 10 30 30 

    Height of tree: 2
    benraiss@MacBookAir trees % 

*/