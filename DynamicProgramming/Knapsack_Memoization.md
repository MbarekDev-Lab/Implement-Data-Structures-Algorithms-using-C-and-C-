# 0/1 Knapsack with Memoization (Top-Down DP) — Abdul Bari's Approach

## Part 1: The Problem Setup (Crystal Clear)

### What We're Solving

You have:
```
N items (indexed 0 to N-1)

Each item i has:
  weight[i] = how much it weighs
  value[i] = how valuable it is

A knapsack with maximum capacity W

Constraint: total weight ≤ W

Goal: Maximize total value
```

### Mathematical Definition

$$\text{Maximize} \sum_{i \in \text{selected}} \text{value}[i]$$

$$\text{Subject to:} \sum_{i \in \text{selected}} \text{weight}[i] \leq W$$

### Why "0/1"?

```
For each item, you have exactly TWO choices:

0 = don't take the item
1 = take the item

No fractions (unlike Fractional Knapsack)
No duplicates (each item once at most)

This binary nature is central to the algorithm.
```

### Concrete Example

```
Items:
  Item 0: weight=10, value=60
  Item 1: weight=20, value=100
  Item 2: weight=30, value=120

Knapsack capacity: W = 50

Question: Which items should I select?

Possible solutions:
  {0,1}: weight=30, value=160 ✓
  {0,2}: weight=40, value=180 ✓
  {1,2}: weight=50, value=220 ✓✓ OPTIMAL
  {0,1,2}: weight=60 > 50 ✗ exceeds capacity
  {2}: weight=30, value=120

Answer: Take items 1 and 2, total value = 220
```

---

## Part 2: The Recursive Approach (Before Memoization)

### The Thinking Process

**For each item, ask:**
```
"Should I take this item?"

Two possibilities:

1. Take it
   → Gain its value
   → Reduce capacity
   → Solve for remaining items with less capacity

2. Skip it
   → Don't gain value
   → Keep capacity
   → Solve for remaining items with same capacity

Choose whichever gives more total value.
```

### The Recursive Function

**Definition:**
```
knapsack(i, w) = maximum value we can get
                  starting from item i
                  with remaining capacity w
```

**Base cases:**
```
if (i == n)      return 0  // no more items
if (w == 0)      return 0  // no capacity left
```

**Recursive cases:**
```
If weight[i] > w:
  // Item doesn't fit
  knapsack(i, w) = knapsack(i+1, w)
  
If weight[i] <= w:
  // Item fits, we have a choice
  knapsack(i, w) = max(
    value[i] + knapsack(i+1, w - weight[i]),  // Take item i
    knapsack(i+1, w)                          // Skip item i
  )
```

### Pseudocode (Before Memoization)

```
function knapsack(i, w):
    
    // Base cases
    if i == n or w == 0:
        return 0
    
    // Item doesn't fit
    if weight[i] > w:
        return knapsack(i+1, w)
    
    // Item fits: choose better option
    else:
        return max(
            value[i] + knapsack(i+1, w - weight[i]),  // Include
            knapsack(i+1, w)                          // Exclude
        )
```

---

## Part 3: Overlapping Subproblems (Why Memoization Is Needed)

### The Problem: Repeated Computation

**Without storing results:**

Multiple branches of recursion compute the same `knapsack(i, w)` pair.

```
Example:

knapsack(0, 50) calls:
  knapsack(1, 40)
  knapsack(1, 50)
  
knapsack(1, 40) calls:
  knapsack(2, 20)
  knapsack(2, 40)
  
knapsack(1, 50) calls:
  knapsack(2, 30)
  knapsack(2, 50)

Notice: knapsack(2, ...) appears multiple times!

Each appearance recomputes from scratch.
```

### Visual: Recursion Tree with Overlaps

```
                    K(0,50)
                   /       \
              K(1,40)      K(1,50)
              /    \       /     \
          K(2,20) K(2,40) K(2,30) K(2,50)
          
K(2,20) might appear from different paths
K(2,40) might appear from different paths

Same subproblem, different paths = overlapping
```

### Time Complexity Without Memoization

```
Worst case: O(2^n)

Why? For each item, 2 choices (take or skip)
     With n items: 2^n combinations

Examples:
  n=10:  2^10 = 1,024
  n=20:  2^20 ≈ 1 million
  n=30:  2^30 ≈ 1 billion ← Already impractical

This is why pure recursion doesn't work for large inputs.
```

### The Key Insight (Abdul Bari's Teaching)

