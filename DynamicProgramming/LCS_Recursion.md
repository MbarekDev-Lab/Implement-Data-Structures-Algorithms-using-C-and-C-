# Longest Common Subsequence (LCS) — Recursion Approach

## Part 1: Understanding Subsequences vs Substrings

### What is a Subsequence?

A **subsequence** is a sequence that appears within a string **in order**, but **not necessarily contiguous**.

#### Key Difference:
- **Substring:** Must be contiguous characters
- **Subsequence:** Characters can be separated

#### Examples:

```
Original String: "ABCBDAB"

Valid Subsequences:
  "A"
  "ABC" 
  "ABD"
  "ACB"
  "BDAB" ← order preserved, but not contiguous
  "BCBA" ← order preserved, but not contiguous
  "ABCBD"
  "BCDB"
  
NOT valid subsequences:
  "CAB" ← order not preserved in original
  "ABX" ← X not in original
```

### The Core Insight

For subsequences:
- We care about **relative order** (not adjacency)
- We can "skip" characters by not including them
- Multiple valid subsequences exist for any string

---

## Part 2: What is Longest Common Subsequence?

### Definition

The **Longest Common Subsequence (LCS)** of two strings is:
> The longest sequence of characters that appears in **both** strings, **in the same order**, but **not necessarily contiguous**.

### Real Example (From Abdul Bari)

```
String X = "ABCBDAB"
String Y = "BDCABA"

Common subsequences:
  "B"     (length 1)
  "BA"    (length 2)
  "BDA"   (length 3)
  "BDAB"  (length 4) ✓ longest
  "BCBA"  (length 4) ✓ also longest
  "BCAB"  (length 4) ✓ also longest

LCS LENGTH = 4
```

### Why This Matters

LCS is fundamental in:
- **Version control** (diff algorithms)
- **Bioinformatics** (DNA sequence alignment)
- **Plagiarism detection** (text similarity)
- **Edit distance calculations**

---

## Part 3: The Recursive Formula (Part 1)

### Problem Definition

Given:
- String X of length m: $X = x_1 x_2 \ldots x_m$
- String Y of length n: $Y = y_1 y_2 \ldots y_n$

Define:
$$L(i, j) = \text{LCS length of first } i \text{ characters of X and first } j \text{ characters of Y}$$

### Base Cases

When either string is empty, LCS length is 0:

$$L(i, 0) = 0 \quad \forall i$$
$$L(0, j) = 0 \quad \forall j$$

**Why?** If one string has no characters, there's nothing common.

---

## Part 4: The Recursive Formula (Part 2 — Core Cases)

### Case 1️⃣: Last Characters Match

**Condition:** $X[i-1] == Y[j-1]$

**Recurrence:**
$$L(i, j) = 1 + L(i-1, j-1)$$

**Intuition:**
```
If X = "ABCBD" and Y = "BDAB"
                  D                    B
         ↑                      ↑
      Last of X             Last of Y

They match! 

So: LCS("ABCBD", "BDAB") = 1 + LCS("ABCB", "BDA")
    
    The matching D

    MUST be in the LCS

    So we include it (add 1)

    And reduce to subproblem without last char
```

### Case 2️⃣: Last Characters Don't Match

**Condition:** $X[i-1] \neq Y[j-1]$

**Recurrence:**
$$L(i, j) = \max(L(i-1, j), L(i, n-1))$$

**Intuition:**
```
If X = "ABCBX" and Y = "BDABY"
                X                   Y
         ↑                      ↑
      Last of X             Last of Y

They DON'T match!

We have two choices:

Option 1: Ignore last char of X
          LCS("ABCB", "BDABY")

Option 2: Ignore last char of Y
          LCS("ABCBX", "BDAB")

Take whichever gives longer result
```

---

## Part 5: Complete Recursive Formula

$$L(i, j) = \begin{cases}
0 & \text{if } i = 0 \text{ or } j = 0 \\
1 + L(i-1, j-1) & \text{if } X[i-1] = Y[j-1] \\
\max(L(i-1, j), L(i, j-1)) & \text{otherwise}
\end{cases}$$

### Symbol Breakdown

| Symbol | Meaning |
|--------|---------|
| $L(i,j)$ | LCS length of first $i$ chars of X, first $j$ chars of Y |
| $X[i-1]$ | Character at index $i-1$ in string X (0-indexed) |
| $Y[j-1]$ | Character at index $j-1$ in string Y (0-indexed) |
| $m$ | Length of string X |
| $n$ | Length of string Y |
| Answer: | $L(m, n)$ — full LCS length |

