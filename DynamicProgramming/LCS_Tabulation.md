# Longest Common Subsequence (LCS) — Tabulation Approach (Bottom-Up DP)

## Part 1: Problem Setup — No Change from Recursion

### The Same Problem, Different Solution

We're still finding the **Longest Common Subsequence** of two strings.

**Input:**
- String X of length m
- String Y of length n

**Output:**
- The length of their LCS

**The Recurrence (Same as Before):**

$$L(i, j) = \begin{cases}
0 & \text{if } i = 0 \text{ or } j = 0 \\
1 + L(i-1, j-1) & \text{if } X[i-1] = Y[j-1] \\
\max(L(i-1, j), L(i, j-1)) & \text{if } X[i-1] \neq Y[j-1]
\end{cases}$$

### The Core Insight

The formula is **identical to recursion**.

What changes is **HOW we compute it:**
- **Recursion:** Top-down (start at L(m,n), recurse to base cases)
- **Tabulation:** Bottom-up (start at base cases, build to L(m,n))

---

## Part 2: The DP Table Structure

### Matrix Definition

Create a 2D table (array):
$$\text{dp}[i][j] = \text{LCS length for first } i \text{ characters of X and first } j \text{ characters of Y}$$

### Dimensions

- **Rows:** 0 to m (because we include empty string case)
- **Columns:** 0 to n (because we include empty string case)
- **Size:** (m+1) × (n+1)

### Example Setup

```
For X = "ABCBDAB" (length 7) and Y = "BDCABA" (length 6):

        ""  B  D  C  A  B  A
    ""   0  0  0  0  0  0  0
    A    0  
    B    0  
    C    0  
    B    0  
    D    0  
    A    0  
    B    0  

Size: (7+1) × (6+1) = 8×7 matrix
```

---

## Part 3: Initialization

### Base Cases

The first row and column are all **0**:

$$\text{dp}[0][j] = 0 \quad \forall j \in [0, n]$$
$$\text{dp}[i][0] = 0 \quad \forall i \in [0, m]$$

**Why?** If one string is empty, the LCS length is 0.

### Visualized

```
        ""  B  D  C  A  B  A
    ""   0  0  0  0  0  0  0
    A    0  ?  ?  ?  ?  ?  ?
    B    0  ?  ?  ?  ?  ?  ?
    C    0  ?  ?  ?  ?  ?  ?
    B    0  ?  ?  ?  ?  ?  ?
    D    0  ?  ?  ?  ?  ?  ?
    A    0  ?  ?  ?  ?  ?  ?
    B    0  ?  ?  ?  ?  ?  ?

First row = 0 ✓
First column = 0 ✓
Remaining cells = to be filled
```

---

## Part 4: Filling Strategy

### Standard Approach: Row by Row

Fill the table **row by row**, from left to right:

```
FOR i = 1 TO m
    FOR j = 1 TO n
        IF X[i-1] == Y[j-1]
            dp[i][j] = 1 + dp[i-1][j-1]
        ELSE
            dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

### Dependency Analysis

When computing **dp[i][j]**, we need:
- **dp[i-1][j-1]** (diagonal parent)
- **dp[i-1][j]** (top parent)
- **dp[i][j-1]** (left parent)

**All three are in cells we've already computed if we fill row by row!**

---

## Part 5: Detailed Worked Example (Small)

### Example: X = "ABD", Y = "BD"

#### Step 0: Initialize

```
       ""  B  D
   ""   0  0  0
   A    0  0  0
   B    0  0  0
   D    0  0  0
```

#### Step 1: Fill Row 1 (for 'A')

**Cell [1][1]: Comparing X[0]='A' with Y[0]='B'**
```
X[0] = 'A', Y[0] = 'B'
They don't match (A ≠ B)

dp[1][1] = max(dp[0][1], dp[1][0])
         = max(0, 0)
         = 0
