// Sparse Matrix Implementation - Abdul Bari's Approach
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ============================================================================
// ABDUL BARI'S SPARSE MATRIX - COMPLETE IMPLEMENTATION
// ============================================================================
/*
 * SPARSE MATRIX DEFINITION:
 * A matrix is sparse if: Number of ZERO elements >> Number of NON-ZERO elements
 *
 * Example (4×5 matrix with 6 non-zero elements):
 *
 * [ 0  0  3  0  4 ]
 * [ 0  0  5  7  0 ]
 * [ 0  0  0  0  0 ]
 * [ 0  2  6  0  0 ]
 *
 * Total: 20 elements, Non-zero: 6 (30%), Zero: 14 (70%) → SPARSE!
 *
 * WHY NOT STORE AS NORMAL MATRIX?
 *  Memory Waste: Storing 14 zeros
 *  Time Waste: Processing zeros in operations
 *
 * SOLUTION: Store only (row, column, value) tuples for non-zero elements
 *
 * TWO REPRESENTATIONS:
 * 1. Array Representation (3-tuple / Triplet form)
 * 2. Linked List Representation (Dynamic)
 */

// ============================================================================
// METHOD 1: ARRAY REPRESENTATION (3-TUPLE FORM)
// ============================================================================
/*
 * STRUCTURE:
 * Store sparse matrix as 2D array of size [3][K]
 * where K = number of non-zero elements
 *
 * Row 0: Row indices
 * Row 1: Column indices
 * Row 2: Values
 *
 * Example:
 *   Row:    [ 0  0  1  1  3  3 ]
 *   Col:    [ 2  4  2  3  1  2 ]
 *   Value:  [ 3  4  5  7  2  6 ]
 *
 * Space Complexity: O(K) where K = non-zero count
 * Time to create: O(M×N) - must scan entire original matrix
 */

typedef struct ArraySparseMatrix
{
    int rows;         // Original matrix rows
    int cols;         // Original matrix columns
    int nonZeroCount; // Number of non-zero elements
    int **elements;   // 2D array [3][nonZeroCount]
} ArraySparseMatrix;

// Count non-zero elements in matrix
int CountNonZero(int **matrix, int rows, int cols)
{
    int count = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                count++;
            }
        }
    }
    return count;
}

// Create sparse matrix from regular matrix (Array representation)
ArraySparseMatrix *CreateArraySparse(int **matrix, int rows, int cols)
{
    // Allocate sparse matrix structure
    ArraySparseMatrix *sparse = (ArraySparseMatrix *)malloc(sizeof(ArraySparseMatrix));

    sparse->rows = rows;
    sparse->cols = cols;
    sparse->nonZeroCount = CountNonZero(matrix, rows, cols);

    // Allocate 3 rows for [row indices, col indices, values]
    sparse->elements = (int **)malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++)
    {
        sparse->elements[i] = (int *)malloc(sparse->nonZeroCount * sizeof(int));
    }

    // Fill sparse matrix with non-zero elements
    int k = 0; // Index for non-zero elements
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                sparse->elements[0][k] = i;            // Row index
                sparse->elements[1][k] = j;            // Column index
                sparse->elements[2][k] = matrix[i][j]; // Value
                k++;
            }
        }
    }

    return sparse;
}

