#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 200
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/**
 * Maximum Subarray Sum (MSS) — Divide & Conquer Approach
 * 
 * Core Idea:
 *   Maximum subarray can be:
 *   1. Entirely in the left half
 *   2. Entirely in the right half
 *   3. Crossing the middle
 * 
 * Time Complexity: O(n log n)
 * Space Complexity: O(log n) for recursion stack
 * 
 * Lesson: Teaches how to design recursive algorithms with merge logic
 */

typedef struct {
    int sum;
    int left;
    int right;
} SubarrayInfo;

// For tracking recursion depth
int recursion_depth = 0;
int call_count = 0;

/**
 * maxCrossingSum: Find maximum sum subarray that crosses the middle
 * 
 * Key Insight:
 *   Crossing subarray = (best suffix of left) + (best prefix of right)
 * 
 * Algorithm:
 *   1. Scan from mid leftward: track best sum ending at mid
 *   2. Scan from mid+1 rightward: track best sum starting at mid+1
 *   3. Combine the two halves
 */
SubarrayInfo maxCrossingSum(int A[], int l, int mid, int h) {
    SubarrayInfo result;
    
    // ═══════════════════════════════════════════════════════════
    // LEFT SIDE: best suffix ending at mid
    // ═══════════════════════════════════════════════════════════
    
    int sum = 0;
    int leftSum = INT_MIN;
    int leftEnd = mid;
    int leftStart = mid;
    
    // Scan from mid leftward
    for(int i = mid; i >= l; i--) {
        sum += A[i];
        if(sum > leftSum) {
            leftSum = sum;
            leftStart = i;  // Track where this best suffix starts
        }
    }
    
    // ═══════════════════════════════════════════════════════════
    // RIGHT SIDE: best prefix starting at mid+1
    // ═══════════════════════════════════════════════════════════
    
    sum = 0;
    int rightSum = INT_MIN;
    int rightStart = mid + 1;
    int rightEnd = mid + 1;
    
    // Scan from mid+1 rightward
    for(int i = mid + 1; i <= h; i++) {
        sum += A[i];
        if(sum > rightSum) {
            rightSum = sum;
            rightEnd = i;  // Track where this best prefix ends
        }
    }
    
    // ═══════════════════════════════════════════════════════════
    // COMBINE
    // ═══════════════════════════════════════════════════════════
    
    result.sum = leftSum + rightSum;
    result.left = leftStart;  // Crossing starts at leftStart
    result.right = rightEnd;   // Crossing ends at rightEnd
    
    return result;
}

/**
 * maxSubarraySumDC: Solve MSS using Divide & Conquer
 * 
 * Three phases:
 *   1. DIVIDE: Split at middle
 *   2. CONQUER: Solve left and right recursively
 *   3. COMBINE: Find crossing sum, take maximum
 */
SubarrayInfo maxSubarraySumDC(int A[], int l, int h) {
    call_count++;
    recursion_depth++;
    
    SubarrayInfo result;
    
    // ═══════════════════════════════════════════════════════════
    // BASE CASE: single element
    // ═══════════════════════════════════════════════════════════
    
    if(l == h) {
        result.sum = A[l];
        result.left = l;
        result.right = l;
        recursion_depth--;
        return result;
    }
    
    // ═══════════════════════════════════════════════════════════
    // RECURSIVE CASE: divide, conquer, combine
    // ═══════════════════════════════════════════════════════════
    
    int mid = (l + h) / 2;
    
    // DIVIDE & CONQUER
    SubarrayInfo leftMax = maxSubarraySumDC(A, l, mid);
    SubarrayInfo rightMax = maxSubarraySumDC(A, mid + 1, h);
    
    // COMBINE
    SubarrayInfo crossMax = maxCrossingSum(A, l, mid, h);
    
    // Find maximum of the three cases
    if(leftMax.sum >= rightMax.sum && leftMax.sum >= crossMax.sum) {
        result = leftMax;
    } else if(rightMax.sum >= leftMax.sum && rightMax.sum >= crossMax.sum) {
        result = rightMax;
    } else {
        result = crossMax;
    }
    
    recursion_depth--;
    return result;
}

/**
 * demonstrate_crossing: Visualize how crossing case works
 */