```
"If the same subproblem appears multiple times,
 don't recompute it. STORE THE RESULT."

This is the core idea of memoization.
```

---

## Part 4: Introducing Memoization

### What Is Memoization?

```
= Caching results of subproblems
= Top-down DP (start with main problem, recurse, cache results)
= "Remember what you've already computed"
```

### Data Structure for Memoization

**Create a 2D array:**
```
dp[i][w] = maximum value when considering items i to n-1
           with remaining capacity w

Dimensions: (n+1) × (W+1)
Initialize: dp[i][w] = -1 (means "not yet computed")
```

### Algorithm with Memoization

**Check memo first:**
```
if dp[i][w] != -1:
    return dp[i][w]  // Already computed
```

**Compute if not found:**
```
Solve the subproblem as before
Store result: dp[i][w] = result
Return result
```

### Time Complexity With Memoization

```
Before: O(2^n)  ← exponential

After: O(n × W)  ← polynomial!

Why? Each unique (i, w) pair computed once
    Number of unique pairs: n × W
    Each pair: O(1) work (just a max comparison)
    Total: O(n × W)
```

---

## Part 5: Complete Code (C Implementation)

### Headers and Global Variables

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_W 1000

int n;           // number of items
int W;           // knapsack capacity
int weight[MAX_N];
int value[MAX_N];
int dp[MAX_N + 1][MAX_W + 1];  // memoization table
```

### Memoization-Based Knapsack Function

```c
int knapsack(int i, int w) {
    
    // Base cases
    if (i == n || w == 0) {
        return 0;  // No items left or no capacity
    }
    
    // Check if already computed
    if (dp[i][w] != -1) {
        return dp[i][w];
    }
    
    // Item doesn't fit
    if (weight[i] > w) {
        dp[i][w] = knapsack(i + 1, w);
    }
    
    // Item fits: choose the better option
    else {
        int take = value[i] + knapsack(i + 1, w - weight[i]);
        int skip = knapsack(i + 1, w);
        dp[i][w] = (take > skip) ? take : skip;
    }
    
    return dp[i][w];
}
```

### Main Function

```c
int main() {
    
    // Initialize memoization table
    memset(dp, -1, sizeof(dp));
    
    // Read input
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    printf("Enter knapsack capacity: ");
    scanf("%d", &W);
    
    printf("Enter weight and value for each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i);
        scanf("%d %d", &weight[i], &value[i]);
    }
    
    // Solve and print answer
    int result = knapsack(0, W);
    printf("\nMaximum value: %d\n", result);
    
    return 0;
}
```

### With Example Input

```c
int main() {
    
    memset(dp, -1, sizeof(dp));
    
    // Hard-coded example
    n = 3;
    W = 50;
    
    weight[0] = 10;  value[0] = 60;
    weight[1] = 20;  value[1] = 100;
    weight[2] = 30;  value[2] = 120;
    
    printf("Number of items: %d\n", n);
    printf("Capacity: %d\n", W);
    printf("\nItems:\n");
    for (int i = 0; i < n; i++) {
        printf("  Item %d: weight=%d, value=%d\n", i, weight[i], value[i]);
    }
    
    int result = knapsack(0, W);
    
    printf("\nMaximum value: %d\n", result);
    
    return 0;
}
```

---

## Part 6: Detailed Trace (Example Execution)

### Problem Instance

```
Items:
  0: weight=10, value=60
  1: weight=20, value=100
  2: weight=30, value=120

Capacity: W = 50
```

### Execution Trace

```
Call: knapsack(0, 50)
  │
  ├─ Item 0 (w=10, v=60) fits in capacity 50
  │
  ├─ Compute:
  │   take_0 = 60 + knapsack(1, 40)
  │   skip_0 = knapsack(1, 50)
  │
  └─ Need to solve both branches...

Branch 1: knapsack(1, 40)
  │
  ├─ Item 1 (w=20, v=100) fits in capacity 40
  │
  ├─ Compute:
  │   take_1 = 100 + knapsack(2, 20)
  │   skip_1 = knapsack(2, 40)
  │
  └─ Need to solve both branches...

  Sub-branch 1a: knapsack(2, 20)
    │
    ├─ Item 2 (w=30, v=120) does NOT fit in capacity 20
    │
    ├─ Therefore:
    │   knapsack(2, 20) = knapsack(3, 20) = 0
    │ dp[2][20] = 0
    │
    └─ RETURN 0

  Sub-branch 1b: knapsack(2, 40)
    │
    ├─ Item 2 (w=30, v=120) fits in capacity 40
    │
    ├─ Compute:
    │   take_2 = 120 + knapsack(3, 10) = 120 + 0 = 120
    │   skip_2 = knapsack(3, 40) = 0
    │
    ├─ max(120, 0) = 120
    │ dp[2][40] = 120
    │
    └─ RETURN 120
    
  Back to knapsack(1, 40):
    take_1 = 100 + 0 = 100
    skip_1 = 120
    
    max(100, 120) = 120
    dp[1][40] = 120
    RETURN 120