---

## Part 6: Worked Example (Manual Trace)

### Example: X = "ABCBDAB", Y = "BDCABA"

Let me trace through the recursion manually:

```
Call Tree Structure (PARTIAL — showing key branches):

                L(7, 6)
                   |
         ___________+___________
        |                       |
    L(6,6)                   L(7,5)
    (B≠A)                    (B≠A)
      |                         |
  _____+_____                ____+____
 |           |              |        |
L(5,6)      L(6,5)      L(6,5)     L(7,4)

Note: L(6,5) appears in MULTIPLE branches
      This is OVERLAPPING SUBPROBLEMS
```

### Key Observations

1. **Same subproblems computed multiple times**
   - L(5,5) needed in multiple paths
   - L(4,4) needed in multiple paths
   - Creates exponential explosion

2. **Base cases are reached** (i=0 or j=0)
   - Returns 0
   - Base of recursion tree

3. **Result:** L(7,6) = 4 (the answer)

### Manual Verification for Small Example

```
X = "ABD"
Y = "BD"

Step 1: Compare X[2]='D' and Y[1]='D' → MATCH!
        L(3,2) = 1 + L(2,1)

Step 2: Compare X[1]='B' and Y[0]='B' → MATCH!
        L(2,1) = 1 + L(1,0)

Step 3: L(1,0) = 0 (Y is exhausted)

Result: L(3,2) = 1 + (1 + 0) = 2
        LCS = "BD"
```

---

## Part 7: Optimal Substructure

### Proof

**Theorem:** LCS exhibits optimal substructure.

**Proof:**

Suppose $L(m, n)$ is the LCS of X and Y. 

**Case A: If $X[m] = Y[n]$**
- The LCS must end with this character
- Remove this character from both strings
- Remaining LCS of X[1..m-1] and Y[1..n-1] must be optimal
- Otherwise, we could construct a better LCS for original strings (contradiction)

**Case B: If $X[m] \neq Y[n]$**
- LCS doesn't use both characters
- At least one character is not in LCS
- LCS is one of:
  - Optimal LCS of X[1..m-1] and Y[1..n]
  - Optimal LCS of X[1..m] and Y[1..n-1]
- If either subproblem had a better LCS, we could get better solution for original (contradiction)

**Conclusion:** Optimal solutions built from optimal subproblem solutions ✓

---

## Part 8: Overlapping Subproblems

### The Problem

When we call $L(i, j)$ recursively:

```
From L(i, j), we make calls:
  • L(i-1, j-1)
  • L(i-1, j)
  • L(i, j-1)

Each of these calls branches further:
  • L(i-1, j) calls L(i-2, j-1), L(i-2, j), L(i-1, j-1)
  • L(i, j-1) calls L(i-1, j-2), L(i-1, j-1), L(i, j-2)
              
Notice: L(i-1, j-1) is in BOTH branches!
```

### Visual Example: X = "ABC", Y = "DEF"

```
L(3,3) needs:
├─ L(2,3)  — ignore C
└─ L(3,2)  — ignore F

L(2,3) needs:
├─ L(1,3)
└─ L(2,2)  ← ALSO needed from L(3,2)!

L(3,2) needs:
├─ L(2,2)  ← HERE AGAIN
└─ L(3,1)
```

### Exponential Explosion

Without memoization:
```
L(n, n) has approximately 2^(2n) subproblems to compute
But only n² distinct subproblems exist!

This redundancy creates exponential time complexity: O(2^n)
```

### The Insight

This is a classic sign that **Dynamic Programming is the solution**.

---

## Part 9: Pure Recursion Implementation

### C Implementation Structure

```c
#include <stdio.h>
#include <string.h>

#define MAX_LCS 100

// Global counter for tracking recursive calls
long long call_count = 0;

// Pure recursion
int lcs_recursive(char *X, char *Y, int m, int n) {
    call_count++;
    
    // Base cases
    if (m == 0 || n == 0)
        return 0;
    
    // Characters match
    if (X[m-1] == Y[n-1])
        return 1 + lcs_recursive(X, Y, m-1, n-1);
    
    // Characters don't match — try both options
    return max(
        lcs_recursive(X, Y, m-1, n),     // Ignore last of X
        lcs_recursive(X, Y, m, n-1)      // Ignore last of Y
    );
}
```

