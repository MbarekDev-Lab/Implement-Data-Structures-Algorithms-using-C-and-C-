# Maximum Subarray Sum (MSS) — Dynamic Programming Approach

> **Core Insight**: This lecture isn't about computing a sum. It's about transforming O(n²) brute force into O(n) DP by defining the right state and understanding how local decisions build global optimum.

---

## 📊 Part 1: The Problem Statement

**Maximum Subarray Sum (MSS) Problem:**

Given an array of integers (positive and negative):

```
A = [-2, -3, 4, -1, -2, 1, 5, -3]
```

**Goal:**

Find the **maximum sum of any contiguous subarray**.

**Contiguous Constraint:**

You **cannot skip elements**. You must take consecutive elements.

**Correct Answer:**

```
Subarray: [4, -1, -2, 1, 5]
Sum:      4 + (-1) + (-2) + 1 + 5 = 7
```

This is the **maximum possible sum** among all contiguous subarrays.

---

## 🔥 Part 2: The Brute Force Approach (Why It Fails)

**Brute Force Idea:**

```
FOR each starting index i:
  FOR each ending index j >= i:
    Compute sum of A[i...j]
    Update maximum
```

**Code Sketch:**

```c
int maxSum = INT_MIN;

for(int i = 0; i < n; i++) {
    int sum = 0;
    for(int j = i; j < n; j++) {
        sum += A[j];
        maxSum = max(maxSum, sum);
    }
}
```

**Time Complexity:**

$O(n^2)$

**The Critical Problem:**

We are recomputing sums again and again.

**Example:**

When computing sum [0...5], we already computed [0...4].

Then for subarray [1...5], we could use [0...5] minus A[0].

But we recompute from scratch.

**This is the signal for DP thinking!**

---

## 💡 Part 3: The State Definition (The Most Important Insight)

**The Brute Force Question:**

> "What is the maximum sum over **all possible subarrays**?"

**The DP Question (DIFFERENTLY DEFINED):**

> "What is the maximum sum **for subarrays ending exactly at position i**?"

**State Definition:**

$$\text{dp}[i] = \text{Maximum subarray sum that MUST end at index } i$$

**Why This Definition Is Everything:**

This seemingly small change **unlocks the entire solution**.

### Why This Works

**Without restriction:**
- "Maximum overall" is answered by finding max subarray anywhere.
- No recurrence relation possible.
- We must check all subarrays → O(n²).

**With restriction:**
- "Maximum ending at i" has a clear recurrence.
- Each state depends on **only the previous state**.
- We can compute all dp[i] in one pass → O(n).

**The Restriction Creates Opportunity.**

---

## 📐 Part 4: The Recurrence Relation

**Problem:**

If I want the best subarray ending at index i, what are my choices?

**Answer:**

You have **exactly two options:**

### Option 1: Start Fresh

Ignore everything before i.

Just take A[i] alone.

Sum = A[i]

### Option 2: Extend Previous

Extend the best subarray that ended at i-1.

Add A[i] to dp[i-1].

Sum = A[i] + dp[i-1]

**The Decision:**

Choose **whichever gives larger sum**.

### The Recurrence Formula

$$\text{dp}[i] = \max(\text{A}[i], \text{A}[i] + \text{dp}[i-1])$$

**What This Means:**

At each index, you decide: **Continue or Restart?**

---

## ✅ Part 5: Why This Recurrence Works

**Case 1: dp[i-1] is NEGATIVE**

If the previous subarray sum is negative:

$$\text{A}[i] + \text{dp}[i-1] < \text{A}[i]$$

**Logic:**

Adding a negative number makes the sum smaller.

So **restart fresh** is better.

**Decision:** Start new subarray.

**Case 2: dp[i-1] is POSITIVE**

If the previous subarray sum is positive:

$$\text{A}[i] + \text{dp}[i-1] > \text{A}[i]$$

**Logic:**

Adding a positive number makes the sum larger.

So **extending** is better.

**Decision:** Extend previous subarray.

**This is Optimal Substructure:**

The algorithm **automatically chooses the optimal decision** at each position.

---

## 🎯 Part 6: Base Case

**For index 0:**

Only one element exists.

$$\text{dp}[0] = \text{A}[0]$$

**Why:**

No previous subarray to extend.

So the best subarray ending at 0 is just A[0].

---

## 🔍 Part 7: The Final Answer

**Question:**

Do we want dp[n-1]?

**Answer:**

No! dp[n-1] is the best subarray ending at the last index.

But the best subarray overall might end **anywhere**.

**Solution:**

Scan all dp values and take the maximum:

$$\text{Answer} = \max(\text{dp}[0], \text{dp}[1], \ldots, \text{dp}[n-1])$$

**Why:**

The maximum subarray problem asks: "Maximum sum **anywhere**?"