// Display array sparse matrix
void DisplayArraySparse(ArraySparseMatrix *sparse)
{
    printf("\n═══════════════════════════════════════════════════════\n");
    printf("    SPARSE MATRIX (ARRAY REPRESENTATION)\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf("Original size: %d×%d = %d elements\n",
           sparse->rows, sparse->cols, sparse->rows * sparse->cols);
    printf("Non-zero elements: %d\n", sparse->nonZeroCount);
    printf("Space saved: %.1f%%\n\n",
           (1.0 - (float)sparse->nonZeroCount / (sparse->rows * sparse->cols)) * 100);

    printf("3-Tuple Format:\n");
    printf("Row:   ");
    for (int i = 0; i < sparse->nonZeroCount; i++)
    {
        printf("%3d ", sparse->elements[0][i]);
    }
    printf("\nCol:   ");
    for (int i = 0; i < sparse->nonZeroCount; i++)
    {
        printf("%3d ", sparse->elements[1][i]);
    }
    printf("\nValue: ");
    for (int i = 0; i < sparse->nonZeroCount; i++)
    {
        printf("%3d ", sparse->elements[2][i]);
    }
    printf("\n\n");

    // Reconstruct and display original matrix
    printf("Reconstructed Matrix:\n");
    for (int i = 0; i < sparse->rows; i++)
    {
        for (int j = 0; j < sparse->cols; j++)
        {
            int found = 0;
            for (int k = 0; k < sparse->nonZeroCount; k++)
            {
                if (sparse->elements[0][k] == i && sparse->elements[1][k] == j)
                {
                    printf("%3d ", sparse->elements[2][k]);
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                printf("  0 ");
            }
        }
        printf("\n");
    }
}

// Free array sparse matrix
void FreeArraySparse(ArraySparseMatrix *sparse)
{
    for (int i = 0; i < 3; i++)
    {
        free(sparse->elements[i]);
    }
    free(sparse->elements);
    free(sparse);
}

// ============================================================================
// SPARSE MATRIX ADDITION (Array Representation)
// ============================================================================
/*
 * ALGORITHM (Abdul Bari's Method):
 * Given: Two sparse matrices A and B (same dimensions)
 *
 * 1. Compare elements from A and B by (row, col) position
 * 2. If positions match → add values
 * 3. If A comes first → include A's element
 * 4. If B comes first → include B's element
 *
 * Time Complexity: O(K1 + K2) where K1, K2 are non-zero counts
 */

ArraySparseMatrix *AddArraySparse(ArraySparseMatrix *A, ArraySparseMatrix *B)
{
    // Check dimensions
    if (A->rows != B->rows || A->cols != B->cols)
    {
        printf("Error: Matrix dimensions must match for addition\n");
        return NULL;
    }

    // Allocate result (max possible non-zeros)
    ArraySparseMatrix *result = (ArraySparseMatrix *)malloc(sizeof(ArraySparseMatrix));
    result->rows = A->rows;
    result->cols = A->cols;

    int maxNonZero = A->nonZeroCount + B->nonZeroCount;
    result->elements = (int **)malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++)
    {
        result->elements[i] = (int *)malloc(maxNonZero * sizeof(int));
    }

    int i = 0, j = 0, k = 0; // Pointers for A, B, result

    while (i < A->nonZeroCount && j < B->nonZeroCount)
    {
        int rowA = A->elements[0][i];
        int colA = A->elements[1][i];
        int rowB = B->elements[0][j];
        int colB = B->elements[1][j];

        // Compare positions (row-major order)
        if (rowA < rowB || (rowA == rowB && colA < colB))
        {
            // A comes first
            result->elements[0][k] = rowA;
            result->elements[1][k] = colA;
            result->elements[2][k] = A->elements[2][i];
            i++;
            k++;
        }
        else if (rowA > rowB || (rowA == rowB && colA > colB))
        {
            // B comes first
            result->elements[0][k] = rowB;
            result->elements[1][k] = colB;
            result->elements[2][k] = B->elements[2][j];
            j++;
            k++;
        }
        else
        {
            // Same position: add values
            int sum = A->elements[2][i] + B->elements[2][j];
            if (sum != 0)
            { // Only store if non-zero
                result->elements[0][k] = rowA;
                result->elements[1][k] = colA;
                result->elements[2][k] = sum;
                k++;
            }
            i++;
            j++;
        }
    }

    // Copy remaining elements from A
    while (i < A->nonZeroCount)
    {
        result->elements[0][k] = A->elements[0][i];
        result->elements[1][k] = A->elements[1][i];
        result->elements[2][k] = A->elements[2][i];
        i++;
        k++;
    }

    // Copy remaining elements from B
    while (j < B->nonZeroCount)
    {
        result->elements[0][k] = B->elements[0][j];
        result->elements[1][k] = B->elements[1][j];
        result->elements[2][k] = B->elements[2][j];
        j++;
        k++;
    }

    result->nonZeroCount = k;
    return result;
}

