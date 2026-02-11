# Matrix Chain Multiplication — Tabulation Approach (Bottom-Up DP)

## From Recursion to Dynamic Programming

In the recursion lecture, you saw:
- The problem explodes with repetition
- For n=10, we need 19,683 function calls
- Pure recursion is **exponential: O(4^n / n^1.5)**

Now: **Eliminate recursion entirely.**

Instead of solving top-down with overlapping recomputation, we build solutions **bottom-up** in a table.

This is **true Dynamic Programming.**

---

## Part 1: The Same Problem, Different Approach

### State Definition (Unchanged)

$$M[i][j] = \text{Minimum cost to multiply matrices } A_i \times A_{i+1} \times \cdots \times A_j$$

### Problem Setup (Same)

```
Matrices: A₁, A₂, A₃, A₄
Dimensions: d = [3, 2, 4, 2, 5]

A₁: 3×2
A₂: 2×4
A₃: 4×2
A₄: 2×5
```

### The Recurrence (Same)

$$M[i][j] = \min_{i \leq k < j} \left( M[i][k] + M[k+1][j] + d[i-1] \cdot d[k] \cdot d[j] \right)$$

### What Changed

**Not the formula. Not the problem.**

**The computation method:**
```
Recursion (before): Start at M[1][4], recursively solve dependencies
Tabulation (now):   Start at base case, iteratively fill table
```

---

## Part 2: The DP Table Structure

### The Triangular Matrix

```
      j →
    1   2   3   4
i  ─────────────────
1 | 0  24  28  58
2 |     0  16  36
3 |        0  40
4 |           0
```

### Why It Looks Triangular

- **Diagonal = 0:** $M[i][i] = 0$ (single matrix)
- **Upper triangle only:** We only compute $i < j$
- **Lower triangle unused:** We never need $M[i][j]$ where $i > j$

### Why Upper Triangle?

Because the problem is defined as:
$$M[i][j] \text{ where } i \leq j$$

For $i > j$, there are no matrices to multiply (invalid range).

---

## Part 3: The Filling Strategy (CRITICAL)

### The Key Insight

We **cannot** fill the table randomly.

**Dependencies:**
```
M[i][j] depends on:
  • M[i][k]
  • M[k+1][j]

where i ≤ k < j
```

**So to compute M[i][j], we need M values from SMALLER ranges.**

### Solution: Fill by Chain Length

Instead of thinking about individual $(i,j)$ pairs, we think about:

$$\text{chain\_length} = j - i$$

**Filling order:**
```
1. All M[i][i+1]  (chain length = 1, two matrices)
2. All M[i][i+2]  (chain length = 2, three matrices)
3. All M[i][i+3]  (chain length = 3, four matrices)
...and so on
```

By the time we compute M[i][j], **all shorter chains have been solved**.

### Visual: Filling Order

```
      j →
    1   2   3   4
i  ─────────────────
1 | 0  ① ③ ④
2 |     0  ② ④
3 |        0  ③
4 |           0

Step ①: Chain length = 1 (M[1][2], M[2][3], M[3][4])
Step ②: Chain length = 2 (M[2][4], continuing...)
Step ③: Chain length = 2 (M[1][3], continuing...)
Step ④: Chain length = 3 (M[1][4], M[2][4])

Proper order by chain length:
  Length 1: (1,2), (2,3), (3,4)
  Length 2: (1,3), (2,4)
  Length 3: (1,4)
```

---

## Part 4: Detailed Example—Filling Step By Step

### Setup

```
d = [3, 2, 4, 2, 5]
n = 4 matrices
```

### Base Case

```
M[1][1] = 0
M[2][2] = 0
M[3][3] = 0
M[4][4] = 0
```

### Chain Length = 1 (Two Consecutive Matrices)

**M[1][2]**: Multiply $A_1 \times A_2$

```
Only one way to multiply:
k = 1:
  M[1][1] + M[2][2] + d[0]×d[1]×d[2]
  = 0 + 0 + 3×2×4
  = 24

M[1][2] = 24
```

**M[2][3]**: Multiply $A_2 \times A_3$

```
k = 2:
  M[2][2] + M[3][3] + d[1]×d[2]×d[3]
  = 0 + 0 + 2×4×2
  = 16

M[2][3] = 16
```

