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
} *top = NULL;

void push(char x)
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

char pop()
{
    struct Node *t;
    char x = '\0'; // default return value for empty stack

    if (top == NULL)
    {
        printf("Stack is Empty\n");
        return '\0';
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

char peek()
{
    if (top == NULL)
        return '\0';
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

    printf("Stack (Top → Bottom): ");
    while (p != NULL)
    {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}

// ============================================================================
// OPERATOR PRECEDENCE
// ============================================================================
int precedence(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    else if (x == '^') // Exponentiation
        return 3;
    return 0;
}

// ============================================================================
// CHECK IF CHARACTER IS OPERAND (a, b, c, etc.)
// ============================================================================
int isOperand(char x)
{
    if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '(' || x == ')')
        return 0; // It's an operator or parenthesis
    else
        return 1; // It's an operand
}

// ============================================================================
// CONVERT INFIX TO POSTFIX
// ============================================================================
char *infixToPostfix(char *infix)
{
    int i = 0, j = 0;
    char *postfix;
    int len = strlen(infix);
    postfix = (char *)malloc((len + 2) * sizeof(char));

    while (infix[i] != '\0')
    {
        // If operand, add to output
        if (isOperand(infix[i]))
        {
            postfix[j++] = infix[i++];
        }
        // If '(', push to stack
        else if (infix[i] == '(')
        {
            push(infix[i++]);
        }
        // If ')', pop until '('
        else if (infix[i] == ')')
        {
            while (!isEmpty() && peek() != '(')
            {
                postfix[j++] = pop();
            }
            if (!isEmpty() && peek() == '(')
                pop(); // Remove '(' from stack
            i++;
        }
        // If operator
        else
        {
            // Check stack is not empty before accessing peek()
            while (!isEmpty() && precedence(infix[i]) <= precedence(peek()))
            {
                postfix[j++] = pop();
            }
            push(infix[i++]);
        }
    }

    // Pop remaining operators
    while (!isEmpty())
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
    return postfix;
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
    printf("       INFIX TO POSTFIX CONVERSION\n");
    printf("═══════════════════════════════════════════════════════\n\n");

    // Test cases
    char *test1 = "a+b*c-d/e";
    char *test2 = "a+b*c";
    char *test3 = "(a+b)*c";
    char *test4 = "a+b*c-d/e+f";
    char *test5 = "((a+b)*c-d)^e";

    printf("═══ TEST CASE 1 ═══\n");
    printf("Infix:    %s\n", test1);
    char *postfix1 = infixToPostfix(test1);
    printf("Postfix:  %s\n", postfix1);
    printf("Expected: abc*+de/-\n\n");
    free(postfix1);
    freeStack();

    printf("═══ TEST CASE 2 ═══\n");
    printf("Infix:    %s\n", test2);
    char *postfix2 = infixToPostfix(test2);
    printf("Postfix:  %s\n", postfix2);
    printf("Expected: abc*+\n\n");
    free(postfix2);
    freeStack();

    printf("═══ TEST CASE 3 ═══\n");
    printf("Infix:    %s\n", test3);
    char *postfix3 = infixToPostfix(test3);
    printf("Postfix:  %s\n", postfix3);
    printf("Expected: ab+c*\n\n");
    free(postfix3);
    freeStack();

    printf("═══ TEST CASE 4 ═══\n");
    printf("Infix:    %s\n", test4);
    char *postfix4 = infixToPostfix(test4);
    printf("Postfix:  %s\n", postfix4);
    printf("Expected: abc*+de/-f+\n\n");
    free(postfix4);
    freeStack();

    printf("═══ TEST CASE 5 ═══\n");
    printf("Infix:    %s\n", test5);
    char *postfix5 = infixToPostfix(test5);
    printf("Postfix:  %s\n", postfix5);
    printf("Expected: ab+c*d-e^\n\n");
    free(postfix5);
    freeStack();

    printf("═══════════════════════════════════════════════════════\n");
    printf("Program completed successfully!\n");

    return 0;
}
/*

    benraiss@Mbareks-MacBook-Air operators %  clang -std=c17 -Wall -Wextra -o _c InfixAndPostfix.c
    benraiss@Mbareks-MacBook-Air operators % ./_c
    ═══════════════════════════════════════════════════════
        INFIX TO POSTFIX CONVERSION
    ═══════════════════════════════════════════════════════

    ═══ TEST CASE 1 ═══
    Infix:    a+b*c-d/e
    Postfix:  abc*+de/-
    Expected: abc*+de/-

    ═══ TEST CASE 2 ═══
    Infix:    a+b*c
    Postfix:  abc*+
    Expected: abc*+

    ═══ TEST CASE 3 ═══
    Infix:    (a+b)*c
    Postfix:  ab+c*
    Expected: ab+c*

    ═══ TEST CASE 4 ═══
    Infix:    a+b*c-d/e+f
    Postfix:  abc*+de/-f+
    Expected: abc*+de/-f+

    ═══ TEST CASE 5 ═══
    Infix:    ((a+b)*c-d)^e
    Postfix:  ab+c*d-e^
    Expected: ab+c*d-e^

    ═══════════════════════════════════════════════════════
    Program completed successfully!

*/