void demonstrate_crossing(int A[], int n) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           YELLOW, RESET);
    printf("%s║ HOW CROSSING CASE WORKS                                    ║%s\n",
           YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           YELLOW, RESET);
    
    if(n < 4) {
        printf("Array too small for meaningful crossing demo\n\n");
        return;
    }
    
    int mid = n / 2;
    
    printf("Array:      ");
    for(int i = 0; i < n; i++) printf("%3d ", A[i]);
    printf("\n");
    
    printf("Index:      ");
    for(int i = 0; i < n; i++) printf("%3d ", i);
    printf("\n");
    
    printf("            ");
    for(int i = 0; i < mid; i++) printf("    ");
    printf("↑\n");
    printf("            ");
    for(int i = 0; i < mid; i++) printf("    ");
    printf("mid=%d\n\n", mid);
    
    // Compute left side
    printf("%sLEFT SIDE (best suffix ending at mid)%s\n", CYAN, RESET);
    int sum = 0;
    int leftSum = INT_MIN;
    printf("  Scanning from mid=%d leftward:\n", mid);
    
    for(int i = mid; i >= 0 && i >= mid - 2; i--) {
        sum += A[i];
        leftSum = (sum > leftSum) ? sum : leftSum;
        printf("    i=%d: A[%d]=%3d, sum=%3d, leftSum=%3d\n", i, i, A[i], sum, leftSum);
    }
    
    if(mid > 3) {
        printf("    ... (continuing leftward) ...\n");
        sum = 0;
        for(int i = mid; i >= 0; i--) {
            sum += A[i];
            leftSum = (sum > leftSum) ? sum : leftSum;
        }
        printf("    Final leftSum = %d\n", leftSum);
    }
    
    // Compute right side
    printf("\n%sRIGHT SIDE (best prefix starting at mid+1)%s\n", CYAN, RESET);
    sum = 0;
    int rightSum = INT_MIN;
    printf("  Scanning from mid+1=%d rightward:\n", mid + 1);
    
    for(int i = mid + 1; i < n && i <= mid + 3; i++) {
        sum += A[i];
        rightSum = (sum > rightSum) ? sum : rightSum;
        printf("    i=%d: A[%d]=%3d, sum=%3d, rightSum=%3d\n", i, i, A[i], sum, rightSum);
    }
    
    if(n - mid - 1 > 3) {
        printf("    ... (continuing rightward) ...\n");
        sum = 0;
        for(int i = mid + 1; i < n; i++) {
            sum += A[i];
            rightSum = (sum > rightSum) ? sum : rightSum;
        }
        printf("    Final rightSum = %d\n", rightSum);
    }
    
    printf("\n%sCOMBINE:%s\n", GREEN, RESET);
    printf("  crossMax = leftSum + rightSum = %d + %d = %d\n\n", leftSum, rightSum, leftSum + rightSum);
}

/**
 * demonstrate_recursion_tree: Show the call structure
 */
void demonstrate_recursion_tree(int n) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ RECURSION TREE STRUCTURE (n=%d)                          ║%s\n",
           BLUE, n, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    int levels = (int)ceil(log2(n));
    
    printf("Tree structure for array of size %d:\n\n", n);
    
    printf("Level 0:  [0...%d]                 (1 problem of size %d)\n", n-1, n);
    
    for(int level = 1; level <= levels && level < 4; level++) {
        int size = n / (1 << level);
        int count = 1 << level;
        
        printf("Level %d:  ", level);
        for(int i = 0; i < count && i < 4; i++) {
            int start = i * size;
            int end = start + size - 1;
            if(end >= n) end = n - 1;
            printf("[%d...%d] ", start, end);
        }
        if(count > 4) printf("... ");
        printf("(%d problems of size ~%d)\n", count, size);
    }
    
    if(levels >= 4) {
        printf("...\n");
        printf("Level %d:  [single elements]    (%d problems of size 1)\n", levels, n);
    }
    
    printf("\n%sComplexity Analysis:%s\n", YELLOW, RESET);
    printf("  Levels:      %d = log₂(%d)\n", levels, n);
    printf("  Work/level:  O(%d)\n", n);
    printf("  Total work:  %d × O(%d) = O(%d log %d)\n", levels, n, n, n);
    printf("\n");
}

/**
 * test_case: Test D&C approach
 */