But we computed: "Maximum sum ending at **each position**?"

So we must check all positions for the global answer.

---

## 🎬 Part 8: Full Example Walkthrough

**Array:**

```
A = [-2, -3, 4, -1, -2, 1, 5, -3]
     0   1  2  3   4  5 6   7
```

**Initialize:**

```
dp[0] = A[0] = -2
max_overall = -2  (best we've seen so far)
```

**i = 1:**

```
dp[1] = max(A[1], A[1] + dp[0])
      = max(-3, -3 + (-2))
      = max(-3, -5)
      = -3
      
max_overall = max(-2, -3) = -2

Interpretation: 
At index 1, best subarray ending here is [-3] alone (start fresh).
```

**i = 2:**

```
dp[2] = max(A[2], A[2] + dp[1])
      = max(4, 4 + (-3))
      = max(4, 1)
      = 4

max_overall = max(-2, 4) = 4

Interpretation:
At index 2, best subarray ending here is [4] alone (start fresh).
We ignore the negative prefix.
```

**i = 3:**

```
dp[3] = max(A[3], A[3] + dp[2])
      = max(-1, -1 + 4)
      = max(-1, 3)
      = 3

max_overall = max(4, 3) = 4

Interpretation:
At index 3, extend the [4] to [4, -1] = 3 (better than -1 alone).
```

**i = 4:**

```
dp[4] = max(A[4], A[4] + dp[3])
      = max(-2, -2 + 3)
      = max(-2, 1)
      = 1

max_overall = max(4, 1) = 4

Interpretation:
At index 4, extend [4, -1] to [4, -1, -2] = 1 (positive, so continue).
```

**i = 5:**

```
dp[5] = max(A[5], A[5] + dp[4])
      = max(1, 1 + 1)
      = max(1, 2)
      = 2

max_overall = max(4, 2) = 4

Interpretation:
At index 5, extend [4, -1, -2] to [4, -1, -2, 1] = 2 (still positive).
```

**i = 6:**

```
dp[6] = max(A[6], A[6] + dp[5])
      = max(5, 5 + 2)
      = max(5, 7)
      = 7

max_overall = max(4, 7) = 7  ← NEW MAXIMUM!

Interpretation:
At index 6, extend all the way to [4, -1, -2, 1, 5] = 7 (great!).
This is our maximum subarray sum!
```

**i = 7:**

```
dp[7] = max(A[7], A[7] + dp[6])
      = max(-3, -3 + 7)
      = max(-3, 4)
      = 4

max_overall = max(7, 4) = 7

Interpretation:
At index 7, extend to [4, -1, -2, 1, 5, -3] = 4 (worse than 7).
Best subarray still ends at index 6.
```

**Final Answer:**

$$\text{max\_overall} = 7$$

**Optimal Subarray:**

$$[4, -1, -2, 1, 5]$$

---

## 📊 Part 9: DP Table Visualization

**State Table:**

| i | A[i] | dp[i] | Decision | max_so_far |
|---|------|-------|----------|-----------|
| 0 | -2 | -2 | Start | -2 |
| 1 | -3 | -3 | Start | -2 |
| 2 | 4 | 4 | Start | **4** |
| 3 | -1 | 3 | Extend | 4 |
| 4 | -2 | 1 | Extend | 4 |
| 5 | 1 | 2 | Extend | 4 |
| 6 | 5 | 7 | Extend | **7** ← ANSWER |
| 7 | -3 | 4 | Extend | 7 |

**Pattern Observation:**

1. First few indices: Negative elements, all "Start fresh"
2. Index 2 onwards: All "Extend" because we found positive base (4)
3. dp[6] hits maximum → Our answer

---

## 💡 Part 10: The Deep Concept — State Definition

**Why State Definition Is EVERYTHING:**

Most people think of DP problems as:

> "Find the best answer."

**But the real thinking is:**

> "Define what 'best' means for EACH position."

### The Right State vs Wrong State

#### ❌ Wrong State:

```
dp[i] = Maximum sum of any subarray using first i elements
```

This doesn't create a recurrence.

#### ✅ Correct State:

```
dp[i] = Maximum sum of any subarray ENDING AT i
```

This **forces a structure** that has a recurrence.

### The Insight

**By restricting to "ending at i":**

- We create **local decision points** (continue or restart)
- Local decisions **build global optimum** (scan all dp for max)
- Each state depends on **only one previous** state → O(n) possible

---

## 🔄 Part 11: Local Decisions → Global Optimum

**The Computation Process:**

```
Position 0:  dp[0] = -2                    (Local: best here)
Position 1:  dp[1] = -3                    (Local: best here)
Position 2:  dp[2] = 4                     (Local: best here) 
Position 3:  dp[3] = 3                     (Local: best here)
...
Position 6:  dp[6] = 7                     (Local: best here)
...
Global:      max(dp[0..7]) = 7             (Global: best anywhere)
```

