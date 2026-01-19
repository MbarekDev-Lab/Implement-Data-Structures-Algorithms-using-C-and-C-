#include <iostream>
#include <cstring>
#include <stack>
#include <iomanip>

using namespace std;

// ============================================================================
// CHECK IF CHARACTER IS OPERAND (a, b, c, etc.)
// ============================================================================
int isOperand(char x)
{
    if (x == '+' || x == '-' || x == '*' || x == '/' ||
        x == '^' || x == '(' || x == ')')
    {
        return 0; // It's an operator or parenthesis
    }
    return 1; // It's an operand
}

// ============================================================================
// OUTSIDE STACK PRECEDENCE (before pushing to stack)
// ============================================================================
int outPrecedence(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 3;
    else if (x == '^')
        return 6;
    else if (x == '(')
        return 7; // Highest - always push '(' to stack
    else if (x == ')')
        return 0; // Lowest - trigger popping until '('
    return -1;
}

// ============================================================================
// INSIDE STACK PRECEDENCE (already on stack)
// ============================================================================
int inPrecedence(char x)
{
    if (x == '+' || x == '-')
        return 2;
    else if (x == '*' || x == '/')
        return 4;
    else if (x == '^')
        return 5; // Right associative (lower than out-precedence)
    else if (x == '(')
        return 0; // Lowest - blocks popping until ')' arrives
    return -1;
}

// ============================================================================
// CONVERT INFIX TO POSTFIX
// ============================================================================
char *convert(char *infix)
{
    char *postfix = new char[strlen(infix) + 1];
    stack<char> stk;

    int i = 0;
    int j = 0;

    cout << "\n┌────────┬──────────┬─────────────┬──────────────────┐\n";
    cout << "  │  Char  │   Type   │   Stack     │     Postfix      │\n";
    cout << "  ├────────┼──────────┼─────────────┼──────────────────┤\n";

    while (infix[i] != '\0')
    {
        cout << "│   " << infix[i] << "    │";

        if (isOperand(infix[i]))
        {
            cout << " Operand  │";
            postfix[j++] = infix[i++];
        }
        else
        {
            cout << " Operator │";

            if (stk.empty() || outPrecedence(infix[i]) > inPrecedence(stk.top()))
            {
                stk.push(infix[i++]);
            }
            else if (outPrecedence(infix[i]) == inPrecedence(stk.top()))
            {
                stk.pop(); // Pop matching parenthesis
                i++;
            }
            else
            {
                postfix[j++] = stk.top();
                stk.pop();
            }
        }

        // Display stack
        stack<char> temp = stk;
        string stackStr = "";
        while (!temp.empty())
        {
            stackStr = temp.top() + stackStr;
            temp.pop();
        }
        cout << setw(11) << left << stackStr << " │";

        // Display postfix so far
        postfix[j] = '\0';
        cout << setw(16) << left << postfix << " │\n";
    }

    // Pop remaining operators
    while (!stk.empty())
    {
        postfix[j++] = stk.top();
        stk.pop();
    }

    postfix[j] = '\0';

    cout << "│  END   │          │      ∅      │";
    cout << setw(16) << left << postfix << "   │\n";
    cout << "└────────┴──────────┴─────────────┴──────────────────┘\n";

    return postfix;
}

// ============================================================================
// MAIN FUNCTION 
// ============================================================================
int main()
{
    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "       INFIX TO POSTFIX CONVERSION (C++ STL)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    // Test cases
    char test1[] = "((a+b)*c)-d^e^f";
    char test2[] = "a+b*c";
    char test3[] = "(a+b)*(c+d)";
    char test4[] = "a^b^c";
    char test5[] = "a+b*c-d/e";

    cout << "\n═══ TEST CASE 1 ═══";
    cout << "\nInfix:    " << test1;
    char *postfix1 = convert(test1);
    cout << "\n Postfix:  " << postfix1;
    cout << "\n   Expected: ab+c*def^^-\n";
    delete[] postfix1;

    cout << "\n═══ TEST CASE 2 ═══";
    cout << "\nInfix:    " << test2;
    char *postfix2 = convert(test2);
    cout << "\n Postfix:  " << postfix2;
    cout << "\n   Expected: abc*+\n";
    delete[] postfix2;

    cout << "\n═══ TEST CASE 3 ═══";
    cout << "\nInfix:    " << test3;
    char *postfix3 = convert(test3);
    cout << "\n Postfix:  " << postfix3;
    cout << "\n   Expected: ab+cd+*\n";
    delete[] postfix3;

    cout << "\n═══ TEST CASE 4 (Right Associative) ═══";
    cout << "\nInfix:    " << test4;
    char *postfix4 = convert(test4);
    cout << "\n Postfix:  " << postfix4;
    cout << "\n   Expected: abc^^ (a^(b^c))\n";
    delete[] postfix4;

    cout << "\n═══ TEST CASE 5 ═══";
    cout << "\nInfix:    " << test5;
    char *postfix5 = convert(test5);
    cout << "\n Postfix:  " << postfix5;
    cout << "\n   Expected: abc*+de/-\n";
    delete[] postfix5;

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "Program completed successfully!\n";

    return 0;
}