// ============================================================================
// SPARSE MATRIX TRANSPOSE (Array Representation)
// ============================================================================
/*
 * SIMPLE METHOD:
 * 1. Swap row ↔ column indices
 * 2. Sort by new (row, col) positions
 *
 * Time: O(K log K) due to sorting
 *
 * ABDUL BARI'S FAST METHOD:
 * 1. Count non-zeros in each column
 * 2. Calculate starting positions for each column
 * 3. Place elements directly in correct position
 *
 * Time: O(K + N) - Single pass!
 */

ArraySparseMatrix *TransposeArraySparse(ArraySparseMatrix *sparse)
{
    ArraySparseMatrix *result = (ArraySparseMatrix *)malloc(sizeof(ArraySparseMatrix));

    // Transpose dimensions
    result->rows = sparse->cols;
    result->cols = sparse->rows;
    result->nonZeroCount = sparse->nonZeroCount;

    // Allocate result
    result->elements = (int **)malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++)
    {
        result->elements[i] = (int *)malloc(result->nonZeroCount * sizeof(int));
    }

    // Fast transpose using Abdul Bari's method
    int *colCount = (int *)calloc(sparse->cols, sizeof(int));
    int *colPosition = (int *)malloc(sparse->cols * sizeof(int));

    // Step 1: Count elements in each column
    for (int i = 0; i < sparse->nonZeroCount; i++)
    {
        colCount[sparse->elements[1][i]]++;
    }

    // Step 2: Calculate starting positions
    colPosition[0] = 0;
    for (int i = 1; i < sparse->cols; i++)
    {
        colPosition[i] = colPosition[i - 1] + colCount[i - 1];
    }

    // Step 3: Place elements in result
    for (int i = 0; i < sparse->nonZeroCount; i++)
    {
        int col = sparse->elements[1][i];
        int pos = colPosition[col];

        result->elements[0][pos] = sparse->elements[1][i]; // col → row
        result->elements[1][pos] = sparse->elements[0][i]; // row → col
        result->elements[2][pos] = sparse->elements[2][i]; // value

        colPosition[col]++;
    }

    free(colCount);
    free(colPosition);

    return result;
}

// ============================================================================
// METHOD 2: LINKED LIST REPRESENTATION
// ============================================================================
/*
 * STRUCTURE:
 * Each non-zero element is a node with (row, col, value, next)
 *
 * Advantages:
 *  Dynamic size
 *  Easy insertion/deletion
 *  No memory waste
 *
 * Disadvantages:
 *  Extra memory for pointers
 *  Slower traversal than array
 *  Cache-unfriendly
 */

typedef struct Node
{
    int row;
    int col;
    int value;
    struct Node *next;
} Node;

typedef struct LinkedSparseMatrix
{
    int rows;
    int cols;
    int nonZeroCount;
    Node *head;
} LinkedSparseMatrix;

// Create node
Node *CreateNode(int row, int col, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Create sparse matrix from regular matrix (Linked List)
LinkedSparseMatrix *CreateLinkedSparse(int **matrix, int rows, int cols)
{
    LinkedSparseMatrix *sparse = (LinkedSparseMatrix *)malloc(sizeof(LinkedSparseMatrix));
    sparse->rows = rows;
    sparse->cols = cols;
    sparse->nonZeroCount = 0;
    sparse->head = NULL;

    Node *tail = NULL;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                Node *newNode = CreateNode(i, j, matrix[i][j]);

                if (sparse->head == NULL)
                {
                    sparse->head = newNode;
                    tail = newNode;
                }
                else
                {
                    tail->next = newNode;
                    tail = newNode;
                }

                sparse->nonZeroCount++;
            }
        }
    }

    return sparse;
}

