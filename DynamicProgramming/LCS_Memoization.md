# Longest Common Subsequence (LCS) — Memoization Approach (Top-Down DP)

## Part 1: What is Memoization? The Bridge Between Recursion and Tabulation

### The Problem We're Solving

Pure recursion for LCS is **exponential** O(2^(m+n)) because the same subproblems are computed **thousands of times**.

**Example:** Computing LCS(4,4) might call LCS(3,3) **50 times**.

### The Solution: Memoization

**Memoization** means:
> Store the result of a subproblem the first time you compute it, and **reuse that stored result** on future calls.

### How It Works (Conceptually)

```
First call to LCS(3,3):
  → Not in memory
  → Compute it
  → Store result in dp[3][3]
  → Return result

Later call to LCS(3,3):
  → Check memory first
  → Found in dp[3][3]!
  → Return immediately (no recomputation)
```

### Key Insight

Same recurrence formula as recursion.
Same logic as tabulation.

**Only difference:** When we compute, we **remember the answer for next time**.

---

## Part 2: Understanding the Memoization Table Structure

### The DP Memo Table

Create a 2D array to store computed results:

```c
int dp[MAX_M+1][MAX_N+1];
```

### Initialization

Initialize all cells to **-1** (sentinel value meaning "not yet computed"):

```c
// Initialize all to -1 (means "not computed")
for (int i = 0; i <= m; i++)
    for (int j = 0; j <= n; j++)
        dp[i][j] = -1;
```

Why **-1**? Because:
- LCS length can be 0 (empty subsequence) ← valid answer
- So we need a value that means "not computed yet"
- Use -1 as sentinel

### What Each Cell Represents

$$dp[i][j] = \text{LCS length of first } i \text{ chars of X and first } j \text{ chars of Y}$$

**Example for X="ABC", Y="DEF":**

```
       j → 0  1  2  3
              ""D  E  F
    i ↓ 0 "" 0  0  0  0
      1 A   0  ?  ?  ?
      2 B   0  ?  ?  ?
      3 C   0  ?  ?  ?
```

Each `?` will be filled with the LCS length for that prefix pair.

---

## Part 3: The Memoized Recurrence Formula

### Core Logic

$$LCS(i, j) = \begin{cases}
0 & \text{if } i = 0 \text{ or } j = 0 \\
\text{return } dp[i][j] & \text{if } dp[i][j] \neq -1 \\
1 + LCS(i-1, j-1) & \text{if } X[i-1] = Y[j-1] \\
\max(LCS(i-1, j), LCS(i, j-1)) & \text{otherwise}
\end{cases}$$

### In Plain Language

```
LCS(i, j):
    1. Check if we already computed this:
       if dp[i][j] ≠ -1:
           return dp[i][j]
    
    2. Base cases:
       if i == 0 or j == 0:
           dp[i][j] = 0
           return 0
    
    3. Recurrence:
       if X[i-1] == Y[j-1]:
           dp[i][j] = 1 + LCS(i-1, j-1)
       else:
           dp[i][j] = max(LCS(i-1, j), LCS(i, j-1))
    
    4. Store and return:
       return dp[i][j]
```

### Code Sketch

```c
int LCS_memo(char *X, char *Y, int i, int j) {
    // Step 1: Check memo table
    if (dp[i][j] != -1)
        return dp[i][j];
    
    // Step 2: Base case
    if (i == 0 || j == 0)
        return dp[i][j] = 0;
    
    // Step 3: Recurrence
    if (X[i-1] == Y[j-1])
        dp[i][j] = 1 + LCS_memo(X, Y, i-1, j-1);
    else
        dp[i][j] = max(
            LCS_memo(X, Y, i-1, j),
            LCS_memo(X, Y, i, j-1)
        );
    
    // Step 4: Return stored value
    return dp[i][j];
}
```

---

## Part 4: Deep Concept 1 — State Definition

### What is State?

In DP, **state** means the parameters that **uniquely define a subproblem**.

For LCS, the state is: **(i, j)**

- **i** = first i characters of X
- **j** = first j characters of Y

### Why This Choice?

Different (i,j) pairs represent different subproblems:

