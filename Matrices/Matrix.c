#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// ABDUL BARI'S DIAGONAL MATRIX - LECTURE IMPLEMENTATION
// ============================================================================

/*
 * PROBLEM: Why waste memory storing zeros?
 *
 * Example 5x5 Diagonal Matrix:
 *
 *     3  0  0  0  0
 *     0  7  0  0  0
 *     0  0  4  0  0
 *     0  0  0  9  0
 *     0  0  0  0  6
 *
 * Total elements = 25
 * Useful elements = 5 (only diagonal)
 * Wasted elements = 20 zeros
 *
 * SOLUTION: Store only diagonal elements in 1D array
 * Space: n instead of n²
 * Saved: n² - n = n(n-1) integers
 */

/*
 * DEFINITION (Very Important):
 * A Diagonal Matrix is a SQUARE matrix where:
 * 1. All non-diagonal elements are 0
 * 2. Only elements where i == j can be non-zero
 *
 * Mathematical condition:
 * M[i][j] = { value  if i == j (diagonal)
 *           { 0      if i != j (non-diagonal)
 */

// ============================================================================
// STRUCTURE DEFINITION
// ============================================================================

typedef struct DiagonalMatrix
{
    int *A; // 1D array to store only diagonal elements
    int n;  // dimension (n x n matrix)
} DiagonalMatrix;

struct Matrix
{
    int A[10];
    int n;
};

// ============================================================================
// CORE FUNCTIONS (From Abdul Bari's Lecture)
// ============================================================================

/*
 * SET FUNCTION (Write Operation)
 *
 * Purpose: Insert value x at position [i][j]
 * Logic:
 *   - If i != j → Ignore (must be 0, we don't store zeros)
 *   - If i == j → Store in 1D array at index (i-1)
 *
 * Mapping Formula (1-based indexing):
 *   Matrix[i][j] → Array[i-1] when i == j
 *
 * Example: set(A, 3, 3, 10)
 *   → Stores 10 at A[2]
 */
void Set(DiagonalMatrix *m, int i, int j, int x)
{
    if (i == j) // Only diagonal elements
        m->A[i - 1] = x;
    // If i != j, do nothing (non-diagonal must be 0)
}

void SetMatrix(struct Matrix *m, int i, int j, int x)
{
    if (i == j)
        m->A[i - 1] = x;
}

/*
 * GET FUNCTION (Read Operation)
 *
 * Purpose: Retrieve value at position [i][j]
 * Logic:
 *   - If i == j → Return stored value A[i-1]
 *   - If i != j → Return 0 automatically
 *
 * This reconstructs the full matrix LOGICALLY,
 * without storing it PHYSICALLY.
 *
 * Example:
 *   get(A, 2, 3) → 0 (non-diagonal)
 *   get(A, 4, 4) → A[3] (diagonal)
 */
int Get(DiagonalMatrix m, int i, int j)
{
    if (i == j)
        return m.A[i - 1];
    else
        return 0;
}

GetMatrix(struct Matrix m, int i, int j)
{
    if (i == j)
        return m.A[i - 1];
    else
        return 0;
}

/*
 * DISPLAY FUNCTION (Important Concept)
 *
 * Even though we store only 1D array,
 * we DISPLAY as 2D to the user.
 *
 * This demonstrates the ABSTRACT DATA TYPE concept:
 *   - User sees: 2D matrix
 *   - Internal storage: 1D array
 *
 * Logic:
 *   for each row i:
 *     for each column j:
 *       if i == j: print A[i-1]
 *       else: print 0
 */

void Display(DiagonalMatrix m)
{
    int i, j;
    printf("\nDiagonal Matrix (%dx%d):\n", m.n, m.n);
    for (i = 1; i <= m.n; i++)
    {
        for (j = 1; j <= m.n; j++)
        {
            if (i == j)
                printf("%3d ", m.A[i - 1]);
            else
                printf("%3d ", 0);
        }
        printf("\n");
    }
}

void DisplayMatrix(struct Matrix m)
{
    int i, j;
    printf("\nMatrix (%dx%d):\n", m.n, m.n);

    for (i = 0; i < m.n; i++)
    {
        for (j = 0; j < m.n; j++)
        {
            if (i == j)
                printf("%3d ", m.A[i]);
            else
                printf("%3d ", 0);
        }
        printf("\n");
    }
}

/*
 * CREATE FUNCTION (Memory Allocation)
 *
 * Allocates memory for ONLY n elements
 * (not n² like normal 2D array)
 *
 * User provides dimension n
 * Then enters n diagonal values
 */
void Create(DiagonalMatrix *m)
{
    printf("Enter dimension (n for nxn matrix): ");
    scanf("%d", &m->n);

    // Allocate memory for ONLY n elements
    m->A = (int *)malloc(m->n * sizeof(int));

    printf("Enter %d diagonal elements:\n", m->n);
    for (int i = 1; i <= m->n; i++)
    {
        printf("Element [%d][%d]: ", i, i);
        scanf("%d", &m->A[i - 1]);
    }
}

// ============================================================================
// ADDITIONAL OPERATIONS (Building on Core Concept)
// ============================================================================

/*
 * MULTIPLY TWO DIAGONAL MATRICES
 *
 * Property: Diagonal × Diagonal = Diagonal
 * Result[i][i] = A[i][i] × B[i][i]
 *
 * Space efficient: Only store n elements per matrix
 */
