#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 20

int d[MAX_N];           // Dimension array
int n;                  // Number of matrices
int callCount = 0;      // Track recursion calls (for analysis)

// ============================================================================
// MATRIX CHAIN MULTIPLICATION - PURE RECURSION
// ============================================================================

/*
 * Problem: Find minimum number of scalar multiplications needed to compute
 * the product of matrices A[i] × A[i+1] × ... × A[j]
 * 
 * State: m[i][j] = minimum cost to multiply matrices from i to j
 * Base: m[i][i] = 0 (single matrix needs no multiplication)
 * 
 * Recurrence:
 * m[i][j] = min over k=i to j-1 of {
 *           m[i][k] + m[k+1][j] + d[i-1] * d[k] * d[j]
 *           }
 * 
 * where:
 *   m[i][k] = cost to multiply left subproblem
 *   m[k+1][j] = cost to multiply right subproblem
 *   d[i-1]*d[k]*d[j] = cost to merge the two results
 */

int matrixChainCost(int i, int j) {
    callCount++;
    
    // Base case: single matrix requires no multiplication
    if (i == j) {
        return 0;
    }
    
    int minCost = INT_MAX;
    
    // Try all possible split points k
    for (int k = i; k < j; k++) {
        
        // Cost of multiplying matrices from i to k
        int leftCost = matrixChainCost(i, k);
        
        // Cost of multiplying matrices from k+1 to j
        int rightCost = matrixChainCost(k + 1, j);
        
        // Cost of multiplying the two results:
        // Left result: d[i-1] × d[k] matrix
        // Right result: d[k] × d[j] matrix
        // Multiplying them costs: d[i-1] * d[k] * d[j] scalar multiplications
        int mergeCost = d[i-1] * d[k] * d[j];
        
        // Total cost for this split point
        int totalCost = leftCost + rightCost + mergeCost;
        
        // Keep track of minimum
        if (totalCost < minCost) {
            minCost = totalCost;
        }
    }
    
    return minCost;
}

// ============================================================================
// Debug version: trace recursion calls (educational)
// ============================================================================

void matrixChainCostTrace(int i, int j, int depth) {
    
    // Indentation for tree visualization
    for (int d = 0; d < depth; d++) printf("  ");
    printf("m(%d,%d)", i, j);
    
    if (i == j) {
        printf(" → 0 (base case)\n");
        return;
    }
    
    printf("\n");
    
    int minCost = INT_MAX;
    int bestK = i;
    
    for (int k = i; k < j; k++) {
        int leftCost = matrixChainCost(i, k);
        int rightCost = matrixChainCost(k + 1, j);
        int mergeCost = d[i-1] * d[k] * d[j];
        int totalCost = leftCost + rightCost + mergeCost;
        
        if (totalCost < minCost) {
            minCost = totalCost;
            bestK = k;
        }
    }
    
    for (int d = 0; d < depth; d++) printf("  ");
    printf("  → split at k=%d, cost=%d\n", bestK, minCost);
}

// ============================================================================
// Dimension Setup Helpers
// ============================================================================

void setupDimensions(int numMatrices, int dims[]) {
    n = numMatrices;
    for (int i = 0; i <= n; i++) {
        d[i] = dims[i];
    }
}

void printMatrixDimensions() {
    printf("\n📐 Matrix Dimensions:\n");
    for (int i = 0; i < n; i++) {
        printf("   A[%d]: %d × %d\n", i+1, d[i], d[i+1]);
    }
    printf("\n   Dimension array: d = [");
    for (int i = 0; i <= n; i++) {
        printf("%d%s", d[i], i < n ? ", " : "");
    }
    printf("]\n");
}

// ============================================================================
// TEST CASES
// ============================================================================

void test_case_1() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║    TEST CASE 1: Simple 4-Matrix Example (From Lecture)        ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    int dims[] = {3, 2, 4, 2, 5};
    setupDimensions(4, dims);
    
    /*
     * A₁: 3×2
     * A₂: 2×4
     * A₃: 4×2
     * A₄: 2×5
     */
    
    printMatrixDimensions();
    
    printf("\n🔍 Computing: m[1][4] (minimum cost to multiply A[1]×A[2]×A[3]×A[4])\n");
    
    callCount = 0;
    int result = matrixChainCost(1, 4);
    
    printf("\n✅ Minimum Cost: %d scalar multiplications\n", result);
    printf("   Recursive calls made: %d\n", callCount);
    
    printf("\n📊 Manual verification of some subproblems:\n");
    printf("   m[2][3] = 2×4×2 = 16\n");
    printf("   m[3][4] = 4×2×5 = 40\n");
    printf("   m[1][2] = 3×2×4 = 24\n");
}

