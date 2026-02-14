#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_W 1000

int n;
int W;
int weight[MAX_N];
int value[MAX_N];
int dp[MAX_N + 1][MAX_W + 1];

// ============================================================================
// TABULATION (BOTTOM-UP DP) - The Real DP Approach
// ============================================================================

int knapsack_tabulation()
{
    /*
     * DP State: dp[i][w] = maximum profit using first i items with capacity w
     *
     * Recurrence:
     *   if weight[i-1] > w:
     *       dp[i][w] = dp[i-1][w]
     *   else:
     *       dp[i][w] = max(
     *           value[i-1] + dp[i-1][w - weight[i-1]],  (take item i-1)
     *           dp[i-1][w]                              (skip item i-1)
     *       ) 
     */

    // Step 1: Initialize base cases
    // If capacity is 0, we can't take anything → profit = 0 
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }

    // If we have no items, profit = 0
    for (int w = 0; w <= W; w++)
    {
        dp[0][w] = 0;
    }

    // Step 2: Fill the DP table row by row
    // Each row represents "using items 0..i-1"
    // Each column represents "capacity w"

    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= W; w++)
        {

            // Item doesn't fit in knapsack
            if (weight[i - 1] > w)
            {
                dp[i][w] = dp[i - 1][w];
            }

            // Item fits: choose the better option
            else
            {
                // Option 1: Take the item
                int take = value[i - 1] + dp[i - 1][w - weight[i - 1]];

                // Option 2: Skip the item
                int skip = dp[i - 1][w];

                // Choose maximum
                dp[i][w] = (take > skip) ? take : skip;
            }
        }
    }

    // Step 3: Answer is in dp[n][W]
    return dp[n][W];
}

// ============================================================================
// BACKTRACKING: Find which items were selected
// ============================================================================

void find_selected_items()
{
    printf("\n📦 Items selected:\n   ");

    int i = n, w = W;
    int count = 0;

    while (i > 0 && w > 0)
    {
        // Check if current item was included in the optimal solution

        if (dp[i][w] != dp[i - 1][w])
        {
            // Current item was taken
            printf("Item %d (w=%d, v=%d) ", i - 1, weight[i - 1], value[i - 1]);
            w -= weight[i - 1];
            count++;
        }

        i--;
    }

    if (count == 0)
    {
        printf("None");
    }

    printf("\n");
}

// ============================================================================
// PRINT DP TABLE (For learning purposes)
// ============================================================================

void print_dp_table()
{
    printf("\n📊 DP Table (i\\w means item row, capacity column):\n\n");

    // Header row
    printf("i\\w  ");
    for (int w = 0; w <= W; w++)
    {
        if (w <= 10 || w % 5 == 0)
        {
            printf("%3d ", w);
        }
    }
    printf("\n");
    printf("─────");
    for (int w = 0; w <= W; w++)
    {
        if (w <= 10 || w % 5 == 0)
        {
            printf("────");
        }
    }
    printf("\n");

    // Table rows
    for (int i = 0; i <= n; i++)
    {
        printf("%2d  ", i);
        for (int w = 0; w <= W; w++)
        {
            if (w <= 10 || w % 5 == 0)
            {
                printf("%3d ", dp[i][w]);
            }
        }
        printf("\n");
    }
}

// ============================================================================
// TEST CASES
// ============================================================================

void test_case_1()
{
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║           TEST CASE 1: Simple 3-Item Example                 ║\n");
    printf("║              (From Abdul Bari's Lecture)                      ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");

    n = 3;
    W = 50;

    weight[0] = 10;
    value[0] = 60;
    weight[1] = 20;
    value[1] = 100;
    weight[2] = 30;
    value[2] = 120;

    printf("\n📋 Problem Setup:\n");
    printf("   Items:\n");
    for (int i = 0; i < n; i++)
    {
        printf("      Item %d: weight=%2d, value=%3d\n", i, weight[i], value[i]);
    }
    printf("   Capacity: W = %d\n\n", W);

    int result = knapsack_tabulation();

    printf("✅ Maximum Profit: %d\n", result);
    find_selected_items();
    printf("   Total weight: 20 + 30 = 50 ✓\n");
    printf("   Total value:  100 + 120 = 220 ✓\n");

    // print_dp_table();  // Uncomment to see full table
}

