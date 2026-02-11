# Matrix Chain Multiplication — Recursion Approach

## The Gateway to True DP Thinking

Matrix Chain Multiplication is where Abdul Bari teaches you the **real** Dynamic Programming mindset.

Not just "solve subproblems and cache results" (that's memoization).

But **"how to recognize optimal substructure and overlapping subproblems in ANY problem."**

---

## Part 1: The Actual Problem

### What's On The Whiteboard?

```
A × B × C × D
```

With dimensions:
```
A: 3×2
B: 2×4
C: 4×2
D: 2×5
```

### Encoding As Dimension Array

Instead of thinking "matrix by matrix," think as a **sequence of dimensions**:

$$d = [3, 2, 4, 2, 5]$$

**Mapping:**
```
Matrix A: rows = d[0] = 3,  cols = d[1] = 2
Matrix B: rows = d[1] = 2,  cols = d[2] = 4
Matrix C: rows = d[2] = 4,  cols = d[3] = 2
Matrix D: rows = d[3] = 2,  cols = d[4] = 5
```

So for $n$ matrices, you need $n+1$ dimensions.

### Why This Representation?

Because the **middle dimension gets absorbed** during multiplication:

$$A_{p \times q} \times B_{q \times r} = C_{p \times r}$$

Notice: The $q$ appears in both but only once in the result.

So you only need to track the **boundary dimensions** for the chain.

---

## Part 2: The Core Question

### Same Result, Different Cost

No matter how you parenthesize, you get the same final matrix.

But the **number of scalar multiplications changes drastically**.

**Option 1:** $((A \times B) \times C) \times D$
```
A×B: 3×2×4 = 24 multiplications → 3×4 matrix
(AB)×C: 3×4×2 = 24 multiplications → 3×2 matrix
(AB×C)×D: 3×2×5 = 30 multiplications → 3×5 matrix
Total: 24 + 24 + 30 = 78 multiplications
```

**Option 2:** $A \times (B \times (C \times D))$
```
C×D: 4×2×5 = 40 multiplications → 4×5 matrix
B×(CD): 2×4×5 = 40 multiplications → 2×5 matrix
A×(B(CD)): 3×2×5 = 30 multiplications → 3×5 matrix
Total: 40 + 40 + 30 = 110 multiplications
```

**Option 3:** $(A \times B) \times (C \times D)$
```
A×B: 3×2×4 = 24 multiplications → 3×4 matrix
C×D: 4×2×5 = 40 multiplications → 4×5 matrix
(AB)×(CD): 3×4×5 = 60 multiplications → 3×5 matrix
Total: 24 + 40 + 60 = 124 multiplications
```

**Question:** Which is optimal?

**Answer:** Option 1 with 78 multiplications (but this isn't always optimal—it depends!)

---

## Part 3: The State Definition (CRITICAL)

### Abdul Bari's Definition

$$m[i][j] = \text{Minimum number of scalar multiplications to compute } A_i \times A_{i+1} \times \cdots \times A_j$$

**Important note on indexing:**
- $i$ and $j$ refer to **matrix indices** (1-indexed in the mathematical definition)
- In C code, we'll use 0-indexed arrays

### Base Case

$$m[i][i] = 0$$

Why? Because multiplying a single matrix by itself requires **zero multiplications**—it's already computed.

---

## Part 4: The Recurrence Formula (The Heart)

### What He Writes On Whiteboard

$$m[i][j] = \min_{i \leq k < j} \left( m[i][k] + m[k+1][j] + d[i-1] \cdot d[k] \cdot d[j] \right)$$

### Breaking It Down Symbol By Symbol

**The Minimization:**
```
We try ALL possible split points k
from k=i to k=j-1

For each k, we calculate the cost.
Then we take the minimum.
```

**For a Specific Split at $k$:**

$$\text{Cost} = m[i][k] + m[k+1][j] + d[i-1] \times d[k] \times d[j]$$

**First term:** $m[i][k]$
```
Optimal cost of multiplying matrices i through k
The result is a d[i-1] × d[k] matrix
```

**Second term:** $m[k+1][j]$
```
Optimal cost of multiplying matrices k+1 through j
The result is a d[k] × d[j] matrix
```

**Third term:** $d[i-1] \times d[k] \times d[j]$
```
Cost of multiplying those two results:
(d[i-1] × d[k]) × (d[k] × d[j])
     ↑ rows      ↑ cols and rows  ↑ cols

This is the definition of matrix multiplication cost.
Number of multiplications = rows_left × shared_dim × cols_right
```

**Why Take The Minimum?**
```
We want the OPTIMAL way to parenthesize.
Different split points k give different costs.
We choose the one with minimum cost.
```

---

## Part 5: Visual Example (4 Matrices)

### Setup

```
Matrices: A₁, A₂, A₃, A₄
Dimensions: d = [3, 2, 4, 2, 5]

A₁: 3×2
A₂: 2×4
A₃: 4×2
A₄: 2×5
```

### Computing m[1][4] (Cost to multiply all 4 matrices)

We try all splits $k \in \{1, 2, 3\}$:

**Split at k=1:**
$$m[1][4] = m[1][1] + m[2][4] + d[0] \times d[1] \times d[4]$$
$$= 0 + m[2][4] + 3 \times 2 \times 5 = m[2][4] + 30$$

**Split at k=2:**
$$m[1][4] = m[1][2] + m[3][4] + d[0] \times d[2] \times d[4]$$
$$= m[1][2] + m[3][4] + 3 \times 4 \times 5 = m[1][2] + m[3][4] + 60$$

**Split at k=3:**
$$m[1][4] = m[1][3] + m[4][4] + d[0] \times d[3] \times d[4]$$
$$= m[1][3] + 0 + 3 \times 2 \times 5 = m[1][3] + 30$$

Then we **recursively solve** $m[2][4]$, $m[1][2]$, $m[3][4]$, and $m[1][3]$.

### Recursion Tree Structure

```
                    m(1,4)
                   /  |  \
                  /   |   \
                 /    |    \
           m(1,1)   m(2,4)   (recurse)
            = 0        /  \
                       /    \
                  m(2,2)    m(3,4)
                   = 0        / \
                             /   \
                        m(3,3)  m(4,4)
                         = 0      = 0

(This is simplified; full tree has more branches)
```

The tree **explodes** because each subproblem spawns more.

For example, $m(2,4)$ appears again in other paths.

---

## Part 6: Optimal Substructure (The DP Property)

### What Does It Mean?

**A problem has optimal substructure if:**
```
An optimal solution to the problem
contains optimal solutions to subproblems.
```

### Proof for MCM

Suppose the optimal way to compute $A_i \times \cdots \times A_j$ splits at $k^*$.

Then:
```
→ The optimal way to compute A_i × ... × A_k*
  must be OPTIMAL for that subproblem.

→ The optimal way to compute A_k*+1 × ... × A_j
  must be OPTIMAL for that subproblem.

Why?

If either subproblem wasn't optimal,
we could replace it with the optimal solution,
getting a cheaper overall solution.

But that contradicts the assumption that our original split was optimal.

Therefore, BOTH subproblems must be solved optimally.
```

**This is why DP works:**
```
Optimal solution = optimal subproblems + merge cost
```

---

## Part 7: Overlapping Subproblems (The Recursion Killer)

### What Happens When We Recurse?

Watch the recursion tree:

```
                           m(1,4)
                          /  |  \
                         /   |   \
                    m(1,1) m(2,4) ... 
                     / | \
                    /  |  \
                   ...m(2,3)...
                   / | \
                  /  |  \
              m(2,2) m(3,3) ...
               = 0    = 0
                      
At another branch:
                    ...m(2,4)...
                       / | \
                      /  |  \
                   m(2,2) m(3,4) ...
```

**Notice:** $m(2,3)$, $m(3,4)$, and many others appear **multiple times**.

**Example Count:**
```
For n=6 matrices:

Some subproblems are computed THOUSANDS of times.

That's why pure recursion is exponential.

Time complexity ≈ O(4^n / n^(3/2))
That's WORSE than 2^n for large n!
```

### The Key Insight

```
These overlapping subproblems are what kill pure recursion.

BUT...

They are also what make DP so powerful.

Because:
• We can identify the overlaps
• We can store results (memoization)
• We can build bottom-up (tabulation)
```

---

## Part 8: Abdul Bari's Teaching Strategy

### What He's NOT Teaching

He's NOT teaching you: "How to multiply matrices optimally."

(That's just the application domain.)

### What He IS Teaching

He's teaching you **the DP recognition pattern:**

```
1️⃣ Define state clearly
   → m[i][j] = cost of i to j

2️⃣ Identify base case
   → m[i][i] = 0

3️⃣ Express as recurrence with split point k
   → Solve left: m[i][k]
   → Solve right: m[k+1][j]
   → Add merge cost: cost_of_multiplying_two_results
   → Take minimum over all k

4️⃣ Draw the recursion tree
   → See the exponential explosion
   → Recognize overlapping subproblems
   → Realize pure recursion is too slow

5️⃣ Recognize you MUST cache
   → This is where DP comes in
```

---

## Part 9: The Recursion Implementation

### Pseudocode

```
function matrixChainCost(i, j, d):
    
    // Base case: single matrix
    if i == j:
        return 0
    
    minCost = INFINITY
    
    // Try all split points
    for k = i to j-1:
        
        // Cost of left partition
        leftCost = matrixChainCost(i, k, d)
        
        // Cost of right partition
        rightCost = matrixChainCost(k+1, j, d)
        
        // Cost of multiplying left and right results
        mergeCost = d[i-1] * d[k] * d[j]
        
        // Total cost for this split
        totalCost = leftCost + rightCost + mergeCost
        
        // Keep track of minimum
        minCost = min(minCost, totalCost)
    
    return minCost
```

### C Implementation

```c
#include <stdio.h>
#include <limits.h>

int d[100];  // dimension array
int n;       // number of matrices

int matrixChainCost(int i, int j) {
    
    // Base case: single matrix requires no multiplication
    if (i == j) {
        return 0;
    }
    
    int minCost = INT_MAX;
    
    // Try all split points
    for (int k = i; k < j; k++) {
        
        // Cost of multiplying matrices from i to k
        int leftCost = matrixChainCost(i, k);
        
        // Cost of multiplying matrices from k+1 to j
        int rightCost = matrixChainCost(k+1, j);
        
        // Cost of multiplying the two results:
        // (rows of left matrix) × (shared dimension) × (cols of right matrix)
        // = d[i-1] × d[k] × d[j]
        int mergeCost = d[i-1] * d[k] * d[j];
        
        // Total cost for this split
        int totalCost = leftCost + rightCost + mergeCost;
        
        // Update minimum
        if (totalCost < minCost) {
            minCost = totalCost;
        }
    }
    
    return minCost;
}
```

---

## Part 10: Worked Example (Manual Trace)

### Problem Setup

```
4 matrices: A₁, A₂, A₃, A₄
Dimensions: d = [1, 2, 3, 4, 5]

A₁: 1×2
A₂: 2×3
A₃: 3×4
A₄: 4×5
```

### Computing m[1][4]

**Call:** `matrixChainCost(1, 4)`

Since $1 \neq 4$, we try splits:

#### Try k=1:
```
leftCost = matrixChainCost(1, 1) = 0
rightCost = matrixChainCost(2, 4) = ?
mergeCost = d[0] * d[1] * d[4] = 1 * 2 * 5 = 10

Need to compute m[2][4]...
```

#### Try k=2:
```
leftCost = matrixChainCost(1, 2) = ?
rightCost = matrixChainCost(3, 4) = ?
mergeCost = d[0] * d[2] * d[4] = 1 * 3 * 5 = 15

Need to compute m[1][2] and m[3][4]...
```

#### Try k=3:
```
leftCost = matrixChainCost(1, 3) = ?
rightCost = matrixChainCost(4, 4) = 0
mergeCost = d[0] * d[3] * d[4] = 1 * 4 * 5 = 20

Need to compute m[1][3]...
```

### Computing Subproblems

**m[1][1] = 0** (single matrix)
**m[2][2] = 0** (single matrix)
**m[3][3] = 0** (single matrix)
**m[4][4] = 0** (single matrix)

**m[1][2]:**
```
Split at k=1:
leftCost = m[1][1] = 0
rightCost = m[2][2] = 0
mergeCost = d[0] * d[1] * d[2] = 1 * 2 * 3 = 6
Total = 0 + 0 + 6 = 6
m[1][2] = 6
```

**m[2][3]:**
```
Split at k=2:
leftCost = m[2][2] = 0
rightCost = m[3][3] = 0
mergeCost = d[1] * d[2] * d[3] = 2 * 3 * 4 = 24
Total = 0 + 0 + 24 = 24
m[2][3] = 24
```

**m[3][4]:**
```
Split at k=3:
leftCost = m[3][3] = 0
rightCost = m[4][4] = 0
mergeCost = d[2] * d[3] * d[4] = 3 * 4 * 5 = 60
Total = 0 + 0 + 60 = 60
m[3][4] = 60
```

**m[1][3]:**
```
Try k=1:
leftCost = m[1][1] = 0
rightCost = m[2][3] = 24
mergeCost = d[0] * d[1] * d[3] = 1 * 2 * 4 = 8
Total = 0 + 24 + 8 = 32

Try k=2:
leftCost = m[1][2] = 6
rightCost = m[3][3] = 0
mergeCost = d[0] * d[2] * d[3] = 1 * 3 * 4 = 12
Total = 6 + 0 + 12 = 18

m[1][3] = min(32, 18) = 18  (split at k=2 is better)
```

**m[2][4]:**
```
Try k=2:
leftCost = m[2][2] = 0
rightCost = m[3][4] = 60
mergeCost = d[1] * d[2] * d[4] = 2 * 3 * 5 = 30
Total = 0 + 60 + 30 = 90

Try k=3:
leftCost = m[2][3] = 24
rightCost = m[4][4] = 0
mergeCost = d[1] * d[3] * d[4] = 2 * 4 * 5 = 40
Total = 24 + 0 + 40 = 64

m[2][4] = min(90, 64) = 64  (split at k=3 is better)
```

**m[1][4]:**
```
Try k=1:
leftCost = m[1][1] = 0
rightCost = m[2][4] = 64
mergeCost = d[0] * d[1] * d[4] = 1 * 2 * 5 = 10
Total = 0 + 64 + 10 = 74

Try k=2:
leftCost = m[1][2] = 6
rightCost = m[3][4] = 60
mergeCost = d[0] * d[2] * d[4] = 1 * 3 * 5 = 15
Total = 6 + 60 + 15 = 81

Try k=3:
leftCost = m[1][3] = 18
rightCost = m[4][4] = 0
mergeCost = d[0] * d[3] * d[4] = 1 * 4 * 5 = 20
Total = 18 + 0 + 20 = 38

m[1][4] = min(74, 81, 38) = 38  (split at k=3 is optimal!)
```

### Answer

$$m[1][4] = 38$$

Optimal parenthesization: $((A_1 \times A_2 \times A_3) \times A_4)$

---

## Part 11: Why Pure Recursion Fails

### Time Complexity Analysis

The recursion tree has **exponential depth and breadth**.

**Why?**

Each call to `matrixChainCost(i, j)` branches into:
- `matrixChainCost(i, i+1)`, `matrixChainCost(i+2, j)`
- `matrixChainCost(i, i+2)`, `matrixChainCost(i+3, j)`
- ... and so on

This creates roughly $O(4^n / n^{3/2})$ subproblems (even worse than $O(2^n)$).

### The Problem

```
For n = 10:  ~30 million recursive calls
For n = 15:  ~billions of recursive calls
For n = 20:  doesn't finish in reasonable time

This is why pure recursion is impractical.
```

### The Visualization

```
                                  m(1,4)
                    ┌──────────┬─────┴──────┬──────────┐
                    │          │            │          │
                m(1,1)    m(2,4)       ...  m(1,3)
         (base)      │         └──────┬──────┴──────┐
                     │               │             │
                    m(2,2)      m(3,4)      ...  m(4,4)
              (base)  (base)                   (base)

Many subproblems repeat:
  • m(2,3) computed multiple times
  • m(3,4) computed multiple times
  • etc.
```

---

## Part 12: The Gateway Insight

### What This Recursion Shows You

A **perfect example of why DP is necessary:**

```
✅ Problem has optimal substructure
   (optimal solution uses optimal subproblems)

✅ Problem has overlapping subproblems
   (same subproblems computed many times)

✓ Pure recursion = exponential time
   (infeasible for moderate n)

✓ But... we can see every possible subproblem
   (only O(n²) distinct subproblems!)

💡 Solution: CACHE the results!
   Either memoization (top-down) or
   Tabulation (bottom-up)
```

This is **exactly** when you need DP, and **why** it works.

---

## Part 13: The Pattern (Appears Everywhere)

### Recognition Check

**When you see a problem asking:**

```
✓ "Find the minimum (or maximum) cost"
✓ "By considering all ways to split/partition"
✓ "Combining results from subproblems"

→ Think Matrix Chain Multiplication
→ Think: optimal substructure + split pattern
→ Think: DP solution with recurrence
   state = m[i][j]
   answer = min over k of (m[i][k] + m[k+1][j] + cost)
```

### Problems With Same Pattern

| Problem | State | Recurrence |
|---------|-------|-----------|
| **Matrix Chain Multiplication** | m[i][j] = min cost i to j | split at k, merge cost = d[i-1]×d[k]×d[j] |
| **Optimal Binary Search Tree** | e[i][j] = min cost i to j | split at k, merge cost = weight[i..j] |
| **Polygon Triangulation** | m[i][j] = min cost to triangulate edge i to j | split at k, merge cost = dp[i][k] + dp[k][j] + triangle_area |
| **Longest Palindromic Subsequence** | m[i][j] = LPS length i to j | if equal, extend inner; else split |

**The mental model is the same:**
```
1. Define m[i][j]
2. Base case: m[i][i]
3. Recurrence: split at k, solve both sides, merge
4. Return min (or max) over all k
```

---

## Part 14: What Abdul Bari Teaches (Deep Level)

### The Four Pillars of DP Problem Solving

After Matrix Chain Multiplication, you should understand:

**1️⃣ State Definition**
```
How do we characterize a subproblem?
For MCM: range [i, j]
State must encode exactly what we're solving.
```

**2️⃣ Base Cases**
```
When does recursion stop?
For MCM: i == j (single matrix)
Without base case, recursion never stops.
```

**3️⃣ Recurrence Relation**
```
How do we express larger problems using smaller ones?
For MCM: try all k, take min
The transition equation is the heart of DP.
```

**4️⃣ Table Filling Order**
```
In what order must we compute subproblems?
For MCM (bottom-up):
  First: length=1 (m[i][i])
  Then:  length=2 (m[i][i+1])
  Then:  length=3 (m[i][i+2])
  ...
  Finally: length=n (m[1][n])

This order ensures dependencies are met.
```

---

## Part 15: Summary for Exams

### One-Liner Definitions

**Problem:**
```
"Find minimum cost to parenthesize matrix chain multiplication"
```

**State:**
```
m[i][j] = minimum scalar multiplications to compute A_i × ... × A_j
```

**Base Case:**
```
m[i][i] = 0
```

**Recurrence:**
```
m[i][j] = min(m[i][k] + m[k+1][j] + d[i-1]×d[k]×d[j]) for k=i to j-1
```

**Time Complexity (Recursion):**
```
Ω(4^n / n^1.5)  [worse than 2^n, exponential]
```

**Why It Works:**
```
Optimal substructure: optimal solution uses optimal subproblems
Overlapping subproblems: same subproblems appear many times
These two properties are exactly when DP is applicable.
```

---

## Part 16: The Real Takeaway

### What Abdul Bari Wants You To Remember

Not the formula. Not matrix multiplication.

**But this pattern:**

> *Whenever you need to find the optimal way to split a problem into parts, solve the parts, and combine them—**you're looking at a DP problem.** Define your state clearly. Express the recurrence with split point k. Recognize the overlaps. Use DP instead of pure recursion.*

This understanding applies across dozens of problems.

**Master this once. Use it forever.**

---

**Next: Memoization version (top-down DP) and Tabulation version (bottom-up DP).**

The recursion foundation is now solid.