**The Pattern:**

1. **At each position i:** Decide whether to extend or restart (local optimization)
2. **After all positions:** Pick the position with highest dp value (global optimization)

This is why DP works for this problem!

---

## 📈 Part 12: Complexity Analysis

**Time Complexity:**

$$O(n)$$

**Why:**

- Single pass through array: O(n)
- Each element processed once
- Constant work per element

**Space Complexity:**

$$O(n)$$

**Why:**

- Need dp array of size n

**Comparison with Brute Force:**

| Approach | Time | Space |
|----------|------|-------|
| Brute Force | O(n²) | O(1) |
| DP (Full Array) | O(n) | O(n) |
| **DP can be optimized further** | O(n) | **O(1)** |

The last row shows Kadane's Algorithm (coming in next section).

**Growth Comparison (n = 1000):**

| Approach | Operations |
|----------|-----------|
| Brute Force | 1,000,000 |
| DP | 1,000 |
| **1000× faster!** | |

---

## 🎯 Part 13: The Complete Algorithm

**Pseudocode:**

```
FUNCTION MaxSubarraySum(A, n):
    IF n == 0:
        RETURN 0  (or handle empty array)
    
    dp[0] = A[0]
    max_overall = dp[0]
    
    FOR i = 1 TO n-1:
        dp[i] = max(A[i], A[i] + dp[i-1])
        max_overall = max(max_overall, dp[i])
    
    RETURN max_overall
```

**Step-by-Step Execution:**

```
Step 1: Initialize dp[0] and max_overall
Step 2: For each index i from 1 to n-1:
        a) Compute recurrence: dp[i] = max(A[i], A[i] + dp[i-1])
        b) Update max_overall if current dp[i] is larger
Step 3: Return max_overall
```

---

## 🔍 Part 14: Edge Cases

### Case 1: All Negative

**Array:** [-5, -3, -8, -1, -4]

**Computation:**

```
dp[0] = -5
dp[1] = max(-3, -3 + (-5)) = max(-3, -8) = -3
dp[2] = max(-8, -8 + (-3)) = max(-8, -11) = -8
dp[3] = max(-1, -1 + (-8)) = max(-1, -9) = -1
dp[4] = max(-4, -4 + (-1)) = max(-4, -5) = -4

max_overall = -1 (best is the single largest element)
```

**Key Learning:**

When all elements are negative, the answer is the **largest (least negative) single element**.

DP handles this correctly via the "Start fresh" option.

### Case 2: All Positive

**Array:** [2, 3, 5, 1, 4]

**Computation:**

```
dp[0] = 2
dp[1] = max(3, 3 + 2) = 5     (extend, since 2 > 0)
dp[2] = max(5, 5 + 5) = 10    (extend, since 5 > 0)
dp[3] = max(1, 1 + 10) = 11   (extend, since 10 > 0)
dp[4] = max(4, 4 + 11) = 15   (extend, since 11 > 0)

max_overall = 15 (entire array)
```

**Key Learning:**

When all elements are positive, the answer is the **entire array sum**.

DP handles this correctly by always extending.

### Case 3: Single Element

**Array:** [7]

```
dp[0] = 7
max_overall = 7
```

**Works correctly!**

### Case 4: Mix with Zeros

**Array:** [2, 0, -1, 3, 0, 2]

**Computation:**

```
dp[0] = 2
dp[1] = max(0, 0 + 2) = 2     (extend, 2 = 0)
dp[2] = max(-1, -1 + 2) = 1   (extend, 2 > 0)
dp[3] = max(3, 3 + 1) = 4     (extend, 1 > 0)
dp[4] = max(0, 0 + 4) = 4     (extend, 4 > 0)
dp[5] = max(2, 2 + 4) = 6     (extend, 4 > 0)

max_overall = 6 (entire array)
```

**Works correctly!**

---

## 🧠 Part 15: What He Is Really Teaching You

This lecture is NOT about computing subarray sums.

It's about three fundamental DP concepts:

### 1️⃣ State Definition

> **Choosing the right state is 80% of DP.**

Many students think:

```
dp[i] = best we can do with first i elements
```

But this doesn't work for this problem.

The **right state** is:

```
dp[i] = best subarray ENDING at i
```

This simple restriction **changes everything**.

**The Lesson:**

When defining DP state, ask:

- Can I express current answer using previous answer?
- Do current and previous answers have clear relationship?
- Does the restriction create a recurrence?

### 2️⃣ Local vs Global

**Local Decision (at each position i):**

- Should I extend the previous subarray?
- Or start a new one?

**Global Optimum (over all positions):**

- Which position has the best subarray ending there?

**The Lesson:**

DP often works by:

1. Making locally optimal decisions → this is what recurrence does
2. Comparing all local answers → this finds global optimum

