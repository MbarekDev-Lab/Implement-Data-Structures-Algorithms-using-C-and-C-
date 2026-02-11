# 0/1 Knapsack — Tabulation Approach (Bottom-Up DP)

## The Evolution: From Recursion to DP

### What Was Wrong With Our Earlier Approaches?

**Pure Recursion:**
```
Problem: O(2^n) time complexity
Why?     Because we explore all 2^n possibilities
Result:  Too slow for n > 20-30
```

**Memoization (Top-Down DP):**
```
Improvement:  O(n×W) time
Trade-off:    Uses recursion stack (O(n) space)
              Harder to visualize
              Still thinking "recursively"
```

**What We Need:**
```
A way to think bottom-up instead of top-down
Eliminate recursion entirely
Build solutions progressively
This is TRUE Dynamic Programming
```

---

## Part 1: The Core Insight

### State Definition (MOST IMPORTANT)

$$\boxed{DP[i][w] = \text{Maximum profit using first } i \text{ items with capacity } w}$$

**This single definition is the key to everything.**

Once you define this, the algorithm writes itself.

### Why This Works

```
DP[i][w] depends on:
  • DP[i-1][w]         (don't take item i)
  • DP[i-1][w-weight[i]] (take item i)

Both of these are in the previous row.

So we can compute row by row, from top to bottom.

No recursion needed.
No retracing paths.
Just fill one cell at a time.
```

---

## Part 2: The Recurrence Formula (Whiteboard Format)

### The Mathematical Definition

$$DP[i][w] = \begin{cases}
0 & \text{if } i = 0 \text{ or } w = 0 \\[0.5em]
\max\left( value[i] + DP[i-1][w-weight[i]], \; DP[i-1][w] \right) & \text{if } weight[i] \leq w \\[0.5em]
DP[i-1][w] & \text{if } weight[i] > w
\end{cases}$$

### Breaking It Down

**Case 1: Base Case**
```
DP[i][0] = 0   (no capacity, no profit)
DP[0][w] = 0   (no items, no profit)
```

**Case 2: Item Fits (weight[i] ≤ w)**
```
Two choices:
  1. Take item i:   value[i] + DP[i-1][w-weight[i]]
     → Gain value[i]
     → Reduce capacity by weight[i]
     → Use remaining capacity for previous items

  2. Don't take item i:  DP[i-1][w]
     → No value gained
     → Full capacity available for previous items

Choose whichever is larger: max(choice1, choice2)
```

**Case 3: Item Doesn't Fit (weight[i] > w)**
```
Only one choice: skip the item
DP[i][w] = DP[i-1][w]

(Forced to not take it)
```

---

## Part 3: Table Structure

### Size of DP Table

```
Rows:    i from 0 to n        (n+1 rows)
Columns: w from 0 to W        (W+1 columns)

Total size: (n+1) × (W+1)
```

### Visual Structure

```
i \ w    0    1    2    3    4    5  ...  W
──────────────────────────────────────────────
0        0    0    0    0    0    0       0
1        ?    ?    ?    ?    ?    ?       ?
2        ?    ?    ?    ?    ?    ?       ?
3        ?    ?    ?    ?    ?    ?       ?
...      ?    ?    ?    ?    ?    ?       ?
n        ?    ?    ?    ?    ?    ?       ?
```

### Initialization

```
First row (no items):
  DP[0][w] = 0 for all w (0 to W)

First column (no capacity):
  DP[i][0] = 0 for all i (0 to n)

The rest: computed using recurrence
```

---

## Part 4: The Algorithm (Pseudocode)

```
algorithm Knapsack_Tabulation(weight[], value[], n, W):
    
    // Create DP table
    DP[0..n][0..W]
    
    // Initialize base cases
    for i = 0 to n:
        DP[i][0] = 0
    
    for w = 0 to W:
        DP[0][w] = 0
    
    // Fill the table
    for i = 1 to n:                    // For each item
        for w = 1 to W:                // For each capacity
            
            if weight[i-1] > w:        // Item doesn't fit
                DP[i][w] = DP[i-1][w]
            
            else:                      // Item fits
                take_item = value[i-1] + DP[i-1][w - weight[i-1]]
                skip_item = DP[i-1][w]
                DP[i][w] = max(take_item, skip_item)
    
    // Answer is in DP[n][W]
    return DP[n][W]
```

