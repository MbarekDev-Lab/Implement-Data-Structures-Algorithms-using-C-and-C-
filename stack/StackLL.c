#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// STACK USING LINKED LIST
// ============================================================================
struct Node
{
    int data;
    struct Node *next;
};

struct Node *top = NULL; // pointer to the top of the stack

// ============================================================================
// PUSH OPERATION - O(1)
// ============================================================================
void push(int x)
{
    struct Node *t;
    t = (struct Node *)malloc(sizeof(struct Node));

    // Stack grows only when memory exists
    if (t == NULL)
    {
        printf("Stack Overflow (Heap memory full)\n");
    }
    else
    {
        t->data = x;
        t->next = top;
        top = t;
        printf("Pushed: %d\n", x);
    }
}

// ============================================================================
// POP OPERATION - O(1)
// ============================================================================
int pop()
{
    struct Node *t;
    int x = -1; // default return value for empty stack

    if (top == NULL)
    {
        printf("Stack Underflow (empty)\n");
        return -1;
    }
    else
    {
        t = top;
        top = top->next;
        x = t->data;
        free(t);
        return x;
    }
}

// ============================================================================
// PEEK OPERATION - Get element at position (1-based)
// ============================================================================
int peek(int pos)
{
    struct Node *p = top;
    int i;

    for (i = 0; p != NULL && i < pos - 1; i++)
    {
        p = p->next;
    }

    if (p != NULL)
        return p->data;
    else
        return -1;
}

// ============================================================================
// STACK TOP - Get top element without removing
// ============================================================================
int stackTop()
{
    if (top != NULL)
        return top->data;
    return -1;
}

// ============================================================================
// IS EMPTY CHECK
// ============================================================================
int isEmpty()
{
    return top == NULL;
}

// ============================================================================
// DISPLAY STACK (Top to Bottom)
// ============================================================================
void Display()
{
    struct Node *p = top;

    if (p == NULL)
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack (Top → Bottom): ");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    printf("═══════════════════════════════════════════════════════\n");
    printf("       STACK IMPLEMENTATION USING LINKED LIST\n");
    printf("═══════════════════════════════════════════════════════\n\n");

    printf("═══ PUSH OPERATIONS ═══\n");
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);

    printf("\n═══ DISPLAY STACK ═══\n");
    Display();

    printf("\n═══ POP OPERATIONS ═══\n");
    printf("Popped: %d\n", pop());
    printf("Popped: %d\n", pop());

    printf("\n═══ DISPLAY AFTER POP ═══\n");
    Display();

    printf("\n═══ PEEK OPERATIONS ═══\n");
    printf("Element at position 1 (top): %d\n", peek(1));
    printf("Element at position 2: %d\n", peek(2));
    printf("Element at position 3: %d\n", peek(3));

    printf("\n═══ STACK STATUS ═══\n");
    printf("Stack Top: %d\n", stackTop());
    printf("Is Empty: %s\n", isEmpty() ? "Yes" : "No");

    printf("\n═══ POP ALL ELEMENTS ═══\n");
    while (!isEmpty())
    {
        printf("Popped: %d\n", pop());
    }

    printf("\n═══ FINAL STATUS ═══\n");
    Display();
    printf("Is Empty: %s\n", isEmpty() ? "Yes" : "No");

    printf("\n═══════════════════════════════════════════════════════\n");
    printf("Program completed successfully!\n");

    return 0;
}

/*

    benraiss@MacBookAir stack % clang -std=c17 -Wall -Wextra -o stack_ll StackLL.c
    benraiss@MacBookAir stack % ./stack_ll
    ═══════════════════════════════════════════════════════
        STACK IMPLEMENTATION USING LINKED LIST
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

    ═══ PEEK OPERATIONS ═══
    Element at position 1 (top): 30
    Element at position 2: 20
    Element at position 3: 10

    ═══ STACK STATUS ═══
    Stack Top: 30
    Is Empty: No

    ═══ POP ALL ELEMENTS ═══
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