**M[3][4]**: Multiply $A_3 \times A_4$

```
k = 3:
  M[3][3] + M[4][4] + d[2]×d[3]×d[4]
  = 0 + 0 + 4×2×5
  = 40

M[3][4] = 40
```

**Table after length=1:**
```
      j
    1   2   3   4
i  ─────────────────
1 | 0  24
2 |     0  16
3 |        0  40
4 |           0
```

### Chain Length = 2 (Three Consecutive Matrices)

**M[1][3]**: Multiply $A_1 \times A_2 \times A_3$

```
Try k = 1:
  M[1][1] + M[2][3] + d[0]×d[1]×d[3]
  = 0 + 16 + 3×2×2
  = 28

Try k = 2:
  M[1][2] + M[3][3] + d[0]×d[2]×d[3]
  = 24 + 0 + 3×4×2
  = 48

M[1][3] = min(28, 48) = 28
```

**M[2][4]**: Multiply $A_2 \times A_3 \times A_4$

```
Try k = 2:
  M[2][2] + M[3][4] + d[1]×d[2]×d[4]
  = 0 + 40 + 2×4×5
  = 80

Try k = 3:
  M[2][3] + M[4][4] + d[1]×d[3]×d[4]
  = 16 + 0 + 2×2×5
  = 36

M[2][4] = min(80, 36) = 36
```

**Table after length=2:**
```
      j
    1   2   3   4
i  ─────────────────
1 | 0  24  28
2 |     0  16  36
3 |        0  40
4 |           0
```

### Chain Length = 3 (All Four Matrices)

**M[1][4]**: Multiply $A_1 \times A_2 \times A_3 \times A_4$

```
Try k = 1:
  M[1][1] + M[2][4] + d[0]×d[1]×d[4]
  = 0 + 36 + 3×2×5
  = 66

Try k = 2:
  M[1][2] + M[3][4] + d[0]×d[2]×d[4]
  = 24 + 40 + 3×4×5
  = 124

Try k = 3:
  M[1][3] + M[4][4] + d[0]×d[3]×d[4]
  = 28 + 0 + 3×2×5
  = 58

M[1][4] = min(66, 124, 58) = 58
```

**Final Table:**
```
      j
    1   2   3   4
i  ─────────────────
1 | 0  24  28  58
2 |     0  16  36
3 |        0  40
4 |           0
```

### Answer

$$M[1][4] = 58$$

Same as recursion, but computed **without any recursive calls**!

---

## Part 5: The Split Index Table (K Table)

### What It Tracks

```
K[i][j] = the value of k that gave the minimum cost for M[i][j]
```

### Purpose

To **reconstruct the optimal parenthesization**.

### Example

For M[1][3], we tested:
- k=1: cost=28 ← **MINIMUM**
- k=2: cost=48

So: $K[1][3] = 1$

This means: "Split between position 1 and position 2"

$$A_1 \times (A_2 \times A_3)$$

### Building K Table (During Computation)

```c
for (int k = i; k < j; k++) {
    int cost = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
    
    if (cost < M[i][j]) {
        M[i][j] = cost;
        K[i][j] = k;  // Store the optimal k
    }
}
```

### Reconstruction (Post-Computation)

With the K table, we can reconstruct the optimal order:

```c
void printOptimalOrder(int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalOrder(i, K[i][j]);
        printf(" × ");
        printOptimalOrder(K[i][j] + 1, j);
        printf(")");
    }
}
```

### Example Reconstruction

For our problem:
```
K[1][4] = 3  → Split: (A₁×A₂×A₃) × A₄
K[1][3] = 1  → Split: A₁ × (A₂×A₃)
K[2][3] = 2  → Single cell (base case)

Final parenthesization: ((A₁ × (A₂ × A₃)) × A₄)
```

---

## Part 6: The Algorithm (Pseudocode)