Branch 2: knapsack(1, 50)
  │
  ├─ Item 1 (w=20, v=100) fits in capacity 50
  │
  ├─ Compute:
  │   take_1 = 100 + knapsack(2, 30)
  │   skip_1 = knapsack(2, 50)
  │
  └─ Need to solve both branches...

  Sub-branch 2a: knapsack(2, 30)
    │
    ├─ Item 2 (w=30, v=120) fits in capacity 30
    │
    ├─ Compute:
    │   take_2 = 120 + knapsack(3, 0) = 120 + 0 = 120
    │   skip_2 = knapsack(3, 30) = 0
    │
    ├─ max(120, 0) = 120
    │ dp[2][30] = 120
    │
    └─ RETURN 120

  Sub-branch 2b: knapsack(2, 50)
    │
    ├─ Item 2 (w=30, v=120) fits in capacity 50
    │
    ├─ Compute:
    │   take_2 = 120 + knapsack(3, 20) = 120 + 0 = 120
    │   skip_2 = knapsack(3, 50) = 0
    │
    ├─ max(120, 0) = 120
    │ dp[2][50] = 120
    │
    └─ RETURN 120
    
  Back to knapsack(1, 50):
    take_1 = 100 + 120 = 220
    skip_1 = 120
    
    max(220, 120) = 220
    dp[1][50] = 220
    RETURN 220

Back to knapsack(0, 50):
  take_0 = 60 + 120 = 180
  skip_0 = 220
  
  max(180, 220) = 220
  dp[0][50] = 220
  RETURN 220

═══════════════════════════════════════
FINAL ANSWER: 220
═══════════════════════════════════════

Selection: Items 1 and 2
  Weight: 20 + 30 = 50 ✓
  Value: 100 + 120 = 220 ✓
```

---

## Part 7: Abdul Bari's Key Teaching Points

### 1. State Definition Is Everything

```
Define: knapsack(i, w)
  i = current item index (0 to n-1)
  w = remaining capacity (0 to W)

This definition captures the ENTIRE problem state.

Different state definition → different algorithm
Example:
  Could define: knapsack(capacity_used, items_considered)
  Would lead to a different recurrence
  But same time complexity O(n × W)
```

### 2. The Two Choices Are Always Present

```
For each item, ALWAYS ask:

"Take it or skip it?"

If you can't take it (doesn't fit):
  Only one choice exists → skip

If you can take it:
  Two choices → choose the better one

The max() encodes this decision-making.
```

### 3. Base Cases Are Critical

```
if (i == n):
  All items considered. Return 0.
  
if (w == 0):
  No capacity left. Can't add anything. Return 0.
  
These STOP the recursion.
Without them, infinite recursion.
```

### 4. Memoization vs. Tabulation

```
Both solve the same problem.

Memoization (top-down):
  Start with knapsack(0, W)
  Recurse downward
  Cache results as we compute them
  
Tabulation (bottom-up):
  Build table from base cases upward
  Iteratively fill dp[i][w]
  Same recurrence, different approach

Both: O(n × W) time, O(n × W) space

Memoization is more intuitive for recursion-based thinking.
Tabulation is more efficient memory-wise (can optimize to O(W)).
```

### 5. Overlapping Subproblems Are THE Reason DP Works

```
Without overlapping: memoization doesn't help much.

With overlapping:
  Same subproblem computed many times
  First computation: O(1) work
  Future lookups: O(1) lookup from memo
  Savings: exponential → polynomial

0/1 Knapsack has heavy overlap:
  Many paths lead to the same (i, w) state
  Memoization cache prevents redundant work
```

---

## Part 8: Visualization of Memoization Table

### Memo Table Layout

For the example: n=3, W=50

```
       w=0  w=10 w=20 w=30 w=40 w=50
i=0     0    ?    ?    ?    ?    ?
i=1     0    ?    ?    ?    ?    ?
i=2     0    ?    ?    ?    ?    ?
i=3     0    0    0    0    0    0