---

## Part 5: Example with Concrete Numbers

### Problem Setup

```
Items:
  Item 0: weight=10, value=60
  Item 1: weight=20, value=100
  Item 2: weight=30, value=120

Knapsack capacity: W = 50
Number of items: n = 3

Table size: 4 × 51 (rows 0-3, columns 0-50)
```

### Initialization (First Row & Column)

```
i \ w    0    1    2    3  ...  50
──────────────────────────────────
0        0    0    0    0  ...  0
1        0
2        0
3        0
```

### Filling Row by Row

#### Row i=1 (Item 0: w=10, v=60)

```
i=1, w=5:
  weight[0]=10 > w=5
  DP[1][5] = DP[0][5] = 0

i=1, w=10:
  weight[0]=10 ≤ w=10 ✓
  take = 60 + DP[0][0] = 60 + 0 = 60
  skip = DP[0][10] = 0
  DP[1][10] = max(60, 0) = 60

i=1, w=20:
  weight[0]=10 ≤ w=20 ✓
  take = 60 + DP[0][10] = 60 + 0 = 60
  skip = DP[0][20] = 0
  DP[1][20] = max(60, 0) = 60

...and so on (60 for all w ≥ 10)

Result Row 1:
i \ w    0   5   10   20   30   40   50
──────────────────────────────────────────
0        0   0    0    0    0    0    0
1        0   0   60   60   60   60   60
```

#### Row i=2 (Item 1: w=20, v=100)

```
i=2, w=5:
  weight[1]=20 > w=5
  DP[2][5] = DP[1][5] = 0

i=2, w=20:
  weight[1]=20 ≤ w=20 ✓
  take = 100 + DP[1][0] = 100 + 0 = 100
  skip = DP[1][20] = 60
  DP[2][20] = max(100, 60) = 100

i=2, w=30:
  weight[1]=20 ≤ w=30 ✓
  take = 100 + DP[1][10] = 100 + 60 = 160
  skip = DP[1][30] = 60
  DP[2][30] = max(160, 60) = 160

i=2, w=50:
  weight[1]=20 ≤ w=50 ✓
  take = 100 + DP[1][30] = 100 + 60 = 160
  skip = DP[1][50] = 60
  DP[2][50] = max(160, 60) = 160

Result Row 2:
i \ w    0   5   10   20   30   40   50
──────────────────────────────────────────
0        0   0    0    0    0    0    0
1        0   0   60   60   60   60   60
2        0   0   60  100  160  160  160
```

#### Row i=3 (Item 2: w=30, v=120)

```
i=3, w=30:
  weight[2]=30 ≤ w=30 ✓
  take = 120 + DP[2][0] = 120 + 0 = 120
  skip = DP[2][30] = 160
  DP[3][30] = max(120, 160) = 160

i=3, w=40:
  weight[2]=30 ≤ w=40 ✓
  take = 120 + DP[2][10] = 120 + 60 = 180
  skip = DP[2][40] = 160
  DP[3][40] = max(180, 160) = 180

i=3, w=50:
  weight[2]=30 ≤ w=50 ✓
  take = 120 + DP[2][20] = 120 + 100 = 220
  skip = DP[2][50] = 160
  DP[3][50] = max(220, 160) = 220

Result Row 3:
i \ w    0   5   10   20   30   40   50
──────────────────────────────────────────
0        0   0    0    0    0    0    0
1        0   0   60   60   60   60   60
2        0   0   60  100  160  160  160
3        0   0   60  100  160  180  220
```

### Final Answer

$$DP[3][50] = 220$$

**Selection: Items 1 and 2**
- Weights: 20 + 30 = 50 ✓
- Values: 100 + 120 = 220 ✓

---

## Part 6: Complete Example (With All Capacities)

### Larger Example

```
Items:
  0: w=1,  v=1
  1: w=3,  v=4
  2: w=4,  v=5
  3: w=5,  v=7

Capacity: W=7
Table: 5 × 8
```

### Full DP Table (All Values)