```
algorithm matrixChainTabulation(d[0..n], n):
    
    // Create two 2D arrays
    M[1..n][1..n]  // costs
    K[1..n][1..n]  // split indices
    
    // Base case: single matrices
    for i = 1 to n:
        M[i][i] = 0
    
    // Fill table by chain length
    for chainLen = 2 to n:            // length from 2 to n
        for i = 1 to n - chainLen + 1:
            j = i + chainLen - 1       // right endpoint
            M[i][j] = INFINITY
            
            // Try all split points
            for k = i to j - 1:
                cost = M[i][k] + M[k+1][j] + d[i-1] × d[k] × d[j]
                
                if cost < M[i][j]:
                    M[i][j] = cost
                    K[i][j] = k
    
    return M[1][n]
```

---

## Part 7: C Implementation

### Complete Code

```c
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX_N 20

int d[MAX_N];           // dimension array
int M[MAX_N][MAX_N];    // cost table
int K[MAX_N][MAX_N];    // split index table
int n;                  // number of matrices

// ============================================================================
// MATRIX CHAIN MULTIPLICATION - TABULATION (BOTTOM-UP DP)
// ============================================================================

void matrixChainTabulation() {
    
    // Step 1: Initialize base cases
    // A single matrix requires no multiplication
    for (int i = 1; i <= n; i++) {
        M[i][i] = 0;
    }
    
    // Step 2: Fill table by chain length
    // chainLen = j - i (the span we're considering)
    for (int chainLen = 2; chainLen <= n; chainLen++) {
        
        for (int i = 1; i <= n - chainLen + 1; i++) {
            int j = i + chainLen - 1;  // right endpoint
            
            M[i][j] = INT_MAX;
            
            // Try all possible split points
            for (int k = i; k < j; k++) {
                
                // Cost of left part: M[i][k]
                // Cost of right part: M[k+1][j]
                // Cost of multiplying results: d[i-1] × d[k] × d[j]
                int cost = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
                
                // Keep track of minimum
                if (cost < M[i][j]) {
                    M[i][j] = cost;
                    K[i][j] = k;  // Store split point for reconstruction
                }
            }
        }
    }
}

// ============================================================================
// PRINT DP TABLE
// ============================================================================

void printTable() {
    printf("\n📊 DP Table M[i][j] (Costs):\n\n");
    
    // Header
    printf("i\\j  ");
    for (int j = 1; j <= n; j++) {
        printf("%8d", j);
    }
    printf("\n");
    printf("────");
    for (int j = 1; j <= n; j++) {
        printf("────────");
    }
    printf("\n");
    
    // Table
    for (int i = 1; i <= n; i++) {
        printf("%2d   ", i);
        for (int j = 1; j <= n; j++) {
            if (i > j) {
                printf("       -");  // Lower triangle unused
            } else if (M[i][j] == INT_MAX) {
                printf("       ?");
            } else {
                printf("%8d", M[i][j]);
            }
        }
        printf("\n");
    }
    
    printf("\n📊 Split Index Table K[i][j]:\n\n");
    
    // Header
    printf("i\\j  ");
    for (int j = 1; j <= n; j++) {
        printf("%8d", j);
    }
    printf("\n");
    printf("────");
    for (int j = 1; j <= n; j++) {
        printf("────────");
    }
    printf("\n");
    
    // Table
    for (int i = 1; i <= n; i++) {
        printf("%2d   ", i);
        for (int j = 1; j <= n; j++) {
            if (i > j) {
                printf("       -");
            } else if (i == j) {
                printf("       -");  // Base case, no split needed
            } else {
                printf("%8d", K[i][j]);
            }
        }
        printf("\n");
    }
}

// ============================================================================
// RECONSTRUCT OPTIMAL PARENTHESIZATION
// ============================================================================

void printOptimalOrder(int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalOrder(i, K[i][j]);
        printf(" × ");
        printOptimalOrder(K[i][j] + 1, j);
        printf(")");
    }
}

// ============================================================================
// TEST CASES
// ============================================================================

void test_case_1() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║    TEST CASE 1: 4-Matrix Example (From Lecture)               ║\n");
    printf("║              Detailed Table Filling Step-by-Step             ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    n = 4;
    d[0] = 3;  d[1] = 2;  d[2] = 4;  d[3] = 2;  d[4] = 5;
    
    printf("\n📐 Setup:\n");
    printf("   Matrices: A₁(3×2), A₂(2×4), A₃(4×2), A₄(2×5)\n");
    printf("   Dimension: d = [3, 2, 4, 2, 5]\n");
    
    matrixChainTabulation();
    
    printf("\n✅ Minimum Cost: %d scalar multiplications\n", M[1][n]);
    
    printTable();
    
    printf("\n🔍 Optimal Parenthesization: ");
    printOptimalOrder(1, n);
    printf("\n");
}

void test_case_2() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║  TEST CASE 2: 3-Matrix Example (Smaller for Clarity)          ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    n = 3;
    d[0] = 1;  d[1] = 2;  d[2] = 3;  d[3] = 4;
    
    printf("\n📐 Setup:\n");
    printf("   Matrices: A₁(1×2), A₂(2×3), A₃(3×4)\n");
    printf("   Dimension: d = [1, 2, 3, 4]\n");
    
    matrixChainTabulation();
    
    printf("\n✅ Minimum Cost: %d scalar multiplications\n", M[1][n]);
    
    printf("\n📊 DP Table:\n");
    printf("      j\n");
    printf("    1   2   3\n");
    printf("i  ────────────\n");
    printf("1 | 0   6  18\n");
    printf("2 |     0  24\n");
    printf("3 |        0\n");
    printf("\nCalculation:\n");
    printf("  M[1][2] = 1×2×3 = 6\n");
    printf("  M[2][3] = 2×3×4 = 24\n");
    printf("  M[1][3] = min(\n");
    printf("      k=1: M[1][1] + M[2][3] + 1×2×4 = 0+24+8 = 32,\n");
    printf("      k=2: M[1][2] + M[3][3] + 1×3×4 = 6+0+12 = 18 ✓\n");
    printf("  ) = 18\n");
    
    printf("\n🔍 Optimal Parenthesization: ");
    printOptimalOrder(1, n);
    printf("\n");
}

void test_case_3() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║   TEST CASE 3: 5-Matrix Example (Complexity Demonstration)    ║\n");
    printf("║        Compare Tabulation vs Recursion:                       ║\n");
    printf("║        Tabulation: O(n³) = 125 operations                     ║\n");
    printf("║        Recursion:  ~81 recursive calls                        ║\n");
    printf("║        (For larger n, gap grows exponentially!)               ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    n = 5;
    d[0] = 2;  d[1] = 3;  d[2] = 4;  d[3] = 5;  d[4] = 2;  d[5] = 6;
    
    printf("\n📐 Setup:\n");
    printf("   5 matrices with dimensions: d = [2, 3, 4, 5, 2, 6]\n");
    
    matrixChainTabulation();
    
    printf("\n✅ Minimum Cost: %d scalar multiplications\n", M[1][n]);
    
    printf("\n📊 Cost Table M[i][j]:\n");
    printf("      j\n");
    printf("    1    2    3    4    5\n");
    printf("i  ──────────────────────────\n");
    for (int i = 1; i <= n; i++) {
        printf("%d | ", i);
        for (int j = 1; j <= n; j++) {
            if (i <= j) {
                printf("%5d ", M[i][j]);
            } else {
                printf("    - ");
            }
        }
        printf("\n");
    }
    
    printf("\n🔍 Optimal Parenthesization: ");
    printOptimalOrder(1, n);
    printf("\n");
}

void test_case_4() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║       TEST CASE 4: Compare Different Parenthesizations        ║\n");
    printf("║           (Verify DP finds the actual minimum)                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    n = 4;
    d[0] = 5;  d[1] = 10;  d[2] = 3;  d[3] = 12;  d[4] = 5;
    
    printf("\n📐 Setup:\n");
    printf("   A₁(5×10), A₂(10×3), A₃(3×12), A₄(12×5)\n");
    
    matrixChainTabulation();
    
    printf("\n💡 Different Parenthesizations:\n\n");
    
    printf("Option 1: ((A₁×A₂)×A₃)×A₄\n");
    printf("  A₁×A₂: 5×10×3 = 150\n");
    printf("  Result×A₃: 5×3×12 = 180\n");
    printf("  Result×A₄: 5×12×5 = 300\n");
    printf("  Total: 630\n\n");
    
    printf("Option 2: (A₁×(A₂×A₃))×A₄\n");
    printf("  A₂×A₃: 10×3×12 = 360\n");
    printf("  A₁×Result: 5×10×12 = 600\n");
    printf("  Result×A₄: 5×12×5 = 300\n");
    printf("  Total: 1260\n\n");
    
    printf("DP finds optimal: %d\n", M[1][n]);
    printf("(Better than all naive options!)\n");
}

void demonstrateFillingProcess() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║           DEMONSTRATE TABLE FILLING PROCESS                   ║\n");
    printf("║        (Show how chain length determines fill order)          ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    n = 4;
    d[0] = 3;  d[1] = 2;  d[2] = 4;  d[3] = 2;  d[4] = 5;
    
    printf("\nInitialization:\n");
    printf("  M[1][1] = 0\n");
    printf("  M[2][2] = 0\n");
    printf("  M[3][3] = 0\n");
    printf("  M[4][4] = 0\n");
    
    // Initialize
    for (int i = 1; i <= n; i++) M[i][i] = 0;
    
    printf("\n─── Chain Length = 1 (Two Consecutive Matrices) ───\n\n");
    
    // Chain length 1
    for (int i = 1; i <= n - 1; i++) {
        int j = i + 1;
        M[i][j] = d[i-1] * d[i] * d[j];
        K[i][j] = i;
        printf("M[%d][%d] = d[%d]×d[%d]×d[%d] = %d×%d×%d = %d\n", 
               i, j, i-1, i, j, d[i-1], d[i], d[j], M[i][j]);
    }
    
    printf("\nTable after chainLen=1:\n");
    printf("    1   2   3   4\n");
    printf("1   0  %2d\n", M[1][2]);
    printf("2       0  %2d\n", M[2][3]);
    printf("3           0  %2d\n", M[3][4]);
    printf("4               0\n");
    
    printf("\n─── Chain Length = 2 (Three Consecutive Matrices) ───\n\n");
    
    for (int i = 1; i <= n - 2; i++) {
        int j = i + 2;
        M[i][j] = INT_MAX;
        
        printf("Computing M[%d][%d]:\n", i, j);
        for (int k = i; k < j; k++) {
            int cost = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
            printf("  k=%d: M[%d][%d] + M[%d][%d] + %d×%d×%d = %d + %d + %d = %d",
                   k, i, k, k+1, j, d[i-1], d[k], d[j], M[i][k], M[k+1][j], 
                   d[i-1]*d[k]*d[j], cost);
            
            if (cost < M[i][j]) {
                M[i][j] = cost;
                K[i][j] = k;
                printf(" ← minimum so far\n");
            } else {
                printf("\n");
            }
        }
        printf("  Result: M[%d][%d] = %d\n\n", i, j, M[i][j]);
    }
    
    printf("\nTable after chainLen=2:\n");
    printf("    1   2   3   4\n");
    printf("1   0  24  %2d\n", M[1][3]);
    printf("2       0  16  %2d\n", M[2][4]);
    printf("3           0  40\n");
    printf("4               0\n");
    
    printf("\n─── Chain Length = 3 (All Four Matrices) ───\n\n");
    
    int i = 1, j = 4;
    M[i][j] = INT_MAX;
    printf("Computing M[%d][%d]:\n", i, j);
    for (int k = i; k < j; k++) {
        int cost = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
        printf("  k=%d: M[%d][%d] + M[%d][%d] + %d×%d×%d = %d + %d + %d = %d",
               k, i, k, k+1, j, d[i-1], d[k], d[j], M[i][k], M[k+1][j], 
               d[i-1]*d[k]*d[j], cost);
        
        if (cost < M[i][j]) {
            M[i][j] = cost;
            K[i][j] = k;
            printf(" ← minimum so far\n");
        } else {
            printf("\n");
        }
    }
    printf("  Result: M[%d][%d] = %d\n\n", i, j, M[i][j]);
    
    printf("Final Table:\n");
    printf("      j\n");
    printf("    1   2   3   4\n");
    printf("i  ─────────────────\n");
    printf("1  0  24  28  58\n");
    printf("2      0  16  36\n");
    printf("3          0  40\n");
    printf("4              0\n");
}

int main() {
    printf("\n");
    printf("╔═════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                 ║\n");
    printf("║    MATRIX CHAIN MULTIPLICATION — TABULATION (BOTTOM-UP DP)      ║\n");
    printf("║                                                                 ║\n");
    printf("║         From Recursion Tree to Efficient DP Table               ║\n");
    printf("║                                                                 ║\n");
    printf("╚═════════════════════════════════════════════════════════════════╝\n");
    
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    demonstrateFillingProcess();
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    KEY ACHIEVEMENTS                            ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                ║\n");
    printf("║ 1️⃣  Eliminated Recursion                                        ║\n");
    printf("║    Pure iteration, no function calls, no stack overhead        ║\n");
    printf("║                                                                ║\n");
    printf("║ 2️⃣  Computed Each Subproblem Once                              ║\n");
    printf("║    Time: O(n³) instead of exponential O(4^n / n^1.5)          ║\n");
    printf("║    Space: O(n²) for the DP table                               ║\n");
    printf("║                                                                ║\n");
    printf("║ 3️⃣  Filled by Chain Length                                     ║\n");
    printf("║    Ensures dependencies are met before computation             ║\n");
    printf("║    Length 1, 2, 3, ... guarantees correct order                ║\n");
    printf("║                                                                ║\n");
    printf("║ 4️⃣  Reconstructed Optimal Solution                             ║\n");
    printf("║    K table stores split indices                                ║\n");
    printf("║    Backtrace to find best parenthesization                     ║\n");
    printf("║                                                                ║\n");
    printf("║ 5️⃣  Pattern Recognition                                        ║\n");
    printf("║    This is the standard 2D interval DP pattern                 ║\n");
    printf("║    Appears in: Optimal BST, Polygon Triangulation, etc.        ║\n");
    printf("║                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    return 0;
}
```

