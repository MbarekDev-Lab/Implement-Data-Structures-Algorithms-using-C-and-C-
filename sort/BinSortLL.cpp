#include <iostream>

using namespace std;

template <class T>
void Print(T &vec, int n, string s)
{
    cout << s << ": [" << flush;
    for (int i = 0; i < n; i++)
    {
        cout << vec[i] << flush;
        if (i < n - 1)
        {
            cout << ", " << flush;
        }
    }
    cout << "]" << endl;
}

int Max(int A[], int n)
{
    int max = -32768;
    for (int i = 0; i < n; i++)
    {
        if (A[i] > max)
        {
            max = A[i];
        }
    }
    return max;
}

// Linked List node
class Node
{
public:
    int value;
    Node *next;
};

void Insert(Node **ptrBins, int idx)
{
    Node *temp = new Node;
    temp->value = idx; // value to be stored in bin
    temp->next = nullptr;

    if (ptrBins[idx] == nullptr)
    {                        // ptrBins[idx] is head ptr
        ptrBins[idx] = temp; // first node in bin
    }
    else
    {
        Node *p = ptrBins[idx];
        while (p->next != nullptr)
        {
            p = p->next; // traverse to end of bin
        }
        p->next = temp; // insert at end of bin
    }
}

int Delete(Node **ptrBins, int idx)
{
    Node *p = ptrBins[idx];            // ptrBins[idx] is head ptr
    ptrBins[idx] = ptrBins[idx]->next; // update head ptr to next node (move head to next node)
    int x = p->value;
    delete p;
    return x;
}

void BinSort(int A[], int n)
{
    int max = Max(A, n);

    // Create bins array
    Node **bins = new Node *[max + 1];

    // Initialize bins array with nullptr
    for (int i = 0; i < max + 1; i++)
    {
        bins[i] = nullptr;
    }

    // Update count array values based on A values
    for (int i = 0; i < n; i++)
    {
        Insert(bins, A[i]);
    }

    // Update A with sorted elements
    int i = 0;
    int j = 0;
    while (i < max + 1)
    {
        while (bins[i] != nullptr)
        {
            A[j++] = Delete(bins, i);
        }
        i++;
    }

    // Delete heap memory
    delete[] bins;
}

int main()
{
    // Test BinSort with linked list (Bucket Sort )

    int A[] = {2, 5, 8, 12, 3, 6, 7, 10};
    int n = sizeof(A) / sizeof(A[0]);

    Print(A, n, "\t\tA");
    BinSort(A, n);
    Print(A, n, " Sorted A");
    cout << endl;
    return 0;
}

/*
benraiss@Mbareks-MacBook-Air data-structures-c-cpp %  cd /Users/benraiss/Documents/data-structures-c-cpp/sort && clang++ -std=c++17 -Wall -Wextra -o _b
insort BinSortLL.cpp && ./_binsort
                A: [2, 5, 8, 12, 3, 6, 7, 10]
 Sorted A: [2, 3, 5, 6, 7, 8, 10, 12]

benraiss@Mbareks-MacBook-Air sort %

max = Max(A, n);  // max = 12

Node** bins = new Node* [max + 1];  // 13 bins (0 to 12)

bins[0] → nullptr
bins[1] → nullptr
bins[2] → nullptr
...
bins[12] → nullptr


A[] = {2, 5, 8, 12, 3, 6, 7, 10}

After insertions:
bins[0] → nullptr
bins[1] → nullptr
bins[2] → [2] → nullptr
bins[3] → [3] → nullptr
bins[4] → nullptr
bins[5] → [5] → nullptr
bins[6] → [6] → nullptr
bins[7] → [7] → nullptr
bins[8] → [8] → nullptr
bins[9] → nullptr
bins[10] → [10] → nullptr
bins[11] → nullptr
bins[12] → [12] → nullptr


i=0: bins[0] empty, skip
i=1: bins[1] empty, skip
i=2: bins[2] has [2] → Delete(bins, 2) → A[0] = 2
i=3: bins[3] has [3] → Delete(bins, 3) → A[1] = 3
i=4: bins[4] empty, skip
i=5: bins[5] has [5] → Delete(bins, 5) → A[2] = 5
...

Result: [2, 3, 5, 6, 7, 8, 10, 12] ✓

A[] = {5, 2, 8, 2, 9, 1, 5, 5}

bins[1] → [1] → nullptr
bins[2] → [2] → [2] → nullptr           // 2 appears twice
bins[5] → [5] → [5] → [5] → nullptr     // 5 appears three times
bins[8] → [8] → nullptr
bins[9] → [9] → nullptr


*/