// Display linked sparse matrix
void DisplayLinkedSparse(LinkedSparseMatrix *sparse)
{
    printf("\n═══════════════════════════════════════════════════════\n");
    printf("    SPARSE MATRIX (LINKED LIST REPRESENTATION)\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf("Original size: %d×%d = %d elements\n",
           sparse->rows, sparse->cols, sparse->rows * sparse->cols);
    printf("Non-zero elements: %d\n", sparse->nonZeroCount);
    printf("Memory overhead: %d pointers\n\n", sparse->nonZeroCount);

    printf("Node List Format:\n");
    printf("(row, col, value) → \n");

    Node *current = sparse->head;
    while (current != NULL)
    {
        printf("(%d, %d, %d) → ", current->row, current->col, current->value);
        current = current->next;
    }
    printf("NULL\n\n");

    // Reconstruct matrix
    printf("Reconstructed Matrix:\n");
    for (int i = 0; i < sparse->rows; i++)
    {
        for (int j = 0; j < sparse->cols; j++)
        {
            Node *temp = sparse->head;
            int found = 0;

            while (temp != NULL)
            {
                if (temp->row == i && temp->col == j)
                {
                    printf("%3d ", temp->value);
                    found = 1;
                    break;
                }
                temp = temp->next;
            }

            if (!found)
            {
                printf("  0 ");
            }
        }
        printf("\n");
    }
}

// Free linked sparse matrix
void FreeLinkedSparse(LinkedSparseMatrix *sparse)
{
    Node *current = sparse->head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(sparse);
}

// ============================================================================
// MAIN FUNCTION - DEMONSTRATION
// ============================================================================

int main()
{
    printf("═══════════════════════════════════════════════════════\n");
    printf("    ABDUL BARI'S SPARSE MATRIX - COMPLETE DEMO\n");
    printf("═══════════════════════════════════════════════════════\n\n");

    // Create example sparse matrix (4×5)
    int rows = 4, cols = 5;
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // Initialize sparse matrix
    int data[4][5] = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0}};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = data[i][j];
        }
    }

    printf("Original Matrix (4×5):\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Method 1: Array Representation
    ArraySparseMatrix *arraySparse = CreateArraySparse(matrix, rows, cols);
    DisplayArraySparse(arraySparse);

    // Method 2: Linked List Representation
    LinkedSparseMatrix *linkedSparse = CreateLinkedSparse(matrix, rows, cols);
    DisplayLinkedSparse(linkedSparse);

    // Demonstrate Transpose
    printf("\n═══════════════════════════════════════════════════════\n");
    printf("    TRANSPOSE OPERATION\n");
    printf("═══════════════════════════════════════════════════════\n");

    ArraySparseMatrix *transposed = TransposeArraySparse(arraySparse);
    DisplayArraySparse(transposed);

    // Demonstrate Addition
    printf("\n═══════════════════════════════════════════════════════\n");
    printf("    ADDITION OPERATION\n");
    printf("═══════════════════════════════════════════════════════\n");

    // Create second matrix for addition
    int **matrix2 = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix2[i] = (int *)malloc(cols * sizeof(int));
    }

    int data2[4][5] = {
        {0, 0, 1, 0, 0},
        {0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0}};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix2[i][j] = data2[i][j];
        }
    }

    printf("\nSecond Matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%3d ", matrix2[i][j]);
        }
        printf("\n");
    }

    ArraySparseMatrix *arraySparse2 = CreateArraySparse(matrix2, rows, cols);
    ArraySparseMatrix *sum = AddArraySparse(arraySparse, arraySparse2);

    printf("\nResult of Addition:\n");
    DisplayArraySparse(sum);

    // Cleanup
    FreeArraySparse(arraySparse);
    FreeArraySparse(arraySparse2);
    FreeArraySparse(transposed);
    FreeArraySparse(sum);
    FreeLinkedSparse(linkedSparse);

    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
        free(matrix2[i]);
    }
    free(matrix);
    free(matrix2);

    printf("\n═══════════════════════════════════════════════════════\n");
    printf("    DEMO COMPLETE\n");
    printf("═══════════════════════════════════════════════════════\n");

    return 0;
}

