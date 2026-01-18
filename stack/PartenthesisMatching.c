#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// STACK USING LINKED LIST
// ============================================================================
struct Node
{
    char data;
    struct Node *next;
};

struct Node *top = NULL; // pointer to the top of the stack

// ============================================================================
// PUSH OPERATION - O(1)
// ============================================================================
void push(char x)
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
        printf("Pushed: %c\n", x);
    }
}

// ============================================================================
// POP OPERATION - O(1)
// ============================================================================
char pop()
{
    struct Node *t;
    char x = -1; // default return value for empty stack

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

int isBalanced(char *exp)
{

    int i;

    for (i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '(')
            push(exp[i]);
        else if (exp[i] == ')')
        {
            if (top == NULL)
                return 0;
            pop();
        }
    }

    if (top == NULL)
    {
        /* code */
        return 1;
    }
    else
    {
        return 0;
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    printf("═══════════════════════════════════════════════════════\n");
    printf("       STACK IMPLEMENTATION USING LINKED LIST\n");
    printf("═══════════════════════════════════════════════════════\n\n");

    char *exp = "{[(a+b)*(c+d)] - (e+f))}"; // Example expression
    printf("Expression: %s\n", exp);

    if (isBalanced(exp))
        printf("Balanced\n");
    else
        printf("Not Balanced\n");

    printf("\n═══ FINAL STATUS ═══\n");
    Display();
    printf("Is Empty: %s\n", isEmpty() ? "Yes" : "No");

    printf("\n═══════════════════════════════════════════════════════\n");
    printf("Program completed successfully!\n");

    return 0;
}

/*
benraiss@Mbareks-MacBook-Air stack %  clang -std=c17 -Wall -Wextra -o _c PartenthesisMatching.c
benraiss@Mbareks-MacBook-Air stack % ./_c
═══════════════════════════════════════════════════════
       STACK IMPLEMENTATION USING LINKED LIST
═══════════════════════════════════════════════════════

Expression: {[(a+b)*(c+d)] - (e+f))}
Pushed: (
Pushed: (
Pushed: (
Not Balanced

═══ FINAL STATUS ═══
Stack is empty
Is Empty: Yes

═══════════════════════════════════════════════════════
Program completed successfully!
benraiss@Mbareks-MacBook-Air stack %
*/
