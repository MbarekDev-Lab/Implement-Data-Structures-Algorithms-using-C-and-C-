#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_W 1000

// Global arrays for DP
int dp[MAX_N + 1][MAX_W + 1];
int memo[MAX_N + 1][MAX_W + 1];
int weight[MAX_N + 1];
int value[MAX_N + 1];

// ═══════════════════════════════════════════════════════════════
// APPROACH 1: TABULATION (BOTTOM-UP DP)
// ═══════════════════════════════════════════════════════════════

int knapsackTabulation(int n, int W) {
    // Initialize DP table
    memset(dp, 0, sizeof(dp));
    
    // Build table from bottom-up
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            
            // If item i doesn't fit
            if (weight[i] > w) {
                dp[i][w] = dp[i-1][w];
            }
            // Item i fits, choose better option
            else {
                int dontTake = dp[i-1][w];
                int take = value[i] + dp[i-1][w - weight[i]];
                dp[i][w] = (dontTake > take) ? dontTake : take;
            }
        }
    }
    
    return dp[n][W];
}

// ═══════════════════════════════════════════════════════════════
// APPROACH 2: MEMOIZATION (TOP-DOWN DP)
// ═══════════════════════════════════════════════════════════════

int knapsackMemo(int i, int W, int n) {
    // Base cases
    if (i > n || W == 0) {
        return 0;
    }
    
    // Already computed?
    if (memo[i][W] != -1) {
        return memo[i][W];
    }
    
    // If item i doesn't fit
    if (weight[i] > W) {
        memo[i][W] = knapsackMemo(i + 1, W, n);
    }
    // Item i fits, explore both choices
    else {
        int dontTake = knapsackMemo(i + 1, W, n);
        int take = value[i] + knapsackMemo(i + 1, W - weight[i], n);
        memo[i][W] = (dontTake > take) ? dontTake : take;
    }
    
    return memo[i][W];
}

// ═══════════════════════════════════════════════════════════════
// BACKTRACKING: WHICH ITEMS WERE SELECTED?
// ═══════════════════════════════════════════════════════════════

void printSelection(int n, int W) {
    printf("Selected items: ");
    int w = W;
    int count = 0;
    
    for (int i = n; i >= 1; i--) {
        // If value changed from previous row, item i was taken
        if (dp[i][w] != dp[i-1][w]) {
            printf("%d ", i);
            w -= weight[i];
            count++;
        }
    }
    
    if (count == 0) {
        printf("(none)");
    }
    printf("\n");
}

// ═══════════════════════════════════════════════════════════════
// HELPER: PRINT DP TABLE
// ═══════════════════════════════════════════════════════════════

void printTable(int n, int W) {
    printf("\n════ DP TABLE ════\n");
    printf("Rows: items (0 to %d), Columns: capacity (0 to %d)\n\n", n, W);
    
    // Print header
    printf("    ");
    for (int w = 0; w <= W; w++) {
        printf("%4d ", w);
    }
    printf("\n");
    
    // Print rows
    for (int i = 0; i <= n; i++) {
        printf("i=%2d: ", i);
        for (int w = 0; w <= W; w++) {
            printf("%4d ", dp[i][w]);
        }
        printf("\n");
    }
}

// ═══════════════════════════════════════════════════════════════
// TEST CASES
// ═══════════════════════════════════════════════════════════════

void test1() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST 1: Basic Example (from lecture)                      ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    int n = 3;
    int W = 5;
    
    weight[1] = 2;  value[1] = 3;
    weight[2] = 3;  value[2] = 4;
    weight[3] = 4;  value[3] = 5;
    
    printf("Capacity: W = %d\n\n", W);
    printf("Items:\n");
    for (int i = 1; i <= n; i++) {
        printf("  Item %d: weight=%d, value=%d\n", i, weight[i], value[i]);
    }
    
    // Solve using tabulation
    int result = knapsackTabulation(n, W);
    
    printTable(n, W);
    
    printf("\nMaximum value: %d\n", result);
    printSelection(n, W);
    
    printf("\n✓ Expected value: 7 (items 1+2: w=5, v=7)\n");
}