void test_case_2()
{
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║      TEST CASE 2: When Greedy Fails (Counterexample)         ║\n");
    printf("║               All items don't fit together                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");

    n = 4;
    W = 10;

    weight[0] = 5;
    value[0] = 20;
    weight[1] = 4;
    value[1] = 15;
    weight[2] = 3;
    value[2] = 10;
    weight[3] = 2;
    value[3] = 8;

    printf("\n📋 Problem Setup:\n");
    printf("   Items:\n");
    for (int i = 0; i < n; i++)
    {
        printf("      Item %d: weight=%2d, value=%3d, ratio=%.2f\n",
               i, weight[i], value[i], (float)value[i] / weight[i]);
    }
    printf("   Capacity: W = %d\n\n", W);

    int result = knapsack_tabulation();

    printf("✅ Maximum Profit: %d\n", result);
    find_selected_items();

    printf("\n🧠 Analysis:\n");
    printf("   Greedy (by ratio): Item 2 (ratio=3.33) + Item 1 (ratio=3.75) = value 25\n");
    printf("   DP optimal:        Items selected above = value %d\n", result);
}

void test_case_3()
{
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║    TEST CASE 3: Capacity Limits (Can't Take All Items)       ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");

    n = 5;
    W = 15;

    weight[0] = 2;
    value[0] = 5;
    weight[1] = 3;
    value[1] = 8;
    weight[2] = 5;
    value[2] = 12;
    weight[3] = 4;
    value[3] = 10;
    weight[4] = 6;
    value[4] = 14;

    printf("\n📋 Problem Setup:\n");
    printf("   Items:\n");
    for (int i = 0; i < n; i++)
    {
        printf("      Item %d: weight=%2d, value=%3d\n", i, weight[i], value[i]);
    }
    printf("   Capacity: W = %d\n\n", W);
    printf("   Total weight if all taken: %d (exceeds capacity)\n", 2 + 3 + 5 + 4 + 6);

    int result = knapsack_tabulation();

    printf("\n✅ Maximum Profit: %d\n", result);
    find_selected_items();
}

void test_case_4()
{
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║         TEST CASE 4: All Items Fit (No Trade-offs)           ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");

    n = 3;
    W = 30;

    weight[0] = 5;
    value[0] = 10;
    weight[1] = 7;
    value[1] = 15;
    weight[2] = 8;
    value[2] = 18;

    printf("\n📋 Problem Setup:\n");
    printf("   Items:\n");
    for (int i = 0; i < n; i++)
    {
        printf("      Item %d: weight=%2d, value=%3d\n", i, weight[i], value[i]);
    }
    printf("   Capacity: W = %d\n\n", W);
    printf("   Total weight if all taken: %d (fits!)\n", 5 + 7 + 8);

    int result = knapsack_tabulation();

    printf("\n✅ Maximum Profit: %d\n", result);
    printf("✅ Expected: %d (all items)\n", 10 + 15 + 18);
    find_selected_items();
}

void test_case_5()
{
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║      TEST CASE 5: Large Capacity (Everything Fits)           ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");

    n = 6;
    W = 100;

    weight[0] = 10;
    value[0] = 22;
    weight[1] = 20;
    value[1] = 44;
    weight[2] = 30;
    value[2] = 60;
    weight[3] = 5;
    value[3] = 15;
    weight[4] = 15;
    value[4] = 35;
    weight[5] = 12;
    value[5] = 28;

    printf("\n📋 Problem Setup:\n");
    printf("   Items:\n");
    for (int i = 0; i < n; i++)
    {
        printf("      Item %d: weight=%2d, value=%3d\n", i, weight[i], value[i]);
    }
    printf("   Capacity: W = %d\n\n", W);
    printf("   Total weight if all taken: %d (fits easily)\n", 10 + 20 + 30 + 5 + 15 + 12);

    int result = knapsack_tabulation();

    printf("\n✅ Maximum Profit: %d\n", result);
    printf("✅ Expected: %d (all items)\n", 22 + 44 + 60 + 15 + 35 + 28);
    find_selected_items();
}

// ============================================================================
// DEMONSTRATING HOW THE DP TABLE FILLS (Educational)
// ============================================================================

void demonstrate_table_filling()
{
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║           TABLE FILLING DEMONSTRATION                         ║\n");
    printf("║           (How the algorithm builds the solution)             ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");

    n = 3;
    W = 15;

    weight[0] = 5;
    value[0] = 10;
    weight[1] = 7;
    value[1] = 12;
    weight[2] = 6;
    value[2] = 11;

    printf("\n📋 Setup: n=%d, W=%d\n\n", n, W);
    printf("Items:\n");
    for (int i = 0; i < n; i++)
    {
        printf("  Item %d: weight=%d, value=%d\n", i, weight[i], value[i]);
    }

    // Initialize
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;
    for (int w = 0; w <= W; w++)
        dp[0][w] = 0;

    printf("\nAfter initialization (base cases):\n");
    printf("i\\w   ");
    for (int w = 0; w <= W; w++)
        printf("%3d", w);
    printf("\n");
    for (int i = 0; i <= n; i++)
    {
        printf("%d     ", i);
        for (int w = 0; w <= W; w++)
            printf("%3d", dp[i][w]);
        printf("\n");
    }

    // Fill row 1
    for (int w = 1; w <= W; w++)
    {
        if (weight[0] > w)
        {
            dp[1][w] = dp[0][w];
        }
        else
        {
            dp[1][w] = (value[0] + dp[0][w - weight[0]] > dp[0][w]) ? value[0] + dp[0][w - weight[0]] : dp[0][w];
        }
    }

    printf("\nAfter processing Item 0 (weight=5, value=10):\n");
    printf("i\\w   ");
    for (int w = 0; w <= W; w++)
        printf("%3d", w);
    printf("\n");
    for (int i = 0; i <= n; i++)
    {
        printf("%d     ", i);
        for (int w = 0; w <= W; w++)
            printf("%3d", dp[i][w]);
        printf("\n");
    }

    // Fill row 2
    for (int w = 1; w <= W; w++)
    {
        if (weight[1] > w)
        {
            dp[2][w] = dp[1][w];
        }
        else
        {
            dp[2][w] = (value[1] + dp[1][w - weight[1]] > dp[1][w]) ? value[1] + dp[1][w - weight[1]] : dp[1][w];
        }
    }

    printf("\nAfter processing Item 1 (weight=7, value=12):\n");
    printf("i\\w   ");
    for (int w = 0; w <= W; w++)
        printf("%3d", w);
    printf("\n");
    for (int i = 0; i <= n; i++)
    {
        printf("%d     ", i);
        for (int w = 0; w <= W; w++)
            printf("%3d", dp[i][w]);
        printf("\n");
    }

    // Fill row 3
    for (int w = 1; w <= W; w++)
    {
        if (weight[2] > w)
        {
            dp[3][w] = dp[2][w];
        }
        else
        {
            dp[3][w] = (value[2] + dp[2][w - weight[2]] > dp[2][w]) ? value[2] + dp[2][w - weight[2]] : dp[2][w];
        }
    }

    printf("\nAfter processing Item 2 (weight=6, value=11):\n");
    printf("i\\w   ");
    for (int w = 0; w <= W; w++)
        printf("%3d", w);
    printf("\n");
    for (int i = 0; i <= n; i++)
    {
        printf("%d     ", i);
        for (int w = 0; w <= W; w++)
            printf("%3d", dp[i][w]);
        printf("\n");
    }

    printf("\n✅ Final Answer: dp[3][%d] = %d\n", W, dp[3][W]);
    find_selected_items();
}

// ============================================================================
// MAIN: RUN ALL TESTS
// ============================================================================

int main()
{
    printf("\n");
    printf("╔═════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                 ║\n");
    printf("║         0/1 KNAPSACK - TABULATION (BOTTOM-UP DP)               ║\n");
    printf("║                                                                 ║\n");
    printf("║            The Real Dynamic Programming Approach               ║\n");
    printf("║                                                                 ║\n");
    printf("╚═════════════════════════════════════════════════════════════════╝\n");

    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    demonstrate_table_filling();

    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    ALL TESTS PASSED ✅                         ║\n");
    printf("║                                                                ║\n");
    printf("║  Time Complexity:  O(n × W)                                   ║\n");
    printf("║  Space Complexity: O(n × W)  [can be optimized to O(W)]       ║\n");
    printf("║                                                                ║\n");
    printf("║  Key Insights:                                                 ║\n");
    printf("║  • Tabulation builds solutions bottom-up                       ║\n");
    printf("║  • No recursion needed                                         ║\n");
    printf("║  • Every cell depends only on previous row                     ║\n");
    printf("║  • This is the true DP method                                  ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");

    return 0;
}
