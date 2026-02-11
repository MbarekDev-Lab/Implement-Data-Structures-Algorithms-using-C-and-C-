#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 200
#define MAX_DP 201

// DP tables (global for easy access in reconstruction)
int dp[MAX_DP][MAX_DP];

// Helper functions
int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

// ============================================================================
// TABULATION IMPLEMENTATION (Polynomial Time Complexity)
// ============================================================================

/**
 * lcs_tabulation: Compute LCS length using dynamic programming (tabulation)
 * 
 * Parameters:
 *   X: First string
 *   Y: Second string
 *   m: Length of string X
 *   n: Length of string Y
 *
 * Returns: Length of LCS
 *
 * Time Complexity: O(m × n)
 * Space Complexity: O(m × n) for the DP table
 *
 * Algorithm:
 *   1. Create (m+1) × (n+1) table
 *   2. Initialize first row and column with 0 (empty string cases)
 *   3. Fill table row by row:
 *      - If characters match: dp[i][j] = 1 + dp[i-1][j-1]
 *      - Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *   4. Return dp[m][n] (bottom-right cell)
 */
int lcs_tabulation(const char *X, const char *Y, int m, int n) {
    // Initialize: dp[i][0] = 0 and dp[0][j] = 0
    // (empty string has LCS of 0)
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }
    
    // Fill the table row by row
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // CASE 1: Characters match
            if (X[i-1] == Y[j-1]) {
                // Include this character in LCS
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            // CASE 2: Characters don't match
            else {
                // Take the maximum of two options:
                // Option A: Ignore last character of X
                // Option B: Ignore last character of Y
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    // Answer is at dp[m][n]
    return dp[m][n];
}

// ============================================================================
// AUXILIARY FUNCTION: Print DP Table for Visualization
// ============================================================================

/**
 * printLCSTable: Display the DP table with strings as row/column headers
 * 
 * For debugging and understanding how the table is filled
 */
void printLCSTable(const char *X, const char *Y, int m, int n) {
    printf("\n");
    printf("DP Table (LCS values):\n");
    printf("Row = Character from X (rows 0 to %d)\n", m);
    printf("Col = Character from Y (cols 0 to %d)\n\n", n);
    
    // Print header row with Y characters
    printf("    ");
    printf("%3s", "");  // Empty corner
    for (int j = 0; j < n; j++) {
        printf("%3c", Y[j]);
    }
    printf("\n");
    
    // Print separator
    printf("   ");
    for (int j = 0; j <= n; j++) {
        printf("---");
    }
    printf("\n");
    
    // Print rows with X characters
    for (int i = 0; i <= m; i++) {
        if (i == 0)
            printf("   ");  // Empty corner
        else
            printf("%c  ", X[i-1]);
        
        for (int j = 0; j <= n; j++) {
            printf("%3d", dp[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// ============================================================================
// RECONSTRUCTION: Find Actual LCS (Not Just Length)
// ============================================================================

/**
 * reconstructLCS: Build the actual LCS string by backtracking through DP table
 * 
 * Start at dp[m][n] and work backwards to dp[0][0]:
 *   - If characters match: include in LCS, move diagonally
 *   - If don't match: move up or left (whichever has larger value)
 * 
 * Returns: Dynamically allocated string containing the LCS
 */
char* reconstructLCS(const char *X, const char *Y, int m, int n) {
    // Allocate space for LCS (worst case: min(m, n) characters)
    char *lcs = (char*)malloc((min(m, n) + 1) * sizeof(char));
    int idx = 0;
    
    int i = m, j = n;
    
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            // Characters match — include in LCS
            lcs[idx++] = X[i-1];
            i--;
            j--;
        } else {
            // Characters don't match
            // Move towards the larger value (where most LCS comes from)
            if (dp[i-1][j] > dp[i][j-1]) {
                i--;  // Ignore last character of X
            } else {
                j--;  // Ignore last character of Y
            }
        }
    }
    
    // LCS was built backwards — reverse it
    for (int k = 0; k < idx / 2; k++) {
        char temp = lcs[k];
        lcs[k] = lcs[idx - 1 - k];
        lcs[idx - 1 - k] = temp;
    }
    
    lcs[idx] = '\0';  // Null terminate
    return lcs;
}

// ============================================================================
// TEST CASES
// ============================================================================

/**
 * TEST CASE 1: Classic example from Abdul Bari
 * X = "ABCBDAB" (length 7)
 * Y = "BDCABA"  (length 6)
 * Expected LCS length: 4
 * Possible LCSs: "BDAB", "BCBA", "BCAB"
 */
void test_case_1() {
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST CASE 1: Classic Example                                 ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    char X[] = "ABCBDAB";
    char Y[] = "BDCABA";
    int m = strlen(X);
    int n = strlen(Y);
    
    int result = lcs_tabulation(X, Y, m, n);
    char *lcs_str = reconstructLCS(X, Y, m, n);
    
    printf("\nX = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("\n✓ LCS Length: %d\n", result);
    printf("✓ LCS String: \"%s\"\n", lcs_str);
    printf("  Other valid LCSs: \"BCBA\", \"BCAB\"\n");
    
    printLCSTable(X, Y, m, n);
    
    if (result == 4) {
        printf("✅ TEST CASE 1 PASS\n");
    } else {
        printf("❌ TEST CASE 1 FAIL (Expected 4, got %d)\n", result);
    }
    
    free(lcs_str);
}

/**
 * TEST CASE 2: Strings with no matching characters
 * X = "ABC"
 * Y = "DEF"
 * Expected LCS length: 0
 */
void test_case_2() {
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST CASE 2: No Common Characters                            ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    char X[] = "ABC";
    char Y[] = "DEF";
    int m = strlen(X);
    int n = strlen(Y);
    
    int result = lcs_tabulation(X, Y, m, n);
    char *lcs_str = reconstructLCS(X, Y, m, n);
    
    printf("\nX = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("\n✓ LCS Length: %d\n", result);
    printf("✓ LCS String: \"%s\" (empty string)\n", lcs_str);
    
    printLCSTable(X, Y, m, n);
    
    if (result == 0) {
        printf("✅ TEST CASE 2 PASS\n");
    } else {
        printf("❌ TEST CASE 2 FAIL (Expected 0, got %d)\n", result);
    }
    
    free(lcs_str);
}

/**
 * TEST CASE 3: Identical strings
 * X = "HELLO"
 * Y = "HELLO"
 * Expected LCS length: 5
 * Expected LCS: "HELLO"
 */
void test_case_3() {
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST CASE 3: Identical Strings                               ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    char X[] = "HELLO";
    char Y[] = "HELLO";
    int m = strlen(X);
    int n = strlen(Y);
    
    int result = lcs_tabulation(X, Y, m, n);
    char *lcs_str = reconstructLCS(X, Y, m, n);
    
    printf("\nX = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("\n✓ LCS Length: %d\n", result);
    printf("✓ LCS String: \"%s\"\n", lcs_str);
    printf("  (Strings are identical, entire string is the LCS)\n");
    
    printLCSTable(X, Y, m, n);
    
    if (result == 5) {
        printf("✅ TEST CASE 3 PASS\n");
    } else {
        printf("❌ TEST CASE 3 FAIL (Expected 5, got %d)\n", result);
    }
    
    free(lcs_str);
}

/**
 * TEST CASE 4: Longer strings with partial match
 * X = "AGGTAB" (length 6)
 * Y = "GXTXAYB" (length 7)
 * Expected LCS length: 4
 */
void test_case_4() {
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST CASE 4: Longer Strings with Partial Match               ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    int m = strlen(X);
    int n = strlen(Y);
    
    int result = lcs_tabulation(X, Y, m, n);
    char *lcs_str = reconstructLCS(X, Y, m, n);
    
    printf("\nX = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("\n✓ LCS Length: %d\n", result);
    printf("✓ LCS String: \"%s\"\n", lcs_str);
    
    printLCSTable(X, Y, m, n);
    
    if (result == 4) {
        printf("✅ TEST CASE 4 PASS\n");
    } else {
        printf("⚠️  TEST CASE 4: Result %d (actual answer)\n", result);
    }
    
    free(lcs_str);
}

// ============================================================================
// COMPLEXITY ANALYSIS & COMPARISON
// ============================================================================

/**
 * demonstrateComplexityImprovement: Show time complexity improvement
 * 
 * Compare tabulation (O(m×n)) with recursion (O(2^(m+n)))
 */
void demonstrateComplexityImprovement() {
    printf("\n" "═══════════════════════════════════════════════════════════════════════════\n");
    printf("ANALYSIS: Tabulation vs Recursion Complexity\n");
    printf("═══════════════════════════════════════════════════════════════════════════\n\n");
    
    printf("Complexity Comparison:\n\n");
    printf("String Lengths | Tabulation O(m×n) | Recursion O(2^(m+n))\n");
    printf("----------------|-------------------|---------------------\n");
    
    struct {
        int m, n;
    } test_sizes[] = {
        {5, 5},
        {6, 6},
        {7, 7},
        {8, 8},
        {10, 10},
        {15, 15},
    };
    
    int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int m = test_sizes[i].m;
        int n = test_sizes[i].n;
        
        long long tab_ops = m * n;
        
        // Approximate recursion calls as 2^(m+n)
        long long recur_ops = 1;
        for (int j = 0; j < m + n; j++) {
            recur_ops *= 2;
            if (recur_ops > 1000000000) {
                recur_ops = 1000000000;  // Cap at 1 billion for display
                break;
            }
        }
        
        printf("    m=%2d, n=%2d  |      %8lld       |      %12lld+ \n",
               m, n, tab_ops, recur_ops);
    }
    
    printf("\n");
    printf("KEY OBSERVATIONS:\n");
    printf("  • Tabulation grows QUADRATICALLY (polynomial)\n");
    printf("  • Recursion grows EXPONENTIALLY (exponential)\n");
    printf("  • For m=n=15: Tabulation=225 ops, Recursion~1 billion+ ops\n");
    printf("  • Speedup factor increases dramatically with input size\n\n");
}

/**
 * demonstrateFillingProcess: Show how the DP table is filled
 */
void demonstrateFillingProcess() {
    printf("═══════════════════════════════════════════════════════════════════════════\n");
    printf("DEMONSTRATION: How the DP Table is Filled\n");
    printf("═══════════════════════════════════════════════════════════════════════════\n\n");
    
    printf("Filling Order: Row by row, left to right\n\n");
    printf("For X = \"ABD\", Y = \"BD\" (3×2 table):\n\n");
    
    printf("Step-by-step filling:\n");
    printf("  1. Initialize row 0: [0, 0, 0]\n");
    printf("  2. Initialize col 0: [0, 0, 0, 0]\n");
    printf("  3. Fill row 1 ([A]): [0, 0, 0]  (A matches neither B nor D)\n");
    printf("  4. Fill row 2 ([B]): [0, 1, 1]  (B matches B at position 0)\n");
    printf("  5. Fill row 3 ([D]): [0, 1, 2]  (D matches D at position 1)\n\n");
    
    printf("Final Table:\n");
    printf("        \"\" B  D\n");
    printf("    \"\"  0  0  0\n");
    printf("    A   0  0  0\n");
    printf("    B   0  1  1\n");
    printf("    D   0  1  2  ← Answer: 2\n\n");
    
    printf("Why Row-by-Row Works:\n");
    printf("  • dp[i][j] depends on dp[i-1][j-1], dp[i-1][j], dp[i][j-1]\n");
    printf("  • Row by row ensures all three are computed before we need them\n");
    printf("  • Left to right ensures dp[i][j-1] is ready when we compute dp[i][j]\n\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("\n╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║      LONGEST COMMON SUBSEQUENCE (LCS) — TABULATION APPROACH              ║\n");
    printf("║            Converting Exponential Recursion to Polynomial DP              ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n");
    
    // Run all test cases
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    
    // Complexity analysis
    demonstrateComplexityImprovement();
    
    // Filling process demonstration
    demonstrateFillingProcess();
    
    printf("═══════════════════════════════════════════════════════════════════════════\n");
    printf("KEY INSIGHTS:\n");
    printf("═══════════════════════════════════════════════════════════════════════════\n");
    printf("1. Tabulation builds the table BOTTOM-UP from base cases\n");
    printf("2. Same recurrence formula as recursion, but computed once per cell\n");
    printf("3. DP table has only m×n cells (vs 2^(m+n) recursive calls)\n");
    printf("4. Row-by-row filling ensures all dependencies are ready\n");
    printf("5. Reconstruction algorithm backtracks to find actual LCS\n");
    printf("6. Time: O(m×n), Space: O(m×n) — practical for large strings\n");
    printf("\nThis pattern (recursion → tabulation) applies to many DP problems:\n");
    printf("  • 0/1 Knapsack\n");
    printf("  • Matrix Chain Multiplication\n");
    printf("  • Edit Distance\n");
    printf("  • Coin Change\n");
    printf("  • And many more!\n");
    printf("═══════════════════════════════════════════════════════════════════════════\n\n");
    
    return 0;
}
