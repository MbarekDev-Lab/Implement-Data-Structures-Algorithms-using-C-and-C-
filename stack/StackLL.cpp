#include <iostream>
// ============================================================================
// NODE CLASS
// ============================================================================
class Node
{
public:
    int data;
    Node *next;
};

// ============================================================================
// STACK CLASS USING LINKED LIST
// ============================================================================
class StackLL
{
private:
    Node *top; // pointer to the top of the stack

public:
    StackLL()
    {
        top = NULL;
    }

    ~StackLL()
    {
        while (top != NULL)
        {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(int x);
    int pop();
    void Display();
    int stackTop();
    bool isEmpty();
};

// ============================================================================
// PUSH OPERATION  O(1)
// ============================================================================
void StackLL::push(int x)
{
    Node *t = new Node;

    // Stack grows only when memory exists
    if (t == NULL)
    {
        std::cout << "Stack Overflow (Heap memory full)\n";
    }
    else
    {
        t->data = x;
        t->next = top;
        top = t;
        std::cout << "Pushed: " << x << "\n";
    }
}

// ============================================================================
// POP OPERATION  O(1)
// ============================================================================
int StackLL::pop()
{
    int x = -1; // default return value for empty stack

    if (top == NULL)
    {
        std::cout << "Stack Underflow (empty stack)\n";
        return -1;
    }
    else
    {
        x = top->data;
        Node *t = top;
        top = top->next;
        std::cout << "Popped: " << x << "\n";
        delete t;
        return x;
    }
}

// ============================================================================
// DISPLAY STACK (Top to Bottom)
// ============================================================================
void StackLL::Display()
{
    Node *p = top;

    if (p == NULL)
    {
        std::cout << "Stack is empty\n";
        return;
    }

    std::cout << "Stack (Top → Bottom): ";
    while (p != NULL)
    {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

// ============================================================================
// STACK TOP Get top element without removing
// ============================================================================
int StackLL::stackTop()
{
    if (top != NULL)
        return top->data;
    return -1;
}

// ============================================================================
// IS EMPTY CHECK
// ============================================================================
bool StackLL::isEmpty()
{
    return top == NULL;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    StackLL stack;

    std::cout << "═══════════════════════════════════════════════════════\n";
    std::cout << "       STACK IMPLEMENTATION USING LINKED LIST (C++)\n";
    std::cout << "═══════════════════════════════════════════════════════\n\n";

    std::cout << "═══ PUSH OPERATIONS ═══\n";
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);

    std::cout << "\n═══ DISPLAY STACK ═══\n";
    stack.Display();

    std::cout << "\n═══ POP OPERATIONS ═══\n";
    stack.pop();
    stack.pop();

    std::cout << "\n═══ DISPLAY AFTER POP ═══\n";
    stack.Display();

    std::cout << "\n═══ STACK STATUS ═══\n";
    std::cout << "Stack Top: " << stack.stackTop() << "\n";
    std::cout << "Is Empty: " << (stack.isEmpty() ? "Yes" : "No") << "\n";

    std::cout << "\n═══ POP ALL REMAINING ═══\n";
    while (!stack.isEmpty())
    {
        stack.pop();
    }

    std::cout << "\n═══ FINAL STATUS ═══\n";
    stack.Display();
    std::cout << "Is Empty: " << (stack.isEmpty() ? "Yes" : "No") << "\n";

    std::cout << "\n═══════════════════════════════════════════════════════\n";
    std::cout << "Program completed successfully!\n";

    return 0;
}

/*
    benraiss@MacBookAir stack % ./stack_ll_cpp
    ═══════════════════════════════════════════════════════
        STACK IMPLEMENTATION USING LINKED LIST (C++)
    ═══════════════════════════════════════════════════════

    ═══ PUSH OPERATIONS ═══
    Pushed: 10
    Pushed: 20
    Pushed: 30
    Pushed: 40
    Pushed: 50

    ═══ DISPLAY STACK ═══
    Stack (Top → Bottom): 50 40 30 20 10

    ═══ POP OPERATIONS ═══
    Popped: 50
    Popped: 40

    ═══ DISPLAY AFTER POP ═══
    Stack (Top → Bottom): 30 20 10

    ═══ STACK STATUS ═══
    Stack Top: 30
    Is Empty: No

    ═══ POP ALL REMAINING ═══
    Popped: 30
    Popped: 20
    Popped: 10

    ═══ FINAL STATUS ═══
    Stack is empty
    Is Empty: Yes

    ═══════════════════════════════════════════════════════
    Program completed successfully!
    benraiss@MacBookAir stack %
*/