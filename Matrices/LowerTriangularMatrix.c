// Lower Triangular Matrix Implementation (Row-Major Mapping) - C Version
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ============================================================================
// ABDUL BARI'S LOWER TRIANGULAR MATRIX LECTURE IMPLEMENTATION
// ============================================================================
/*
 * Lower Triangular Matrix: All elements above diagonal are 0
 * 
 * Example (5×5):
 * [ a11  0    0    0    0  ]
 * [ a21  a22  0    0    0  ]
 * [ a31  a32  a33  0    0  ]
 * [ a41  a42  a43  a44  0  ]
 * [ a51  a52  a53  a54  a55]
 * 
 * Storage: Only stores n(n+1)/2 elements instead of n²
 * 
 * Row-Major Mapping Formula (1-based indexing):
 * Index(i,j) = (i-1)i/2 + (j-1)   where i ≥ j
 * 
 * Key Intuition:
 * - Row 1 has 1 element
 * - Row 2 has 2 elements
 * - Row i has i elements
 * - Elements before row i: 1+2+...+(i-1) = (i-1)i/2
 * - Position in row i: (j-1)
 */

typedef struct Matrix
{
    int *A;     // 1D array storing only lower triangle elements
    int n;      // Dimension of square matrix (n×n)
} Matrix;

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

// Convert 2D (i,j) to 1D index using row-major formula
int Index(int i, int j)
{
    // Row-major: Index = (i-1)i/2 + (j-1)
    // Valid only when i >= j (lower triangle)
    if (i >= j)
        return (i - 1) * i / 2 + (j - 1);
    else
        return -1; // Invalid for upper triangle
}

int GetStoredElements(int n)
{
    return n * (n + 1) / 2;
}

// ============================================================================
// INITIALIZATION AND CLEANUP
// ============================================================================

void InitMatrix(Matrix *m, int n)
{
    if (n < 0)
    {
        fprintf(stderr, "Error: Matrix dimension cannot be negative\n");
        m->A = NULL;
        m->n = 0;
        return;
    }

    m->n = n;
    if (n > 0)
    {
        int size = GetStoredElements(n);
        m->A = (int *)calloc(size, sizeof(int)); // Zero initialized
        // m->A = (int *)malloc(size * sizeof(int));    
        /*
            (calloc vs malloc) 
            // Using calloc  BETTER for matrices
            int *arr1 = (int *)calloc(5, sizeof(int));
            // Result: [0, 0, 0, 0, 0] - Safe!

            // Using malloc  RISKY for matrices
            int *arr2 = (int *)malloc(5 * sizeof(int));
            // Result: [34623, -1, 9876, 0, 42] - Garbage!
        */

        if (m->A == NULL)
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            m->n = 0;
        }
    }
    else
    {
        m->A = NULL;
    }
}

void DestroyMatrix(Matrix *m)
{
    if (m->A != NULL)
    {
        free(m->A);
        m->A = NULL;
    }
    m->n = 0;
}

bool IsEmpty(const Matrix *m)
{
    return m->A == NULL || m->n == 0;
}

// ============================================================================
// CORE OPERATIONS
// ============================================================================

void Set(Matrix *m, int i, int j, int x)
{
    if (i < 1 || i > m->n || j < 1 || j > m->n)
    {
        fprintf(stderr, "Index out of bounds (%d, %d)\n", i, j);
        return;
    }
    
    // formula alternative
    /*if(i >= j){
        m->A[m->n*(j-1) + (j-2) * (j-1) / 2+(i - j )] = x;
    }*/

    if (i >= j) // Lower triangle (including diagonal)
    {
        int index = Index(i, j);
        m->A[index] = x;
    }
    else if (x != 0) // Upper triangle: only allow zeros
    {
        fprintf(stderr, "Cannot store non-zero value %d in upper triangle at (%d, %d)\n", x, i, j);
    }
}

int Get(const Matrix *m, int i, int j)
{
    if (i < 1 || i > m->n || j < 1 || j > m->n)
        return 0;

    // formula alternative
    /*if(i>= j){
     return m->A[m->n*(j-1) + (j-2) * (j-1) / 2+(i - j)];  
    } else return 0;*/


    if (i >= j) // Lower triangle
    {
        int index = Index(i, j);
        return m->A[index];
    }
    else // Upper triangle
    {
        return 0;
    }
}

void Display(const Matrix *m)
{
    if (IsEmpty(m))
    {
        printf("Empty matrix\n");
        return;
    }

    printf("Lower Triangular Matrix (%d×%d):\n", m->n, m->n);
    printf("Storing %d elements instead of %d\n", GetStoredElements(m->n), m->n * m->n);

    for (int i = 1; i <= m->n; i++)
    {
        for (int j = 1; j <= m->n; j++)
        {
            printf("%4d", Get(m, i, j));
        }
        printf("\n");
    }
}

// ============================================================================
// MATHEMATICAL OPERATIONS
// ============================================================================

int Trace(const Matrix *m)
{
    if (IsEmpty(m))
        return 0;

    int sum = 0;
    for (int i = 1; i <= m->n; i++)
    {
        sum += Get(m, i, i); // Sum of diagonal elements
    }
    return sum;
}