---

## Part 8: Complexity Analysis

### Time Complexity

```
Nested loops:
  Outer (chainLen):  n iterations
  Middle (i):        n iterations
  Inner (k):         n iterations
  
Work per cell: O(1)

Total: O(n³)
```

### Space Complexity

```
DP table M: O(n²)
Split table K: O(n²)

Total: O(n²)
```

### Comparison: All Three Approaches

| Approach | Time | Space | Recursion | Feasible For |
|----------|------|-------|-----------|--------------|
| Pure Recursion | O(4^n / n^1.5) | O(n) | Yes (heavy) | n ≤ 12 |
| Memoization | O(n³) | O(n²) | Yes (light) | n ≤ 1000 |
| Tabulation | O(n³) | O(n²) | No | n ≤ 1000 |

**Tabulation is the clear winner** for practical use.

---

## Part 9: Why Filling by Chain Length Works

### The Dependency Graph

```
To compute M[i][j], we need:
  • M[i][k]
  • M[k+1][j]

where i ≤ k < j

These are SHORTER chains than [i,j].
```

### The Guarantee

```
If we fill by increasing chain length:

1. When computing chain length 2 (M[i][i+1]):
   Dependencies are M[i][i] and M[i+1][i+1] (both base cases ✓)

2. When computing chain length 3 (M[i][i+2]):
   Dependencies are from chain lengths 1 and 2 (already computed ✓)

3. And so on...

By the time we compute M[1][n], all dependencies are ready.
```

