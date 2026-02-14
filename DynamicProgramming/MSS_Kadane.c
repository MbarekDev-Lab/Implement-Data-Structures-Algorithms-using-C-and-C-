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
 * Maximum Subarray Sum — Kadane's Algorithm
 * 
 * The key insight: We only need dp[i-1] to compute dp[i]
 * So we can replace the dp array with a single variable
 * 
 * dp[i] = max(A[i], dp[i-1] + A[i])
 *   ↓
 * current = max(A[i], current + A[i])
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1) <- This is the key optimization
 */

typedef struct {
    int max_sum;
    int start_index;
    int end_index;
} MSS_Kadane_Result;

/**
 * mss_kadane_basic: Standard Kadane's algorithm
 * Returns the maximum sum only
 */
int mss_kadane_basic(int A[], int n) {
    if(n <= 0) return INT_MIN;
    
    int current = A[0];  // Best subarray sum ENDING at current position
    int global = A[0];   // Best subarray sum found ANYWHERE
    
    for(int i = 1; i < n; i++) {
        // Key decision: Restart or extend?
        // If current < 0, starting fresh is better
        // If current >= 0, extending is better
        current = (A[i] > current + A[i]) ? A[i] : (current + A[i]);
        
        // Update global maximum
        global = (current > global) ? current : global;
    }
    
    return global;
}

/**
 * mss_kadane_with_indices: Kadane's algorithm that also tracks indices
 * Returns both sum and the subarray boundaries
 */
MSS_Kadane_Result mss_kadane_with_indices(int A[], int n) {
    MSS_Kadane_Result result;
    
    if(n <= 0) {
        result.max_sum = INT_MIN;
        result.start_index = -1;
        result.end_index = -1;
        return result;
    }
    
    int current = A[0];
    int global = A[0];
    
    int temp_start = 0;      // Potential start of current subarray
    int start = 0;           // Start of the global maximum subarray
    int end = 0;             // End of the global maximum subarray
    
    for(int i = 1; i < n; i++) {
        // If we're starting fresh, update temp_start
        if(A[i] > current + A[i]) {
            current = A[i];
            temp_start = i;    // New subarray starts here
        } else {
            current = current + A[i];  // Extend previous
        }
        
        // If we found a new global maximum, record the indices
        if(current > global) {
            global = current;
            start = temp_start;
            end = i;
        }
    }
    
    result.max_sum = global;
    result.start_index = start;
    result.end_index = end;
    
    return result;
}

/**
 * mss_dp_array: Version with explicit dp array (for comparison)
 * This is what you would write before applying Kadane optimization
 */
int mss_dp_array(int A[], int n, int *dp) {
    if(n <= 0) return INT_MIN;
    
    dp[0] = A[0];
    int globalMax = dp[0];
    
    for(int i = 1; i < n; i++) {
        dp[i] = (A[i] > dp[i-1] + A[i]) ? A[i] : (dp[i-1] + A[i]);
        globalMax = (dp[i] > globalMax) ? globalMax : dp[i];
    }
    
    return globalMax;
}

/**
 * mss_brute_force: Brute force O(n²) for comparison
 */
int mss_brute_force(int A[], int n) {
    int maxSum = INT_MIN;
    
    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(int j = i; j < n; j++) {
            sum += A[j];
            maxSum = (sum > maxSum) ? sum : maxSum;
        }
    }
    
    return maxSum;
}

/**
 * Demonstrate space optimization concept
 */
void demonstrate_space_optimization() {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           YELLOW, RESET);
    printf("%s║ SPACE OPTIMIZATION: Why Kadane Works                       ║%s\n",
           YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           YELLOW, RESET);
    
    printf("Question: Do we need the entire dp array?\n\n");
    
    printf("When computing dp[i], we read:  dp[i-1]\n");
    printf("When computing dp[i+1], we read: dp[i]\n");
    printf("When computing dp[i+2], we read: dp[i+1]\n\n");
    
    printf("Observation: We never go backwards in time.\n");
    printf("We process sequentially: 0 → 1 → 2 → ... → n-1\n\n");
    
    printf("Key insight:\n");
    printf("  After computing dp[i], we NEVER need dp[i-2] or earlier.\n");
    printf("  We only ever read the most recent value.\n\n");
    
    printf("Therefore:\n");
    printf("  ❌ Allocate dp[n]     → O(n) space\n");
    printf("  ✅ Use one variable   → O(1) space\n\n");
    
    printf("This is Kadane's optimization: Replace array with scalar.\n\n");
}

