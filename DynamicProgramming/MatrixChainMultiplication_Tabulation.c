#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX_N 20

int d[MAX_N];           // dimension array
int M[MAX_N][MAX_N];    // cost table
int K[MAX_N][MAX_N];    // split index table (for reconstruction)
int n;                  // number of matrices

// ============================================================================
// MATRIX CHAIN MULTIPLICATION - TABULATION (BOTTOM-UP DP)
// ============================================================================

/*
 * Problem: Find minimum number of scalar multiplications needed to compute
 * the product of matrices A[i] × A[i+1] × ... × A[j]
 * 
 * DP Approach (Tabulation/Bottom-Up):
 * 
 * State: M[i][j] = minimum cost to multiply matrices from i to j
 * Base: M[i][i] = 0 (single matrix needs no multiplication)
 * 
 * Recurrence:
 * M[i][j] = min over k=i to j-1 of {
 *           M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j]
 *           }
 * 
 * Fill Order: By chain length (j - i)
 * This ensures that when computing M[i][j], all dependencies
 * M[i][k] and M[k+1][j] are already computed.
 * 
 * Time Complexity: O(n³)
 * Space Complexity: O(n²)
 */

void matrixChainTabulation() {
    
    // Step 1: Initialize base cases
    // A single matrix requires no multiplication
    for (int i = 1; i <= n; i++) {
        M[i][i] = 0;
    }
    
    // Step 2: Fill table by chain length
    // chainLen = j - i (the span we're considering)
    // We iterate through increasing chain lengths to ensure
    // that dependencies are computed before they're needed
    
    for (int chainLen = 2; chainLen <= n; chainLen++) {
        
        for (int i = 1; i <= n - chainLen + 1; i++) {
            int j = i + chainLen - 1;  // right endpoint
            
            M[i][j] = INT_MAX;
            
            // Try all possible split points
            // Split at k means: (A_i...A_k) × (A_{k+1}...A_j)
            for (int k = i; k < j; k++) {
                
                // Cost of left part: M[i][k]
                // Cost of right part: M[k+1][j]
                // Cost of multiplying results: d[i-1] × d[k] × d[j]
                //   Left result has dimensions: d[i-1] × d[k]
                //   Right result has dimensions: d[k] × d[j]
                //   Multiplying costs: d[i-1] × d[k] × d[j]
                int cost = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
                
                // Keep track of minimum cost and which k achieved it
                if (cost < M[i][j]) {
                    M[i][j] = cost;
                    K[i][j] = k;  // Store split point for reconstruction
                }
            }
        }
    }
}

// ============================================================================
// PRETTY PRINTING TABLES
// ============================================================================

void printTables() {
    printf("\n📊 DP Cost Table M[i][j]:\n\n");
    
    // Header row
    printf("i\\j  ");
    for (int j = 1; j <= n; j++) {
        printf("%8d", j);
    }
    printf("\n");
    printf("────");
    for (int j = 1; j <= n; j++) {
        printf("────────");
    }
    printf("\n");
    
    // Table rows
    for (int i = 1; i <= n; i++) {
        printf("%2d   ", i);
        for (int j = 1; j <= n; j++) {
            if (i > j) {
                printf("       -");  // Lower triangle not used
            } else if (M[i][j] == INT_MAX) {
                printf("       ?");  // Not computed
            } else {
                printf("%8d", M[i][j]);
            }
        }
        printf("\n");
    }
    
    printf("\n📊 Split Index Table K[i][j] (for reconstruction):\n\n");
    
    // Header row
    printf("i\\j  ");
    for (int j = 1; j <= n; j++) {
        printf("%8d", j);
    }
    printf("\n");
    printf("────");
    for (int j = 1; j <= n; j++) {
        printf("────────");
    }
    printf("\n");
    
    // Table rows
    for (int i = 1; i <= n; i++) {
        printf("%2d   ", i);
        for (int j = 1; j <= n; j++) {
            if (i > j) {
                printf("       -");
            } else if (i == j) {
                printf("       -");  // Base case, no split
            } else {
                printf("%8d", K[i][j]);
            }
        }
        printf("\n");
    }
}

