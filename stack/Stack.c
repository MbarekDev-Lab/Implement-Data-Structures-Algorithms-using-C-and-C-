#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    /* data */
    int size;
    int top;
    int *S;
};

void CreateStack(struct Stack *st)
{
    printf("Enter size of stack: ");
    scanf("%d", &st->size);
    st->top = -1;
    st->S = (int *)malloc(st->size * sizeof(int));
}

// copying the structure is NOT a problem here because the structure contains a pointer to dynamically allocated memory
void Display(struct Stack st)
{
    int i;
    for (i = st.top; i >= 0; i--)
    {
        printf("%d ", st.S[i]);
    }
    printf("\n");
}

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

    printf("Stack after pushing 10, 20, 30, 40, 50:\n");
    Display(st);

    // Free memory
    free(st.S);

    printf("\n═══════════════════════════════════════════════════════\n");
    printf("Program completed successfully!\n");
    return 0;
}

/*benraiss@MacBookAir stack % clang -std=c17 -Wall -Wextra -o stack_ll Stack.c
benraiss@MacBookAir stack % ./stack_ll
═══════════════════════════════════════════════════════
            ABDUL BARI'S STACK IMPLEMENTATION
═══════════════════════════════════════════════════════

Enter size of stack: 5

═══ PUSH OPERATIONS ═══
Stack after pushing 10, 20, 30, 40, 50:
50 40 30 20 10

═══════════════════════════════════════════════════════
Program completed successfully!
benraiss@MacBookAir stack % */