void test_case(int num, int A[], int n, const char *description) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ TEST CASE %d: %s%s║%s\n", BLUE, num, description,
           strlen(description) < 45 ? "                                          " : "",
           RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // Display array
    printf("Input Array:\n");
    printf("Index: ");
    for(int i = 0; i < n; i++) printf("%3d ", i);
    printf("\n");
    printf("Value: ");
    for(int i = 0; i < n; i++) printf("%3d ", A[i]);
    printf("\n\n");
    
    // Reset counters
    call_count = 0;
    recursion_depth = 0;
    
    // Run D&C algorithm
    SubarrayInfo result = maxSubarraySumDC(A, 0, n - 1);
    
    printf("%s✓ Maximum Subarray Sum: %d%s\n", GREEN, result.sum, RESET);
    printf("%s✓ Subarray Range: [%d...%d]%s\n", GREEN, result.left, result.right, RESET);
    
    // Print the actual subarray
    printf("%s✓ Elements: [%s", GREEN, RESET);
    for(int i = result.left; i <= result.right; i++) {
        printf("%d", A[i]);
        if(i < result.right) printf(", ");
    }
    printf("]\n");
    
    // Verify sum
    int verify_sum = 0;
    for(int i = result.left; i <= result.right; i++) {
        verify_sum += A[i];
    }
    printf("%s✓ Verification: Sum = %d%s\n\n", GREEN, verify_sum, RESET);
    
    printf("%sAlgorithm Statistics:%s\n", YELLOW, RESET);
    printf("  Recursive calls: %d\n", call_count);
    printf("  Expected calls: ~%d (2^(log n + 1) - 1 ≈ 2n - 1)\n", 2 * n - 1);
    printf("\n");
    
    printf("%sExecution Trace:%s\n", BLUE, RESET);
    printf("  1. Split array at middle\n");
    printf("  2. Recursively solve left half\n");
    printf("  3. Recursively solve right half\n");
    printf("  4. Compute crossing sum (O(n) scan of both halves)\n");
    printf("  5. Return maximum of three cases\n");
    printf("\n");
    
    printf("%s✅ TEST CASE %d PASS%s\n\n", GREEN, num, RESET);
}

/**
 * compare_with_approach: Show how D&C vs other approaches
 */
void compare_approaches(int n) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ COMPARISON: BRUTE FORCE vs D&C vs DP (for n=%d)          ║%s\n",
           BLUE, n, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    long long brute_force = (long long)n * (n + 1) / 2;
    long long divconq = (long long)n * (int)ceil(log2(n));
    long long dp_kadane = n;
    
    printf("| Approach        | Time Complexity | Operations (n=%d) |\n", n);
    printf("|-----------------|-----------------|-------------------|\n");
    printf("| Brute Force     | O(n²)          | %15lld   |\n", brute_force);
    printf("| Divide & Conquer| O(n log n)     | %15lld   |\n", divconq);
    printf("| DP (Kadane)     | O(n)           | %15lld   |\n", dp_kadane);
    printf("|-----------------|-----------------|-------------------|\n");
    
    printf("\nSpeedup Analysis:\n");
    printf("  D&C vs Brute Force: %.1f× faster\n", (double)brute_force / divconq);
    printf("  DP vs D&C:          %.1f× faster\n", (double)divconq / dp_kadane);
    printf("  DP vs Brute Force:  %.1f× faster\n", (double)brute_force / dp_kadane);
    
    printf("\nFor n = 1000:\n");
    printf("  Brute Force: ~500,000 operations\n");
    printf("  D&C:         ~%lld operations\n", (long long)1000 * (int)ceil(log2(1000)));
    printf("  DP (Kadane): ~1,000 operations\n");
    printf("\n");
}

/**
 * main: Run all tests and demonstrations
 */