```

**Cell [1][2]: Comparing X[0]='A' with Y[1]='D'**
```
X[0] = 'A', Y[1] = 'D'
They don't match (A ≠ D)

dp[1][2] = max(dp[0][2], dp[1][1])
         = max(0, 0)
         = 0
```

**After Row 1:**
```
       ""  B  D
   ""   0  0  0
   A    0  0  0
   B    0  ?  ?
   D    0  ?  ?
```

#### Step 2: Fill Row 2 (for 'B')

**Cell [2][1]: Comparing X[1]='B' with Y[0]='B'**
```
X[1] = 'B', Y[0] = 'B'
They MATCH! (B == B)

dp[2][1] = 1 + dp[1][0]
         = 1 + 0
         = 1
```

**Cell [2][2]: Comparing X[1]='B' with Y[1]='D'**
```
X[1] = 'B', Y[1] = 'D'
They don't match (B ≠ D)

dp[2][2] = max(dp[1][2], dp[2][1])
         = max(0, 1)
         = 1
```

**After Row 2:**
```
       ""  B  D
   ""   0  0  0
   A    0  0  0
   B    0  1  1
   D    0  ?  ?
```

#### Step 3: Fill Row 3 (for 'D')

**Cell [3][1]: Comparing X[2]='D' with Y[0]='B'**
```
X[2] = 'D', Y[0] = 'B'
They don't match (D ≠ B)

dp[3][1] = max(dp[2][1], dp[3][0])
         = max(1, 0)
         = 1
```

**Cell [3][2]: Comparing X[2]='D' with Y[1]='D'**
```
X[2] = 'D', Y[1] = 'D'
They MATCH! (D == D)

dp[3][2] = 1 + dp[2][1]
         = 1 + 1
         = 2
```

#### Final Table

```
       ""  B  D
   ""   0  0  0
   A    0  0  0
   B    0  1  1
   D    0  1  2

Answer: dp[3][2] = 2
LCS length = 2
Actual LCS: "BD"
```

---

## Part 6: Larger Example Walkthrough

### Example: X = "ABCBDAB", Y = "BDCABA"

I'll show the completed table and key cell computations:

```
        ""  B  D  C  A  B  A
    ""   0  0  0  0  0  0  0
    A    0  0  0  0  1  1  1
    B    0  1  1  1  1  2  2
    C    0  1  1  2  2  2  2
    B    0  1  1  2  2  3  3
    D    0  1  2  2  2  3  3
    A    0  1  2  2  3  3  4
    B    0  1  2  2  3  4  4
```

### Key Cell Explanations

**Cell [1][3]: X[0]='A', Y[2]='C'**
```
A ≠ C, so:
dp[1][3] = max(dp[0][3], dp[1][2])
         = max(0, 0) = 0
```

**Cell [1][4]: X[0]='A', Y[3]='A'**
```
A == A, so:
dp[1][4] = 1 + dp[0][3]
         = 1 + 0 = 1
```

**Cell [2][2]: X[1]='B', Y[1]='D'**
```
B ≠ D, so:
dp[2][2] = max(dp[1][2], dp[2][1])
         = max(0, 1) = 1
```

**Cell [2][5]: X[1]='B', Y[4]='B'**
```
B == B, so:
dp[2][5] = 1 + dp[1][4]
         = 1 + 1 = 2
```

**Cell [7][6]: X[6]='B', Y[5]='A'**
```
B ≠ A, so:
dp[7][6] = max(dp[6][6], dp[7][5])
         = max(4, 4) = 4