/*
    benraiss@Mbareks-MacBook-Air operators % clang++ -std=c++17 -Wall -Wextra -o infix_postfix_cpp InfixToPostfix.cpp
    ./infix_postfix_cpp
    ═══════════════════════════════════════════════════════════
        INFIX TO POSTFIX CONVERSION (C++ STL)
    ═══════════════════════════════════════════════════════════

    ═══ TEST CASE 1 ═══
    Infix:    ((a+b)*c)-d^e^f
    ┌────────┬──────────┬─────────────┬──────────────────┐
    │  Char  │   Type   │   Stack     │     Postfix      │
    ├────────┼──────────┼─────────────┼──────────────────┤
    │   (    │ Operator │(           │                 │
    │   (    │ Operator │((          │                 │
    │   a    │ Operand  │((          │a                │
    │   +    │ Operator │((+         │a                │
    │   b    │ Operand  │((+         │ab               │
    │   )    │ Operator │((          │ab+              │
    │   )    │ Operator │(           │ab+              │
    │   *    │ Operator │(*          │ab+              │
    │   c    │ Operand  │(*          │ab+c             │
    │   )    │ Operator │(           │ab+c*            │
    │   )    │ Operator │            │ab+c*            │
    │   -    │ Operator │-           │ab+c*            │
    │   d    │ Operand  │-           │ab+c*d           │
    │   ^    │ Operator │-^          │ab+c*d           │
    │   e    │ Operand  │-^          │ab+c*de          │
    │   ^    │ Operator │-^^         │ab+c*de          │
    │   f    │ Operand  │-^^         │ab+c*def         │
    │  END   │          │      ∅      │ab+c*def^^-        │
    └────────┴──────────┴─────────────┴──────────────────┘

    Postfix:  ab+c*def^^-
    Expected: ab+c*def^^-

    ═══ TEST CASE 2 ═══
    Infix:    a+b*c
    ┌────────┬──────────┬─────────────┬──────────────────┐
    │  Char  │   Type   │   Stack     │     Postfix      │
    ├────────┼──────────┼─────────────┼──────────────────┤
    │   a    │ Operand  │            │a                │
    │   +    │ Operator │+           │a                │
    │   b    │ Operand  │+           │ab               │
    │   *    │ Operator │+*          │ab               │
    │   c    │ Operand  │+*          │abc              │
    │  END   │          │      ∅      │abc*+              │
    └────────┴──────────┴─────────────┴──────────────────┘

    Postfix:  abc*+
    Expected: abc*+

    ═══ TEST CASE 3 ═══
    Infix:    (a+b)*(c+d)
    ┌────────┬──────────┬─────────────┬──────────────────┐
    │  Char  │   Type   │   Stack     │     Postfix      │
    ├────────┼──────────┼─────────────┼──────────────────┤
    │   (    │ Operator │(           │                 │
    │   a    │ Operand  │(           │a                │
    │   +    │ Operator │(+          │a                │
    │   b    │ Operand  │(+          │ab               │
    │   )    │ Operator │(           │ab+              │
    │   )    │ Operator │            │ab+              │
    │   *    │ Operator │*           │ab+              │
    │   (    │ Operator │*(          │ab+              │
    │   c    │ Operand  │*(          │ab+c             │
    │   +    │ Operator │*(+         │ab+c             │
    │   d    │ Operand  │*(+         │ab+cd            │
    │   )    │ Operator │*(          │ab+cd+           │
    │   )    │ Operator │*           │ab+cd+           │
    │  END   │          │      ∅      │ab+cd+*            │
    └────────┴──────────┴─────────────┴──────────────────┘

    Postfix:  ab+cd+*
    Expected: ab+cd+*

    ═══ TEST CASE 4 (Right Associative) ═══
    Infix:    a^b^c
    ┌────────┬──────────┬─────────────┬──────────────────┐
    │  Char  │   Type   │   Stack     │     Postfix      │
    ├────────┼──────────┼─────────────┼──────────────────┤
    │   a    │ Operand  │            │a                │
    │   ^    │ Operator │^           │a                │
    │   b    │ Operand  │^           │ab               │
    │   ^    │ Operator │^^          │ab               │
    │   c    │ Operand  │^^          │abc              │
    │  END   │          │      ∅      │abc^^              │
    └────────┴──────────┴─────────────┴──────────────────┘

    Postfix:  abc^^
    Expected: abc^^ (a^(b^c))

    ═══ TEST CASE 5 ═══
    Infix:    a+b*c-d/e
    ┌────────┬──────────┬─────────────┬──────────────────┐
    │  Char  │   Type   │   Stack     │     Postfix      │
    ├────────┼──────────┼─────────────┼──────────────────┤
    │   a    │ Operand  │            │a                │
    │   +    │ Operator │+           │a                │
    │   b    │ Operand  │+           │ab               │
    │   *    │ Operator │+*          │ab               │
    │   c    │ Operand  │+*          │abc              │
    │   -    │ Operator │+           │abc*             │
    │   -    │ Operator │            │abc*+            │
    │   -    │ Operator │-           │abc*+            │
    │   d    │ Operand  │-           │abc*+d           │
    │   /    │ Operator │-/          │abc*+d           │
    │   e    │ Operand  │-/          │abc*+de          │
    │  END   │          │      ∅      │abc*+de/-          │
    └────────┴──────────┴─────────────┴──────────────────┘

    Postfix:  abc*+de/-
    Expected: abc*+de/-

    ═══════════════════════════════════════════════════════════
    Program completed successfully!
    benraiss@Mbareks-MacBook-Air operators % ./infix_postfix_cpp
    ═══════════════════════════════════════════════════════════
*/