// ============================================================================
// RECONSTRUCT OPTIMAL PARENTHESIZATION
// ============================================================================

void printOptimalOrder(int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalOrder(i, K[i][j]);
        printf(" × ");
        printOptimalOrder(K[i][j] + 1, j);
        printf(")");
    }
}

// ============================================================================
// TEST CASES
// ============================================================================

void test_case_1() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║    TEST CASE 1: 4-Matrix Example (From Lecture)               ║\n");
    printf("║              Detailed Table Filling Shown                     ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    n = 4;
    d[0] = 3;  d[1] = 2;  d[2] = 4;  d[3] = 2;  d[4] = 5;
    
    printf("\n📐 Setup:\n");
    printf("   Matrices: A₁(3×2), A₂(2×4), A₃(4×2), A₄(2×5)\n");
    printf("   Dimension: d = [3, 2, 4, 2, 5]\n");
    
    matrixChainTabulation();
    
    printf("\n✅ Answer: M[1][%d] = %d scalar multiplications\n", n, M[1][n]);
    
    printTables();
    
    printf("\n🔍 Optimal Parenthesization: ");
    printOptimalOrder(1, n);
    printf("\n");
    
    printf("\nVerification:\n");
    printf("   Meaning of K table:\n");
    printf("   K[1][4]=%d → Split A₁...A₄ into (A₁...A%d) × (A%d...A₄)\n", K[1][4], K[1][4], K[1][4]+1);
    printf("   K[1][3]=%d → Split A₁...A₃ into (A₁...A%d) × (A%d...A₃)\n", K[1][3], K[1][3], K[1][3]+1);
    printf("   K[2][3]=%d → Split A₂...A₃ into (A₂...A%d) × (A%d...A₃)\n", K[2][3], K[2][3], K[2][3]+1);
}

void test_case_2() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║      TEST CASE 2: Small Example (3 Matrices) For Clarity      ║\n");
    printf("║          Easy to manually verify all calculations             ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    n = 3;
    d[0] = 1;  d[1] = 2;  d[2] = 3;  d[3] = 4;
    
    printf("\n📐 Setup:\n");
    printf("   Matrices: A₁(1×2), A₂(2×3), A₃(3×4)\n");
    printf("   Dimension: d = [1, 2, 3, 4]\n");
    
    printf("\nManual calculation:\n");
    printf("   M[1][1] = 0  (base)\n");
    printf("   M[2][2] = 0  (base)\n");
    printf("   M[3][3] = 0  (base)\n\n");
    
    printf("   M[1][2] = 1×2×3 = 6\n");
    printf("   M[2][3] = 2×3×4 = 24\n\n");
    
    printf("   M[1][3] split options:\n");
    printf("     k=1: M[1][1] + M[2][3] + 1×2×4 = 0+24+8 = 32\n");
    printf("     k=2: M[1][2] + M[3][3] + 1×3×4 = 6+0+12 = 18 ✓ (min)\n");
    printf("   So M[1][3] = 18\n");
    
    matrixChainTabulation();
    
    printf("\n✅ Algorithm Result: M[1][3] = %d\n", M[1][n]);
    
    printTables();
    
    printf("\n🔍 Optimal Parenthesization: ");
    printOptimalOrder(1, n);
    printf("\n");
}