void test_case_2() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║      TEST CASE 2: Small Example (3 Matrices)                  ║\n");
    printf("║           Shows Exhaustive Split Evaluation                   ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    int dims[] = {1, 2, 3, 4};
    setupDimensions(3, dims);
    
    /*
     * A₁: 1×2
     * A₂: 2×3
     * A₃: 3×4
     */
    
    printMatrixDimensions();
    
    printf("\n🔍 Computing: m[1][3] (minimum cost to multiply A[1]×A[2]×A[3])\n");
    printf("\nManual calculation:\n");
    
    printf("   Split at k=1:\n");
    printf("     m[1][1] = 0\n");
    printf("     m[2][3] = 2×3×4 = 24\n");
    printf("     merge = 1×2×4 = 8\n");
    printf("     total = 0 + 24 + 8 = 32\n");
    
    printf("\n   Split at k=2:\n");
    printf("     m[1][2] = 1×2×3 = 6\n");
    printf("     m[3][3] = 0\n");
    printf("     merge = 1×3×4 = 12\n");
    printf("     total = 6 + 0 + 12 = 18 ✓ (minimum)\n");
    
    callCount = 0;
    int result = matrixChainCost(1, 3);
    
    printf("\n✅ Algorithm Result: %d\n", result);
    printf("   Recursive calls: %d\n", callCount);
    printf("   Optimal parenthesization: (A[1] × A[2]) × A[3]\n");
}

void test_case_3() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║     TEST CASE 3: Larger Problem (5 Matrices)                  ║\n");
    printf("║        Notice the Explosion of Recursive Calls!               ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    int dims[] = {2, 3, 4, 5, 2, 6};
    setupDimensions(5, dims);
    
    /*
     * A₁: 2×3
     * A₂: 3×4
     * A₃: 4×5
     * A₄: 5×2
     * A₅: 2×6
     */
    
    printMatrixDimensions();
    
    callCount = 0;
    int result = matrixChainCost(1, 5);
    
    printf("\n✅ Minimum Cost: %d\n", result);
    printf("   Recursive calls made: %d\n", callCount);
    
    printf("\n⚠️  WARNING: See how many calls we made?\n");
    printf("   For just 5 matrices, we need %d function calls!\n", callCount);
    printf("   For 10 matrices, we'd need ~millions of calls.\n");
    printf("   For 15 matrices, ~billions of calls.\n");
    printf("   This is why pure recursion is IMPRACTICAL.\n");
}

void test_case_4() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║  TEST CASE 4: COMPARE DIFFERENT PARENTHESIZATIONS (n=4)      ║\n");
    printf("║              Shows that different orderings have vastly       ║\n");
    printf("║              different costs (though we find the optimum)     ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    int dims[] = {5, 10, 3, 12, 5};
    setupDimensions(4, dims);
    
    /*
     * A₁: 5×10
     * A₂: 10×3
     * A₃: 3×12
     * A₄: 12×5
     */
    
    printMatrixDimensions();
    
    printf("\nManual parenthesization costs:\n");
    
    printf("\n   Option 1: ((A[1]×A[2])×A[3])×A[4]\n");
    printf("     A[1]×A[2]: 5×10×3 = 150 → 5×3\n");
    printf("     (AB)×A[3]: 5×3×12 = 180 → 5×12\n");
    printf("     (AB×C)×A[4]: 5×12×5 = 300 → 5×5\n");
    printf("     Total: 150 + 180 + 300 = 630\n");
    
    printf("\n   Option 2: (A[1]×(A[2]×A[3]))×A[4]\n");
    printf("     A[2]×A[3]: 10×3×12 = 360 → 10×12\n");
    printf("     A[1]×(BC): 5×10×12 = 600 → 5×12\n");
    printf("     (A×BC)×A[4]: 5×12×5 = 300 → 5×5\n");
    printf("     Total: 360 + 600 + 300 = 1260\n");
    
    printf("\n   Option 3: A[1]×((A[2]×A[3])×A[4])\n");
    printf("     A[2]×A[3]: 10×3×12 = 360 → 10×12\n");
    printf("     (BC)×A[4]: 10×12×5 = 600 → 10×5\n");
    printf("     A[1]×(BC×D): 5×10×5 = 250 → 5×5\n");
    printf("     Total: 360 + 600 + 250 = 1210\n");
    
    callCount = 0;
    int result = matrixChainCost(1, 4);
    
    printf("\n✅ Algorithm finds MINIMUM: %d (Option 1 is optimal)\n", result);
    printf("   Recursive calls: %d\n", callCount);
}

