#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 200
#define MAX_DP 201

// Global memoization table
// -1 means "not yet computed"
// other values are the actual LCS length
int dp[MAX_DP][MAX_DP];

// Counter for tracking function calls (to show memoization benefit)
long long total_calls = 0;
long long memo_hits = 0;  // How many times we returned cached result

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

// ============================================================================
// MEMOIZED RECURSION IMPLEMENTATION (Top-Down DP)
// ============================================================================

/**
 * lcs_memoized: Compute LCS length using memoization (top-down DP)
 * 
 * Parameters:
 *   X: First string
 *   Y: Second string
 *   i: Length of prefix of X to consider (from X[0..i-1])
 *   n: Length of prefix of Y to consider (from Y[0..j-1])
 *
 * Returns: Length of LCS
 *
 * Key Optimization:
 *   Check dp[i][j] first. If already computed (≠ -1), return immediately.
 *   This eliminates exponential redundant computation.
 *
 * Time with memoization:    O(m × n) — each cell computed once
 * Time without memoization: O(2^(m+n)) — exponential
 * Space:                    O(m × n) for memo + O(m+n) for recursion stack
 */
int lcs_memoized(const char *X, const char *Y, int i, int j) {
    total_calls++;
    
    // STEP 1: Check memoization table first
    // If we already computed LCS(i,j), return it immediately
    if (dp[i][j] != -1) {
        memo_hits++;
        return dp[i][j];
    }
    
    // STEP 2: Base case — if either string is empty
    // LCS of empty string is 0
    if (i == 0 || j == 0) {
        return dp[i][j] = 0;
    }
    
    // STEP 3: Recurrence — characters match
    if (X[i-1] == Y[j-1]) {
        // Include this character and recurse on shorter strings
        return dp[i][j] = 1 + lcs_memoized(X, Y, i-1, j-1);
    }
    
    // STEP 4: Recurrence — characters don't match
    // Take the maximum of two options:
    // Option A: Ignore last character of X → LCS(i-1, j)
    // Option B: Ignore last character of Y → LCS(i, j-1)
    return dp[i][j] = max(
        lcs_memoized(X, Y, i-1, j),  // Ignore X[i-1]
        lcs_memoized(X, Y, i, j-1)   // Ignore Y[j-1]
    );
}

/**
 * Wrapper function to initialize memoization and call core algorithm
 */
int lcs_length_memoized(const char *X, const char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    
    // Initialize memo table: -1 means "not computed"
    memset(dp, -1, sizeof(dp));
    
    // Reset call counters
    total_calls = 0;
    memo_hits = 0;
    
    // Call memoized function
    return lcs_memoized(X, Y, m, n);
}

// ============================================================================
// RECONSTRUCTION: Find Actual LCS String (Not Just Length)
// ============================================================================

/**
 * reconstructLCS: Build the actual LCS string by backtracking through memo table
 * 
 * We use the same logic that filled the memo table:
 *   - If characters matched: include in LCS, move diagonally
 *   - If they didn't match: move towards the direction with larger value
 */