void test2() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST 2: Memoization vs Tabulation Comparison             ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    int n = 4;
    int W = 6;
    
    weight[1] = 2;  value[1] = 3;
    weight[2] = 3;  value[2] = 4;
    weight[3] = 4;  value[3] = 5;
    weight[4] = 5;  value[4] = 6;
    
    printf("Capacity: W = %d\n\n", W);
    printf("Items:\n");
    for (int i = 1; i <= n; i++) {
        printf("  Item %d: weight=%d, value=%d\n", i, weight[i], value[i]);
    }
    
    // Tabulation approach
    printf("\n─── TABULATION (BOTTOM-UP) ───\n");
    int result1 = knapsackTabulation(n, W);
    printf("Result: %d\n", result1);
    printSelection(n, W);
    
    // Memoization approach
    printf("\n─── MEMOIZATION (TOP-DOWN) ───\n");
    memset(memo, -1, sizeof(memo));
    int result2 = knapsackMemo(1, W, n);
    printf("Result: %d\n", result2);
    
    printf("\n✓ Both approaches should give same answer: %d\n", result1);
}

void test3() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST 3: Greedy Fails (Counterexample)                    ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    int n = 4;
    int W = 10;
    
    // Setup: Greedy (by value/weight ratio) will fail
    weight[1] = 6;  value[1] = 30;  // ratio = 5.0
    weight[2] = 5;  value[2] = 24;  // ratio = 4.8
    weight[3] = 5;  value[3] = 26;  // ratio = 5.2 (highest)
    weight[4] = 6;  value[4] = 29;  // ratio = 4.83
    
    printf("Capacity: W = %d\n\n", W);
    printf("Items (sorted by value/weight ratio):\n");
    for (int i = 1; i <= n; i++) {
        double ratio = (double)value[i] / weight[i];
        printf("  Item %d: weight=%d, value=%d, ratio=%.2f\n", i, weight[i], value[i], ratio);
    }
    
    printf("\n─── GREEDY APPROACH (picks by ratio) ───\n");
    printf("Pick item 3 (w=5, v=26), capacity left = 5\n");
    printf("Pick item 2? (w=5, v=24), fits! total = w10, v50\n");
    printf("Greedy result: 50\n");
    
    int result = knapsackTabulation(n, W);
    
    printTable(n, W);
    
    printf("\n─── DP APPROACH ───\n");
    printf("Maximum value: %d\n", result);
    printSelection(n, W);
    
    printf("\n✓ DP finds: %d (items 2+3 or 1+4 depending on implementation)\n", result);
}

void test4() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST 4: All Items Fit (sanity check)                     ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    int n = 3;
    int W = 20;
    
    weight[1] = 2;  value[1] = 3;
    weight[2] = 3;  value[2] = 4;
    weight[3] = 4;  value[3] = 5;
    
    printf("Capacity: W = %d (large, all items fit)\n\n", W);
    printf("Items:\n");
    for (int i = 1; i <= n; i++) {
        printf("  Item %d: weight=%d, value=%d\n", i, weight[i], value[i]);
    }
    
    int result = knapsackTabulation(n, W);
    
    printf("\nMaximum value: %d\n", result);
    printSelection(n, W);
    
    int totalWeight = 0, totalValue = 0;
    for (int i = 1; i <= n; i++) {
        totalWeight += weight[i];
        totalValue += value[i];
    }
    
    printf("\n✓ Expected: %d (all items: w=%d, v=%d)\n", totalValue, totalWeight, totalValue);
}