void test_case_3() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║     TEST CASE 3: 5-Matrix Example (Shows Scale)               ║\n");
    printf("║        Tabulation: O(5³) = 125 operations                     ║\n");
    printf("║        vs Recursion: ~81 calls (still manageable)             ║\n");
    printf("║        but growing drastically for larger n                   ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    n = 5;
    d[0] = 2;  d[1] = 3;  d[2] = 4;  d[3] = 5;  d[4] = 2;  d[5] = 6;
    
    printf("\n📐 Setup:\n");
    printf("   5 matrices with dimensions: d = [2, 3, 4, 5, 2, 6]\n");
    
    matrixChainTabulation();
    
    printf("\n✅ Minimum Cost: %d scalar multiplications\n", M[1][n]);
    
    printTables();
    
    printf("\n🔍 Optimal Parenthesization: ");
    printOptimalOrder(1, n);
    printf("\n");
    
    printf("\nComplexity Analysis:\n");
    printf("   Tabulation approach uses exactly:\n");
    printf("   n³/6 + O(n²) multiplications\n");
    printf("   ≈ 125/6 ≈ 21 multiplications (per split attempt)\n");
    printf("   Total operations: ~125 (polynomial)\n\n");
    printf("   Pure recursion would make ~81 function calls\n");
    printf("   (For larger n, this gap becomes exponential!)\n");
}

void test_case_4() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║       TEST CASE 4: Heavy Computation (6 Matrices)             ║\n");
    printf("║    Shows that tabulation stays efficient even for n=6         ║\n");
    printf("║    (Recursion would make thousands of calls)                  ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    n = 6;
    d[0] = 2;  d[1] = 5;  d[2] = 3;  d[3] = 4;  d[4] = 6;  d[5] = 7;  d[6] = 4;
    
    printf("\n📐 Setup: 6 matrices with dimensions d = [2,5,3,4,6,7,4]\n");
    
    matrixChainTabulation();
    
    printf("\n✅ Minimum Cost: %d scalar multiplications\n", M[1][n]);
    
    // Only print partial table to save space
    printf("\n📊 Cost Table M[i][j] (top-left corner shown):\n\n");
    printf("i\\j  1      2      3      4      5      6\n");
    printf("────────────────────────────────────────────\n");
    for (int i = 1; i <= n && i <= 3; i++) {
        printf("%d   ", i);
        for (int j = 1; j <= n && j <= 6; j++) {
            if (i <= j) {
                printf("%6d ", M[i][j]);
            }
        }
        printf("\n");
    }
    printf("...(rest of table omitted for brevity)...\n");
    
    printf("\n🔍 Optimal Parenthesization: ");
    printOptimalOrder(1, n);
    printf("\n");
    
    printf("\nKey Observation:\n");
    printf("   For n=6:\n");
    printf("   • Tabulation: O(6³) = 216 operations ✓ Fast\n");
    printf("   • Recursion: ~729 function calls ✗ Slow\n");
    printf("   • Ratio: Gap widens dramatically as n grows!\n");
}