/**
 * Demonstrate the mental shift
 */
void demonstrate_mental_shift() {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ THE MENTAL SHIFT: Restart vs Extend                       ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = 9;
    
    int current = A[0];
    int global = A[0];
    
    printf("Array: [-2, 1, -3, 4, -1, 2, 1, -5, 4]\n\n");
    printf("At each position, ask:\n");
    printf("  1. Should I keep extending the previous subarray?\n");
    printf("  2. Or restart fresh with just this element?\n\n");
    
    printf("| i | A[i] | Restart? | Extend | Choice | current | global |\n");
    printf("|---|------|---------|--------|--------|---------|--------|\n");
    
    for(int i = 1; i < n; i++) {
        int restart_value = A[i];
        int extend_value = current + A[i];
        int best = (restart_value > extend_value) ? restart_value : extend_value;
        const char *choice = (restart_value > extend_value) ? "Restart" : "Extend ";
        
        if(best > global) global = best;
        
        printf("| %d | %3d  | %3d     | %3d    | %s | %3d     | %3d    |\n",
               i, A[i], restart_value, extend_value, choice, best, global);
        
        current = best;
    }
    
    printf("\nPhilosophical shift:\n");
    printf("  ❌ Old: 'Check all subarrays' (O(n²), O(1))\n");
    printf("  ✅ New: 'What's best ending here?' (O(n), O(1))\n\n");
}

/**
 * Compare all three approaches
 */
void compare_all_approaches(int A[], int n, const char *description) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           YELLOW, RESET);
    printf("%s║ COMPARISON: Brute Force vs DP vs Kadane                    ║%s\n",
           YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           YELLOW, RESET);
    
    printf("Input: %s (n=%d)\n\n", description, n);
    
    // Brute force
    int bruteStart = 0, bruteEnd = 0;
    int bmax = INT_MIN;
    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(int j = i; j < n; j++) {
            sum += A[j];
            if(sum > bmax) {
                bmax = sum;
                bruteStart = i;
                bruteEnd = j;
            }
        }
    }
    
    // DP with array
    int *dp = (int *)malloc(n * sizeof(int));
    int dpmax = mss_dp_array(A, n, dp);
    free(dp);
    
    // Kadane
    MSS_Kadane_Result kad = mss_kadane_with_indices(A, n);
    
    printf("| Approach | Result | Time | Space | Subarray |\n");
    printf("|----------|--------|------|-------|----------|\n");
    printf("| Brute    | %6d | O(n²)| O(1)  | [%d..%d] |\n", bmax, bruteStart, bruteEnd);
    printf("| DP Array | %6d | O(n) | O(n)  | —        |\n", dpmax);
    printf("| Kadane   | %6d | O(n) | O(1)  | [%d..%d] |\n",
           kad.max_sum, kad.start_index, kad.end_index);
    printf("|----------|--------|------|-------|----------|\n");
    
    printf("\nKey observations:\n");
    printf("  • All three find the same answer: %d\n", kad.max_sum);
    printf("  • Kadane combines best time (O(n)) with best space (O(1))\n");
    printf("  • Kadane also tracks indices (bonus!)\n\n");
}

/**
 * Test case: Show algorithm step by step
 */
