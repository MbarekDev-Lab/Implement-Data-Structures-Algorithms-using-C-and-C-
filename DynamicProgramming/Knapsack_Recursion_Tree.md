# 0/1 Knapsack — Recursive Approach with Tree Tracing

## Part 1: The Recursive Algorithm (Clean Code)

### Base Logic

```c
int knapsack(int W, int wt[], int val[], int n) {
    
    // Base case: No items left or no capacity left
    if (n == 0 || W == 0)
        return 0;
    
    // If weight of current item exceeds capacity, skip it
    if (wt[n-1] > W)
        return knapsack(W, wt, val, n-1);
    
    // Current item fits, so we have a CHOICE:
    else
        return max(
            val[n-1] + knapsack(W - wt[n-1], wt, val, n-1),  // Include item
            knapsack(W, wt, val, n-1)                         // Exclude item
        );
}
```

### Understanding Each Part

**Function signature:**
```
knapsack(W, wt[], val[], n)
  W   = remaining capacity
  wt[] = weight array
  val[] = value array
  n   = number of items to consider (counting DOWN from n to 0)
```

**Base case:**
```
if (n == 0 || W == 0) return 0

When we reach here:
  Either no items left (n=0)
  Or no capacity left (W=0)
  
Either way: can't fit anything more, value = 0
```

**Item doesn't fit:**
```
if (wt[n-1] > W)
  return knapsack(W, wt, val, n-1)

No choice here. Item is too heavy.
Skip it and solve for remaining items.
```

**Item fits (THE KEY):**
```
return max(
  val[n-1] + knapsack(W - wt[n-1], wt, val, n-1),  // Take it
  knapsack(W, wt, val, n-1)                         // Leave it
)

Two choices:
  1. INCLUDE: get val[n-1], reduce capacity, solve for rest
  2. EXCLUDE: skip this item, keep capacity, solve for rest

Take the maximum.
```

---

## Part 2: Tree Tracing Example (Step by Step)

### Problem Setup

```
Items (indexed 0-based):
  wt[] = [10, 20, 30]    (weights)
  val[] = [60, 100, 120] (values)
  
Knapsack capacity: W = 50
Number of items: n = 3
```

### Reading the Recursion

**Function call: knapsack(50, 3)**

```
knapsack(50, 3)
  n=3, so we're deciding about item index 2 (wt=30, val=120)
  W=50, so we have 50 capacity
  
  Item 2 weight (30) ≤ capacity (50)? YES, so we have a choice.
  
  return max(
    120 + knapsack(50-30=20, 2),  // Include item 2
    knapsack(50, 2)                // Exclude item 2
  )
```

---

## Part 3: Complete Recursion Tree

### The Full Tree (Showing All Branches)

```
                              knapsack(50, 3)
                                    |
                    ┌───────────────┴───────────────┐
                    |                               |
            INCLUDE item 2              EXCLUDE item 2
            (wt=30, val=120)            
                    |                               |
         knapsack(20, 2)                 knapsack(50, 2)
                    |                               |
        ┌───────────┴───────────┐       ┌───────────┴───────────┐
        |                       |       |                       |
  INCLUDE item 1     EXCLUDE item 1  INCLUDE item 1   EXCLUDE item 1
  (wt=20, val=100)              (wt=20, val=100)
        |                       |       |                       |
  knapsack(0, 1)         knapsack(20, 1)  knapsack(30, 1) knapsack(50, 1)
        |                       |       |                       |
  return 0         ┌────┴────┐ ┌────┴────┐ ┌────┴────┐ ┌────┴────┐
                   |        |  |        |  |        |  |        |
                INCL EXCL   INCL EXCL    INCL EXCL   INCL EXCL
              (item 0)      (item 0)    (item 0)    (item 0)
                  |        |  |        |  |        |  |        |
             K(10,0) K(20,0) K(20,0) K(20,0) K(20,0) K(20,0) K(40,0) K(50,0)
              =0      =0      =0      =0      =0      =0      =0      =0
```