```

### Final Answer

$$dp[7][6] = 4$$

The LCS length is **4** (possible LCSs: "BDAB", "BCBA", "BCAB")

---

## Part 7: Reconstruction (Finding the Actual LCS)

### Problem

The DP table gives us the **length**, not the actual subsequence.

We need to **backtrack** through the table to recover which characters are in the LCS.

### Algorithm

Start at **dp[m][n]** and move backwards:

```
FUNCTION reconstruct(i, j):
    IF i == 0 OR j == 0
        return empty string
    
    IF X[i-1] == Y[j-1]
        // Characters match — include in LCS
        return reconstruct(i-1, j-1) + X[i-1]
    ELSE
        // Characters don't match — move towards larger value
        IF dp[i-1][j] > dp[i][j-1]
            return reconstruct(i-1, j)
        ELSE
            return reconstruct(i, j-1)
```

### Step-by-Step Trace (Using Previous Example)

**Starting at [7][6], value = 4:**

```
       ""  B  D  C  A  B  A
   ""   0  0  0  0  0  0  0
   A    0  0  0  0  1  1  1
   B    0  1  1  1  1  2  2
   C    0  1  1  2  2  2  2
   B    0  1  1  2  2  3  3
   D    0  1  2  2  2  3  3
   A    0  1  2  2  3  3  4
   B    0  1  2  2  3  4  4  ← START HERE
```

**Step 1: At [7][6] (X[6]='B', Y[5]='A')**
```
X[6] ≠ Y[5]
dp[6][6]=4 > dp[7][5]=4? NO (equal)
Move to [7][5]
```

**Step 2: At [7][5] (X[6]='B', Y[4]='B')**
```
X[6] == Y[4]? YES! 'B' == 'B'
Include 'B' in LCS
Move to [6][4]
```

**Step 3: At [6][4] (X[5]='A', Y[3]='A')**
```
X[5] == Y[3]? YES! 'A' == 'A'
Include 'A' in LCS
Move to [5][3]
```

**Step 4: At [5][3] (X[4]='D', Y[2]='C')**
```
X[4] ≠ Y[2]
dp[4][3]=2 > dp[5][2]=2? NO (equal)
Move to [5][2]
```

**Step 5: At [5][2] (X[4]='D', Y[1]='D')**
```
X[4] == Y[1]? YES! 'D' == 'D'
Include 'D' in LCS
Move to [4][1]
```

**Step 6: At [4][1] (X[3]='B', Y[0]='B')**
```
X[3] == Y[0]? YES! 'B' == 'B'
Include 'B' in LCS
Move to [3][0]
```

**Step 7: At [3][0]**
```
j == 0, STOP
```

**Collected characters (in reverse order): B, D, A, B**
**Reversed: B, D, A, B → But we collected in reverse, so "BDAB"**

**Final LCS: "BDAB"** ✓

---

## Part 8: Why Row-by-Row Filling Works

### Dependency Chain

When computing `dp[i][j]`, we need:
1. **dp[i-1][j-1]** — diagonal, earlier row, shift column
2. **dp[i-1][j]** — same column, earlier row
3. **dp[i][j-1]** — same row, earlier column

**All three are "already computed" if we:**
- Process row by row (ensures earlier rows ready)
- Process left to right (ensures earlier columns ready)

### Visualization

```
When processing cell [i][j]:

        [i-1][j-1] ← [i-1][j]
              \       /
               \     /
                [i][j] ← [i][j-1]

All three parent cells are in:
• Earlier row(s) — processed in previous loop iteration
• Earlier column — processed in current row earlier
```

---

## Part 9: Time & Space Complexity

### Analysis

**Time Complexity:**
$$\text{Time} = O(m \times n)$$

We compute each cell once, and each cell computation is O(1):
- One comparison: X[i-1] == Y[j-1]
- One or two array lookups
- One max operation

Total: (m+1) × (n+1) ≈ m×n cells

**Space Complexity:**
$$\text{Space} = O(m \times n)$$

We store the entire 2D DP table.

### Comparison: Recursion vs Tabulation

| Aspect | Recursion | Tabulation |
|--------|-----------|------------|
| **Time** | O(2^(m+n)) | O(m×n) |
| **Space (call stack)** | O(m+n) | O(m×n) |
| **Space (table)** | None | O(m×n) |
| **Overhead** | Function calls | Array allocation |
| **Practical limit** | ~15 characters | 1000+ characters |

### Example Growth

```
For m = n = 10:

Recursion: ~2^20 = 1,048,576 calls ❌ Slow
Tabulation: 10×10 = 100 cells ✓ Fast
Speedup: 10,485× faster!

For m = n = 20:

Recursion: ~2^40 ≈ 1 trillion calls ❌ IMPOSSIBLE
Tabulation: 20×20 = 400 cells ✓ Still fast
```

---

## Part 10: Key Insight — Why Tabulation Works

### From Recursion to Tabulation

**Recursion:** Starts at problem → recurses to smaller subproblems → bottoms out at base cases

**Tabulation:** Starts at base cases → builds up to larger subproblems → reaches final answer

### The Magic

**Number of distinct subproblems:**
- Recursion: m×n (but computed exponentially many times)
- Tabulation: m×n (computed exactly once each)

**By removing redundant computation, we transform:**
$$O(2^{m+n}) \text{ (exponential)} \quad \rightarrow \quad O(m \times n) \text{ (polynomial)}$$

---

## Part 11: Complete C Implementation Sketch

### Core Algorithm Structure

```c
// dp[i][j] = LCS length for X[0..i-1] and Y[0..j-1]
int dp[MAX_M+1][MAX_N+1];

// Initialize: first row and column with 0
for (int i = 0; i <= m; i++)
    dp[i][0] = 0;
for (int j = 0; j <= n; j++)
    dp[0][j] = 0;

// Fill the table row by row
for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
        if (X[i-1] == Y[j-1])
            dp[i][j] = 1 + dp[i-1][j-1];  // Characters match
        else
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);  // Try both options
    }
}

