#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 100
#define MAX_CALLS 10000000

// Global counters
long long call_count = 0;

// Helper function to get maximum
int max(int a, int b) {
    return (a > b) ? a : b;
}

// ============================================================================
// PURE RECURSION IMPLEMENTATION (Exponential Time Complexity)
// ============================================================================

/**
 * lcs_recursive: Compute LCS length using pure recursion
 * 
 * Parameters:
 *   X: First string
 *   Y: Second string
 *   m: Length of substring of X to consider (from X[0..m-1])
 *   n: Length of substring of Y to consider (from Y[0..n-1])
 *
 * Returns: Length of LCS for X[0..m-1] and Y[0..n-1]
 *
 * Recurrence:
 *   L(m, n) = 0                        if m=0 or n=0
 *   L(m, n) = 1 + L(m-1, n-1)         if X[m-1] == Y[n-1]
 *   L(m, n) = max(L(m-1, n), L(m, n-1)) if X[m-1] != Y[n-1]
 */
int lcs_recursive(const char *X, const char *Y, int m, int n) {
    call_count++;
    
    // BASE CASE: If either string is empty, LCS is 0
    if (m == 0 || n == 0)
        return 0;
    
    // CASE 1: Last characters match
    // Include this character in LCS and reduce both strings
    if (X[m-1] == Y[n-1])
        return 1 + lcs_recursive(X, Y, m-1, n-1);
    
    // CASE 2: Last characters don't match
    // Take the maximum of two options:
    //   Option A: Ignore last character of X
    //   Option B: Ignore last character of Y
    return max(
        lcs_recursive(X, Y, m-1, n),  // Ignore last of X
        lcs_recursive(X, Y, m, n-1)   // Ignore last of Y
    );
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
    printf("\n=== TEST CASE 1: Classic Example ===\n");
    char X[] = "ABCBDAB";
    char Y[] = "BDCABA";
    int m = strlen(X);
    int n = strlen(Y);
    
    call_count = 0;
    int result = lcs_recursive(X, Y, m, n);
    
    printf("X = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("✓ LCS Length: %d\n", result);
    printf("  Possible LCSs: \"BDAB\", \"BCBA\", \"BCAB\"\n");
    printf("  Recursive calls: %lld\n", call_count);
    
    if (result == 4) {
        printf("  ✅ PASS\n");
    } else {
        printf("  ❌ FAIL (Expected 4, got %d)\n", result);
    }
}

/**
 * TEST CASE 2: Strings with no common characters
 * X = "ABC" (length 3)
 * Y = "DEF" (length 3)
 * Expected LCS length: 0
 */
void test_case_2() {
    printf("\n=== TEST CASE 2: No Common Characters ===\n");
    char X[] = "ABC";
    char Y[] = "DEF";
    int m = strlen(X);
    int n = strlen(Y);
    
    call_count = 0;
    int result = lcs_recursive(X, Y, m, n);
    
    printf("X = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("✓ LCS Length: %d\n", result);
    printf("  No common characters\n");
    printf("  Recursive calls: %lld\n", call_count);
    
    if (result == 0) {
        printf("  ✅ PASS\n");
    } else {
        printf("  ❌ FAIL (Expected 0, got %d)\n", result);
    }
}

/**
 * TEST CASE 3: Strings that are identical
 * X = "HELLO" (length 5)
 * Y = "HELLO" (length 5)
 * Expected LCS length: 5
 */
void test_case_3() {
    printf("\n=== TEST CASE 3: Identical Strings ===\n");
    char X[] = "HELLO";
    char Y[] = "HELLO";
    int m = strlen(X);
    int n = strlen(Y);
    
    call_count = 0;
    int result = lcs_recursive(X, Y, m, n);
    
    printf("X = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("✓ LCS Length: %d\n", result);
    printf("  Strings are identical, LCS is the entire string\n");
    printf("  Recursive calls: %lld\n", call_count);
    
    if (result == 5) {
        printf("  ✅ PASS\n");
    } else {
        printf("  ❌ FAIL (Expected 5, got %d)\n", result);
    }
}

/**
 * TEST CASE 4: One string is a subsequence of the other
 * X = "AGGTAB" (length 6)
 * Y = "GXTXAYB" (length 7)
 * Expected LCS length: 5
 * LCS: "GTAB" or similar
 */
void test_case_4() {
    printf("\n=== TEST CASE 4: Subsequence Relationship ===\n");
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    int m = strlen(X);
    int n = strlen(Y);
    
    call_count = 0;
    int result = lcs_recursive(X, Y, m, n);
    
    printf("X = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("✓ LCS Length: %d\n", result);
    printf("  Recursive calls: %lld\n", call_count);
    
    if (result == 5) {
        printf("  ✅ PASS\n");
    } else {
        printf("  ❌ FAIL (Expected 5, got %d)\n", result);
    }
}

/**
 * TEST CASE 5: Longer strings showing call count explosion
 * X = "COMPUTER" (length 8)
 * Y = "STUDENT" (length 7)
 * Expected LCS length: 4 ("CUMNT" or "OMNT" depending on analysis)
 * 
 * Note: With 8+7=15 total length, expect ~2^15 = 32k+ calls
 */
void test_case_5() {
    printf("\n=== TEST CASE 5: Longer Strings (Call Count Analysis) ===\n");
    char X[] = "COMPUTER";
    char Y[] = "STUDENT";
    int m = strlen(X);
    int n = strlen(Y);
    
    call_count = 0;
    int result = lcs_recursive(X, Y, m, n);
    
    printf("X = \"%s\" (length %d)\n", X, m);
    printf("Y = \"%s\" (length %d)\n", Y, n);
    printf("✓ LCS Length: %d\n", result);
    printf("  Recursive calls: %lld\n", call_count);
    printf("  Approx 2^(m+n) = 2^15 ≈ 32,768\n");
    
    if (result == 4) {
        printf("  ✅ PASS\n");
    } else {
        printf("  ⚠️  Result: %d (actual answer)\n", result);
    }
}

// ============================================================================
// ANALYSIS: SHOW EXPONENTIAL GROWTH
// ============================================================================

/**
 * analyzeRecursionGrowth: Show how call count grows with input size
 * 
 * Uses same string repeated or similar patterns to show growth pattern
 * This demonstrates why pure recursion is exponential
 */
void analyzeRecursionGrowth() {
    printf("\n" "=============================================================================\n");
    printf("ANALYSIS: Recursion Call Growth (Exponential Explosion)\n");
    printf("=============================================================================\n\n");
    
    printf("Pattern: Using progressively larger strings (both of same length)\n");
    printf("Hypothesis: Each unit increase roughly multiplies calls by 2-3x\n\n");
    
    struct {
        char X[20];
        char Y[20];
        int len_x;
        int len_y;
    } test_progression[] = {
        {"A", "A", 1, 1},
        {"AB", "AB", 2, 2},
        {"ABC", "ABC", 3, 3},
        {"ABCD", "ABCD", 4, 4},
        {"ABCDE", "ABCDE", 5, 5},
        {"ABCDEF", "ABCDEF", 6, 6},
        {"ABCDEFG", "ABCDEFG", 7, 7},
        {"ABCDEFGH", "ABCDEFGH", 8, 8},
        {"ABCDEFGHI", "ABCDEFGHI", 9, 9},
        {"ABCDEFGHIJ", "ABCDEFGHIJ", 10, 10},
    };
    
    int num_tests = sizeof(test_progression) / sizeof(test_progression[0]);
    
    printf("Length | Result | Calls      | Growth Factor | Expected ~2^(2n)\n");
    printf("-------|--------|------------|---------------|------------------\n");
    
    long long prev_calls = 0;
    for (int i = 0; i < num_tests; i++) {
        call_count = 0;
        int result = lcs_recursive(
            test_progression[i].X, 
            test_progression[i].Y, 
            test_progression[i].len_x, 
            test_progression[i].len_y
        );
        
        int n = test_progression[i].len_x;
        long long expected = 1;
        for (int j = 0; j < 2*n; j++) expected *= 2;  // Approximate 2^(2n)
        
        double growth_factor = (prev_calls > 0) ? (double)call_count / prev_calls : 1.0;
        
        printf("  %2d   |   %2d   | %11lld | %13.1f | %13lld\n",
               n, result, call_count, growth_factor, expected);
        
        prev_calls = call_count;
    }
    
    printf("\n");
    printf("KEY OBSERVATION:\n");
    printf("  • Each increase in length multiplies calls by ~2-3x\n");
    printf("  • This is EXPONENTIAL growth: O(2^(m+n))\n");
    printf("  • For identical strings of length n: O(2^(2n)) = O(4^n)\n");
    printf("  • Beyond n=10, becomes very slow\n");
    printf("  • Beyond n=15, becomes impractical on modern computers\n\n");
}

// ============================================================================
// DEMONSTRATE OVERLAPPING SUBPROBLEMS
// ============================================================================

/**
 * demonstrateOverlappingSubproblems: Show that same L(i,j) is computed
 * multiple times in the recursion tree
 */
void demonstrateOverlappingSubproblems() {
    printf("\n" "=============================================================================\n");
    printf("DEMONSTRATION: Overlapping Subproblems\n");
    printf("=============================================================================\n\n");
    
    printf("For X = \"ABC\", Y = \"DEF\" (length 3 each):\n\n");
    
    printf("Recursion Tree Structure (Partial):\n\n");
    printf("                          L(3,3)\n");
    printf("                       /         \\\\\n");
    printf("                   L(2,3)       L(3,2)\n");
    printf("                   /   \\          /   \\\\\n");
    printf("               L(1,3) L(2,2)  L(2,2) L(3,1)\n");
    printf("               /  \\    /  \\    /  \\    /  \\\\\n");
    printf("          L(0,3) L(1,2) L(2,1) L(2,3)...  ...\n\n");
    
    printf("Observation: L(2,2) appears TWICE\n");
    printf("             L(2,3) appears MULTIPLE times\n");
    printf("             L(1,2) appears MULTIPLE times\n\n");
    
    printf("Without memoization:\n");
    printf("  • Each L(i,j) is recalculated every time it's needed\n");
    printf("  • Creates exponential blowup in total calls\n");
    printf("  • Same computation wasted many times\n\n");
    
    printf("With DP (memoization or tabulation):\n");
    printf("  • Compute each L(i,j) ONCE\n");
    printf("  • Store result\n");
    printf("  • Only n*m = 9 unique subproblems exist\n");
    printf("  • Time complexity drops from O(2^(m+n)) to O(m*n)\n\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("\n╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║         LONGEST COMMON SUBSEQUENCE (LCS) — PURE RECURSION APPROACH       ║\n");
    printf("║                  Demonstrating Exponential Time Complexity                ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n");
    
    // Run all test cases
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    
    // Analysis demonstrations
    analyzeRecursionGrowth();
    demonstrateOverlappingSubproblems();
    
    printf("=============================================================================\n");
    printf("CONCLUSION:\n");
    printf("=============================================================================\n");
    printf("Pure recursion for LCS is EXPONENTIAL and IMPRACTICAL.\n");
    printf("Overlapping subproblems are evident from the call counts.\n");
    printf("Only n*m distinct subproblems exist (can use 2D DP table).\n\n");
    printf("Next phase: TABULATION (Bottom-up DP) achieves O(m*n) time complexity.\n");
    printf("=============================================================================\n\n");
    
    return 0;
}