This tree is complex. Let's trace it step by step instead.

---

## Part 4: Detailed Step-by-Step Trace

### Starting Call: knapsack(50, 3)

```
Decision: Should I include item 2 (wt=30, val=120)?

Branch 1: INCLUDE item 2
  → 120 + knapsack(20, 2)
  
Branch 2: EXCLUDE item 2
  → knapsack(50, 2)

We need to evaluate both branches.
```

---

### Branch 1: INCLUDE Item 2 → knapsack(20, 2)

```
STATE: Remaining capacity = 20, Items to consider = {0, 1}

Decision: Should I include item 1 (wt=20, val=100)?

  Item 1 weight (20) ≤ capacity (20)? YES
  
  Branch 1a: INCLUDE item 1
    → 100 + knapsack(0, 1)
    → 100 + 0 = 100
    (No capacity left, so knapsack(0, 1) = 0)
  
  Branch 1b: EXCLUDE item 1
    → knapsack(20, 1)
    
    Decision: Should I include item 0 (wt=10, val=60)?
    
      Item 0 weight (10) ≤ capacity (20)? YES
      
      Branch 1b-i: INCLUDE item 0
        → 60 + knapsack(10, 0)
        → 60 + 0 = 60
        (No items left)
      
      Branch 1b-ii: EXCLUDE item 0
        → knapsack(20, 0)
        → 0
        (No items left)
      
      max(60, 0) = 60
  
  max(100, 60) = 100

Result of Branch 1: 120 + 100 = 220
```

---

### Branch 2: EXCLUDE Item 2 → knapsack(50, 2)

```
STATE: Remaining capacity = 50, Items to consider = {0, 1}

Decision: Should I include item 1 (wt=20, val=100)?

  Item 1 weight (20) ≤ capacity (50)? YES
  
  Branch 2a: INCLUDE item 1
    → 100 + knapsack(30, 1)
    
    Decision: Should I include item 0 (wt=10, val=60)?
    
      Item 0 weight (10) ≤ capacity (30)? YES
      
      Branch 2a-i: INCLUDE item 0
        → 60 + knapsack(20, 0)
        → 60 + 0 = 60
      
      Branch 2a-ii: EXCLUDE item 0
        → knapsack(30, 0)
        → 0
      
      max(60, 0) = 60
    
    Result: 100 + 60 = 160
  
  Branch 2b: EXCLUDE item 1
    → knapsack(50, 1)
    
    Decision: Should I include item 0 (wt=10, val=60)?
    
      Item 0 weight (10) ≤ capacity (50)? YES
      
      Branch 2b-i: INCLUDE item 0
        → 60 + knapsack(40, 0)
        → 60 + 0 = 60
      
      Branch 2b-ii: EXCLUDE item 0
        → knapsack(50, 0)
        → 0
      
      max(60, 0) = 60
  
  max(160, 60) = 160

Result of Branch 2: 160
```

---

### Final Answer

```
Starting with knapsack(50, 3):

max(
  Branch 1 (INCLUDE item 2): 220,
  Branch 2 (EXCLUDE item 2): 160
) = 220

✅ MAXIMUM VALUE = 220
✅ SELECTION: Items 1 and 2 (indices 1,2 or values 100,120)
             Weights: 20 + 30 = 50
             Values: 100 + 120 = 220
```

---

## Part 5: Visual Decision Tree

Here's a cleaner visualization of the key decisions:

```
knapsack(50, 3): "Capacity 50, consider items 0,1,2"
│
├─ INCLUDE item 2 (wt=30, val=120)
│  └─ knapsack(20, 2): "Capacity 20, consider items 0,1"
│     ├─ INCLUDE item 1 (wt=20, val=100)
│     │  └─ knapsack(0, 1) = 0
│     │     RESULT: 100 + 0 = 100
│     │
│     └─ EXCLUDE item 1
│        └─ knapsack(20, 1): "Capacity 20, consider item 0"
│           ├─ INCLUDE item 0 (wt=10, val=60)
│           │  └─ knapsack(10, 0) = 0
│           │     RESULT: 60
│           │
│           └─ EXCLUDE item 0
│              └─ knapsack(20, 0) = 0
│              MAX: 60
│        MAX: max(100, 60) = 100
│     TOTAL IF INCLUDE ITEM 2: 120 + 100 = 220
│
└─ EXCLUDE item 2
   └─ knapsack(50, 2): "Capacity 50, consider items 0,1"
      ├─ INCLUDE item 1 (wt=20, val=100)
      │  └─ knapsack(30, 1): "Capacity 30, consider item 0"
      │     ├─ INCLUDE item 0 (wt=10, val=60)
      │     │  └─ knapsack(20, 0) = 0
      │     │     RESULT: 60
      │     │
      │     └─ EXCLUDE item 0
      │        └─ knapsack(30, 0) = 0
      │        MAX: 60
      │     TOTAL IF INCLUDE ITEM 1: 100 + 60 = 160
      │
      └─ EXCLUDE item 1
         └─ knapsack(50, 1): "Capacity 50, consider item 0"
            ├─ INCLUDE item 0 (wt=10, val=60)
            │  └─ knapsack(40, 0) = 0
            │     RESULT: 60
            │
            └─ EXCLUDE item 0
               └─ knapsack(50, 0) = 0
               MAX: 60
        MAX: max(160, 60) = 160

FINAL: max(220, 160) = 220 ✅
```

---

## Part 6: Overlapping Subproblems (Why This Is Inefficient)

### The Problem: Same Subproblems Computed Multiple Times

In the example above, notice:

```
knapsack(20, 0) is computed in:
  - Branch 1a (directly: 0)
  - Branch 2a-i (directly: 0)
  
Both evaluate to 0, but we computed them twice.

In larger examples, this gets MUCH worse.

For example, knapsack(30, 1) might be computed:
  → Multiple times via different paths
  → Each path recomputes from scratch
  → Leads to exponential time
```

### Visualization: Overlapping Calls

```
For the full problem with more items,
you'd see the same (W, n) pair appearing in multiple branches:

                    K(50,3)
                   /      \
              K(20,2)    K(50,2)
              /   \        /    \
          K(0,1) K(20,1) K(30,1) K(50,1)
          /  \   /  \    /  \    /  \
         0   0  K(20,0) K(20,0) K(20,0) ...

Notice: K(20,0) appears in at least 2 places!

In larger instances, the same subproblem
appears MANY times.

Redundant computation = inefficiency
```

---

## Part 7: Time Complexity of Pure Recursion

### Why It's Exponential

```
For each item, we make 2 choices (include or exclude).

With n items total,
we explore 2^n possible combinations.

Each leaf of the recursion tree is a complete solution.

Even if we use memoization,
in the worst case, we have (n+1) × (W+1) unique subproblems.

But without memoization:
  - We compute each subproblem multiple times
  - Time: O(2^n) in worst case
```

### Examples

```
n=10: 2^10 = 1,024
n=20: 2^20 = 1,048,576
n=30: 2^30 = 1,073,741,824 ← Already over 1 billion!
n=40: 2^40 ≈ 1 trillion ← Impractical

This is why recursion alone doesn't work for large inputs.
```

---

## Part 8: Why DP Fixes This

### The Solution: Memoization

Store the result of each `knapsack(W, n)` call.

```
If knapsack(20, 1) is needed again,
don't recompute. Just look it up.

Time becomes: O(n × W)

Instead of: O(2^n)
```

### Example Comparison

```
For n=30, W=100:

Pure Recursion: O(2^30) = 1 billion+ calls
DP with Memoization: O(30 × 100) = 3,000 calls

That's a 333,000x speedup!
```

---

## Part 9: How DP Looks (Preview)

### Tabulation Approach