```
i\w   0   1   2   3   4   5   6   7
───────────────────────────────────
0     0   0   0   0   0   0   0   0
1     0   1   1   1   1   1   1   1
2     0   1   1   4   5   5   5   5
3     0   1   1   4   5   6   6   9
4     0   1   1   4   5   7   8   9
```

### Reading the Table

```
DP[1][1] = 1   → Using item 0 (w=1, v=1) with capacity 1
                  We can take it: value = 1

DP[2][3] = 4   → Using items 0,1 (w=1,3) with capacity 3
                  We can take item 1 only: value = 4
                  (Can't fit both: 1+3=4 > 3)

DP[3][7] = 9   → Using items 0,1,2 with capacity 7
                  We can take items 1,2,3: weights 3+4=7, values 4+5=9

DP[4][7] = 9   → Same as above (item 3 doesn't improve)
```

---

## Part 7: Why Tabulation Works (The Magic)

### Dependency Graph

```
Every cell DP[i][w] depends on:
  • DP[i-1][w]
  • DP[i-1][w-weight[i]]

Both are in the PREVIOUS ROW.

So if we fill row by row from top to bottom,
all dependencies are already available!

No need for recursion.
No need to jump around the table.
Just methodical, left-to-right, top-to-bottom filling.
```

### Visual: Dependencies

```
       Previous Row (i-1)
      ┌─────────────┬─────────────┐
      │             │             │
    Left         Current        Right
  DP[i-1][w-w_i] DP[i-1][w]    DP[i-1][w']
      │             │
      └─────┬───────┘
            │
        Current Cell
        DP[i][w] = max(take_left + value, use_right)
```

---

## Part 8: Time and Space Complexity

### Time Complexity

```
Nested loops:
  Outer loop: i from 1 to n            → n iterations
  Inner loop: w from 1 to W            → W iterations
  
Work per cell: O(1)                      (just a max comparison)

Total: O(n) × O(W) × O(1) = O(n × W)
```

### Space Complexity

```
DP table: (n+1) × (W+1) = O(n × W)

Recursion stack: O(1) (no recursion!)

Total: O(n × W)
```

### Comparison: All Three Approaches

```
Approach              Time      Space      Recursive?
──────────────────────────────────────────────────────
Pure Recursion        O(2^n)    O(n)       Yes(heavy)
Memoization           O(n×W)    O(n×W)     Yes (light)
Tabulation            O(n×W)    O(n×W)     No
```

**Tabulation is the cleanest, most efficient approach.**

---

## Part 9: Complete C Implementation

### Headers and Setup

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_W 1000

int n;                    // number of items
int W;                    // knapsack capacity
int weight[MAX_N];        // weight of each item
int value[MAX_N];         // value of each item
int dp[MAX_N + 1][MAX_W + 1];  // DP table
```

### Main Tabulation Function

```c
int knapsack_tabulation(int n, int W) {
    
    // Step 1: Initialize base cases
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;  // No capacity
    }
    
    for (int w = 0; w <= W; w++) {
        dp[0][w] = 0;  // No items
    }
    
    // Step 2: Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            
            // Item doesn't fit
            if (weight[i-1] > w) {
                dp[i][w] = dp[i-1][w];
            }
            
            // Item fits: choose better option
            else {
                int take = value[i-1] + dp[i-1][w - weight[i-1]];
                int skip = dp[i-1][w];
                dp[i][w] = (take > skip) ? take : skip;
            }
        }
    }
    
    // Step 3: Return answer
    return dp[n][W];
}
```

### Backtracking to Find Selected Items

```c
void find_items(int n, int W) {
    printf("Items selected: ");
    
    int i = n, w = W;
    
    while (i > 0 && w > 0) {
        // Check if current item was taken
        if (dp[i][w] != dp[i-1][w]) {
            printf("%d ", i-1);  // Item i-1 was taken
            w -= weight[i-1];
        }
        i--;
    }
    
    printf("\n");
}
```

### Complete Example Program

```c
#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_W 1000

int n, W;
int weight[MAX_N];
int value[MAX_N];
int dp[MAX_N + 1][MAX_W + 1];