(i=3 means no items left, all return 0)
```

### Filled Memo Table (After Computation)

```
       w=0  w=10 w=20 w=30 w=40 w=50
i=0     0    60   100  120  180  220
i=1     0    0    100  100  100  220
i=2     0    0    0    120  120  120
i=3     0    0    0    0    0    0

dp[0][50] = 220 ← ANSWER
```

### Reading the Table

```
dp[i][w] = maximum value using items i..n-1 with capacity w

dp[0][50] = 220  (items 0,1,2 with capacity 50)
dp[1][50] = 220  (items 1,2 with capacity 50)
dp[2][50] = 120  (items 2 with capacity 50)
dp[1][40] = 120  (items 1,2 with capacity 40)

Each cell answers a specific question.
This table visualizes all subproblems solved.
```

---

## Part 9: Abdul Bari's Pedagogical Approach

### The Learning Path He Uses

```
Step 1: Understand the problem
        (What are items, weights, values, capacity?)

Step 2: Think recursively
        (For each item, take or skip?)

Step 3: Write base cases
        (When do we stop?)

Step 4: Write recursion
        (How do subproblems combine?)

Step 5: Identify overlapping subproblems
        (Will same knapsack(i,w) appear multiple times?)

Step 6: Add memoization
        (Store results to avoid recomputation)

Step 7: Verify complexity
        (From O(2^n) to O(n×W))

Step 8: Code it up
        (Translate pseudocode to actual code)
```

### Why Abdul Bari Emphasizes Memoization

```
Pure recursion: Correct but impractical
Memoization: Correct AND practical

Memoization teaches:
  ✓ Recursion is still important (top-down thinking)
  ✓ Caching is the trick (avoid redundant work)
  ✓ Table structure matches recursion tree

Students see HOW optimization works,
not just THAT it works.

This builds intuition for DP.
```

---

## Part 10: Common Mistakes to Avoid

### Mistake 1: Wrong Initialization

```
❌ WRONG:
   memset(dp, 0, sizeof(dp));
   
Why? dp[i][w] = 0 means "solved, value is 0"
     But 0 is a valid answer!
     Can't distinguish from "not computed"

✓ CORRECT:
   memset(dp, -1, sizeof(dp));
   
Now -1 means "not computed" (negative values impossible)
```

### Mistake 2: Wrong Base Case

```
❌ WRONG:
   if (i >= n) return 0;  // off-by-one error
   
✓ CORRECT:
   if (i == n) return 0;  // exactly n items (0 to n-1)
```

### Mistake 3: Forgetting to Check Memo Before Recursing

```
❌ WRONG:
   Compute first, then cache results
   This defeats the purpose of memoization

✓ CORRECT:
   Check memo FIRST
   if (dp[i][w] != -1) return dp[i][w];
   Then compute if not found
```

### Mistake 4: Wrong Capacity Reduction

```
❌ WRONG:
   knapsack(i + 1, w)  // Should reduce capacity!
   
✓ CORRECT:
   knapsack(i + 1, w - weight[i])  // Reduce capacity by item's weight
```

---

## Part 11: Complexity Analysis (From First Principles)

### Time Complexity

```
Number of unique subproblems:
  i ranges from 0 to n          →  n+1 values
  w ranges from 0 to W          →  W+1 values
  Total states: (n+1) × (W+1)   ≈ O(n × W)

Work per subproblem:
  Base case check: O(1)
  Memo check: O(1)
  Recursion and max: O(1)
  Total: O(1)

Total time: O(n × W) × O(1) = O(n × W)
```

### Space Complexity

```
Memoization table:
  (n+1) × (W+1) 2D array = O(n × W)

Recursion stack:
  Depth: O(n) (at most n items)

Total: O(n × W) for table + O(n) for stack
     = O(n × W) space (table dominates)
```

### Comparison: Recursion vs. Memoization

```
                    Pure Recursion    Memoization
Time                O(2^n)            O(n × W)
Space (stack)       O(n)              O(n)
Space (table)       0                 O(n × W)
Total space         O(n)              O(n × W)
Practical?          No (large n)      Yes (reasonable n,W)
```

---

## Part 12: Complete C Program (Full Example)

```c
#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_W 1000

int n;
int W;
int weight[MAX_N];
int value[MAX_N];
int dp[MAX_N + 1][MAX_W + 1];