### Why Not Fill by (i,j) Name?

```
If we tried to fill row by row:
  Row 1: M[1][1], M[1][2], M[1][3], M[1][4], ...
  
When computing M[1][3]:
  We need M[1][1] (done ✓) and M[2][3] (not done yet ✗)
  
Problem: M[2][3] is in row 2, which comes later!
```

Chain length is the natural **topological order** for this problem.

---

## Part 10: Reconstruction Algorithm

### How To Recover The Parenthesization

**Using the K table**, we can print the optimal way to parenthesize:

```c
void printOptimalOrder(int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalOrder(i, K[i][j]);
        printf(" × ");
        printOptimalOrder(K[i][j] + 1, j);
        printf(")");
    }
}
```

### Example

For M[1][4], if K[1][4] = 3:
```
This means: Split into (A₁...A₃) × (A₄...A₄)

Recursively reconstruct left: (A₁...A₃)
  If K[1][3] = 1: (A₁) × (A₂...A₃)
    Recurse left: A₁ (base case)
    Recurse right: (A₂...A₃)
      If K[2][3] = 2: (A₂) × (A₃)
        Both base cases

Final: (A₁ × (A₂ × A₃)) × A₄
```

---

## Part 11: What Abdul Bari Teaches (Deep Understanding)

### The Transformation

