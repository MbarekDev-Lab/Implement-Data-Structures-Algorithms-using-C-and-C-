#include <iostream>

using namespace std;

// Node class representing each element in the linked list
class Node
{
public:
    int data;
    Node *next;
};

class LinkedList
{
private:
    Node *first;

public:
    LinkedList()
    {
        first = NULL;
    } // constructor to initialize first to nullptr
    // LinkedList() : first(nullptr) {}
    LinkedList(int A[], int n); // Constructor to create linked list from array
    ~LinkedList();              // Destructor to free memory

    // Core operations Methods
    void Display() const;          // Display linked list with const
    void Insert(int index, int x); // Insert node at given index
    int Delete(int index);         // Delete node at given index
    int Length() const;            // Get length of linked list
    bool isLoop(Node *f);          // Detect loop in linked list
};

// Constructor to create linked list from array
LinkedList::LinkedList(int A[], int n)
{
    Node *last, *t;
    int i = 0;

    if (n <= 0)
    {
        first = NULL;
        return;
    }

    first = new Node;
    first->data = A[0];
    first->next = NULL;
    last = first;

    for (i = 1; i < n; i++)
    {
        t = new Node;
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

// Destructor to free memory
LinkedList::~LinkedList()
{
    Node *p = first;
    while (first)
    {
        first = first->next;
        delete p;
        p = first;
    }
}

void LinkedList::Display() const
{
    Node *p = first;

    while (p)
    {
        cout << p->data << " -> ";
        p = p->next;
    }
    cout << "NULL\n"
         << endl;
}

int LinkedList::Length() const
{
    Node *p = first;
    int len = 0;

    while (p)
    {
        len++;
        p = p->next;
    }
    return len;
}

void LinkedList::Insert(int index, int x)
{
    Node *t, *p = first;
    int i;

    if (index < 0 || index > Length())
        return;

    t = new Node;
    t->data = x;
    t->next = NULL;

    if (index == 0)
    {
        t->next = first; // Point new node's next to current first node
        first = t;       // Insert at beginning
    }
    else
    {
        for (i = 0; i < index - 1 && p; i++) // Traverse to (index-1)th node
            p = p->next;                     // Move to next node

        if (p)
        {
            t->next = p->next; // Link new node to next node
            p->next = t;       // Link (index-1)th node to new node
        }
    }
}

int LinkedList::Delete(int index)
{
    Node *p, *q = NULL;
    int x = -1, i;

    if (index < 1 || index > Length()) // check for valid index
        return -1;

    if (index == 1)
    {
        p = first;
        first = first->next;
        x = p->data;
        delete p;
        return x;
    }
    else
    {
        p = first;
        for (i = 0; i < index - 1 && p; i++)
        {
            q = p;
            p = p->next;
        }
        if (p)
        {
            q->next = p->next;
            x = p->data;
            delete p;
        }

        return x;
    }
}

int main()
{
    int A[] = {3, 5, 7, 10, 25, 8, 320};
    int n = sizeof(A) / sizeof(A[0]);

    LinkedList l(A, n);
    l.Display();
    cout << "Length: " << l.Length() << endl;

    l.Insert(2, 100);
    l.Display();
    cout << "Length: " << l.Length() << endl;

    l.Delete(4);
    l.Display();
    cout << "Length: " << l.Length() << endl;
    return 0;
}
/*

    benraiss@Mbareks-MacBook-Air linkedlist % ./ll_cpp
    3 -> 5 -> 7 -> 10 -> 25 -> 8 -> 320 -> NULL

    Length: 7
    3 -> 5 -> 100 -> 7 -> 10 -> 25 -> 8 -> 320 -> NULL

    Length: 8
    3 -> 5 -> 100 -> 10 -> 25 -> 8 -> 320 -> NULL

    Length: 7
    benraiss@Mbareks-MacBook-Air linkedlist %

*/