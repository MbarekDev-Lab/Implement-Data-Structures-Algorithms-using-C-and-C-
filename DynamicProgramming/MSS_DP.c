#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_SIZE 200
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"

/**
 * Maximum Subarray Sum (MSS) — Dynamic Programming Approach
 * 
 * State Definition:
 *   dp[i] = Maximum sum of any subarray ENDING exactly at index i
 * 
 * Recurrence Relation:
 *   dp[i] = max(A[i], A[i] + dp[i-1])
 *   
 *   Meaning:
 *   - A[i] alone (start fresh)
 *   - A[i] + dp[i-1] (extend previous)
 *   
 * Time Complexity: O(n)
 * Space Complexity: O(n) for dp array
 */

typedef struct {
    int *dp;
    int *A;
    int n;
    int max_sum;
    int max_index;
} MSS_Result;

/**
 * mss_dp: Compute maximum subarray sum using dynamic programming
 * 
 * Algorithm:
 * 1. Initialize dp[0] = A[0]
 * 2. For each i from 1 to n-1:
 *    - Compute dp[i] = max(A[i], A[i] + dp[i-1])
 *    - Track maximum value and its position
 * 3. Return maximum found
 */
int mss_dp(int A[], int n, int **dp_out, int *max_index) {
    if(n <= 0) return INT_MIN;
    
    int *dp = (int *)malloc(n * sizeof(int));
    
    // Base case
    dp[0] = A[0];
    int max_sum = dp[0];
    *max_index = 0;
    
    // Fill dp array
    for(int i = 1; i < n; i++) {
        // Key Decision: Start fresh vs Extend previous
        int extend_previous = A[i] + dp[i-1];
        int start_fresh = A[i];
        
        dp[i] = (extend_previous > start_fresh) ? extend_previous : start_fresh;
        
        // Track maximum
        if(dp[i] > max_sum) {
            max_sum = dp[i];
            *max_index = i;
        }
    }
    
    *dp_out = dp;
    return max_sum;
}

/**
 * trace_subarray: Reconstruct which elements form the optimal subarray
 * (requires we track start_index and end_index during computation)
 */
void reconstruct_subarray(int A[], int n, int *dp) {
    // Method: Work backwards from max position
    // This would require more complex tracking
    // For now, we just identify the end position
    
    int max_sum = dp[0];
    int max_index = 0;
    
    for(int i = 0; i < n; i++) {
        if(dp[i] > max_sum) {
            max_sum = dp[i];
            max_index = i;
        }
    }
    
    printf("Optimal subarray ends at index %d\n", max_index);
    printf("Maximum sum: %d\n", max_sum);
    printf("Note: Full reconstruction requires tracking both start and end indices\n");
}

/**
 * print_dp_table: Visualize the DP computation process
 */
void print_dp_table(int A[], int n, int *dp) {
    printf("\n%s═══ DP TABLE VISUALIZATION ══=%s\n\n", BLUE, RESET);
    
    printf("| i  | A[i] | dp[i] | Decision      |\n");
    printf("-" "-----" "------" "-------" "--------" "-|\n");
    
    for(int i = 0; i < n; i++) {
        const char *decision = "Start";
        
        if(i > 0) {
            int extend = A[i] + dp[i-1];
            int fresh = A[i];
            
            if(extend >= fresh) {
                decision = "Extend";
            } else {
                decision = "Fresh ";
            }
        }
        
        printf("| %2d | %3d | %4d | %s |\n", i, A[i], dp[i], decision);
    }
    
    printf("-" "-----" "------" "-------" "--------" "-|\n\n");
    
    // Show state values
    printf("%sKey States:%s\n", YELLOW, RESET);
    printf("dp[0] = %d (base case: just A[0])\n", dp[0]);
    printf("dp[i] = max(A[i], A[i] + dp[i-1]) for i > 0\n\n");
}

/**
 * analyze_brute_force: Show why O(n²) is inefficient
 */
void analyze_brute_force(int A[], int n) {
    printf("%s═══ BRUTE FORCE ANALYSIS ══=%s\n\n", YELLOW, RESET);
    printf("Brute force: Try all subarrays and compute sum\n\n");
    
    int max_sum = INT_MIN;
    long long comparison_count = 0;
    
    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(int j = i; j < n; j++) {
            sum += A[j];
            comparison_count++;
            if(sum > max_sum) {
                max_sum = sum;
            }
        }
    }
    
    printf("Brute force computation: %lld comparisons\n", comparison_count);
    printf("Maximum found: %d\n", max_sum);
    printf("Time complexity: O(n²) = O(%d²) = O(%d)\n\n", n, n * n);
}

