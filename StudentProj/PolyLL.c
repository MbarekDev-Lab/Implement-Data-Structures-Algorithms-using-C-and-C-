#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ============================================================================
// NODE STRUCTURE FOR POLYNOMIAL TERM
// ============================================================================
struct Node
{
    int coeff;         // coefficient of term
    int exp;           // exponent of term
    struct Node *next; // pointer to next term
} *poly = NULL;        // global head pointer

// ============================================================================
// CREATE POLYNOMIAL FROM USER INPUT
// ============================================================================
void create()
{
    struct Node *t, *last = NULL;
    int num, i;

    printf("Enter number of terms: ");
    scanf("%d", &num);
    printf("Enter terms (coefficient exponent):\n");

    for (i = 0; i < num; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        printf("Term %d (coeff exp): ", i + 1);
        scanf("%d %d", &t->coeff, &t->exp);
        t->next = NULL;

        if (poly == NULL)
        {
            poly = last = t; // First node
        }
        else
        {
            last->next = t; // Link at end
            last = t;       // Update last pointer
        }
    }
}

// ============================================================================
// CREATE POLYNOMIAL FROM ARRAYS (FOR TESTING)
// ============================================================================
void createPolynomial(int coeffs[], int exps[], int n)
{
    struct Node *t, *last;
    int i;

    printf("Creating Polynomial with %d terms.\n", n);

    // Create first node
    poly = (struct Node *)malloc(sizeof(struct Node));
    poly->coeff = coeffs[0];
    poly->exp = exps[0];
    poly->next = NULL;
    last = poly;

    // Create remaining nodes
    for (i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->coeff = coeffs[i];
        t->exp = exps[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

// ============================================================================
// DISPLAY POLYNOMIAL
// ============================================================================
void display(struct Node *p)
{
    if (p == NULL)
    {
        printf("Polynomial is empty.\n");
        return;
    }

    int isFirst = 1; // Flag to handle first term formatting

    while (p)
    {
        // Handle sign
        if (p->coeff > 0 && !isFirst)
            printf(" + ");
        else if (p->coeff < 0)
        {
            if (isFirst)
                printf("-");
            else
                printf(" - ");
        }

        // Get absolute coefficient
        int absCoeff = (p->coeff < 0) ? -p->coeff : p->coeff;

        // Print term based on exponent
        if (p->exp == 0)
            printf("%d", absCoeff);
        else if (p->exp == 1)
            printf("%dx", absCoeff);
        else
            printf("%dx^%d", absCoeff, p->exp);

        p = p->next;
        isFirst = 0;
    }
    printf("\n");
}

// ============================================================================
// EVALUATE POLYNOMIAL AT GIVEN X
// ============================================================================
long Eval(struct Node *p, int x)
{
    long val = 0;
    while (p) // Traverse each term
    {
        val += p->coeff * pow(x, p->exp); // Add term value to total
        p = p->next;
    }
    return val;
}

// ============================================================================
// FREE POLYNOMIAL MEMORY
// ============================================================================
void freePoly(struct Node *p)
{
    struct Node *temp;
    while (p)
    {
        temp = p;
        p = p->next;
        free(temp);
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    printf("═══════════════════════════════════════════════════════\n");
    printf("  POLYNOMIAL REPRESENTATION USING LINKED LIST\n");
    printf("═══════════════════════════════════════════════════════\n\n");

    // Method 1: User input
    printf("═══ CREATE POLYNOMIAL FROM USER INPUT ═══\n");
    create();
    printf("\nYour Polynomial: ");
    display(poly);

    // Evaluate polynomial
    int x;
    printf("Enter value of x to evaluate: ");
    scanf("%d", &x);
    printf("P(%d) = %ld\n\n", x, Eval(poly, x));

    // Free memory
    freePoly(poly);
    poly = NULL;

    // Method 2: Pre defined polynomial for testing
    printf("═══ CREATE POLYNOMIAL FROM ARRAY ═══\n");
    int coeffs[] = {5, -3, 2, -1};
    int exps[] = {3, 2, 1, 0};
    createPolynomial(coeffs, exps, 4);

    printf("Polynomial: ");
    display(poly);

    printf("Enter value of x to evaluate: ");
    scanf("%d", &x);
    printf("P(%d) = %ld\n", x, Eval(poly, x));

    // Free memory
    freePoly(poly);

    printf("\n═══════════════════════════════════════════════════════\n");
    printf("Program completed successfully!\n");

    return 0;
}