DiagonalMatrix Multiply(DiagonalMatrix A, DiagonalMatrix B)
{
    DiagonalMatrix C;

    if (A.n != B.n)
    {
        printf("Error: Matrices must have same dimension\n");
        C.n = 0;
        C.A = NULL;
        return C;
    }

    C.n = A.n;
    C.A = (int *)malloc(C.n * sizeof(int));

    // Multiply only diagonal elements
    for (int i = 0; i < C.n; i++)
    {
        C.A[i] = A.A[i] * B.A[i];
    }

    return C;
}

/*
 * ADD TWO DIAGONAL MATRICES
 *
 * Property: Diagonal + Diagonal = Diagonal
 * Result[i][i] = A[i][i] + B[i][i]
 */
DiagonalMatrix Add(DiagonalMatrix A, DiagonalMatrix B)
{
    DiagonalMatrix C;

    if (A.n != B.n)
    {
        printf("Error: Matrices must have same dimension\n");
        C.n = 0;
        C.A = NULL;
        return C;
    }

    C.n = A.n;
    C.A = (int *)malloc(C.n * sizeof(int));

    // Add only diagonal elements
    for (int i = 0; i < C.n; i++)
    {
        C.A[i] = A.A[i] + B.A[i];
    }

    return C;
}

// ============================================================================
// MEMORY ANALYSIS (Display Space Savings)
// ============================================================================

void PrintMemoryAnalysis(int n)
{
    int normal_2D = n * n * sizeof(int);
    int diagonal_1D = n * sizeof(int);
    int saved = normal_2D - diagonal_1D;

    printf("\n╔════════════════════════════════════════╗\n");
    printf("║      MEMORY ANALYSIS (n=%d)             ║\n", n);
    printf("╠════════════════════════════════════════╣\n");
    printf("║ Normal 2D Array:  %d × %d = %d ints    ║\n", n, n, n * n);
    printf("║ Memory needed:    %d bytes          ║\n", normal_2D);
    printf("║                                        ║\n");
    printf("║ Diagonal Storage: %d ints             ║\n", n);
    printf("║ Memory needed:    %d bytes            ║\n", diagonal_1D);
    printf("║                                        ║\n");
    printf("║ MEMORY SAVED:     %d bytes ✓          ║\n", saved);
    printf("║ Efficiency:       %.1f%% reduction      ║\n",
           (float)saved / normal_2D * 100);
    printf("╚════════════════════════════════════════╝\n");
}

// ============================================================================
// DEMONSTRATION PROGRAM
// ============================================================================

int main()
{
    struct Matrix m;
    m.n = 4;

    SetMatrix(&m, 1, 1, 5);
    SetMatrix(&m, 2, 2, 8);
    SetMatrix(&m, 3, 3, 12);

    DisplayMatrix(m);

    return 0;
}

int no_main()
{
    DiagonalMatrix m1, m2, result;

    printf("═══════════════════════════════════════════════════════\n");
    printf("    ABDUL BARI'S DIAGONAL MATRIX IMPLEMENTATION\n");
    printf("═══════════════════════════════════════════════════════\n");

    // Example from lecture
    printf("\n EXAMPLE FROM LECTURE:\n");
    printf("   5×5 Matrix with 5 diagonal elements\n\n");

    // Create first diagonal matrix (manual setup for demo)
    m1.n = 5;
    m1.A = (int *)malloc(m1.n * sizeof(int));
    m1.A[0] = 3; // M[1][1]
    m1.A[1] = 7; // M[2][2]
    m1.A[2] = 4; // M[3][3]
    m1.A[3] = 9; // M[4][4]
    m1.A[4] = 6; // M[5][5]

    printf("Matrix M1 (from lecture example):\n");
    Display(m1);

    // Demonstrate SET and GET operations
    printf("\n TESTING SET() OPERATION:\n");
    printf("Calling Set(&m1, 3, 3, 99)...\n");
    Set(&m1, 3, 3, 99);
    printf("Result: M1[3][3] changed from 4 to 99\n");
    Display(m1);

    printf("\n TESTING GET() OPERATION:\n");
    printf("Get(m1, 3, 3) = %d (diagonal element)\n", Get(m1, 3, 3));
    printf("Get(m1, 2, 4) = %d (non-diagonal, must be 0)\n", Get(m1, 2, 4));

    // Memory analysis
    PrintMemoryAnalysis(m1.n);

    // Create second matrix for operations
    printf("\n\n MATRIX OPERATIONS:\n");
    m2.n = 5;
    m2.A = (int *)malloc(m2.n * sizeof(int));
    m2.A[0] = 2;
    m2.A[1] = 3;
    m2.A[2] = 4;
    m2.A[3] = 5;
    m2.A[4] = 6;

    printf("\nMatrix M2:\n");
    Display(m2);

    // Addition
    printf("\n M1 + M2 =\n");
    result = Add(m1, m2);
    Display(result);
    free(result.A);

    // Multiplication
    printf("\n M1 × M2 =\n");
    result = Multiply(m1, m2);
    Display(result);
    free(result.A);

    // Interactive creation
    printf("\n\n NOW CREATE DIAGONAL MATRIX:\n");
    DiagonalMatrix m3;
    Create(&m3);
    Display(m3);

    // Show mapping
    printf("\n INTERNAL STORAGE (1D Array):\n");
    printf("Index:  ");
    for (int i = 0; i < m3.n; i++)
        printf("[%d] ", i);
    printf("\nValue:  ");
    for (int i = 0; i < m3.n; i++)
        printf(" %d  ", m3.A[i]);
    printf("\n");

    // Clean up
    free(m1.A);
    free(m2.A);
    free(m3.A);

    return 0;
}