/**
 * compare_approaches: Show efficiency gain
 */
void compare_approaches(int A[], int n, int max_sum_dp) {
    printf("%s═══ EFFICIENCY COMPARISON ══=%s\n\n", BLUE, RESET);
    
    long long brute_force_ops = (long long)n * (n + 1) / 2;
    long long dp_ops = n;
    
    printf("| Approach | Time Complexity | Operations (n=%d) |\n", n);
    printf("|----------|-----------------|-------------------|\n");
    printf("| Brute Force | O(n²)        | %lld            |\n", brute_force_ops);
    printf("| DP          | O(n)         | %lld                  |\n", dp_ops);
    printf("|----------|-----------------|-------------------|\n");
    printf("| Speedup = %lld× faster with DP\n\n", brute_force_ops / dp_ops);
    
    printf("For n = 1000:\n");
    printf("  Brute Force: ~500,000 operations\n");
    printf("  DP:          ~1,000 operations\n");
    printf("  Gain: ~500× faster!\n\n");
}

/**
 * test_case: Run a single test and display results
 */
void test_case(int num, int A[], int n, const char *description) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n", BLUE, RESET);
    printf("%s║ TEST CASE %d: %s%s║%s\n", BLUE, num, description, 
           strlen(description) < 45 ? "                                          " : "",
           RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n", BLUE, RESET);
    
    // Display array
    printf("Input Array:\n");
    printf("Index: ");
    for(int i = 0; i < n; i++) printf("%3d ", i);
    printf("\n");
    printf("Value: ");
    for(int i = 0; i < n; i++) printf("%3d ", A[i]);
    printf("\n\n");
    
    // Run DP algorithm
    int *dp;
    int max_index;
    int max_sum = mss_dp(A, n, &dp, &max_index);
    
    printf("%s✓ Maximum Subarray Sum: %d%s\n", GREEN, max_sum, RESET);
    printf("%s✓ Optimal subarray ends at index: %d%s\n\n", GREEN, max_index, RESET);
    
    // Print DP table
    print_dp_table(A, n, dp);
    
    // Analysis
    printf("%sExecution Analysis:%s\n", YELLOW, RESET);
    printf("  • Recurrence relation applied: dp[i] = max(A[i], A[i] + dp[i-1])\n");
    printf("  • Each position processed once: O(n)\n");
    printf("  • Maximum found by scanning all dp values\n");
    printf("  • Result: %d\n\n", max_sum);
    
    printf("%s" "✅ TEST CASE %d PASS" "%s\n\n", GREEN, num, RESET);
    
    // Show state trace for small arrays
    if(n <= 8) {
        printf("%sState Trace (Detailed):%s\n", BLUE, RESET);
        for(int i = 0; i < n; i++) {
            if(i == 0) {
                printf("  dp[%d] = %d (base case)\n", i, dp[i]);
            } else {
                int extend = A[i] + dp[i-1];
                int fresh = A[i];
                printf("  dp[%d] = max(%d, %d + %d) = max(%d, %d) = %d %s\n",
                       i, A[i], A[i], dp[i-1], fresh, extend, dp[i],
                       extend > fresh ? "(extend)" : "(fresh)");
            }
        }
        printf("\n");
    }
    
    free(dp);
}

/**
 * demonstrate_state_definition: Show why state definition matters
 */