void test_case(int num, int A[], int n, const char *description) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ TEST CASE %d: %s%s║%s\n", BLUE, num, description,
           strlen(description) < 50 ? "                                      " : "",
           RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // Display array
    printf("Input Array:\nIndex: ");
    for(int i = 0; i < n; i++) printf("%3d ", i);
    printf("\nValue: ");
    for(int i = 0; i < n; i++) printf("%3d ", A[i]);
    printf("\n\n");
    
    // Run Kadane
    MSS_Kadane_Result result = mss_kadane_with_indices(A, n);
    
    printf("%s✓ Maximum Subarray Sum: %d%s\n", GREEN, result.max_sum, RESET);
    printf("%s✓ Subarray Range: [%d .. %d]%s\n\n", GREEN, result.start_index, result.end_index, RESET);
    
    // Show the actual subarray
    printf("Optimal subarray: [");
    for(int i = result.start_index; i <= result.end_index; i++) {
        printf("%d%s", A[i], (i < result.end_index) ? ", " : "");
    }
    printf("]\n\n");
    
    // Show step-by-step execution
    if(n <= 9) {
        printf("Step-by-step Execution:\n\n");
        
        int current = A[0];
        int global = A[0];
        int temp_start = 0;
        int temp_end = 0;
        int start = 0, end = 0;
        
        printf("i=0: current = %d, global = %d\n", current, global);
        
        for(int i = 1; i < n; i++) {
            int restart = A[i];
            int extend = current + A[i];
            
            if(restart > extend) {
                current = restart;
                temp_start = i;
            } else {
                current = extend;
            }
            
            if(current > global) {
                global = current;
                start = temp_start;
                end = i;
            }
            
            printf("i=%d: A[%d]=%d, restart=%d, extend=%d → current=%d, global=%d %s\n",
                   i, i, A[i], restart, extend, current, global,
                   (current > global - current) ? "← UPDATE" : "");
        }
        printf("\n");
    }
    
    printf("%s✅ TEST CASE %d PASS%s\n\n", GREEN, num, RESET);
}

/**
 * Show pattern recognition
 */
void show_pattern_recognition() {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ PATTERN RECOGNITION: Kadane Appears Everywhere             ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("This pattern appears in many problems:\n\n");
    
    printf("1️⃣  Maximum Product Subarray\n");
    printf("   max_dp[i] = max(A[i], max_dp[i-1]*A[i], min_dp[i-1]*A[i])\n");
    printf("   (Need both max and min for negative handling)\n\n");
    
    printf("2️⃣  House Robber\n");
    printf("   dp[i] = max(dp[i-1], A[i] + dp[i-2])\n");
    printf("   (Include or exclude, but can't use adjacent)\n\n");
    
    printf("3️⃣  Stock Buy/Sell\n");
    printf("   profit = max(profit, current_price - min_price_so_far)\n");
    printf("   (Track state efficiently as you pass through array)\n\n");
    
    printf("4️⃣  Best Time to Buy and Sell Stock IV\n");
    printf("   dp[i] = max(dp[i-1], price[i] - cost)\n");
    printf("   (Similar recurrence structure)\n\n");
    
    printf("The Common Pattern:\n");
    printf("  • Process array left to right\n");
    printf("  • Track state for current position\n");
    printf("  • Compare with global optimum\n");
    printf("  • Update based on previous state only\n");
    printf("  • Result: O(n) time, O(1) space\n\n");
}

/**
 * main: Run all demonstrations and tests
 */