// Answer is in dp[m][n]
return dp[m][n];
```

### Reconstruction

```c
void printLCS(char *X, char *Y, int i, int j) {
    if (i == 0 || j == 0)
        return;
    
    if (X[i-1] == Y[j-1]) {
        // Characters match — include in LCS
        printLCS(X, Y, i-1, j-1);
        printf("%c", X[i-1]);
    } else {
        // Characters don't match — move towards larger value
        if (dp[i-1][j] > dp[i][j-1])
            printLCS(X, Y, i-1, j);
        else
            printLCS(X, Y, i, j-1);
    }
}
```

---

## Part 12: Universal DP Pattern (LCS Instance)

### The Framework Applied to LCS

| Step | Description | LCS Implementation |
|------|-------------|-------------------|
| 1. **Understand** | Find longest common sequence (order preserved in both strings) | |
| 2. **Define State** | L(i,j) = LCS length for first i chars of X, first j of Y | (m+1)×(n+1) table |
| 3. **Recurrence** | Match: 1+L(i-1,j-1), NoMatch: max(L(i-1,j), L(i,j-1)) | if-else structure |
| 4. **DP Check** | Yes! Exponential→Polynomial, overlapping subproblems | 2^(m+n) → m×n |
| 5. **Solution** | Tabulation (fill row-by-row) | Nested loops |
| 6. **Answer** | dp[m][n] gives the length | Print table and answer |
| 7. **Reconstruct** | Backtrack from [m][n] | recursive printLCS() |

---

## Part 13: Pattern Recognition — LCS vs Other DP Problems

### Similarities

**Knapsack:**
- 2D table: dp[i][w] = max value for first i items, weight w
- Fill row by row

**MCM (Matrix Chain Multiplication):**
- 2D table: dp[i][j] = min cost for matrices i to j
- Fill by chain length (ensures dependency ordering)

**LCS:**
- 2D table: dp[i][j] = LCS length for first i and j characters
- Fill row by row (ensures dependencies ready)

### Difference from Others

- **Knapsack:** 1D choice per cell (include/exclude item)
- **MCM:** Optimization over split point k
- **LCS:** String comparison over characters

---

## Part 14: Extensions & Related Problems

### Building on LCS Foundation

**Edit Distance (Levenshtein Distance):**
- DP formula extends LCS with delete/insert/replace costs
- Same 2D matrix structure
- Diagonal movement when characters match

**Sequence Alignment (Bioinformatics):**
- LCS with scoring functions for matches/mismatches
- Used in DNA sequence comparison
- Critical for genomics research

**Diff Algorithms (Version Control):**
- Git, SVN use LCS-like algorithms
- Find minimal changes between file versions
- Display what changed between commits

---

## Part 15: Exam & Interview Quick Reference

### Tabulation Lecture Key Points

**What to Memorize:**
1. **Formula:** Same as recursion (3 cases: empty, match, no-match)
2. **Table size:** (m+1) × (n+1)
3. **Filling order:** Row by row, left to right
4. **Time complexity:** O(m×n)
5. **Space complexity:** O(m×n)

**What to Explain:**
1. **Why tabulation:** Avoids recomputing same subproblems
2. **Why row-by-row:** Ensures all dependencies ready
3. **How to reconstruct:** Backtrack from [m][n] using comparisons
4. **When matches:** Include character, move diagonally
5. **When no match:** Move up or left (whichever had larger value)

**What to Code:**
1. Initialization (first row/column = 0)
2. Double loop (row by row, column by column)
3. If-else for character comparison
4. Optional reconstruction function

---

## Part 16: Complete Understanding Summary

### What You Now Know (Tabulation Phase)

✅ **Tabulation concept:** Build table bottom-up from base cases  
✅ **Table initialization:** First row and column are 0  
✅ **Filling strategy:** Row by row, left to right (ensures dependencies)  
✅ **Cell computation:** Same formula as recursion, just computed once  
✅ **Reconstruction:** Backtrack to find actual LCS, not just length  
✅ **Complexity:** O(m×n) time and space (polynomial, practical)  
✅ **Pattern recognition:** Same framework applies to Knapsack, MCM, etc.  
✅ **Extensions:** Edit distance, sequence alignment use similar approach  

### The Full Journey

**Recursion Phase:**
- Understands WHAT the problem is
- Shows WHY elegant answer is hard to compute
- Demonstrates exponential explosion with overlapping subproblems

**Tabulation Phase:**
- Shows HOW to compute efficiently
- Removes redundancy by computing each subproblem once
- Transforms O(2^(m+n)) → O(m×n)

**The Wisdom:**
> When you see optimal substructure and overlapping subproblems, DP converts exponential recursion into polynomial tabulation.

---

## 🎯 Final Insight

**LCS is not just a problem. It's a gateway to understanding:**
- Optimal substructure
- Overlapping subproblems
- DP table design and filling
- Reconstruction algorithms
- Why some problems are easy and others are hard

**Mastering LCS means you can approach:**
- Edit distance
- Sequence alignment
- Longest increasing subsequence
- And many other DP problems using the same pattern

---

## Exam Quick Reference Table

| Aspect | Details |
|--------|---------|
| **Problem** | Find longest sequence common to both strings in order |
| **State** | dp[i][j] = LCS length for first i chars of X, first j of Y |
| **Recurrence** | 0 if i=0∨j=0; 1+dp[i-1][j-1] if X[i-1]=Y[j-1]; max(dp[i-1][j],dp[i][j-1]) else |
| **Table Size** | (m+1) × (n+1) |
| **Initialization** | dp[0][j]=0 and dp[i][0]=0 for all i,j |
| **Filling Order** | Row by row, left to right |
| **Time** | O(m×n) ✓ Polynomial |
| **Space** | O(m×n) ✓ Practical |
| **Answer** | dp[m][n] |
| **Reconstruction** | Backtrack from [m][n], include chars when X[i-1]==Y[j-1] |