void test_case_5() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║        TEST CASE 5: Edge Case (Just 2 Matrices)               ║\n");
    printf("║              No split needed, direct computation              ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    int dims[] = {10, 20, 30};
    setupDimensions(2, dims);
    
    /*
     * A₁: 10×20
     * A₂: 20×30
     */
    
    printMatrixDimensions();
    
    printf("\nWith just 2 matrices, there's only one way to multiply:\n");
    printf("   A[1] × A[2] = (10×20) × (20×30)\n");
    printf("   Cost = 10 × 20 × 30 = 6000\n");
    
    callCount = 0;
    int result = matrixChainCost(1, 2);
    
    printf("\n✅ Algorithm Result: %d\n", result);
    printf("   Recursive calls: %d (minimal, just one split tried)\n", callCount);
}

// ============================================================================
// ANALYSIS: Show Recursion Tree Explosion
// ============================================================================

void analyzeRecursionGrowth() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║        RECURSION ANALYSIS: How Fast Does It Explode?         ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    printf("\nCalling matrixChainCost(1, n) for different n:\n");
    printf("(with simple dimension array d = [1,2,3,4,5,...])\n\n");
    
    int results[9][3] = {0};  // [n][calls, time_estimate, feasible]
    
    for (int numMat = 2; numMat <= 10; numMat++) {
        int dims[11];
        for (int i = 0; i <= numMat; i++) {
            dims[i] = i + 1;
        }
        
        setupDimensions(numMat, dims);
        callCount = 0;
        
        int cost = matrixChainCost(1, numMat);
        
        printf("n = %2d:  Cost = %10d,  Calls = %10d", numMat, cost, callCount);
        
        if (callCount > 10000000) {
            printf("  ⚠️  INFEASIBLE\n");
        } else if (callCount > 1000000) {
            printf("  ⚠️  slow\n");
        } else if (callCount > 10000) {
            printf("  (slow)\n");
        } else {
            printf("  ✓\n");
        }
    }
    
    printf("\n⚠️  Notice the EXPONENTIAL GROWTH!\n");
    printf("   This is why pure recursion fails for n > 12 or so.\n");
    printf("   This is EXACTLY why we need DP (memoization or tabulation).\n");
}

// ============================================================================
// MAIN: RUN ALL TESTS
// ============================================================================

int main() {
    printf("\n");
    printf("╔═════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                 ║\n");
    printf("║       MATRIX CHAIN MULTIPLICATION — RECURSION APPROACH          ║\n");
    printf("║                                                                 ║\n");
    printf("║          Teaching: Optimal Substructure & Overlapping SP        ║\n");
    printf("║                                                                 ║\n");
    printf("╚═════════════════════════════════════════════════════════════════╝\n");
    
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    analyzeRecursionGrowth();
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    KEY INSIGHTS DEMONSTRATED                   ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                ║\n");
    printf("║ 1️⃣  Optimal Substructure                                        ║\n");
    printf("║    Optimal solution = optimal subproblems + merge cost         ║\n");
    printf("║                                                                ║\n");
    printf("║ 2️⃣  Overlapping Subproblems                                    ║\n");
    printf("║    Many subproblems are computed MULTIPLE TIMES                ║\n");
    printf("║    That's where the exponential explosion comes from           ║\n");
    printf("║                                                                ║\n");
    printf("║ 3️⃣  Why Pure Recursion Fails                                   ║\n");
    printf("║    Time Complexity ≈ O(4^n / n^1.5)                           ║\n");
    printf("║    For n=5: ~100 calls                                         ║\n");
    printf("║    For n=10: ~millions of calls                                ║\n");
    printf("║    For n=15: ~billions of calls (INFEASIBLE)                   ║\n");
    printf("║                                                                ║\n");
    printf("║ 4️⃣  Why DP Works                                               ║\n");
    printf("║    Only O(n²) distinct subproblems exist                       ║\n");
    printf("║    Each computed once (with memoization/tabulation)            ║\n");
    printf("║    Time becomes O(n³)                                          ║\n");
    printf("║                                                                ║\n");
    printf("║ 5️⃣  The DP Recognition Pattern                                ║\n");
    printf("║    State: m[i][j] = optimal cost for range [i,j]              ║\n");
    printf("║    Recurrence: try all split points k                          ║\n");
    printf("║    This pattern appears in MANY problems (see guide)           ║\n");
    printf("║                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    return 0;
}
