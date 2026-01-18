#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (t == NULL)
    {
        printf("Stack Overflow (Heap memory full)\n");
    }
    else
    {
        t->data = x;
        t->next = top;
        top = t;
    }
}

// ============================================================================
// POP OPERATION - O(1)
// ============================================================================
char pop()
{
    struct Node *t;
    char x = '\0'; // default return value for empty stack

    if (top == NULL)
    {
        printf("Stack Underflow (empty)\n");
        return '\0';
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
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}

// ============================================================================
// CHECK IF PARENTHESES ARE BALANCED
// ============================================================================
int isBalanced(const char *exp)
{
    int i;

    for (i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
        {
            push(exp[i]);
        }
        else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}')
        {
            if (top == NULL)
            {
                return 0; // Unmatched closing bracket
            }

            char popped = pop();

            // Check if brackets match
            if ((exp[i] == ')' && popped != '(') ||
                (exp[i] == ']' && popped != '[') ||
                (exp[i] == '}' && popped != '{'))
            {
                return 0; // Mismatched brackets
            }
        }
    }

    // Stack should be empty if balanced
    return (top == NULL) ? 1 : 0;
}

// ============================================================================
// FREE STACK MEMORY
// ============================================================================
void freeStack()
{
    while (top != NULL)
    {
        pop();
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    printf("═══════════════════════════════════════════════════════\n");
    printf("       PARENTHESIS MATCHING USING STACK\n");
    printf("═══════════════════════════════════════════════════════\n\n");

    // Test cases
    const char *test1 = "{[(a+b)*(c-d)]}";
    const char *test2 = "{[(a+b)*(c-d)]";
    const char *test3 = "{[(a+b)*(c-d)]}]";
    const char *test4 = "((a+b))";
    const char *test5 = "((a+b)";
    const char *test6 = "{[()]}";

    printf("═══ TEST CASES ═══\n");

    printf("1. Expression: %s\n", test1);
    printf("   Result: %s\n\n", isBalanced(test1) ? " Balanced" : " Not Balanced");
    freeStack();

    printf("2. Expression: %s\n", test2);
    printf("   Result: %s\n\n", isBalanced(test2) ? " Balanced" : " Not Balanced");
    freeStack();

    printf("3. Expression: %s\n", test3);
    printf("   Result: %s\n\n", isBalanced(test3) ? " Balanced" : " Not Balanced");
    freeStack();

    printf("4. Expression: %s\n", test4);
    printf("   Result: %s\n\n", isBalanced(test4) ? " Balanced" : " Not Balanced");
    freeStack();

    printf("5. Expression: %s\n", test5);
    printf("   Result: %s\n\n", isBalanced(test5) ? " Balanced" : " Not Balanced");
    freeStack();

    printf("6. Expression: %s\n", test6);
    printf("   Result: %s\n\n", isBalanced(test6) ? " Balanced" : " Not Balanced");
    freeStack();

    printf("═══════════════════════════════════════════════════════\n");
    printf("Program completed successfully!\n");

    return 0;
}

/*
    benraiss@Mbareks-MacBook-Air stack %  clang -std=c17 -Wall -Wextra -o _c PartenthesisMatching.c
    benraiss@Mbareks-MacBook-Air stack % ./_c
    ═══════════════════════════════════════════════════════
        PARENTHESIS MATCHING USING STACK
    ═══════════════════════════════════════════════════════

    ═══ TEST CASES ═══
    1. Expression: {[(a+b)*(c-d)]}
    Result:  Balanced

    2. Expression: {[(a+b)*(c-d)]
    Result:  Not Balanced

    3. Expression: {[(a+b)*(c-d)]}]
    Result:  Not Balanced

    4. Expression: ((a+b))
    Result:  Balanced

    5. Expression: ((a+b)
    Result:  Not Balanced

    6. Expression: {[()]}
    Result:  Balanced

    ═══════════════════════════════════════════════════════
    Program completed successfully!
    benraiss@Mbareks-MacBook-Air stack %

*/