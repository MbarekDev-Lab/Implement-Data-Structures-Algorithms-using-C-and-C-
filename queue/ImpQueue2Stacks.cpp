#include <iostream>
#include <stack>

using namespace std;

class Queue
{
private:
    stack<int> e_stk; // Enqueue stack
    stack<int> d_stk; // Dequeue stack
public:
    Queue() {};
    ~Queue() {};
    void enqueue(int x);
    int dequeue();
};

void Queue::enqueue(int x)
{
    e_stk.push(x);
}

int Queue::dequeue()
{
    int x = -1;
    if (d_stk.empty())
    {
        if (e_stk.empty())
        {
            cout << "Queue Underflow" << endl;
            return x;
        }
        else
        {
            while (!e_stk.empty())
            {
                d_stk.push(e_stk.top());
                e_stk.pop();
            }
        }
    }
    x = d_stk.top();
    d_stk.pop();
    return x;
}

int main()
{

    int A[] = {1, 3, 5, 7, 9};

    Queue q;

    cout << "Enqueue: " << flush;
    for (int i = 0; i < sizeof(A) / sizeof(A[0]); i++)
    {
        q.enqueue(A[i]);
        cout << A[i] << flush;
        if (i < sizeof(A) / sizeof(A[0]) - 1)
        {
            cout << " <- " << flush;
        }
    }
    cout << endl;

    cout << "Dequeue: " << flush;
    for (int i = 0; i < sizeof(A) / sizeof(A[0]); i++)
    {
        cout << q.dequeue() << flush;
        if (i < sizeof(A) / sizeof(A[0]) - 1)
        {
            cout << " <- " << flush;
        }
    }
    cout << endl;

    return 0;
}

/*
═══════════════════════════════════════════════════════════════════════
    QUEUE IMPLEMENTATION USING TWO STACKS ABDUL BARI'S METHOD
═══════════════════════════════════════════════════════════════════════

CONCEPT:
--------
Stack = LIFO (Last In, First Out)
Queue = FIFO (First In, First Out)

How can we create FIFO behavior using TWO LIFO structures?
Answer: to Use one stack for enqueue, another for dequeue!

THE ALGORITHM (Abdul Bari's Method):
-------------------------------------

Two Stacks:
1. e_stk (Enqueue Stack) - for inserting elements
2. d_stk (Dequeue Stack) - for removing elements

ENQUEUE Operation: O(1)
-----------------------
Simply push to e_stk
    e_stk.push(x);

Example:
    enqueue(1) → e_stk: [1]
    enqueue(3) → e_stk: [1, 3]
    enqueue(5) → e_stk: [1, 3, 5]

DEQUEUE Operation: O(1) amortized
----------------------------------
If d_stk is empty:
    Transfer ALL elements from e_stk to d_stk
    (This reverses the order, making FIFO!)

Then pop from d_stk

Example Walkthrough:
--------------------

Step 1: Enqueue 1, 3, 5
    e_stk: [1, 3, 5] ← top
    d_stk: []

Step 2: First dequeue
    d_stk is empty, so transfer:

    Transfer process (reverses order):
        Pop 5 from e_stk → Push to d_stk
        Pop 3 from e_stk → Push to d_stk
        Pop 1 from e_stk → Push to d_stk

    After transfer:
        e_stk: []
        d_stk: [5, 3, 1] ← top

    Pop from d_stk → return 1 (FIFO!)

Step 3: Second dequeue
    d_stk not empty, just pop:
        d_stk: [5, 3] ← top
        return 3 (FIFO!)

Step 4: Third dequeue
    d_stk not empty, just pop:
        d_stk: [5] ← top
        return 5

Visual Representation:
---------------------

Enqueue(1), Enqueue(3), Enqueue(5):

e_stk:  d_stk:
┌────┐  ┌────┐
│ 5  │  │    │ ← top
├────┤  └────┘
│ 3  │
├────┤
│ 1  │
└────┘

First Dequeue (transfer happens):

e_stk:  d_stk:
┌────┐  ┌────┐
│    │  │ 1  │ ← top (this is what we want!)
└────┘  ├────┤
        │ 3  │
        ├────┤
        │ 5  │
        └────┘

Return 1 (FIFO achieved!)

WHY THIS WORKS:
---------------
1. Stack reverses order: [1,3,5] → transfer → [5,3,1]
2. Second reversal gets back to original: [5,3,1] → pop order → 1,3,5
3. Two reversals = FIFO!

TIME COMPLEXITY:
---------------
Enqueue: O(1) - always just one push
Dequeue:
    - Worst case: O(n) - when we need to transfer all n elements
    - Amortized: O(1) - each element transferred exactly once

SPACE COMPLEXITY: O(n)
----------------------
Two stacks can together hold n elements

OUTPUT:
-------
Enqueue: 1 <- 3 <- 5 <- 7 <- 9
Dequeue: 1 <- 3 <- 5 <- 7 <- 9

Notice: Same order! FIFO behavior achieved!

═══════════════════════════════════════════════════════════════════════
*/