/*
═══════════════════════════════════════════════════════
KEY TAKEAWAYS (ABDUL BARI'S PERSPECTIVE)
═══════════════════════════════════════════════════════

1. DEFINITION:
   Sparse matrix: zeros >> non-zeros (typically >70% zeros)

2. WHY SPARSE REPRESENTATION?
    Space: O(K) instead of O(M×N) where K << M×N
    Time: Operations skip zeros
    Real-world: Social networks, text mining, scientific computing

3. ARRAY vs LINKED LIST:
   Array:      Fast access, fixed size, cache-friendly
   Linked:     Dynamic, easy insertion, pointer overhead

4. OPERATIONS:
   Addition:   O(K1 + K2) - merge algorithm
   Transpose:  O(K + N) - fast method with counting

5. TIME COMPLEXITIES:
   Create:     O(M×N) - must scan original matrix
   Access:     O(K) worst case - linear search
   Space:      O(K) - only non-zeros

6. INTERVIEW GOLD:
   - Always mention sparse threshold (70-80%)
   - Explain 3-tuple format clearly
   - Compare array vs linked trade-offs
   - Know fast transpose algorithm
   - Connect to real applications (graphs, ML)

═══════════════════════════════════════════════════════
COMPILE & RUN:
═══════════════════════════════════════════════════════
cd /Users/benraiss/Documents/data-structures-c-cpp/Matrices && clang -std=c17 -Wall -Wextra -o sparse SparseMatrix.c && ./sparse

clang -std=c17 -Wall -Wextra -o sparse SparseMatrix.c
./sparse





Original Matrix (4×5):
  0   0   3   0   4
  0   0   5   7   0
  0   0   0   0   0
  0   2   6   0   0

═══════════════════════════════════════════════════════
    SPARSE MATRIX (ARRAY REPRESENTATION)
═══════════════════════════════════════════════════════
Original size: 4×5 = 20 elements
Non-zero elements: 6
Space saved: 70.0%

3-Tuple Format:
Row:     0   0   1   1   3   3
Col:     2   4   2   3   1   2
Value:   3   4   5   7   2   6

Reconstructed Matrix:
  0   0   3   0   4
  0   0   5   7   0
  0   0   0   0   0
  0   2   6   0   0

═══════════════════════════════════════════════════════
    SPARSE MATRIX (LINKED LIST REPRESENTATION)
═══════════════════════════════════════════════════════
Original size: 4×5 = 20 elements
Non-zero elements: 6
Memory overhead: 6 pointers

Node List Format:
(row, col, value) →
(0, 2, 3) → (0, 4, 4) → (1, 2, 5) → (1, 3, 7) → (3, 1, 2) → (3, 2, 6) → NULL

Reconstructed Matrix:
  0   0   3   0   4
  0   0   5   7   0
  0   0   0   0   0
  0   2   6   0   0

═══════════════════════════════════════════════════════
    TRANSPOSE OPERATION
═══════════════════════════════════════════════════════

═══════════════════════════════════════════════════════
    SPARSE MATRIX (ARRAY REPRESENTATION)
═══════════════════════════════════════════════════════
Original size: 5×4 = 20 elements
Non-zero elements: 6
Space saved: 70.0%

3-Tuple Format:
Row:     1   2   2   2   3   4
Col:     3   0   1   3   1   0
Value:   2   3   5   6   7   4

Reconstructed Matrix:
  0   0   0   0
  0   0   0   2
  3   5   0   6
  0   7   0   0
  4   0   0   0

═══════════════════════════════════════════════════════
    ADDITION OPERATION
═══════════════════════════════════════════════════════

Second Matrix:
  0   0   1   0   0
  0   0   0   3   0
  0   0   0   0   0
  0   1   0   0   0

Result of Addition:

═══════════════════════════════════════════════════════
    SPARSE MATRIX (ARRAY REPRESENTATION)
═══════════════════════════════════════════════════════
Original size: 4×5 = 20 elements
Non-zero elements: 6
Space saved: 70.0%

3-Tuple Format:
Row:     0   0   1   1   3   3
Col:     2   4   2   3   1   2
Value:   4   4   5  10   3   6

Reconstructed Matrix:
  0   0   4   0   4
  0   0   5  10   0
  0   0   0   0   0
  0   3   6   0   0
*/