```
LCS(1,1) → comparing X[0] with Y[0]
LCS(1,2) → comparing X[0] with Y[0..1]
LCS(2,1) → comparing X[0..1] with Y[0]
LCS(2,2) → comparing X[0..1] with Y[0..1]
```

All are different subproblems → different answers expected.

### What Makes a Good State?

1. **Unique:** Different states = different answers
2. **Complete:** State contains all needed information
3. **Minimal:** No unnecessary parameters

For LCS:
- ✓ Unique: Each (i,j) pair is unique
- ✓ Complete: Knowing i and j tells us exactly which prefixes to compare
- ✓ Minimal: We don't need anything else

### What Bad State Looks Like

```
❌ State = "some prefix of X"
   Not complete! We don't know which prefix of Y

❌ State = length of X and Y
   Not unique! Many different (X,Y) have same lengths
   
✓ State = (i, j) = prefixes of both strings
   Unique, complete, minimal!
```

---

## Part 5: Deep Concept 2 — Recurrence Relation

### What is Recurrence?

The **recurrence relation** is the math formula that tells us:
> "How do I solve a bigger problem using smaller problems?"

### For LCS, The Recurrence Has Two Cases

**Case A: Characters Match — X[i-1] == Y[j-1]**

```
If they match, that character MUST be in the LCS.

So we:
1. Include it (add 1)
2. Reduce to smaller problem: LCS(i-1, j-1)

Formula: LCS(i,j) = 1 + LCS(i-1, j-1)

Why?
Because including a matching character increases LCS length by 1,
and the rest of the LCS comes from the remaining prefixes.
```

**Case B: Characters Don't Match — X[i-1] ≠ Y[j-1]**

```
If they don't match, we have TWO choices:

Option 1: Ignore last character of X
          Take LCS(i-1, j)
          
Option 2: Ignore last character of Y
          Take LCS(i, j-1)

We take the MAXIMUM of these two:

Formula: LCS(i,j) = max(LCS(i-1, j), LCS(i, j-1))

Why maximum?
Because we want the LONGEST common subsequence.
One option might be better than the other,
so we take whichever produces the longer result.
```

### Visual Interpretation

```
            LCS(i-1, j-1)  ← diagonal move (match)
                 /\
                /  \
               /    \
         LCS(i-1,j) — LCS(i,j)
             |        /
             |       /
             |      /
        LCS(i,j-1)

When characters match: go diagonal + 1
When they don't: take max from up or left
```

### Why This Makes Sense

The recurrence captures the problem structure:
- Matching character = must include = diagonal movement + 1
- Non-matching = must choose = take better option

---

## Part 6: Deep Concept 3 — Overlapping Subproblems

### What Are Overlapping Subproblems?

**Overlapping subproblems** means the same subproblem is encountered **multiple times** during recursion.

### Concrete Example: LCS(4,4)

```
                LCS(4,4)
                   / \
                  /   \
            LCS(3,4)   LCS(4,3)
            /    \       /    \
       LCS(2,4)  LCS(3,3)  LCS(3,3)  LCS(4,2)
          / \      /  \      /  \      / \
      ...  ...  ...   ...  ...   ...  ... ...

Notice: LCS(3,3) appears TWICE!
        LCS(2,3) appears MULTIPLE times!
        LCS(1,2) appears MULTIPLE times!
```

### Quantifying the Overlap

**Without memoization:** LCS(3,3) might be computed:
- Once via LCS(4,4) → LCS(3,4) → LCS(3,3)
- Again via LCS(4,4) → LCS(4,3) → LCS(3,3)
- Again via other paths...

**Result:** Same computation done many times.

### Why Memoization Fixes This

```
First call to LCS(3,3):
  → Compute it
  → Store in dp[3][3] = <result>

Later calls to LCS(3,3):
  → Check dp[3][3]
  → Found! Return immediately
  → No recomputation!
```

### The Waste Without Memoization

```
Without memo: 2^(m+n) recursive calls
With memo:    m×n unique subproblems

For m=n=10:
Without: 2^20 = 1,048,576 calls
With:    10×10 = 100 unique subproblems

That's a 10,485× wasted computation eliminated!
```

---