```
Instead of recursion, fill a 2D table:

dp[i][w] = maximum value using first i items with capacity w

Base cases:
  dp[0][w] = 0 for all w (no items)
  dp[i][0] = 0 for all i (no capacity)

Recurrence:
  for i from 1 to n:
    for w from 1 to W:
      if wt[i-1] > w:
        dp[i][w] = dp[i-1][w]
      else:
        dp[i][w] = max(
          val[i-1] + dp[i-1][w - wt[i-1]],  // Include
          dp[i-1][w]                         // Exclude
        )

Result: dp[n][W]
```

### The Same Logic, But Efficient

```
Recursion (inefficient):
  - Top-down
  - Many redundant calls
  - Hard to trace

DP (efficient):
  - Bottom-up
  - Compute each subproblem once
  - Can easily see the table
```

---

## Part 10: Complete C Implementation (Recursive)

```c
#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Recursive function
int knapsack(int W, int wt[], int val[], int n) {
    // Base case
    if (n == 0 || W == 0)
        return 0;
    
    // Item doesn't fit
    if (wt[n-1] > W)
        return knapsack(W, wt, val, n-1);
    
    // Item fits: choose better option
    else
        return max(
            val[n-1] + knapsack(W - wt[n-1], wt, val, n-1), // Include
            knapsack(W, wt, val, n-1)                        // Exclude
        );
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = 3;
    
    printf("Maximum value: %d\n", knapsack(W, wt, val, n));
    // Output: Maximum value: 220
    
    return 0;
}
```

---

## Part 11: Tracing with Calls Count

### To See The Inefficiency

Keep a global counter:

```c
int callCount = 0;

int knapsack(int W, int wt[], int val[], int n) {
    callCount++;
    printf("Call %d: knapsack(%d, %d)\n", callCount, W, n);
    
    if (n == 0 || W == 0)
        return 0;
    
    if (wt[n-1] > W)
        return knapsack(W, wt, val, n-1);
    
    else
        return max(
            val[n-1] + knapsack(W - wt[n-1], wt, val, n-1),
            knapsack(W, wt, val, n-1)
        );
}

// Running the example:
// You'll see MANY repeated calls like:
// - knapsack(20, 1) appears multiple times
// - knapsack(30, 0) appears multiple times
```

---

## Part 12: The Key Takeaway

### From Recursion to DP

```
Recursion says: "I'll explore all possibilities"
  ✓ Correct
  ✗ Slow (2^n)
  
The problem: We explore the same possibility multiple times

DP says: "I'll explore all possibilities, but remember them"
  ✓ Correct
  ✓ Fast (n × W)
  
The solution: Memoize (store) results

Both use the SAME recurrence relation.
DP just avoids redundant computation.
```

### Why Understand Recursion First?

Understanding the recursive approach shows:

```
✓ Where the choices are
✓ How subproblems relate to larger problems
✓ Why overlapping subproblems happen
✓ Why memoization helps

Once you see this, DP becomes obvious.
It's just "smart recursion with storage."
```

---

## Part 13: Next Step: Memoization

After understanding pure recursion, add a memo table:

```c
int memo[MAX_N][MAX_W];

int knapsack(int W, int n) {
    // Check if already computed
    if (memo[n][W] != -1)
        return memo[n][W];
    
    // Base case
    if (n == 0 || W == 0)
        return memo[n][W] = 0;
    
    // Compute and store
    if (wt[n-1] > W)
        memo[n][W] = knapsack(W, n-1);
    else
        memo[n][W] = max(
            val[n-1] + knapsack(W - wt[n-1], n-1),
            knapsack(W, n-1)
        );
    
    return memo[n][W];
}
```

This is the bridge between recursion and tabulation.

---

## Summary Table

| Aspect | Pure Recursion | Memoization | Tabulation |
|--------|---|---|---|
| **Approach** | Top-down, explore all | Top-down, store results | Bottom-up, build table |
| **Time** | O(2^n) | O(n × W) | O(n × W) |
| **Space** | O(n) stack | O(n × W) memo | O(n × W) table |
| **Intuitive?** | Yes | Yes | Less intuitive initially |
| **Practical?** | No, for large inputs | Yes | Yes |

---

The recursive approach teaches WHY DP is needed.

Master this first, then memoization becomes obvious.