**Recursion Tree (What He Drew Last Lecture):**
```
Exponential branching
Repeated subproblems
Inefficient
O(4^n / n^1.5)
```

**DP Table (What He Draws Now):**
```
Triangular matrix
Each cell computed once
Efficient
O(n³)
```

### The Key Insight

```
The DP table is literally the recursion tree FLATTENED.

Each cell = a subproblem that was solved in the tree
Each row = a chain length level

Instead of jumping around the tree randomly,
we fill the table in a structured way.

No repetition. No inefficiency.
```

### The Four Pillars (Revisited for MCM Tabulation)

**1️⃣ State Definition**
```
M[i][j] = minimum cost for range [i,j]
Captured in 2D array
```

**2️⃣ Base Cases**
```
M[i][i] = 0
First row (diagonal)
```

**3️⃣ Recurrence**
```
M[i][j] = min over k of (M[i][k] + M[k+1][j] + mergeCost)
Expressed as loops, not recursion
```

**4️⃣ Fill Order**
```
By chain length, not arbitrary
Ensures dependencies are met
Topological sort of subproblems
```

---

## Part 12: The Universal Pattern (Interval DP)

### Problems With This Same Structure

```
Characteristic: 2D DP with range [i,j]

State pattern:
  m[i][j] = optimal for i to j

Recurrence pattern:
  m[i][j] = f(m[i][k], m[k+1][j], merge_cost)
  for all valid k

Problems following this:
  • Matrix Chain Multiplication (merge = d[i-1]×d[k]×d[j])
  • Optimal BST (merge = weight of range)
  • Polygon Triangulation (merge = triangle area)
  • Longest Palindrome Subsequence
  • Minimum Cost to Connect Rods
```