void demonstrateFillingProcess() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║       DEMONSTRATE CHAIN LENGTH FILLING PROCESS                 ║\n");
    printf("║        (Show exactly how the algorithm fills the table)       ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    n = 4;
    d[0] = 3;  d[1] = 2;  d[2] = 4;  d[3] = 2;  d[4] = 5;
    
    printf("\n📐 Dimensions: d = [3, 2, 4, 2, 5]\n");
    printf("\n⚙️  Algorithm Execution:\n");
    
    // Initialize
    printf("\nStep 1: Initialize base cases (diagonal)\n");
    for (int i = 1; i <= n; i++) {
        M[i][i] = 0;
    }
    printf("  M[1][1] = M[2][2] = M[3][3] = M[4][4] = 0\n");
    
    // Chain length 1
    printf("\nStep 2a: Fill chain length = 1 (two consecutive matrices)\n");
    for (int i = 1; i <= n - 1; i++) {
        int j = i + 1;
        M[i][j] = d[i-1] * d[i] * d[j];
        K[i][j] = i;
        printf("  M[%d][%d] = d[%d]×d[%d]×d[%d] = %d×%d×%d = %d (k=%d)\n",
               i, j, i-1, i, j, d[i-1], d[i], d[j], M[i][j], i);
    }
    
    printf("\n  Table state:\n");
    printf("      1    2    3    4\n");
    printf("  1   0   24\n");
    printf("  2        0   16\n");
    printf("  3             0   40\n");
    printf("  4                  0\n");
    
    // Chain length 2
    printf("\nStep 2b: Fill chain length = 2 (three consecutive matrices)\n");
    for (int i = 1; i <= n - 2; i++) {
        int j = i + 2;
        M[i][j] = INT_MAX;
        printf("  Computing M[%d][%d]:\n", i, j);
        
        for (int k = i; k < j; k++) {
            int cost = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
            printf("    k=%d: M[%d][%d](%d) + M[%d][%d](%d) + %d×%d×%d = %d",
                   k, i, k, M[i][k], k+1, j, M[k+1][j], d[i-1], d[k], d[j], cost);
            
            if (cost < M[i][j]) {
                M[i][j] = cost;
                K[i][j] = k;
                printf(" ← best");
            }
            printf("\n");
        }
        printf("    M[%d][%d] = %d (k=%d)\n\n", i, j, M[i][j], K[i][j]);
    }
    
    // Chain length 3
    printf("Step 2c: Fill chain length = 3 (all four matrices)\n");
    int i = 1, j = 4;
    M[i][j] = INT_MAX;
    printf("  Computing M[%d][%d]:\n", i, j);
    
    for (int k = i; k < j; k++) {
        int cost = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
        printf("    k=%d: M[%d][%d](%d) + M[%d][%d](%d) + %d×%d×%d = %d",
               k, i, k, M[i][k], k+1, j, M[k+1][j], d[i-1], d[k], d[j], cost);
        
        if (cost < M[i][j]) {
            M[i][j] = cost;
            K[i][j] = k;
            printf(" ← best");
        }
        printf("\n");
    }
    printf("    M[%d][%d] = %d (k=%d)\n", i, j, M[i][j], K[i][j]);
    
    printf("\n✅ Final Answer: M[1][4] = %d\n", M[1][4]);
    
    printf("\nFinal Table:\n");
    printf("      1    2    3    4\n");
    printf("  1   0   24   28   58\n");
    printf("  2        0   16   36\n");
    printf("  3             0   40\n");
    printf("  4                  0\n");
}

// ============================================================================
// MAIN: RUN ALL TESTS
// ============================================================================

int main() {
    printf("\n");
    printf("╔═════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                 ║\n");
    printf("║    MATRIX CHAIN MULTIPLICATION — TABULATION (BOTTOM-UP DP)      ║\n");
    printf("║                                                                 ║\n");
    printf("║         Efficient Algorithm: O(n³) instead of exponential       ║\n");
    printf("║                                                                 ║\n");
    printf("╚═════════════════════════════════════════════════════════════════╝\n");
    
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    demonstrateFillingProcess();
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║               TRANSFORMATION COMPLETE                          ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                ║\n");
    printf("║ From Recursion (Lecture 1):                                    ║\n");
    printf("║   • Exponential time: O(4^n / n^1.5)                           ║\n");
    printf("║   • Recursive calls lead to repeated work                      ║\n");
    printf("║   • Only feasible for n ≤ 12                                   ║\n");
    printf("║                                                                ║\n");
    printf("║ To Tabulation (This Lecture):                                  ║\n");
    printf("║   • Polynomial time: O(n³)                                     ║\n");
    printf("║   • DP table solved bottom-up, each once                       ║\n");
    printf("║   • Feasible for n ≤ 1000+                                     ║\n");
    printf("║                                                                ║\n");
    printf("║ The DP Table Represents:                                       ║\n");
    printf("║   • Compressed recursion tree                                  ║\n");
    printf("║   • Structured computation order                               ║\n");
    printf("║   • Efficient answer retrieval                                 ║\n");
    printf("║                                                                ║\n");
    printf("║ Key Achievement:                                               ║\n");
    printf("║   • Filled by chain length, not arbitrary                      ║\n");
    printf("║   • Ensures all dependencies computed before use               ║\n");
    printf("║   • K table enables reconstruction                             ║\n");
    printf("║                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    return 0;
}