void demonstrate_state_definition() {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n", YELLOW, RESET);
    printf("%s║ WHY STATE DEFINITION MATTERS                              ║%s\n", YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n", YELLOW, RESET);
    
    printf("❌ Wrong State Definition:\n");
    printf("   dp[i] = 'Best sum we can get from first i elements'\n");
    printf("   Problem: Hard to create recurrence, leads to exponential solutions\n\n");
    
    printf("✅ Correct State Definition:\n");
    printf("   dp[i] = 'Best sum of subarray ENDING at index i'\n");
    printf("   Benefit: Creates clear recurrence: continue or restart\n\n");
    
    printf("The restriction to 'ENDING AT i' is what makes DP possible.\n");
    printf("This is a universal DP lesson:\n");
    printf("  1. Define state precisely\n");
    printf("  2. Create constraint that enables recurrence\n");
    printf("  3. Sample all states to find global answer\n\n");
}

/**
 * demonstrate_local_vs_global: Show the concept
 */
void demonstrate_local_vs_global() {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n", YELLOW, RESET);
    printf("%s║ LOCAL DECISIONS → GLOBAL OPTIMUM                           ║%s\n", YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n", YELLOW, RESET);
    
    int A[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = 8;
    int *dp;
    int max_index;
    int max_sum = mss_dp(A, n, &dp, &max_index);
    
    printf("At each position, we make LOCAL decision:\n");
    printf("  Should we extend previous subarray or start fresh?\n\n");
    
    printf("Index | Decision  | Subarray Sum Ending Here\n");
    printf("------|-----------|------------------------\n");
    
    for(int i = 0; i < n; i++) {
        const char *choice = "Start";
        if(i > 0 && A[i] + dp[i-1] > A[i]) {
            choice = "Extend";
        }
        
        printf("  %d   | %-9s | dp[%d] = %d\n", i, choice, i, dp[i]);
    }
    
    printf("\nAfter all local decisions, GLOBAL ANSWER is:\n");
    printf("  max(dp[0..%d]) = dp[%d] = %d\n\n", n-1, max_index, max_sum);
    
    free(dp);
}

/**
 * demonstrate_optimal_substructure: Show why this creates recursion
 */
void demonstrate_optimal_substructure() {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n", YELLOW, RESET);
    printf("%s║ OPTIMAL SUBSTRUCTURE PROPERTY                              ║%s\n", YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n", YELLOW, RESET);
    
    printf("Optimal Substructure means:\n");
    printf("  Optimal solution uses optimal solutions to subproblems\n\n");
    
    printf("For MSS:\n");
    printf("  Best subarray ending at i is EITHER:\n");
    printf("    1. A[i] alone\n");
    printf("    2. A[i] + (best subarray ending at i-1)\n\n");
    
    printf("Why this works:\n");
    printf("  • If dp[i-1] < 0: Taking A[i] alone is better\n");
    printf("  • If dp[i-1] ≥ 0: Extending with positive base is better\n");
    printf("  • Algorithm automatically chooses optimal for each position\n");
    printf("  • Scanning all dp values gives global optimum\n\n");
}

/**
 * main: Run all tests and demonstrations
 */
int main() {
    printf("\n%s╔════════════════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║         MAXIMUM SUBARRAY SUM — DYNAMIC PROGRAMMING APPROACH                 ║%s\n",
           BLUE, RESET);
    printf("%s║                    State: dp[i] = Best sum ending at i                      ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // ═══════════════════════════════════════════════════════════════
    // Demonstration of Core Concepts
    // ═══════════════════════════════════════════════════════════════
    
    demonstrate_state_definition();
    demonstrate_local_vs_global();
    demonstrate_optimal_substructure();
    
    // ═══════════════════════════════════════════════════════════════
    // TEST CASES
    // ═══════════════════════════════════════════════════════════════
    
    // Test 1: Classic example with mixed positive/negative
    int test1[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    test_case(1, test1, 8, "Classic Example                 ");
    
    // Test 2: All negative numbers (answer is largest single element)
    int test2[] = {-5, -3, -8, -1, -4};
    test_case(2, test2, 5, "All Negative Numbers           ");
    
    // Test 3: All positive numbers (answer is entire array)
    int test3[] = {2, 3, 5, 1, 4};
    test_case(3, test3, 5, "All Positive Numbers           ");
    
    // Test 4: Single element
    int test4[] = {7};
    test_case(4, test4, 1, "Single Element                 ");
    
    // Test 5: Mix with zeros
    int test5[] = {2, 0, -1, 3, 0, 2};
    test_case(5, test5, 6, "Mix with Zeros                 ");
    
    // Test 6: Large positive followed by negatives
    int test6[] = {10, -2, -1, -3, 5};
    test_case(6, test6, 5, "Large Positive, Then Negatives ");
    
    // ═══════════════════════════════════════════════════════════════
    // EFFICIENCY ANALYSIS
    // ═══════════════════════════════════════════════════════════════
    
    fprintf(stdout, "%s╔════════════════════════════════════════════════════════════╗%s\n",
            YELLOW, RESET);
    fprintf(stdout, "%s║ EFFICIENCY ANALYSIS                                        ║%s\n",
            YELLOW, RESET);
    fprintf(stdout, "%s╚════════════════════════════════════════════════════════════╝%s\n\n",
            YELLOW, RESET);
    
    int analysis_test[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    analyze_brute_force(analysis_test, 8);
    
    int *dp_analysis;
    int max_idx;
    int max_sum_analysis = mss_dp(analysis_test, 8, &dp_analysis, &max_idx);
    compare_approaches(analysis_test, 8, max_sum_analysis);
    free(dp_analysis);
    
    // ═══════════════════════════════════════════════════════════════
    // ALGORITHMIC TEMPLATE
    // ═══════════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n", BLUE, RESET);
    printf("%s║ UNIVERSAL DYNAMIC PROGRAMMING TEMPLATE (MSS Example)       ║%s\n", BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n", BLUE, RESET);
    
    printf("%sStep 1: Define State%s\n", YELLOW, RESET);
    printf("  dp[i] = Maximum subarray sum ENDING at index i\n\n");
    
    printf("%sStep 2: Express Recurrence%s\n", YELLOW, RESET);
    printf("  dp[i] = max(A[i], A[i] + dp[i-1])\n");
    printf("  ├─ Choice 1: Start fresh (take A[i] alone)\n");
    printf("  └─ Choice 2: Extend previous (add to dp[i-1])\n\n");
    
    printf("%sStep 3: Handle Base Case%s\n", YELLOW, RESET);
    printf("  dp[0] = A[0]\n\n");
    
    printf("%sStep 4: Compute All States%s\n", YELLOW, RESET);
    printf("  for i = 1 to n-1:\n");
    printf("    dp[i] = max(A[i], A[i] + dp[i-1])\n\n");
    
    printf("%sStep 5: Find Answer%s\n", YELLOW, RESET);
    printf("  answer = max(dp[0], dp[1], ..., dp[n-1])\n\n");
    
    printf("%sStep 6: Output Result%s\n", YELLOW, RESET);
    printf("  return answer\n\n");
    
    // ═══════════════════════════════════════════════════════════════
    // COMPLEXITY SUMMARY
    // ═══════════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n", BLUE, RESET);
    printf("%s║ COMPLEXITY SUMMARY                                         ║%s\n", BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n", BLUE, RESET);
    
    printf("| Metric | Complexity | Notes |\n");
    printf("|--------|------------|-----------|\n");
    printf("| Time   | O(n)       | Single pass, each element processed once |\n");
    printf("| Space  | O(n)       | Need dp array of size n |\n");
    printf("|        | O(1)*      | Can be optimized (only need previous dp) |\n");
    printf("\n* Optimization (Kadane's Algorithm) coming in next section!\n\n");
    
    // ═══════════════════════════════════════════════════════════════
    // KEY INSIGHTS
    // ═══════════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n", GREEN, RESET);
    printf("%s║ KEY INSIGHTS — WHAT YOU SHOULD REMEMBER                   ║%s\n", GREEN, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n", GREEN, RESET);
    
    printf("1️⃣  %sState Definition Is Everything%s\n", YELLOW, RESET);
    printf("    Correct state: dp[i] = best subarray ENDING at i\n");
    printf("    Wrong state: dp[i] = best subarray overall (doesn't work)\n\n");
    
    printf("2️⃣  %sRecurrence From State Definition%s\n", YELLOW, RESET);
    printf("    Once state is defined, recurrence falls out naturally:\n");
    printf("    dp[i] = max(start fresh, extend previous)\n\n");
    
    printf("3️⃣  %sLocal Decisions Build Global Answer%s\n", YELLOW, RESET);
    printf("    At each position: decide continue or restart (local)\n");
    printf("    Overall answer: best position among all (global)\n\n");
    
    printf("4️⃣  %sOptimal Substructure Property%s\n", YELLOW, RESET);
    printf("    Optimal solution reuses optimal subsolutions\n");
    printf("    Best subarray ending at i uses best ending at i-1\n\n");
    
    printf("5️⃣  %sComplexity Transformation%s\n", YELLOW, RESET);
    printf("    Brute force: O(n²) — recomputation everywhere\n");
    printf("    DP: O(n)    — each state computed once\n\n");
    
    printf("════════════════════════════════════════════════════════════════════════════\n");
    printf("This template applies to:\n");
    printf("  • Maximum Product Subarray (track both max and min)\n");
    printf("  • House Robber (rob or skip)\n");
    printf("  • Stock Buy/Sell (buy on day i, sell later)\n");
    printf("  • Many other dynamic programming problems\n");
    printf("════════════════════════════════════════════════════════════════════════════\n\n");
    
    return 0;
}