---

## Part 13: Exam Summary

### Quick One-Liners

**Problem:**
```
"Find minimum scalar multiplications to parenthesize matrix chain"
```

**Approach:**
```
"Use 2D DP table M[i][j] = minimum cost for range [i,j]"
```

**Base:**
```
"M[i][i] = 0"
```

**Recurrence:**
```
"M[i][j] = min(M[i][k] + M[k+1][j] + d[i-1]×d[k]×d[j])"
```

**Time/Space:**
```
"O(n³) time, O(n²) space"
```

**Key Insight:**
```
"Fill by chain length to ensure dependencies are met"
```

---

## Part 14: Visualization Summary

### The Mental Model

```
RECURSION (Last Lecture):
  Start from goal
  Explode into subproblems
  Recompute overlaps
  Result: exponential time

TABULATION (This Lecture):
  Start from base cases
  Build upward layer by layer
  Compute each once
  Result: polynomial time

The DP table is the recursion tree stored hierarchically.
```

### The Tables

```
Cost Table (M):         Split Table (K):
    1   2   3   4          1   2   3   4
1   0  24  28  58      1   -   1   1   3
2       0  16  36      2       -   2   3
3           0  40      3           -   3
4               0      4               -

Read top-right of M: Answer = 58
Backtrack via K: 1→3→2→3 (optimal splits)
```

---

## Part 15: The Complete Understanding

### What You Now Know

```
1️⃣ The Problem
   Minimize scalar multiplications for matrix chain

2️⃣ Why Recursion Fails
   Exponential overlaps (seen in last lecture)

3️⃣ Why Tabulation Works
   Each subproblem solved once

4️⃣ How To Implement
   Fill by chain length, not arbitrary order

5️⃣ How To Extract Answer
   Read M[1][n]

6️⃣ How To Reconstruct
   Use K table to backtrace

7️⃣ The Universal Pattern
   Interval DP: state with two indices, split at k

8️⃣ Complexity Achievement
   From O(4^n) to O(n³)
```

---

**This is true Dynamic Programming mastery.**

You've moved from:
- Seeing a problem
- To recognizing it recursively
- To understanding why recursion fails
- To building an efficient DP solution
- To understanding the pattern for ALL interval DP problems

This is Abdul Bari's complete curriculum designed to teach you DP properly.