int Determinant(const Matrix *m)
{
    if (IsEmpty(m))
        return 0;

    // For triangular matrices: det = product of diagonal elements
    int det = 1;
    for (int i = 1; i <= m->n; i++)
    {
        det *= Get(m, i, i);
    }
    return det;
}

// ============================================================================
// MAIN FUNCTION - DEMONSTRATING ROW-MAJOR MAPPING
// ============================================================================

int main()
{
    printf("═══════════════════════════════════════════════════════\n");
    printf("    ABDUL BARI'S LOWER TRIANGULAR MATRIX (C VERSION)\n");
    printf("═══════════════════════════════════════════════════════\n\n");

    // ========== DEMO 1: User Input Matrix ==========
    Matrix m1;
    int i, j, x, userDim;

    printf("Enter Matrix dimensions: ");
    scanf("%d", &userDim);
    InitMatrix(&m1, userDim);  // Properly initialize with allocation
    printf("\n");

    printf("Enter lower triangular elements (row by row):\n");
    printf("(Note: Upper triangle values will be ignored)\n\n");

    for (i = 1; i <= m1.n; i++)
    {
        for (j = 1; j <= m1.n; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &x);
            Set(&m1, i, j, x);
        }
    }
    printf("\n");

    printf("Your Matrix:\n");
    Display(&m1);
    printf("\n");

    printf("Properties:\n");
    printf("  Trace: %d\n", Trace(&m1));
    printf("  Determinant: %d\n\n", Determinant(&m1));

    // Cleanup first matrix
    DestroyMatrix(&m1);

    printf("═══════════════════════════════════════════════════════\n\n");

    // ========== DEMO 2: Pre-filled Example Matrix ==========
    Matrix m2;
    InitMatrix(&m2, 5);

    printf("Pre-filled 5×5 Example Matrix:\n");
    printf("Storage needed: %d elements (instead of 25)\n\n", GetStoredElements(m2.n));

    // Fill with example values (like Abdul Bari's lecture)
    int value = 1;
    for (i = 1; i <= 5; i++)
    {
        for (j = 1; j <= i; j++)
        {
            Set(&m2, i, j, value++);
        }
    }

    printf("Matrix after filling:\n");
    Display(&m2);
    printf("\n");

    // Demonstrate the mapping
    printf("═══════════════════════════════════════════════════════\n");
    printf("    INDEX MAPPING DEMONSTRATION\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf("Formula: Index(i,j) = (i-1)i/2 + (j-1)\n\n");

    printf("Example: Element [4][3]:\n");
    printf("  → Elements before row 4: 1+2+3 = 6\n");
    printf("  → Position in row 4: 3-1 = 2\n");
    printf("  → 1D Index = 6 + 2 = 8\n");
    printf("  → Value = %d\n\n", Get(&m2, 4, 3));

    // Mathematical properties
    printf("═══════════════════════════════════════════════════════\n");
    printf("    MATRIX PROPERTIES\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf("Trace (sum of diagonal): %d\n", Trace(&m2));
    printf("Determinant: %d\n\n", Determinant(&m2));

    // Try to set upper triangle (should fail)
    printf("═══════════════════════════════════════════════════════\n");
    printf("    TESTING UPPER TRIANGLE PROTECTION\n");
    printf("═══════════════════════════════════════════════════════\n");
    Set(&m2, 2, 4, 99); // Should print error
    printf("\n");

    // Cleanup second matrix
    DestroyMatrix(&m2);

    printf("═══════════════════════════════════════════════════════\n");
    printf("    DEMO COMPLETE\n");
    printf("═══════════════════════════════════════════════════════\n");

    return 0;
}

/**
=== Lower Triangular Matrix (Row-Major) Demo ===
cd Matrices
clang -std=c17 -Wall -Wextra -o lower_tri_c LowerTriangularMatrix.c
./lower_tri_c

═══════════════════════════════════════════════════════
    ABDUL BARI'S LOWER TRIANGULAR MATRIX (C VERSION)
═══════════════════════════════════════════════════════
=== Lower Triangular Matrix (Row-Major) Demo ===
Element [1][1]: 5      ← Diagonal (any number)
Element [1][2]: 0      ← Upper triangle (MUST be 0)
Element [1][3]: 0      ← Upper triangle (MUST be 0)

Element [2][1]: 10     ← Lower triangle (any number)
Element [2][2]: 15     ← Diagonal (any number)
Element [2][3]: 0      ← Upper triangle (MUST be 0)

Element [3][1]: 20     ← Lower triangle (any number)
Element [3][2]: 25     ← Lower triangle (any number)
Element [3][3]: 30     ← Diagonal (any number)


// 5×5 matrix:
Row 1:  [1][1]=5,  [1][2]=0,  [1][3]=0,  [1][4]=0,  [1][5]=0
Row 2:  [2][1]=10, [2][2]=15, [2][3]=0,  [2][4]=0,  [2][5]=0
Row 3:  [3][1]=20, [3][2]=25, [3][3]=30, [3][4]=0,  [3][5]=0
Row 4:  [4][1]=35, [4][2]=40, [4][3]=45, [4][4]=50, [4][5]=0
Row 5:  [5][1]=55, [5][2]=60, [5][3]=65, [5][4]=70, [5][5]=75


═══════════════════════════════════════════════════════
    ABDUL BARI'S LOWER TRIANGULAR MATRIX (C VERSION)
═══════════════════════════════════════════════════════

Enter Matrix dimensions: 5

Enter lower triangular elements (row by row):
(Note: Upper triangle values will be ignored)

Element [1][1]: 5
Element [1][2]: 0
Element [1][3]: 0
Element [1][4]: 0
Element [1][5]: 10
Cannot store non-zero value 10 in upper triangle at (1, 5)
Element [2][1]: 10
Element [2][2]: 15
Element [2][3]: 0
Element [2][4]: 0
Element [2][5]: 0
Element [3][1]: 20
Element [3][2]: 25
Element [3][3]: 30
Element [3][4]: 0
Element [3][5]: 35
Cannot store non-zero value 35 in upper triangle at (3, 5)
Element [4][1]: 35
Element [4][2]: 40
Element [4][3]: 45
Element [4][4]: 50
Element [4][5]: 0
Element [5][1]: 55
Element [5][2]: 60
Element [5][3]: 65
Element [5][4]: 70
Element [5][5]: 75

Your Matrix:
Lower Triangular Matrix (5×5):
Storing 15 elements instead of 25
   5   0   0   0   0
  10  15   0   0   0
  20  25  30   0   0
  35  40  45  50   0
  55  60  65  70  75

Properties:
  Trace: 175
  Determinant: 8437500

═══════════════════════════════════════════════════════

Pre-filled 5×5 Example Matrix:
Storage needed: 15 elements (instead of 25)

Matrix after filling:
Lower Triangular Matrix (5×5):
Storing 15 elements instead of 25
   1   0   0   0   0
   2   3   0   0   0
   4   5   6   0   0
   7   8   9  10   0
  11  12  13  14  15

═══════════════════════════════════════════════════════
    INDEX MAPPING DEMONSTRATION
═══════════════════════════════════════════════════════
Formula: Index(i,j) = (i-1)i/2 + (j-1)

Example: Element [4][3]:
  → Elements before row 4: 1+2+3 = 6
  → Position in row 4: 3-1 = 2
  → 1D Index = 6 + 2 = 8
  → Value = 9

═══════════════════════════════════════════════════════
    MATRIX PROPERTIES
═══════════════════════════════════════════════════════
Trace (sum of diagonal): 35
Determinant: 2700

═══════════════════════════════════════════════════════
    TESTING UPPER TRIANGLE PROTECTION
═══════════════════════════════════════════════════════
Cannot store non-zero value 99 in upper triangle at (2, 4)

Matrix dimensions: 5×5
Storage needed: 15 elements (instead of 25)

Matrix after filling:
Lower Triangular Matrix (5×5):
   1   0   0   0   0
   2   3   0   0   0
   4   5   6   0   0
   7   8   9  10   0
  11  12  13  14  15

=== Index Mapping Demonstration ===
Formula: Index(i,j) = (i-1)i/2 + (j-1)

Element [4][3]:
  Elements before row 4: 1+2+3 = 6
  Position in row 4: 3-1 = 2
  1D Index = 6 + 2 = 8
  Value = 9

=== Matrix Properties ===
Trace (sum of diagonal): 35
Determinant: 2700
Is symmetric? No

=== Testing Upper Triangle Protection ===
Cannot store non-zero value 99 in upper triangle at (2, 4)

=== Demo Complete ===
benraiss@MacBookAir Matrices % clang -std=c17 -Wall -Wextra -o lower_tri_c LowerTriangularMatrix.c && ./lower_tri_c
═══════════════════════════════════════════════════════
    ABDUL BARI'S LOWER TRIANGULAR MATRIX (C VERSION)
═══════════════════════════════════════════════════════

Matrix dimensions: 5×5
Storage needed: 15 elements (instead of 25)

Matrix after filling:
Lower Triangular Matrix (5×5):
Storing 15 elements instead of 25
   1   0   0   0   0
   2   3   0   0   0
   4   5   6   0   0
   7   8   9  10   0
  11  12  13  14  15

═══════════════════════════════════════════════════════
    INDEX MAPPING DEMONSTRATION
═══════════════════════════════════════════════════════
Formula: Index(i,j) = (i-1)i/2 + (j-1)

Example: Element [4][3]:
  → Elements before row 4: 1+2+3 = 6
  → Position in row 4: 3-1 = 2
  → 1D Index = 6 + 2 = 8
  → Value = 9

═══════════════════════════════════════════════════════
    MATRIX PROPERTIES
═══════════════════════════════════════════════════════
Trace (sum of diagonal): 35
Determinant: 2700

═══════════════════════════════════════════════════════
    TESTING UPPER TRIANGLE PROTECTION
═══════════════════════════════════════════════════════
Cannot store non-zero value 99 in upper triangle at (2, 4)

═══════════════════════════════════════════════════════
    DEMO COMPLETE
═══════════════════════════════════════════════════════

*/



