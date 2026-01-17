#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    /* data */
    int size;
    int top;
    int *S;
};

// creating stack
void CreateStack(struct Stack *st)
{
    printf("Enter size of stack: ");
    scanf("%d", &st->size);
    st->top = -1;
    st->S = (int *)malloc(st->size * sizeof(int));
}

// push operation on stack
void Push(struct Stack *st, int x)
{
    if (st->top == st->size - 1)
    {
        printf("Stack Overflow\n");
    }
    else
    {
        st->top++;
        st->S[st->top] = x;
    }
}

// pop operation on stack
int pop(struct Stack *st)
{
    int x = -1;

    if (st->top == -1)
        printf("Stack Underflow\n");
    else
    {
        x = st->S[st->top--];
    }
    return x;
}

// peek operation on stack
int peek(struct Stack st, int index)
{
    int x = -1;
    if (st.top - index + 1 < 0)
        printf("Invalid Index \n");
    x = st.S[st.top - index + 1];

    return x;
}

// check if stack is empty
int isEmpty(struct Stack st)
{
    if (st.top == -1)
        return 1;
    return 0;
}

// check if stack is full
int isFull(struct Stack st)
{
    return st.top == st.size - 1;
}

// get the top element of the stack
int stackTop(struct Stack st)
{
    if (!isEmpty(st))
        return st.S[st.top];
    return -1;
}

// copying the structure is NOT a problem here because the structure
// contains a pointer to dynamically allocated memory
void Display(struct Stack st)
{
    int i;
    for (i = st.top; i >= 0; i--)
    {
        printf("%d ", st.S[i]);
    }
    printf("\n");
}

int main()
{
    printf("═══════════════════════════════════════════════════════\n");
    printf("            ABDUL BARI'S STACK IMPLEMENTATION\n");
    printf("═══════════════════════════════════════════════════════\n\n");

    struct Stack st;
    CreateStack(&st);

    printf("\n═══ PUSH OPERATIONS ═══\n");
    Push(&st, 10);
    Push(&st, 20);
    Push(&st, 30);
    Push(&st, 40);
    Push(&st, 50);

    printf("%d \n", stackTop(st)); // print top element
    printf("%d \n", peek(st, 1));  // print element at index 1

    printf("Stack after pushing 10, 20, 30, 40, 50:\n");
    Display(st);

    // Free memory
    free(st.S);

    printf("\n═══════════════════════════════════════════════════════\n");
    printf("Program completed successfully!\n");
    return 0;
}

/*═══════════════════════════════════════════════════════
            ABDUL BARI'S STACK IMPLEMENTATION
═══════════════════════════════════════════════════════

Enter size of stack: 5

═══ PUSH OPERATIONS ═══
50
50
Stack after pushing 10, 20, 30, 40, 50:
50 40 30 20 10

═══════════════════════════════════════════════════════
Program completed successfully!*/