### Algorithm Explanation

1. **Base case (m=0 or n=0):** Return 0
2. **Match (X[m-1]==Y[n-1]):** Include character, reduce both
3. **No match:** Take max of two choices (shrink X or shrink Y)
4. **Count calls:** Track how many times function executes

---

## Part 10: Complexity Analysis (Recursion)

### Time Complexity: Exponential

**Analysis:**

At each step (when characters don't match), we branch into 2 recursive calls:
$$T(m, n) = T(m-1, n) + T(m, n-1) + O(1)$$

This recurrence yields:
$$T(m, n) = O\left(\binom{m+n}{m}\right) \approx O(2^{m+n})$$

For equal lengths (m = n = k):
$$T(k, k) = O(2^{2k}) = O(4^k)$$

### Space Complexity: Linear

Recursion depth = m + n (at deepest path)
$$S(m, n) = O(m + n)$$

### Growth Comparison

```
String lengths (m=n=k):

k=5:  ~2^10 = 1,024 calls
k=6:  ~2^12 = 4,096 calls
k=7:  ~2^14 = 16,384 calls
k=8:  ~2^16 = 65,536 calls
k=9:  ~2^18 = 262,144 calls
k=10: ~2^20 = 1,048,576 calls

Beyond k=10: INFEASIBLE (too slow)
```

---

## Part 11: Why Recursion Fails

### The Reality

```
Pure recursion is IMPRACTICAL for LCS because:

1. EXPONENTIAL EXPLOSION
   ✗ O(2^(m+n)) is worse than even MCM's O(4^n/n^1.5)
   ✗ 100-character strings? → 2^200 operations (impossible)

2. OVERLAPPING SUBPROBLEMS
   ✗ Same L(i,j) computed thousands of times
   ✗ No caching, no memory of previous calculations
   ✗ Pure waste of computation

3. MODERN EXAMPLE
   ✗ Genome sequencing: strings with thousands of characters
   ✗ Version control: comparing files with thousands of lines
   ✗ Pure recursion would take billions of years
```

### The Lesson

This is **exactly** why Dynamic Programming exists:

Transform exponential recursion → polynomial DP with memoization or tabulation

---

## Part 12: The Gateway Insight

### What Abdul Bari Really Wants You to See

LCS teaches you:

1. **How to identify DP problems:**
   - ✓ Optimal substructure? (Yes — remove matching char or try both)
   - ✓ Overlapping subproblems? (Yes — exponential redundancy)
   - ✓ Can we memoize? (Yes — only n² distinct subproblems)
   - **Conclusion:** THIS IS A DP PROBLEM

2. **The transformation process:**
   - Start with recursive formula
   - Recognize overlapping subproblems
   - Add memoization (top-down DP)
   - OR convert to tabulation (bottom-up DP)

3. **Why the formula matters:**
   - The formula IS the algorithm
   - Just execute it efficiently (store results)
   - Don't compute same subproblem twice

4. **Pattern recognition across problems:**
   - Knapsack: 1D choices → 2D table
   - MCM: Interval DP with merge cost
   - LCS: String comparison → diagonal matches
   - **All follow the same principle:** Convert recursion → DP table

---

## Part 13: Universal DP Pattern

### The Framework (Applies to All DP Problems)

```
STEP 1: Understand the Problem
  → What are we trying to optimize/find?
  → What are the choices/decisions?

STEP 2: Define State
  → What parameters define a subproblem?
  → For LCS: L(i,j) — position in both strings

STEP 3: Write Recurrence
  → What's the formula for combining subproblems?
  → For LCS: Match → 1+L(i-1,j-1), NoMatch → max(...)

STEP 4: Identify DP Opportunity
  → Does it have overlapping subproblems?
  → How many distinct subproblems? (For LCS: m×n)

STEP 5: Convert to DP
  → Memoization (top-down): Add cache to recursion
  → Tabulation (bottom-up): Build matrix iteratively

STEP 6: Extract Answer
  → Where in the table/memoization is the final answer?
  → For LCS: L[m][n]

STEP 7 (Optional): Reconstruct Solution
  → If needed, trace back through table
  → For LCS: Backtrack to find actual subsequence
```

### LCS Mapped to Framework

| Step | LCS Instance |
|------|--------------|
| 1. Problem | Find longest common sequence (order preserved) |
| 2. State | L(i,j) — first i chars of X, first j chars of Y |
| 3. Recurrence | Match: 1+L(i-1,j-1), NoMatch: max(L(i-1,j), L(i,j-1)) |
| 4. DP Check | Yes! O(2^(m+n)) → O(m×n) |
| 5. Solution | Tabulation: Build (m+1)×(n+1) matrix |
| 6. Answer | L[m][n] |
| 7. Reconstruction | Backtrack from L[m][n] using comparison logic |

---

## Part 14: Interview & Exam Insights

### Recursion Lecture Takeaways

**For Interviews:**

1. **Can you explain the recursion?"** 
   - Lead with the formula
   - Explain match vs no-match cases
   - Draw recursion tree to show overlapping

2. **Why is recursion slow?**
   - "Same subproblems computed multiple times"
   - "L(i,j) appears in multiple branches"
   - "Exponential 2^(m+n) complexity"

3. **Can you code it?**
   - Write clean recursive function
   - Use memoization for optimization
   - Show call counting for analysis

**For Exams:**

- Be ready to compute L(m,n) by hand for small inputs
- Explain why recursion fails
- Know the recurrence formula by heart
- Understand optimal substructure proof

---

## Part 15: Common Pitfalls

### Mistake 1: Confusing Subsequence with Substring

```
WRONG: "AB" is not a subsequence of "AXB"
       (need to skip characters, and we do skip X — so it IS)

CORRECT: We can skip characters as long as order is preserved
         "AB" IS a subsequence of "AXB"
```

### Mistake 2: Greedy Approach

```
WRONG: Always pick first matching character
       X = "ABCD", Y = "DBCA"
       Pick D (first match) — leads to suboptimal solution

CORRECT: Try both options (ignore X char or ignore Y char)
         That's why recursion branches into 2 cases
         Greedy fails — need DP
```

### Mistake 3: Wrong Recurrence Cases

```
WRONG: Only handle matching characters
       if (X[m] == Y[n]) return 1 + L(m-1, n-1);
       else return L(m-1, n);  ← INCOMPLETE!

CORRECT: Handle both non-match options
         if (X[m] == Y[n]) return 1 + L(m-1, n-1);
         else return max(L(m-1,n), L(m,n-1));  ← BOTH BRANCHES
```

---

## Part 16: Complete Understanding Summary

### What You Now Know (Recursion Phase)

✓ **Subsequence concept:** Order matters, contiguity doesn't  
✓ **LCS definition:** Longest common sequence in both strings  
✓ **Recursive formula:** 3 cases (empty, match, no-match)  
✓ **Why recursion fails:** Exponential O(2^(m+n)) with overlapping subproblems  
✓ **Optimal substructure:** Remove matching char or try both options  
✓ **DP opportunity:** Only m×n distinct subproblems exist  
✓ **Universal pattern:** Same framework applies to all DP problems  

### Next Phase: Tabulation

In the **Tabulation guide**, we'll:

1. Convert the recursive formula to a **bottom-up matrix**
2. Show **filling order** (typically row-by-row)
3. Prove **optimality** of the DP solution
4. Implement **reconstruction** (find actual LCS, not just length)
5. Achieve **O(m×n) time and space** (polynomial vs exponential)
6. Show how **LCS is foundational** for:
   - Edit distance (Levenshtein distance)
   - DNA sequence alignment
   - Diff algorithms in version control
   - String similarity measures

---

## 🎯 Key Takeaway

> **LCS is one of the most important DP problems because it teaches you that overlapping subproblems + optimal substructure = DP opportunity. The recursion shows WHY it's hard. Tabulation shows HOW to solve it efficiently.**

---

## Exam Quick Reference

| Aspect | Details |
|--------|---------|
| **Problem** | Find longest sequence common to both strings (order preserved) |
| **State Definition** | L(i,j) = LCS length for first i chars of X, first j of Y |
| **Recurrence** | L(i,j)=0 if i=0∨j=0; 1+L(i-1,j-1) if X[i-1]=Y[j-1]; max(L(i-1,j), L(i,j-1)) else |
| **Recurrence Proof** | Optimal substructure: remove matching char or try both branches |
| **Time (Recursion)** | O(2^(m+n)) — exponential, infeasible |
| **Space (Recursion)** | O(m+n) — call stack depth |
| **DP Opportunity** | Only m×n distinct subproblems; overlapping subproblems evident |
| **Next Step** | Convert to tabulation for O(m×n) time solution |