int knapsack_tabulation() {
    
    // Initialize
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;
    
    for (int w = 0; w <= W; w++)
        dp[0][w] = 0;
    
    // Fill table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            
            if (weight[i-1] > w) {
                dp[i][w] = dp[i-1][w];
            }
            else {
                int take = value[i-1] + dp[i-1][w - weight[i-1]];
                int skip = dp[i-1][w];
                dp[i][w] = (take > skip) ? take : skip;
            }
        }
    }
    
    return dp[n][W];
}

void print_table() {
    printf("\nDP Table:\n");
    printf("i\\w  ");
    for (int w = 0; w <= W; w += 5)
        printf("%3d ", w);
    printf("\n");
    
    for (int i = 0; i <= n; i++) {
        printf("%2d:  ", i);
        for (int w = 0; w <= W; w += 5)
            printf("%3d ", dp[i][w]);
        printf("\n");
    }
}

int main() {
    // Example
    n = 3;
    W = 50;
    
    weight[0] = 10;  value[0] = 60;
    weight[1] = 20;  value[1] = 100;
    weight[2] = 30;  value[2] = 120;
    
    printf("═════════════════════════════════════════\n");
    printf("      0/1 KNAPSACK (TABULATION)\n");
    printf("═════════════════════════════════════════\n\n");
    
    printf("Items:\n");
    for (int i = 0; i < n; i++) {
        printf("  Item %d: weight=%d, value=%d\n", i, weight[i], value[i]);
    }
    
    printf("\nCapacity: %d\n", W);
    
    int result = knapsack_tabulation();
    
    printf("\nMaximum value: %d\n", result);
    
    print_table();
    
    printf("\n═════════════════════════════════════════\n");
    
    return 0;
}
```

### Expected Output

```
═════════════════════════════════════════
      0/1 KNAPSACK (TABULATION)
═════════════════════════════════════════

Items:
  Item 0: weight=10, value=60
  Item 1: weight=20, value=100
  Item 2: weight=30, value=120

Capacity: 50

Maximum value: 220

DP Table:
i\w    0   5  10  15  20  25  30  35  40  45  50
 0:    0   0   0   0   0   0   0   0   0   0   0
 1:    0   0  60  60  60  60  60  60  60  60  60
 2:    0   0  60  60 100 100 100 100 160 160 160
 3:    0   0  60  60 100 100 160 160 160 180 220

═════════════════════════════════════════
```

---

## Part 10: Visualization: How the Table Fills

### Step-by-Step Filling (Simplified)

```
Start:
  i\w  0  1  2  3  4  5
───────────────────────── 
  0    0  0  0  0  0  0
  1    0  ?  ?  ?  ?  ?
  2    0  ?  ?  ?  ?  ?

After Row 1 (Item 0: w=1, v=1):
  i\w  0  1  2  3  4  5
────────────────────────
  0    0  0  0  0  0  0
  1    0  1  1  1  1  1
  2    0  ?  ?  ?  ?  ?

After Row 2 (Item 1: w=3, v=4):
  i\w  0  1  2  3  4  5
────────────────────────
  0    0  0  0  0  0  0
  1    0  1  1  1  1  1
  2    0  1  1  4  5  5

Each row improves the answer.
Final answer: bottom-right cell.
```

---

## Part 11: Space Optimization (Advanced)

### The 1D Array Trick

Instead of 2D table, use 1D array:

```c
int dp[MAX_W + 1];  // Just one array

// Read from right to left to avoid overwriting needed values
for (int i = 1; i <= n; i++) {
    for (int w = W; w >= weight[i-1]; w--) {
        dp[w] = max(
            dp[w],
            value[i-1] + dp[w - weight[i-1]]
        );
    }
}

return dp[W];
```

**Why traverse right-to-left?**
```
If we go left-to-right:
  When computing dp[w], we might use dp[w - weight[i-1]]
  But that's already been updated in THIS iteration!
  It becomes the value from the current item, not previous.

If we go right-to-left:
  We process larger capacities first.
  When computing dp[w], we use dp[w - weight[i-1]]
  But w > weight[i-1], so w - weight[i-1] hasn't been processed yet.
  We get the old value (previous row).
  Perfect!
```

**Space reduction:**
```
2D approach: O(n × W)
1D approach: O(W)

