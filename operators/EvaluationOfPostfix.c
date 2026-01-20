#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// STACK USING LINKED LIST
// ============================================================================
struct Node
{
    int data;
    struct Node *next;
} *top = NULL;

void push(int x)
{
    struct Node *t;
    t = (struct Node *)malloc(sizeof(struct Node));
    if (t == NULL)
        printf("Stack is full\n");
    else
    {
        t->data = x;
        t->next = top;
        top = t;
    }
}

int pop()
{
    struct Node *t;
    int x = -1;
    if (top == NULL)
    {
        printf("Stack is Empty\n");
        return -1;
    }
    else
    {
        t = top;
        top = top->next;
        x = t->data;
        free(t);
    }
    return x;
}

int peek()
{
    if (top == NULL)
        return -1;
    return top->data;
}

int isEmpty()
{
    return top == NULL;
}

void Display()
{
    struct Node *p;
    p = top;

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
// CHECK IF CHARACTER IS OPERAND (digit)
// ============================================================================
int isOperand(char x)
{
    if (x >= '0' && x <= '9')
        return 1;
    return 0;
}

// ============================================================================
// EVALUATE POSTFIX EXPRESSION
// ============================================================================
int Eval(char *postfix)
{
    int i = 0;
    int x1, x2, r = 0;

    printf("\n┌────────┬──────────┬─────────────────────────────────┐\n");
    printf("│  Char  │   Type   │          Operation              │\n");
    printf("├────────┼──────────┼─────────────────────────────────┤\n");

    for (i = 0; postfix[i] != '\0'; i++)
    {
        printf("│   %c    │", postfix[i]);

        if (isOperand(postfix[i]))
        {
            int value = postfix[i] - '0'; // Convert char to int
            push(value);
            printf(" Operand  │ Push %d to stack               │\n", value);
        }
        else
        {
            printf(" Operator │");
            x2 = pop(); // Second operand (top of stack)
            x1 = pop(); // First operand

            switch (postfix[i])
            {
            case '+':
                r = x1 + x2;
                printf(" %d + %d = %d                     │\n", x1, x2, r);
                break;
            case '-':
                r = x1 - x2;
                printf(" %d - %d = %d                     │\n", x1, x2, r);
                break;
            case '*':
                r = x1 * x2;
                printf(" %d * %d = %d                    │\n", x1, x2, r);
                break;
            case '/':
                if (x2 == 0)
                {
                    printf(" Division by zero!              │\n");
                    return -1;
                }
                r = x1 / x2;
                printf(" %d / %d = %d                     │\n", x1, x2, r);
                break;
            }
            push(r);
        }
    }

    printf("└────────┴──────────┴─────────────────────────────────┘\n\n");

    return peek(); // Final result is on top of stack
}

// ============================================================================
// FREE STACK MEMORY
// ============================================================================
void freeStack()
{
    while (!isEmpty())
    {
        pop();
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    printf("═══════════════════════════════════════════════════════════\n");
    printf("       POSTFIX EXPRESSION EVALUATION\n");
    printf("═══════════════════════════════════════════════════════════\n");

    // Test cases
    char *postfix1 = "234*+82/-";
    char *postfix2 = "53+82-*";
    char *postfix3 = "46+2/5*7+";

    printf("\n═══ TEST CASE 1 ═══");
    printf("\nPostfix Expression: %s", postfix1);
    printf("\nInfix Equivalent:   2 + 3*4 - 8/2");
    int result1 = Eval(postfix1);
    printf(" Final Result: %d\n", result1);
    freeStack();

    printf("\n═══ TEST CASE 2 ═══");
    printf("\nPostfix Expression: %s", postfix2);
    printf("\nInfix Equivalent:   (5 + 3) * (8 - 2)");
    int result2 = Eval(postfix2);
    printf(" Final Result: %d\n", result2);
    freeStack();

    printf("\n═══ TEST CASE 3 ═══");
    printf("\nPostfix Expression: %s", postfix3);
    printf("\nInfix Equivalent:   (4 + 6) / 2 * 5 + 7");
    int result3 = Eval(postfix3);
    printf(" Final Result: %d\n", result3);
    freeStack();

    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("Program completed successfully!\n");

    return 0;
}

/*
    benraiss@Mbareks-MacBook-Air operators %  clang -std=c17 -Wall -Wextra -o _c EvaluationOfPostfix.c
    benraiss@Mbareks-MacBook-Air operators % ./_c
    ═══════════════════════════════════════════════════════════
        POSTFIX EXPRESSION EVALUATION
    ═══════════════════════════════════════════════════════════

    ═══ TEST CASE 1 ═══
    Postfix Expression: 234*+82/-
    Infix Equivalent:   2 + 3*4 - 8/2
    ┌────────┬──────────┬─────────────────────────────────┐
    │  Char  │   Type   │          Operation              │
    ├────────┼──────────┼─────────────────────────────────┤
    │   2    │ Operand  │ Push 2 to stack               │
    │   3    │ Operand  │ Push 3 to stack               │
    │   4    │ Operand  │ Push 4 to stack               │
    │   *    │ Operator │ 3 * 4 = 12                    │
    │   +    │ Operator │ 2 + 12 = 14                     │
    │   8    │ Operand  │ Push 8 to stack               │
    │   2    │ Operand  │ Push 2 to stack               │
    │   /    │ Operator │ 8 / 2 = 4                     │
    │   -    │ Operator │ 14 - 4 = 10                     │
    └────────┴──────────┴─────────────────────────────────┘

    Final Result: 10

    ═══ TEST CASE 2 ═══
    Postfix Expression: 53+82-*
    Infix Equivalent:   (5 + 3) * (8 - 2)
    ┌────────┬──────────┬─────────────────────────────────┐
    │  Char  │   Type   │          Operation              │
    ├────────┼──────────┼─────────────────────────────────┤
    │   5    │ Operand  │ Push 5 to stack               │
    │   3    │ Operand  │ Push 3 to stack               │
    │   +    │ Operator │ 5 + 3 = 8                     │
    │   8    │ Operand  │ Push 8 to stack               │
    │   2    │ Operand  │ Push 2 to stack               │
    │   -    │ Operator │ 8 - 2 = 6                     │
    │   *    │ Operator │ 8 * 6 = 48                    │
    └────────┴──────────┴─────────────────────────────────┘

    Final Result: 48

    ═══ TEST CASE 3 ═══
    Postfix Expression: 46+2/5*7+
    Infix Equivalent:   (4 + 6) / 2 * 5 + 7
    ┌────────┬──────────┬─────────────────────────────────┐
    │  Char  │   Type   │          Operation              │
    ├────────┼──────────┼─────────────────────────────────┤
    │   4    │ Operand  │ Push 4 to stack                 │
    │   6    │ Operand  │ Push 6 to stack               │
    │   +    │ Operator │ 4 + 6 = 10                     │
    │   2    │ Operand  │ Push 2 to stack               │
    │   /    │ Operator │ 10 / 2 = 5                     │
    │   5    │ Operand  │ Push 5 to stack               │
    │   *    │ Operator │ 5 * 5 = 25                    │
    │   7    │ Operand  │ Push 7 to stack               │
    │   +    │ Operator │ 25 + 7 = 32                     │
    └────────┴──────────┴─────────────────────────────────┘

    Final Result: 32

    ═══════════════════════════════════════════════════════════
    Program completed successfully!
    benraiss@Mbareks-MacBook-Air operators %


=== POSTFIX EVALUATION LOGIC ALGORITHM ===
For each character in postfix expression:
    If operand (digit):
        Convert to integer: '2' - '0' = 2
        Push to stack

    If operator (+, -, *, /):
        Pop two operands: x2 (top), x1 (second)
        Perform operation: result = x1 op x2
        Push result back to stack

After processing all characters:
    Stack contains single value: the final result


    = 2 + (3 * 4) - (8 / 2)
    = 2 + 12 - 4
    = 14 - 4
    = 10
*/