int knapsack(int i, int w) {
    // Base cases
    if (i == n || w == 0) {
        return 0;
    }
    
    // Check memo
    if (dp[i][w] != -1) {
        return dp[i][w];
    }
    
    // Item doesn't fit
    if (weight[i] > w) {
        dp[i][w] = knapsack(i + 1, w);
    }
    // Item fits
    else {
        int take = value[i] + knapsack(i + 1, w - weight[i]);
        int skip = knapsack(i + 1, w);
        dp[i][w] = (take > skip) ? take : skip;
    }
    
    return dp[i][w];
}

int main() {
    // Initialize memo
    memset(dp, -1, sizeof(dp));
    
    // Example: 3 items, capacity 50
    n = 3;
    W = 50;
    
    weight[0] = 10;  value[0] = 60;
    weight[1] = 20;  value[1] = 100;
    weight[2] = 30;  value[2] = 120;
    
    printf("═══════════════════════════════════════\n");
    printf("        0/1 KNAPSACK MEMOIZATION\n");
    printf("═══════════════════════════════════════\n\n");
    
    printf("Items:\n");
    for (int i = 0; i < n; i++) {
        printf("  Item %d: weight=%d, value=%d\n", i, weight[i], value[i]);
    }
    
    printf("\nKnapsack capacity: %d\n", W);
    
    int result = knapsack(0, W);
    
    printf("\n═══════════════════════════════════════\n");
    printf("Maximum value: %d\n", result);
    printf("═══════════════════════════════════════\n");
    
    // Print memo table for visualization
    printf("\nMemo table (dp[i][w]):\n");
    printf("     ");
    for (int w = 0; w <= W; w += 5) {
        printf("w=%2d ", w);
    }
    printf("\n");
    
    for (int i = 0; i <= n; i++) {
        printf("i=%d: ", i);
        for (int w = 0; w <= W; w += 5) {
            if (dp[i][w] == -1) {
                printf("  -  ");
            } else {
                printf(" %3d ", dp[i][w]);
            }
        }
        printf("\n");
    }
    
    return 0;
}
```

### Expected Output

```
═══════════════════════════════════════
        0/1 KNAPSACK MEMOIZATION
═══════════════════════════════════════

Items:
  Item 0: weight=10, value=60
  Item 1: weight=20, value=100
  Item 2: weight=30, value=120

Knapsack capacity: 50

═══════════════════════════════════════
Maximum value: 220
═══════════════════════════════════════

Memo table (dp[i][w]):
     w= 0 w= 5 w=10 w=15 w=20 w=25 w=30 w=35 w=40 w=45 w=50
i=0:  0  60  60  60 100 100 120 120 180 180 220
i=1:  0   0   0   0 100 100 100 100 100 100 220
i=2:  0   0   0   0   0   0 120 120 120 120 120
i=3:  0   0   0   0   0   0   0   0   0   0   0
```

---

## Part 13: Abdul Bari's Final Takeaway (TL;DR)

### The Core Lesson

```
1️⃣ Problem: Maximize value with weight constraint

2️⃣ Recursive thinking: For each item, take or skip

3️⃣ Overlapping subproblems: Same decisions repeat

4️⃣ Memoization: Cache results to avoid recomputation

5️⃣ Complexity shift: O(2^n) → O(n × W)

6️⃣ Top-down DP: Recursion + memoization

This pattern applies to MANY DP problems.
Master it here, apply it everywhere.
```

### Why This Teaching Is Brilliant

```
✓ Pure recursion: Shows the natural thinking
✓ Overlapping subproblems: Motivates memoization
✓ Memoization: Teaches optimization without changing logic
✓ Complexity analysis: Shows concrete speedup
✓ Code implementation: Bridges theory and practice

Students don't just learn an algorithm.
They learn HOW and WHY DP works.
```

---

## Summary: The Memoization Strategy

| Aspect | Detail |
|--------|--------|
| **Base case** | i == n or w == 0 → return 0 |
| **Memo check** | if dp[i][w] != -1 → return dp[i][w] |
| **Item doesn't fit** | weight[i] > w → skip to next item |
| **Item fits** | max(take, skip) → choose better |
| **Time** | O(n × W) because n×W unique states |
| **Space** | O(n × W) for memo table + O(n) for stack |
| **Approach** | Top-down: start with problem, recurse, cache |
| **Key insight** | Memoization eliminates exponential recursion |

---

End of Memoization Guide

This is how Abdul Bari teaches it: problem first, recursion second, optimization third.