## Part 7: Deep Concept 4 — Time Complexity Improvement

### Analysis Without Memoization

**Recurrence:**
$$T(m, n) = T(m-1, n) + T(m, n-1) + O(1)$$

This grows exponentially:
$$T(m, n) = O(2^{m+n})$$

For m=n=10: ~1 million function calls

### Analysis With Memoization

Each unique (i,j) pair is computed **exactly once**:

```
Number of unique subproblems = (m+1) × (n+1)

For each subproblem:
  - Check memo table: O(1)
  - Perform computation: O(1)
  - Store result: O(1)

Total: O(m × n)
```

### The Transformation

| Aspect | Without Memo | With Memo |
|--------|-------------|-----------|
| **Recursive calls** | 2^(m+n) | m×n |
| **Per subproblem** | Computed multiple times | Computed once |
| **Time complexity** | O(2^(m+n)) | O(m×n) |
| **Space (stack)** | O(m+n) | O(m+n) + O(m×n) memo |
| **Practical limit** | ~15 chars | 1000+ chars |

### Growth Comparison

```
String length (m=n=k):

k=10:   Without:   2^20 ≈ 1 million      With:   100 ops      Speedup: 10,000×
k=15:   Without:   2^30 ≈ 1 billion      With:   225 ops      Speedup: 4 million×
k=20:   Without:   2^40 ≈ 1 trillion     With:   400 ops      Speedup: 2.5 billion×
```

---

## Part 8: Deep Concept 5 — Top-Down vs Bottom-Up DP

### The Three Approaches Side by Side

**Pure Recursion (No Memoization):**
```
LCS(m, n)
├─ LCS(m-1, n-1)
│  ├─ LCS(m-2, n-2)
│  └─ ...
└─ LCS(m-1, n)
   └─ ...

Flow: Top-down (start at destination, recurse to base)
Redundancy: Exponential (same subproblems computed repeatedly)
Time: O(2^(m+n))
```

**Memoization (Top-Down DP):**
```
LCS(m, n)  [Check memo? Not found]
├─ LCS(m-1, n-1)  [Check memo? Not found]
│  └─ ...
└─ LCS(m-1, n)  [Check memo? Not found]
   └─ ...

Each subproblem computed once, result stored
Future calls check memo → O(1) lookup

Flow: Top-down (start at destination)
Memoization: Yes (store computed results)
Redundancy: Eliminated (each subproblem once)
Time: O(m×n)
```

**Tabulation (Bottom-Up DP):**
```
dp[0][0] = 0
dp[1][0] = 0
dp[0][1] = 0
...compute row by row...
dp[m][n] = ANSWER

Flow: Bottom-up (start at base, build to destination)
Loop structure: Nested for loops (not recursive)
Redundancy: Eliminated (each cell once)
Time: O(m×n)
```

### The Key Difference

| Aspect | Memoization | Tabulation |
|--------|------------|-----------|
| **Approach** | Top-down | Bottom-up |
| **Control flow** | Recursion | Iteration |
| **Calling pattern** | Call needed subproblems | Compute in fixed order |
| **Space efficiency** | Stack + memo | Memo only |
| **Intuition** | "Solve using smaller problems" | "Build from base cases" |
| **Code style** | Looks like recursion | Looks like loops |

### Why Both Exist

**Tabulation (Bottom-Up):**
- ✓ Iterative (no recursion overhead)
- ✓ Natural loop structure
- ✓ Easier to understand filling order
- ✓ No function call overhead

**Memoization (Top-Down):**
- ✓ Closer to natural thinking
- ✓ Only computes needed subproblems
- ✓ More flexible (skip unnecessary branches)
- ✓ Easier to implement once you have recursion

---

## Part 9: The Complete Memoized Algorithm

### Pseudocode