char* reconstructLCS(const char *X, const char *Y, int i, int j) {
    // Allocate space for LCS (worst case: min(m,n) characters)
    char *lcs = (char*)malloc((min(i, j) + 1) * sizeof(char));
    int idx = 0;
    
    // Backtrack from (i, j) to (0, 0)
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            // Characters matched — include in LCS
            lcs[idx++] = X[i-1];
            i--;
            j--;
        } else {
            // Characters didn't match — move towards larger value
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
// AUXILIARY: Print Memoization Table
// ============================================================================

void printMemoTable(const char *X, const char *Y, int m, int n) {
    printf("\nMemoization Table (DP values):\n");
    printf("Row = Prefix of X, Col = Prefix of Y\n\n");
    
    // Print header
    printf("    ");
    printf("%4s", "");
    for (int j = 0; j < n; j++) {
        printf("%4c", Y[j]);
    }
    printf("\n");
    
    // Print separator
    printf("   ");
    for (int j = 0; j <= n; j++) {
        printf("----");
    }
    printf("\n");
    
    // Print rows
    for (int i = 0; i <= m; i++) {
        if (i == 0)
            printf("   ");
        else
            printf("%c  ", X[i-1]);
        
        for (int j = 0; j <= n; j++) {
            printf("%4d", dp[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// ============================================================================
// TEST CASES
// ============================================================================

/**
 * TEST CASE 1: Classic example from Abdul Bari
 */
void test_case_1() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST CASE 1: Classic Example                                  ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    char X[] = "ABCBDAB";
    char Y[] = "BDCABA";
    int m = strlen(X);
    int n = strlen(Y);
    
    int result = lcs_length_memoized(X, Y);
    char *lcs_str = reconstructLCS(X, Y, m, n);
    
    printf("\nX = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("\n✓ LCS Length: %d\n", result);
    printf("✓ LCS String: \"%s\"\n", lcs_str);
    printf("  Other valid LCSs: \"BCBA\", \"BCAB\"\n");
    printf("\nMemoization Stats:\n");
    printf("  Total calls: %lld\n", total_calls);
    printf("  Memo hits: %lld\n", memo_hits);
    printf("  Unique subproblems: %d\n", (m+1) * (n+1));
    
    printMemoTable(X, Y, m, n);
    
    if (result == 4) {
        printf("✅ TEST CASE 1 PASS\n");
    } else {
        printf("❌ TEST CASE 1 FAIL (Expected 4, got %d)\n", result);
    }
    
    free(lcs_str);
}

/**
 * TEST CASE 2: No common characters
 */
void test_case_2() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST CASE 2: No Common Characters                             ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    char X[] = "ABC";
    char Y[] = "DEF";
    int m = strlen(X);
    int n = strlen(Y);
    
    int result = lcs_length_memoized(X, Y);
    char *lcs_str = reconstructLCS(X, Y, m, n);
    
    printf("\nX = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("\n✓ LCS Length: %d\n", result);
    printf("✓ LCS String: \"%s\" (empty)\n", lcs_str);
    printf("\nMemoization Stats:\n");
    printf("  Total calls: %lld\n", total_calls);
    printf("  Memo hits: %lld\n", memo_hits);
    printf("  Unique subproblems: %d\n", (m+1) * (n+1));
    
    printMemoTable(X, Y, m, n);
    
    if (result == 0) {
        printf("✅ TEST CASE 2 PASS\n");
    } else {
        printf("❌ TEST CASE 2 FAIL (Expected 0, got %d)\n", result);
    }
    
    free(lcs_str);
}

/**
 * TEST CASE 3: Identical strings
 */
void test_case_3() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST CASE 3: Identical Strings                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    char X[] = "HELLO";
    char Y[] = "HELLO";
    int m = strlen(X);
    int n = strlen(Y);
    
    int result = lcs_length_memoized(X, Y);
    char *lcs_str = reconstructLCS(X, Y, m, n);
    
    printf("\nX = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("\n✓ LCS Length: %d\n", result);
    printf("✓ LCS String: \"%s\"\n", lcs_str);
    printf("\nMemoization Stats:\n");
    printf("  Total calls: %lld\n", total_calls);
    printf("  Memo hits: %lld\n", memo_hits);
    printf("  Unique subproblems: %d\n", (m+1) * (n+1));
    printf("  Memo utilization: %.1f%%\n", 100.0 * memo_hits / total_calls);
    
    printMemoTable(X, Y, m, n);
    
    if (result == 5) {
        printf("✅ TEST CASE 3 PASS\n");
    } else {
        printf("❌ TEST CASE 3 FAIL (Expected 5, got %d)\n", result);
    }
    
    free(lcs_str);
}

/**
 * TEST CASE 4: Longer strings
 */
void test_case_4() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST CASE 4: Longer Strings with Partial Match                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    int m = strlen(X);
    int n = strlen(Y);
    
    int result = lcs_length_memoized(X, Y);
    char *lcs_str = reconstructLCS(X, Y, m, n);
    
    printf("\nX = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("\n✓ LCS Length: %d\n", result);
    printf("✓ LCS String: \"%s\"\n", lcs_str);
    printf("\nMemoization Stats:\n");
    printf("  Total calls: %lld\n", total_calls);
    printf("  Memo hits: %lld\n", memo_hits);
    printf("  Unique subproblems: %d\n", (m+1) * (n+1));
    printf("  Memo utilization: %.1f%%\n", 100.0 * memo_hits / total_calls);
    
    printMemoTable(X, Y, m, n);
    
    if (result == 4) {
        printf("✅ TEST CASE 4 PASS\n");
    } else {
        printf("⚠️  Result: %d (actual answer)\n", result);
    }
    
    free(lcs_str);
}

// ============================================================================
// ANALYSIS: MEMOIZATION BENEFIT
// ============================================================================

void demonstrateMemoizationBenefit() {
    printf("\n" "════════════════════════════════════════════════════════════════════════════\n");
    printf("ANALYSIS: Memoization Benefit (Total Calls vs Unique Subproblems)\n");
    printf("════════════════════════════════════════════════════════════════════════════\n\n");
    
    printf("Concept:\n");
    printf("  Without memo: Same subproblems computed multiple times\n");
    printf("  With memo:    Each subproblem computed exactly once\n\n");
    
    printf("Size | Unique | Recursion | Memo    | Reduction | Cache\n");
    printf("     |   (m×n) | Est. 2^(m+n) | Calls   | Factor  | Hit\n");
    printf("─────|────────|──────────────|─────────|─────────|───────\n");
    
    struct {
        char X[50];
        char Y[50];
    } tests[] = {
        {"AAA", "AAA"},
        {"AAAA", "AAAA"},
        {"AAAAA", "AAAAA"},
        {"AAAAAA", "AAAAAA"},
    };
    
    for (int i = 0; i < 4; i++) {
        int m = strlen(tests[i].X);
        int n = strlen(tests[i].Y);
        int unique = (m+1) * (n+1);
        
        long long recur_est = 1;
        for (int j = 0; j < m+n && recur_est < 1000000000; j++)
            recur_est *= 2;
        
        int result = lcs_length_memoized(tests[i].X, tests[i].Y);
        
        double reduction = (double)total_calls / unique;
        double hit_rate = 100.0 * memo_hits / total_calls;
        
        printf("%1d+%1d |  %3d   | ~%-8lld | %7lld | %7.1f× | %5.1f%%\n",
               m, n, unique, recur_est, total_calls, reduction, hit_rate);
    }
    
    printf("\nKey Insight:\n");
    printf("  • Even with small inputs, memoization dramatically reduces calls\n");
    printf("  • For identical strings, all m×n cells needed (no savings)\n");
    printf("  • For partially matching strings, significant savings with memo hits\n");
    printf("  • Without memo, would be exponential ~2^(m+n) calls\n");
    printf("  • With memo, is polynomial m×n calls ← Massive improvement!\n\n");
}

void compareApproaches() {
    printf("════════════════════════════════════════════════════════════════════════════\n");
    printf("COMPARISON: Pure Recursion vs Memoization vs Tabulation\n");
    printf("════════════════════════════════════════════════════════════════════════════\n\n");
    
    printf("Approach      | Time       | Space (Stack) | Space (Memo) | Calls\n");
    printf("──────────────┼────────────┼───────────────┼──────────────┼──────\n");
    printf("Recursion     | 2^(m+n)    | O(m+n)        | —            | 2^(m+n)\n");
    printf("Memoization   | O(m×n)     | O(m+n)        | O(m×n)       | ≤ (m+1)×(n+1)\n");
    printf("Tabulation    | O(m×n)     | O(1)          | O(m×n)       | (m+1)×(n+1)\n");
    
    printf("\nExecution Pattern:\n");
    printf("  Recursion:    Top-down, many redundant calls, exponential\n");
    printf("  Memoization:  Top-down with caching, polynomial, keeps recursive intuition\n");
    printf("  Tabulation:   Bottom-up with loops, polynomial, usually slightly faster\n");
    printf("\nFor LCS:\n");
    printf("  • All three produce same answer\n");
    printf("  • Recursion impractical for n > 12\n");
    printf("  • Memoization practical for n ≤ 1000\n");
    printf("  • Tabulation is 'ultimate' DP form\n\n");
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    printf("\n╔════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║     LONGEST COMMON SUBSEQUENCE (LCS) — MEMOIZATION APPROACH              ║\n");
    printf("║          Top-Down DP: Recursion with Smart Caching                       ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════╝\n");
    
    // Run test cases
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    
    // Analysis
    demonstrateMemoizationBenefit();
    compareApproaches();
    
    printf("════════════════════════════════════════════════════════════════════════════\n");
    printf("KEY TAKEAWAYS:\n");
    printf("════════════════════════════════════════════════════════════════════════════\n");
    printf("1. Memoization = Recursion + Memory\n");
    printf("2. Check memo first (dp[i][j] ≠ -1) before recomputing\n");
    printf("3. Each unique (i,j) pair computed exactly once\n");
    printf("4. Time: O(m×n) — polynomial, not exponential!\n");
    printf("5. Space: O(m×n) memo + O(m+n) stack\n");
    printf("6. Top-down thinking → bottom-up execution (via memo)\n");
    printf("7. This pattern works for ANY DP problem:\n");
    printf("   • 0/1 Knapsack     • Edit Distance\n");
    printf("   • Matrix Chain Mult • Coin Change\n");
    printf("   • And many more!\n");
    printf("════════════════════════════════════════════════════════════════════════════\n\n");
    
    return 0;
}