Same time: O(n × W)
```

This is advanced understanding that separates true masters from novices.

---

## Part 12: Abdul Bari's Teaching Philosophy (Deep Insights)

### What He REALLY Wants You To Learn

He's not teaching you to solve knapsack.

He's teaching you the DP paradigm:

```
1️⃣ State Definition
   Define what dp[i][...] means
   Once you nail this, recursion is obvious

2️⃣ Recurrence Relation
   How does DP[i] relate to DP[i-1]?
   Always build on previous solutions

3️⃣ Base Cases
   When does recursion stop?
   What's the simplest subproblem?

4️⃣ Computation Order
   In what order should we fill the table?
   Dependencies tell us: must fill rows top-to-bottom

5️⃣ Final Answer Location
   Where is the answer? Always at dp[n][W]
```

This pattern repeats in:
- **LCS** (Longest Common Subsequence)
- **Edit Distance**
- **Coin Change**
- **Matrix Chain Multiplication**
- **Optimal BST**
- **Longest Increasing Subsequence**

Master this problem, and you can solve them all.

---

## Part 13: Comparison: Recursion vs. Tabulation

### Side-by-Side View

```
RECURSION (Top-Down):
  knapsack(i, w):
      if i == n or w == 0:
          return 0
      if weight[i] > w:
          return knapsack(i+1, w)
      else:
          return max(
              value[i] + knapsack(i+1, w - weight[i]),
              knapsack(i+1, w)
          )

TABULATION (Bottom-Up):
  for i = 1 to n:
      for w = 1 to W:
          if weight[i-1] > w:
              dp[i][w] = dp[i-1][w]
          else:
              dp[i][w] = max(
                  value[i-1] + dp[i-1][w-weight[i-1]],
                  dp[i-1][w]
              )
```

**Key Difference:**
```
Recursion starts at dpP[n][W] and works upward
Tabulation starts at dp[0][0] and works downward

Same logic, inverted execution direction.
```

---

## Part 14: The Exam Summary (One-Liners)

### If Asked: "Explain 0/1 Knapsack (Tabulation)"

**Level 1 (Passing):**
```
"Make a 2D table dp[i][w] = max value using first i items 
 with capacity w. Fill it row-by-row using recurrence relation."
```

**Level 2 (Good):**
```
"dp[i][w] represents the optimal solution for items 0..i-1 
 with capacity w. For each item, decide take or skip.
 For item i and capacity w: max(take, skip)."
```

**Level 3 (Excellent):**
```
"Tabulation is bottom-up DP. Define dp[i][w] = max value.
 Recurrence: if weight[i-1] ≤ w, then 
 dp[i][w] = max(value[i-1] + dp[i-1][w-weight[i-1]], dp[i-1][w]).
 Fill table row-by-row. Answer: dp[n][W].
 Time: O(n×W), Space: O(n×W) [can optimize to O(W)]."
```

---

## Part 15: Why This Is The REAL DP

### The Fundamental Difference

**Recursion-based thinking:**
```
"To solve the big problem, I need to solve smaller versions.
 Let me recurse down, then combine results upward."
```

**Tabulation-based thinking:**
```
"Let me solve ALL small problems first.
 Then build larger problems from solutions to smaller ones.
 Finally, read off the answer from the bottom-right cell."
```

Tabulation is **true bottom-up optimization**.

It eliminates:
- Recursion overhead
- Function call stack
- Redundant recomputation

It provides:
- Clear computation order
- Visible dependency structure
- Space optimization possibilities
- Easier to reason about

This is why professionals prefer tabulation over memoization.

---

## Summary Table

| Aspect | Recursion | Memoization | Tabulation |
|--------|-----------|-------------|-----------|
| **Direction** | Top-down | Top-down | Bottom-up |
| **Computation** | On-demand | On-demand | All cells |
| **Time** | O(2^n) | O(n×W) | O(n×W) |
| **Space** | O(n) | O(n×W) | O(n×W) |
| **Stack** | Deep | Deep | None |
| **Visibility** | Hidden | Partial | Complete |
| **Optimization** | Hard | Medium | Easy |
| **Preferred** | Learning | Interview | Production |

---

**This is the real Dynamic Programming.**

Tabulation is power without recursion.

Understand this, and you understand DP.