```
FUNCTION LCS_memo(X, Y, i, j):
    // Step 1: Check if already computed
    IF dp[i][j] ≠ -1:
        RETURN dp[i][j]
    
    // Step 2: Base case — empty string
    IF i = 0 OR j = 0:
        dp[i][j] ← 0
        RETURN 0
    
    // Step 3: Characters match
    IF X[i-1] = Y[j-1]:
        dp[i][j] ← 1 + LCS_memo(X, Y, i-1, j-1)
    // Step 4: Characters don't match
    ELSE:
        dp[i][j] ← MAX(
            LCS_memo(X, Y, i-1, j),
            LCS_memo(X, Y, i, j-1)
        )
    
    // Step 5: Store and return
    RETURN dp[i][j]

MAIN FUNCTION:
    Initialize dp[0..m][0..n] = -1
    RETURN LCS_memo(X, Y, m, n)
```

### Step-by-Step Execution Example

**Input: X = "ABD", Y = "BD"**

```
CALL 1: LCS_memo(3, 2)
        Check dp[3][2] = -1 (not computed)
        X[2]='D', Y[1]='D' → MATCH!
        dp[3][2] = 1 + LCS_memo(2, 1)
        
CALL 2: LCS_memo(2, 1)
        Check dp[2][1] = -1 (not computed)
        X[1]='B', Y[0]='B' → MATCH!
        dp[2][1] = 1 + LCS_memo(1, 0)
        
CALL 3: LCS_memo(1, 0)
        Check dp[1][0] = -1 (not computed)
        j = 0 → BASE CASE
        dp[1][0] = 0
        RETURN 0
        
BACK TO CALL 2:
        dp[2][1] = 1 + 0 = 1
        RETURN 1
        
BACK TO CALL 1:
        dp[3][2] = 1 + 1 = 2
        RETURN 2
        
ANSWER: 2 (correct! LCS="BD")
```

---

## Part 10: Reconstruction With Memoization

### Why Reconstruction?

Memoization tells us the **length**, not the actual subsequence.

To find the actual LCS string, we must **backtrack** through the memo table using the same logic:

```
Start at dp[m][n] and move backwards:
- If characters matched when computed: include in LCS, move diagonal
- If they didn't match: move up or left (towards larger value)
```

### Reconstruction Algorithm

```
FUNCTION reconstruct(i, j):
    IF i = 0 OR j = 0:
        RETURN empty string
    
    IF X[i-1] = Y[j-1]:
        // Characters matched → include in LCS
        RETURN reconstruct(i-1, j-1) + X[i-1]
    ELSE:
        // Characters didn't match → move towards larger
        IF dp[i-1][j] > dp[i][j-1]:
            RETURN reconstruct(i-1, j)
        ELSE:
            RETURN reconstruct(i, j-1)
```

### Example Reconstruction

```
After computing memoization table for X="ABCBDAB", Y="BDCABA":

dp table (partial):
        ""  B  D  C  A  B  A
    ""   0  0  0  0  0  0  0
    A    0  0  0  0  1  1  1
    B    0  1  1  1  1  2  2
    C    0  1  1  2  2  2  2
    B    0  1  1  2  2  3  3
    D    0  1  2  2  2  3  3
    A    0  1  2  2  3  3  4
    B    0  1  2  2  3  4  4

Start at [7][6] (value=4):
[7][6]: X[6]='B', Y[5]='A' → don't match
        dp[6][6]=4 = dp[7][5]=4 → go either way (say up)
[6][6]: X[5]='A', Y[5]='A' → MATCH! Include 'A'
        Move to [5][5]
[5][5]: X[4]='D', Y[4]='B' → don't match
        dp[4][5]=3 > dp[5][4]=3 → go up
[4][5]: X[3]='B', Y[4]='B' → MATCH! Include 'B'
        Move to [3][4]
[3][4]: X[2]='C', Y[3]='A' → don't match
        dp[2][4]=2 > dp[3][3]=2 → go up
[2][4]: X[1]='B', Y[3]='A' → don't match
        dp[1][4]=1 > dp[2][3]=1 → go up
[1][4]: X[0]='A', Y[3]='A' → MATCH! Include 'A'
        Move to [0][3]
[0][3]: i=0 → STOP

Collected (reversed): A, B, A
Note: Path dependent on tie-breaking; another path gives "BDAB"
Both are valid LCS of length 4
```

---

## Part 11: Complete C Implementation Structure

### Overall Design