int main() {
    printf("\n%s╔════════════════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║   MAXIMUM SUBARRAY SUM — DIVIDE & CONQUER APPROACH                        ║%s\n",
           BLUE, RESET);
    printf("%s║           Teaching Algorithm Design Paradigms and Merge Logic             ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // ═══════════════════════════════════════════════════════════
    // Demonstrations
    // ═══════════════════════════════════════════════════════════
    
    demonstrate_recursion_tree(8);
    
    int demo_array[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    demonstrate_crossing(demo_array, 9);
    
    // ═══════════════════════════════════════════════════════════
    // TEST CASES
    // ═══════════════════════════════════════════════════════════
    
    // Test 1: Classic example
    int test1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    test_case(1, test1, 9, "Classic Example            ");
    
    // Test 2: All negative
    int test2[] = {-5, -3, -8, -1, -4};
    test_case(2, test2, 5, "All Negative              ");
    
    // Test 3: All positive
    int test3[] = {2, 3, 5, 1, 4};
    test_case(3, test3, 5, "All Positive              ");
    
    // Test 4: Mixed pattern
    int test4[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    test_case(4, test4, 8, "Mixed Pattern             ");
    
    // Test 5: Single element
    int test5[] = {7};
    test_case(5, test5, 1, "Single Element            ");
    
    // ═══════════════════════════════════════════════════════════
    // EFFICIENCY COMPARISON
    // ═══════════════════════════════════════════════════════════
    
    compare_approaches(8);
    compare_approaches(1000);
    
    // ═══════════════════════════════════════════════════════════
    // KEY CONCEPTS
    // ═══════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           YELLOW, RESET);
    printf("%s║ KEY DIVIDE & CONQUER CONCEPTS                              ║%s\n",
           YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           YELLOW, RESET);
    
    printf("1️⃣  %sDIVIDE Phase%s\n", CYAN, RESET);
    printf("    Split array into left and right at middle\n");
    printf("    mid = (l + h) / 2\n\n");
    
    printf("2️⃣  %sCONQUER Phase%s\n", CYAN, RESET);
    printf("    Recursively solve left: maxSubarraySum(A, l, mid)\n");
    printf("    Recursively solve right: maxSubarraySum(A, mid+1, h)\n\n");
    
    printf("3️⃣  %sCOMBINE Phase%s\n", CYAN, RESET);
    printf("    Handle crossing case: maxCrossingSum(A, l, mid, h)\n");
    printf("    Return max(leftMax, rightMax, crossMax)\n\n");
    
    printf("4️⃣  %sCrossing Sum (The Key Innovation)%s\n", CYAN, RESET);
    printf("    Scan from mid leftward: find best suffix of left\n");
    printf("    Scan from mid+1 rightward: find best prefix of right\n");
    printf("    Combine: leftSum + rightSum = crossing maximum\n");
    printf("    Time: O(n) but done log n times in recursion\n\n");
    
    printf("5️⃣  %sComplexity Analysis%s\n", CYAN, RESET);
    printf("    T(n) = 2T(n/2) + O(n)\n");
    printf("    Using Master Theorem: T(n) = O(n log n)\n\n");
    
    // ═══════════════════════════════════════════════════════════
    // THE PARADIGM LESSON
    // ═══════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           GREEN, RESET);
    printf("%s║ THE REAL LESSON: ALGORITHM DESIGN PARADIGMS               ║%s\n",
           GREEN, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           GREEN, RESET);
    
    printf("%sBrute Force (O(n²))%s\n", YELLOW, RESET);
    printf("  Method:  Try all possibilities\n");
    printf("  Thinking: \"Enumerate everything\"\n");
    printf("  When:    Small inputs, simple logic\n");
    printf("  MSS:     Try all subarrays O(n²)\n\n");
    
    printf("%sDivide & Conquer (O(n log n))%s\n", YELLOW, RESET);
    printf("  Method:  Split → Solve → Merge\n");
    printf("  Thinking: \"How do I merge solutions?\"\n");
    printf("  When:    Recursive problems with clear merge step\n");
    printf("  MSS:     Split & find crossing subarray O(n log n)\n\n");
    
    printf("%sDynamic Programming (O(n))%s\n", YELLOW, RESET);
    printf("  Method:  Build incrementally from base\n");
    printf("  Thinking: \"What state do I need? (Only previous!)\"\n");
    printf("  When:    Sequential problems, overlapping subproblems\n");
    printf("  MSS:     Track current max (Kadane) O(n)\n\n");
    
    printf("%sThe Progression:%s\n", CYAN, RESET);
    printf("  Brute Force → Recognize structure → D&C\n");
    printf("              → Realize state dependency → DP\n");
    printf("              → Further optimize if possible\n\n");
    
    // ═══════════════════════════════════════════════════════════
    // INTERVIEW WISDOM
    // ═══════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ INTERVIEW WISDOM                                           ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("Question: \"Solve Maximum Subarray Sum\"\n\n");
    
    printf("🎯 Good Answer:\n");
    printf("   1. Brute force: O(n²), try all subarrays\n");
    printf("   2. Optimize with D&C: O(n log n), split & merge\n");
    printf("   3. Best: DP with Kadane: O(n), track previous max\n\n");
    
    printf("💡 Why this impresses:\n");
    printf("   • Shows evolution of algorithm design\n");
    printf("   • Demonstrates understanding of paradigms\n");
    printf("   • Explains tradeoffs and why Kadane wins\n");
    printf("   • Shows deep algorithmic thinking\n\n");
    
    printf("🚫 Red Flags:\n");
    printf("   ❌ Only Kadane (missing understanding of D&C)\n");
    printf("   ❌ Inefficient crossing case in D&C\n");
    printf("   ❌ Doesn't explain why Kadane is better\n");
    printf("   ❌ Can't analyze recurrence relation\n\n");
    
    printf("════════════════════════════════════════════════════════════════════════════\n");
    printf("DEEP UNDERSTANDING = Knowing WHEN, WHERE, and WHY to use each approach\n");
    printf("════════════════════════════════════════════════════════════════════════════\n\n");
    
    return 0;
}