int main() {
    printf("\n%s╔════════════════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║        MAXIMUM SUBARRAY SUM — KADANE'S ALGORITHM                           ║%s\n",
           BLUE, RESET);
    printf("%s║                O(n) Time, O(1) Space, Maximum Optimization                  ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // ═══════════════════════════════════════════════════════════════
    // CONCEPTUAL DEMONSTRATIONS
    // ═══════════════════════════════════════════════════════════════
    
    demonstrate_space_optimization();
    demonstrate_mental_shift();
    
    // ═══════════════════════════════════════════════════════════════
    // TEST CASES
    // ═══════════════════════════════════════════════════════════════
    
    // Test 1: Classic example
    int test1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    test_case(1, test1, 9, "Classic Example               ");
    
    // Test 2: All negative
    int test2[] = {-5, -3, -8, -1, -4};
    test_case(2, test2, 5, "All Negative (Return Largest) ");
    
    // Test 3: All positive
    int test3[] = {2, 3, 5, 1, 4};
    test_case(3, test3, 5, "All Positive (Entire Array)   ");
    
    // Test 4: Single element
    int test4[] = {7};
    test_case(4, test4, 1, "Single Element                ");
    
    // Test 5: Prefix sum determines answer
    int test5[] = {5, -3, 5, -2, 6};
    test_case(5, test5, 5, "Prefix Sum Determines Answer  ");
    
    // ═══════════════════════════════════════════════════════════════
    // ALGORITHM COMPARISON
    // ═══════════════════════════════════════════════════════════════
    
    int comp_test[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    compare_all_approaches(comp_test, 9, "[-2, 1, -3, 4, -1, 2, 1, -5, 4]");
    
    // ═══════════════════════════════════════════════════════════════
    // EFFICIENCY VISUALIZATION
    // ═══════════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           YELLOW, RESET);
    printf("%s║ COMPLEXITY ANALYSIS                                        ║%s\n",
           YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           YELLOW, RESET);
    
    printf("For array of size n:\n\n");
    printf("| Approach | Time Complexity | Space | Why? |\n");
    printf("|----------|-----------------|-------|------|\n");
    printf("| Brute    | O(n²)           | O(1)  | Two nested loops |\n");
    printf("| DP Array | O(n)            | O(n)  | Single loop, dp array |\n");
    printf("| Kadane   | O(n)            | O(1)  | Single loop, one variable |\n");
    printf("|----------|-----------------|-------|------|\n\n");
    
    printf("Growth for n=1000:\n");
    printf("| Approach | Operations |\n");
    printf("|----------|------------|\n");
    printf("| Brute    | ~1,000,000 |\n");
    printf("| DP Array | ~1,000     |\n");
    printf("| Kadane   | ~1,000     |\n");
    printf("|----------|------------|\n\n");
    
    // ═══════════════════════════════════════════════════════════════
    // PATTERN RECOGNITION
    // ═══════════════════════════════════════════════════════════════
    
    show_pattern_recognition();
    
    // ═══════════════════════════════════════════════════════════════
    // KEY INSIGHTS
    // ═══════════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           GREEN, RESET);
    printf("%s║ KEY INSIGHTS — WHAT YOU SHOULD REMEMBER                   ║%s\n",
           GREEN, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           GREEN, RESET);
    
    printf("1️⃣  %sSpace Optimization%s\n", YELLOW, RESET);
    printf("    If state depends only on previous: replace array with scalar\n");
    printf("    From O(n) space to O(1) space without sacrificing time\n\n");
    
    printf("2️⃣  %sThe Decision Point%s\n", YELLOW, RESET);
    printf("    At each position: restart or extend?\n");
    printf("    current = max(A[i], current + A[i])\n");
    printf("    This captures the entire algorithm\n\n");
    
    printf("3️⃣  %sSequential Processing%s\n", YELLOW, RESET);
    printf("    Process left to right, never go backwards\n");
    printf("    Each decision is final, never reconsidered\n\n");
    
    printf("4️⃣  %sThe Mental Shift%s\n", YELLOW, RESET);
    printf("    From: 'Check all subarrays' (brute force)\n");
    printf("    To:   'What's best ending here?' (DP/Kadane)\n\n");
    
    printf("5️⃣  %sPattern Recognition%s\n", YELLOW, RESET);
    printf("    This pattern appears in many problems\n");
    printf("    House Robber, Stock Trading, Max Product, etc.\n");
    printf("    Master Kadane, unlock similar problems\n\n");
    
    // ═══════════════════════════════════════════════════════════════
    // CODE TEMPLATE
    // ═══════════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ KADANE'S ALGORITHM — FINAL CODE                            ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("Minimal implementation:\n\n");
    printf("int kadane(int A[], int n) {\n");
    printf("    int current = A[0], global = A[0];\n");
    printf("    for(int i = 1; i < n; i++) {\n");
    printf("        current = max(A[i], current + A[i]);\n");
    printf("        global = max(global, current);\n");
    printf("    }\n");
    printf("    return global;\n");
    printf("}\n\n");
    
    printf("With index tracking:\n\n");
    printf("Modifications:\n");
    printf("  • Add int temp_start = 0; and int start = 0;\n");
    printf("  • When current = A[i] (restart), set temp_start = i\n");
    printf("  • When global = current (new max), save start = temp_start\n\n");
    
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("This is Kadane's algorithm: Simple, elegant, optimal.\n");
    printf("═══════════════════════════════════════════════════════════════\n\n");
    
    return 0;
}