```c
#include <stdio.h>
#include <string.h>

#define MAX_M 100
#define MAX_N 100

// Memoization table
int dp[MAX_M+1][MAX_N+1];

// Forward declaration
int lcs_memo(const char *X, const char *Y, int i, int j);

// Core memoized recursion
int lcs_memo(const char *X, const char *Y, int i, int j) {
    // Check memo
    if (dp[i][j] != -1)
        return dp[i][j];
    
    // Base case
    if (i == 0 || j == 0)
        return dp[i][j] = 0;
    
    // Recurrence
    if (X[i-1] == Y[j-1])
        dp[i][j] = 1 + lcs_memo(X, Y, i-1, j-1);
    else
        dp[i][j] = max(lcs_memo(X, Y, i-1, j),
                      lcs_memo(X, Y, i, j-1));
    
    return dp[i][j];
}

// Wrapper function
int lcs_length(const char *X, const char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    
    // Initialize dp table
    memset(dp, -1, sizeof(dp));
    
    // Call memoized function
    return lcs_memo(X, Y, m, n);
}

// Reconstruction
char* reconstruct_lcs(const char *X, const char *Y, int i, int j) {
    if (i == 0 || j == 0)
        return "";  // Simplified
    
    if (X[i-1] == Y[j-1])
        return reconstruct_lcs(X, Y, i-1, j-1) + X[i-1];
    else {
        if (dp[i-1][j] > dp[i][j-1])
            return reconstruct_lcs(X, Y, i-1, j);
        else
            return reconstruct_lcs(X, Y, i, j-1);
    }
}
```

---

## Part 12: Complexity Analysis

### Time Complexity

**With Memoization:**

$$T(m, n) = O(m \times n)$$

**Reasoning:**
- Each of m×n cells is computed **exactly once**
- Each computation is O(1) (one comparison, one max, array lookups)
- Total: (m+1) × (n+1) ≈ m×n cells × O(1) per cell = O(m×n)

### Space Complexity

**Two components:**

1. **Memoization table:** O(m×n)
2. **Recursion stack (call stack depth):** O(m+n)
   - Longest path: move from (m,n) to (0,0)
   - Each step reduces m or n by 1
   - Maximum depth: m+n

**Total Space:** O(m×n) dominated

### Comparison of All Three Approaches

| Approach | Time | Space (Stack) | Space (Memo) | Practical |
|----------|------|---------------|--------------|-----------|
| **Recursion** | O(2^(m+n)) | O(m+n) | — | n ≤ 12 |
| **Memoization** | O(m×n) | O(m+n) | O(m×n) | n ≤ 1000 |
| **Tabulation** | O(m×n) | O(1) | O(m×n) | n ≤ 1000 |

---

## Part 13: Why Memoization Matters

### The Bridge Between Theory and Practice

**Recursion:**
- Intuitive to understand
- Natural problem decomposition
- But exponentially slow

**Tabulation:**
- Fast and efficient
- Iterative structure
- But filling order not obvious

**Memoization:**
- ✓ Keeps recursive structure (intuitive)
- ✓ Adds caching (efficient)
- ✓ You choose which subproblems to compute
- ✓ Understands natural recursion, just optimized

### When to Use Memoization vs Tabulation

**Use Memoization When:**
- ✓ Recursive thinking is natural
- ✓ Not all subproblems are needed
- ✓ Filling order is complex

**Use Tabulation When:**
- ✓ Iterative thinking preferred
- ✓ All subproblems needed
- ✓ Loop structure is straightforward

**For LCS:** Both work equally well!

---

## Part 14: Pattern Recognition — Memoization Template

### Universal Memoization Pattern

This pattern applies to **every DP problem**:

```
1. Define state (what parameters define a subproblem?)
2. Create memo table with same dimensions
3. Initialize memo table to "not computed" (-1)
4. Write recursive function with three parts:
   a) Check memo: if computed, return stored value
   b) Base cases: if terminal condition, return and store
   c) Recurrence: compute using smaller subproblems, store, return

Step 1: Define state → (i, j) for LCS
Step 2: Create memo → dp[m+1][n+1]
Step 3: Initialize → all to -1
Step 4: Write function:
   a) Check dp[i][j] ≠ -1?
   b) Handle i=0, j=0 base cases
   c) Recurse with formula, store in dp[i][j]
```