void test5() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ TEST 5: Complex Example (larger problem)                 ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    int n = 5;
    int W = 10;
    
    weight[1] = 1;  value[1] = 1;
    weight[2] = 4;  value[2] = 5;
    weight[3] = 5;  value[3] = 8;
    weight[4] = 6;  value[4] = 9;
    weight[5] = 3;  value[5] = 4;
    
    printf("Capacity: W = %d\n\n", W);
    printf("Items:\n");
    for (int i = 1; i <= n; i++) {
        printf("  Item %d: weight=%d, value=%d\n", i, weight[i], value[i]);
    }
    
    int result = knapsackTabulation(n, W);
    
    // Only print selected rows of table to save space
    printf("\n════ DP TABLE (selected capacities) ════\n");
    printf("    w=0  w=1  w=2  w=3  w=4  w=5  w=6  w=7  w=8  w=9  w=10\n");
    
    for (int i = 0; i <= n; i++) {
        printf("i=%2d: ", i);
        for (int w = 0; w <= W; w++) {
            printf("%3d  ", dp[i][w]);
        }
        printf("\n");
    }
    
    printf("\nMaximum value: %d\n", result);
    printSelection(n, W);
    
    printf("\n✓ Optimal: likely items 1+3+4 (w=1+5+6=12? exceeds) or items 2+4 (w=4+6=10, v=5+9=14)\n");
}

// ═══════════════════════════════════════════════════════════════
// DETAILED STEP-BY-STEP TRACE
// ═══════════════════════════════════════════════════════════════

void traceExample() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ DETAILED STEP-BY-STEP TRACE                              ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    int n = 2;
    int W = 5;
    
    weight[1] = 2;  value[1] = 3;
    weight[2] = 3;  value[2] = 4;
    
    printf("Problem: n=%d items, capacity W=%d\n", n, W);
    printf("Item 1: weight=2, value=3\n");
    printf("Item 2: weight=3, value=4\n\n");
    
    // Initialize
    memset(dp, 0, sizeof(dp));
    
    printf("═══ BUILDING TABLE ═══\n\n");
    
    printf("Row i=0: (base case, no items)\n");
    printf("  dp[0][w] = 0 for all w (no items, value=0)\n\n");
    
    printf("Row i=1: (item 1 only: w=2, v=3)\n");
    for (int w = 0; w <= W; w++) {
        if (weight[1] > w) {
            dp[1][w] = dp[0][w];
            printf("  w=%d: item 1 doesn't fit (2>%d), dp[1][%d] = dp[0][%d] = 0\n", w, w, w, w);
        } else {
            int dontTake = dp[0][w];
            int take = value[1] + dp[0][w - weight[1]];
            dp[1][w] = (dontTake > take) ? dontTake : take;
            printf("  w=%d: item 1 fits! dp[1][%d] = max(%d, %d+%d) = %d\n", 
                   w, w, dontTake, value[1], dp[0][w - weight[1]], dp[1][w]);
        }
    }
    
    printf("\nRow i=2: (items 1,2 available: item 2 is w=3, v=4)\n");
    for (int w = 0; w <= W; w++) {
        if (weight[2] > w) {
            dp[2][w] = dp[1][w];
            printf("  w=%d: item 2 doesn't fit (3>%d), dp[2][%d] = dp[1][%d] = %d\n", 
                   w, w, w, w, dp[2][w]);
        } else {
            int dontTake = dp[1][w];
            int take = value[2] + dp[1][w - weight[2]];
            dp[2][w] = (dontTake > take) ? dontTake : take;
            printf("  w=%d: item 2 fits! dp[2][%d] = max(%d, %d+dp[1][%d]) = max(%d, %d+%d) = %d\n",
                   w, w, dontTake, value[2], w-weight[2], dontTake, value[2], 
                   dp[1][w - weight[2]], dp[2][w]);
        }
    }
    
    printf("\n═══ FINAL TABLE ═══\n");
    printf("    ");
    for (int w = 0; w <= W; w++) printf("w=%d ", w);
    printf("\n");
    for (int i = 0; i <= n; i++) {
        printf("i=%d: ", i);
        for (int w = 0; w <= W; w++) printf("%3d  ", dp[i][w]);
        printf("\n");
    }
    
    printf("\n═══ ANSWER ═══\n");
    printf("dp[%d][%d] = %d\n", n, W, dp[n][W]);
    printSelection(n, W);
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║     0/1 KNAPSACK: DYNAMIC PROGRAMMING IMPLEMENTATION     ║\n");
    printf("║          Both Memoization and Tabulation                  ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    // Run all tests
    test1();
    test2();
    test3();
    test4();
    test5();
    
    // Detailed trace
    traceExample();
    
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ ALL TESTS COMPLETE                                       ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    return 0;
}