### 3️⃣ Complexity Reduction

**From O(n²) to O(n):**

We reduced complexity by **eliminating redundant computation**.

In brute force, we recompute sums.

In DP, each state computed **once**.

**The Pattern:**

Problems with O(n²) brute force solutions often have **overlapping subproblems**.

DP fixes this by **caching results** (through table) or **defining smarter recurrence** (MSS).

### 4️⃣ Optimal Substructure

**The Key Property:**

The optimal solution to the larger problem can be **built from optimal solutions to smaller problems**.

For MSS:

- Best subarray ending at i is either:
  - A[i] alone (optimal for position i)
  - A[i] + (best subarray ending at i-1) (reuse previous optimal)

---

## 🎓 Part 16: This Pattern Applies Everywhere

The **logic pattern** of MSS appears in many interview problems:

### Problem: House Robber

```
Given array of house values.
You can't rob adjacent houses.
What's the maximum value you can steal?

State Definition:
dp[i] = Max value when considering houses 0 to i

Recurrence:
dp[i] = max(
    dp[i-1],                    (don't rob house i)
    A[i] + dp[i-2]              (rob house i, skip i-1)
)
```

**Same pattern:** Choose to include or exclude, recurrence uses previous states.

### Problem: Stock Buy/Sell

```
Given array of prices.
Find maximum profit if you can buy once and sell once.

State Definition:
min_price = minimum price seen so far

Recurrence:
profit = max(profit, current_price - min_price)
```

**Same pattern:** Track state, update decision at each position, find maximum.

### Problem: Maximum Product Subarray

```
Similar to MSS, but tracking product instead of sum.
Need to track both max and min (negatives flip signs).

Recurrence:
dp_max[i] = max(A[i], A[i] * dp_max[i-1], A[i] * dp_min[i-1])
dp_min[i] = min(A[i], A[i] * dp_max[i-1], A[i] * dp_min[i-1])
```

**Same pattern:** Recurrence depends on previous state, process each element once.

---

## ✨ Part 17: Interview Wisdom

### What Interviewers Are Testing

When they ask MSS in an interview, they're testing:

1. **Can you identify the state correctly?**
   - Most candidates define it wrong → No solution
   - Good candidates define: dp[i] = best ending at i
   - Great candidates explain WHY this definition works

2. **Can you derive the recurrence?**
   - This shows logical thinking
   - The recurrence should be obvious once state is defined

3. **Can you implement cleanly?**
   - Code is secondary
   - But efficiency matters (O(n) not O(n²))

4. **Can you trace an example?**
   - Mentally walk through [-2, -3, 4, -1, -2, 1, 5, -3]
   - Explain each dp[i] value

### Interview Red Flags

❌ Trying all subarrays (O(n²)) without thinking about DP

❌ Defining state as "best overall so far" (doesn't work)

❌ Not explaining the "start fresh vs extend" decision

✅ Define state clearly: "dp[i] = best subarray ending at i"

✅ Explain recurrence: "Either start new or extend previous"

✅ Implement in O(n) time

### Follow-up Questions (Be Ready)

1. **"Can you optimize space?"**
   - Yes! Only need previous dp value
   - Space → O(1)
   - This is Kadane's Algorithm

2. **"Can you return the actual subarray, not just sum?"**
   - Track start and end indices
   - When you update max_overall, also update indices

3. **"What if you could remove one element?"**
   - Requires more complex state
   - Shows you understand state definition flexibility

4. **"What about array with values in range [-100, 100]?"**
   - Doesn't change the algorithm
   - DP works for any integers

---

## 🎯 Part 18: Final Summary

### The Core Insight

```
dp[i] = Maximum subarray sum ENDING exactly at index i

dp[i] = max(
    A[i],                 ← Start fresh
    A[i] + dp[i-1]        ← Extend previous
)

Answer = max(dp[0], dp[1], ..., dp[n-1])
```

### Why This Is Powerful

1. **Transforms the problem:** From "all subarrays" to "position-specific"
2. **Creates clear recurrence:** Two explicit choices
3. **Enables O(n) solution:** Each position computed once
4. **Shows optimization thinking:** Convert exponential to linear

### The Lesson Beyond MSS

When you see a sequence problem:

1. ✅ Can I define a position-specific state?
2. ✅ Can I express current state using previous states?
3. ✅ Can I reduce time complexity via caching/smart recurrence?

If yes to all → **DP is applicable**

### Mastery Checklist

By end of this section, you should:

✅ Define dp[i] without hesitation
✅ Derive recurrence clearly (start vs extend)
✅ Trace example from memory
✅ Explain why O(n) not O(n²)
✅ Identify state definition as the key
✅ See this pattern in other problems

---

Your understanding of MSS is the foundation for understanding 1000+ dynamic programming problems. Master the state definition, and you master DP itself.