### Applying to Other Problems

**0/1 Knapsack:**
- State: (i, w) = first i items, capacity w
- Memo: dp[n+1][W+1]
- Same pattern!

**Edit Distance:**
- State: (i, j) = first i chars of X, first j of Y
- Memo: dp[m+1][n+1]
- Same pattern!

---

## Part 15: Interview & Exam Wisdom

### What Interviewers Look For

When coding memoization LCS:

✓ **State Definition:** "I'll use dp[i][j] for..."
✓ **Memo Check:** "First, check if already computed"
✓ **Base Case:** "If empty string, return 0"
✓ **Recurrence:** "Match → diagonal, no match → max"
✓ **Storage:** "Store the result before returning"

### Common Mistakes to Avoid

| Mistake | Consequence | Fix |
|---------|------------|-----|
| Forget to check memo | Recomputation → exponential | Check first line |
| Initialize memo to 0 | Can't distinguish 0 result from "not computed" | Use -1 |
| Forget to store result | Defeats purpose of memoization | Store before return |
| Wrong recurrence | Wrong answer | Verify match/no-match cases |
| Forget base case | Stack overflow | Add i=0 or j=0 check |

---

## Part 16: Complete Understanding Summary

### What You Now Know (Memoization Phase)

✅ **Memoization concept:** Cache computed results to eliminate recomputation  
✅ **Memo table structure:** 2D array, initialized to -1  
✅ **State definition:** (i, j) parameters define unique subproblem  
✅ **Recurrence relation:** Match vs no-match cases, expressed as recursion  
✅ **Overlapping subproblems:** Same (i,j) computed multiple times without memo  
✅ **Time improvement:** O(2^(m+n)) → O(m×n) by computing each cell once  
✅ **Top-down DP:** Recursive approach with caching (vs tabulation's bottom-up)  
✅ **Reconstruction:** Backtrack through memo table to find actual LCS string  
✅ **Universal pattern:** Apply memoization framework to any DP problem  
✅ **Trade-offs:** Keep recursive intuition but gain polynomial efficiency  

### The Three-Phase Learning Path

**Phase 1: Recursion**
- Problem: Exponential O(2^(m+n))
- Solution: Pure recursion (no optimization)
- Lesson: Understanding natural problem structure

**Phase 2: Memoization (This Phase)**
- Problem: Same subproblems computed many times
- Solution: Cache results in memo table
- Lesson: Optimization through eliminating redundancy
- Transition: Recursion + caching = Top-down DP

**Phase 3: Tabulation**
- Problem: But recursion overhead might exist
- Solution: Rewrite from bottom-up as loops
- Lesson: Further optimization and clarity
- Transition: Loop-based bottom-up DP

### Why This Progression Matters

Most DP problems are easier to **think about recursively** but easier to **code iteratively**.

Memoization is the bridge:
- **Maintain** recursive intuition
- **Add** caching for efficiency
- **Transition** to tabulation if needed

---

## 🎯 Final Insight for Abdul Bari Devotees

> **"Memoization is not a different algorithm. It's just recursion with a memory."**

Once you master memoization:

1. You can solve ANY DP problem recursively first
2. Then add a memo table
3. Then (if needed) convert to tabulation

This is the **thinking pattern** that separates good problem-solvers from great ones.

---

## Exam Quick Reference

| Aspect | Details |
|--------|---------|
| **Approach** | Top-down (recursive with caching) |
| **Memo initialization** | All cells to -1 (means "not computed") |
| **First check** | if (dp[i][j] ≠ -1) return dp[i][j] |
| **Base cases** | if (i=0 or j=0) return 0 |
| **Recurrence** | Match: 1+LCS(i-1,j-1), NoMatch: max(LCS(i-1,j), LCS(i,j-1)) |
| **Storage** | dp[i][j] = result before returning |
| **Time** | O(m×n) — each cell computed once |
| **Space** | O(m×n) memo + O(m+n) stack |
| **Reconstruction** | Backtrack: if match go diagonal, else go max dir |
| **Pattern** | Define state → write memo check → write recursion → store result |
