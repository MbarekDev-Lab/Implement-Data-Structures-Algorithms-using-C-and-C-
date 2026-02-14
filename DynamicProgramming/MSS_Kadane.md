# Maximum Subarray Sum Using Kadane's Algorithm

> **Core Mindset**: This lecture is not just about finding a maximum sum. It's about recognizing when you only need to track the **previous state**, transforming space from O(n) to O(1) while keeping time linear. It's about the mental shift from "check all possibilities" to "what's best ending here?"

---

## 📊 Part 1: The Problem Statement

**Maximum Subarray Sum Problem:**

Given an array of integers (positive and negative):

```
A = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
```

**Goal:**

Find the maximum sum of any contiguous subarray.

**Correct Answer:**

```
Subarray: [4, -1, 2, 1]
Sum:      4 + (-1) + 2 + 1 = 6
```

---

## 🎯 Part 2: The Mental Journey

### The Initial Thinking (Brute Force)

"I need to check all subarrays and compute their sums."

```
for each starting position i:
  for each ending position j >= i:
    compute sum(i...j)
    track maximum
```

Time: **O(n²)**

### The DP Thinking (Previous Section)

"What if I define `dp[i]` = best subarray ending at i?"

Then: `dp[i] = max(A[i], dp[i-1] + A[i])`

Time: **O(n)**
Space: **O(n)** (need dp array)

### The Kadane Insight (This Section)

"Wait... do I actually need the entire dp array?"

Let me look at how we compute:

```
dp[i] depends on dp[i-1]
dp[i+1] depends on dp[i]
dp[i+2] depends on dp[i+1]
```

**The key insight:**

Each state depends only on the **previous state**.

Nothing older matters.

So we only need:

```
currentMax = best subarray ending here (replaces dp[i])
globalMax  = best subarray found anywhere
```

Space: **O(1)** ← No array! Just two variables!

This is the mental shift: **From "I need to remember everything" to "I only need the last value"**

---

## 📐 Part 3: The Space Optimization Theory

### Why the dp array exists in DP version

```c
for(int i = 1; i < n; i++) {
    dp[i] = max(A[i], dp[i-1] + A[i]);
    globalMax = max(globalMax, dp[i]);
}
```

We allocate `int dp[n]` to store all values.

### Why we don't need it in Kadane

```c
int currentMax = A[0];  // replaces dp[i-1]
int globalMax = A[0];

for(int i = 1; i < n; i++) {
    currentMax = max(A[i], currentMax + A[i]);  // replaces dp[i]
    globalMax = max(globalMax, currentMax);
}
```

We reuse the **same two variables** for every iteration.

### The Mathematical Reason This Works

**Base observation:**

When computing position i, we need:
- Current element A[i]
- Previous state dp[i-1]

We **do not need:**
- dp[i-2], dp[i-3], ... (already processed)
- Previous global max (we update it after each state)

**Therefore:**

Sequential processing allows us to discard old data immediately.

$$\text{Memory footprint}: O(n) \rightarrow O(1)$$

---

## 💾 Part 4: Comparison of Three Approaches

### Approach 1: Brute Force

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

| Metric | Value |
|--------|-------|
| Time | O(n²) |
| Space | O(1) |
| Code Clarity | Easy |

### Approach 2: DP (Previous Section)

```c
int dp[n];
dp[0] = A[0];
int maxSum = dp[0];

for(int i = 1; i < n; i++) {
    dp[i] = max(A[i], dp[i-1] + A[i]);
    maxSum = max(maxSum, dp[i]);
}
```

| Metric | Value |
|--------|-------|
| Time | O(n) |
| Space | **O(n)** |
| Code Clarity | Good |
| Recurrence Visible | Yes |

### Approach 3: Kadane's Algorithm (This Section)

```c
int currentMax = A[0];
int globalMax = A[0];

for(int i = 1; i < n; i++) {
    currentMax = max(A[i], currentMax + A[i]);
    globalMax = max(globalMax, currentMax);
}
```

| Metric | Value |
|--------|-------|
| Time | O(n) |
| Space | **O(1)** |
| Code Clarity | Simple |
| Recurrence Visible | Abstracted |

**The Progression:**

Brute Force → DP → Kadane's

O(n²), O(1) → O(n), O(n) → **O(n), O(1)** ✅

---

## 🎬 Part 5: Full Example Walkthrough

**Array:**

```
A = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
     0  1   2  3   4  5  6   7  8
```

**Initialization:**

```
currentMax = -2  (best subarray ending at 0)
globalMax = -2   (best we've found overall)
```

**i = 1, A[1] = 1:**

```
currentMax = max(1, -2 + 1) = max(1, -1) = 1
globalMax = max(-2, 1) = 1

Meaning: Best subarray ending at 1 is [1] alone
         Best overall is [1]
```

**i = 2, A[2] = -3:**

```
currentMax = max(-3, 1 + (-3)) = max(-3, -2) = -2
globalMax = max(1, -2) = 1

Meaning: Best subarray ending at 2 is [1, -3]
         Best overall is still [1]
```

**i = 3, A[3] = 4:**

```
currentMax = max(4, -2 + 4) = max(4, 2) = 4
globalMax = max(1, 4) = 4

Meaning: Best subarray ending at 3 is [4] alone (restart!)
         Best overall is [4]
```

**i = 4, A[4] = -1:**

```
currentMax = max(-1, 4 + (-1)) = max(-1, 3) = 3
globalMax = max(4, 3) = 4

Meaning: Best subarray ending at 4 is [4, -1]
         Best overall is still [4]
```

**i = 5, A[5] = 2:**

```
currentMax = max(2, 3 + 2) = max(2, 5) = 5
globalMax = max(4, 5) = 5

Meaning: Best subarray ending at 5 is [4, -1, 2]
         Best overall is [4, -1, 2]
```

**i = 6, A[6] = 1:**

```
currentMax = max(1, 5 + 1) = max(1, 6) = 6
globalMax = max(5, 6) = 6

Meaning: Best subarray ending at 6 is [4, -1, 2, 1]
         Best overall is [4, -1, 2, 1] ← THIS IS OUR ANSWER
```

**i = 7, A[7] = -5:**

```
currentMax = max(-5, 6 + (-5)) = max(-5, 1) = 1
globalMax = max(6, 1) = 6

Meaning: Best subarray ending at 7 is [4, -1, 2, 1, -5]
         But best overall remains [4, -1, 2, 1]
```

**i = 8, A[8] = 4:**

```
currentMax = max(4, 1 + 4) = max(4, 5) = 5
globalMax = max(6, 5) = 6

Meaning: Best subarray ending at 8 is [4, -1, 2, 1, -5, 4]
         Best overall is still [4, -1, 2, 1]
```

**Final Answer:**

$$\text{globalMax} = 6$$

**Optimal Subarray:**

$$[4, -1, 2, 1]$$

---

## 📊 Part 6: State Evolution Table

| i | A[i] | currentMax | globalMax | Decision |
|---|------|-----------|-----------|----------|
| 0 | -2 | -2 | -2 | Start |
| 1 | 1 | 1 | 1 | Start fresh |
| 2 | -3 | -2 | 1 | Extend |
| 3 | 4 | 4 | 4 | Start fresh ← Restart! |
| 4 | -1 | 3 | 4 | Extend |
| 5 | 2 | 5 | 5 | Extend |
| 6 | 1 | 6 | **6** | Extend ← **ANSWER** |
| 7 | -5 | 1 | 6 | Extend |
| 8 | 4 | 5 | 6 | Extend |

**Key Observations:**

1. **currentMax** is computed from A[i] and previous currentMax only
2. **globalMax** tracks the best currentMax seen
3. At index 3, we "restart" (currentMax = 4, discarding -2)
4. At index 6, we hit our answer (currentMax = 6, highest ever)
5. Later indices don't improve globalMax

---

## 🧠 Part 7: Three Deep Concepts

### Concept 1: The "Previous State Only" Pattern

**The Insight:**

When a problem has recurrence like:

$$\text{dp}[i] = f(\text{dp}[i-1], A[i])$$

You can optimize to O(1) space by replacing the array with a single variable.

**Why This Matters:**

This pattern appears in many problems:
- Maximum product subarray (need two: max and min)
- Climb stairs (fib-like)
- House robber (choose or skip)
- Stock trading (multiple states)

**The Lesson:**

Always ask: "Does my current state depend only on the previous state?"

If yes → O(1) space possible.

### Concept 2: The "Restart vs Extend" Decision

**The Underlying Logic:**

```
if (previous_state < 0):
    throw it away, start fresh
else:
    extend it
```

This is **automatic pruning**.

We never artificially extend a bad history.

**Why This Matters:**

Many greedy-looking problems are actually DP with this pattern.

The "greedy choice" (restart vs extend) is optimal because of **optimal substructure**.

**The Lesson:**

Greedy and DP are not always separate. Some greedy algorithms are secretly DP with one choice-per-position.

### Concept 3: The Space-Time Tradeoff

**Three Levels of Understanding:**

| Understanding Level | Time | Space | Insight |
|-------------------|------|-------|---------|
| 1. Brute Force | O(n²) | O(1) | Check all, optimize nothing |
| 2. DP | O(n) | O(n) | Remember all states |
| 3. Kadane | O(n) | O(1) | Only previous state matters |

**Why This Matters:**

In systems design, you often choose based on constraints:
- Memory constrained? Use Kadane
- Need to reconstruct solution? Use DP table
- Just need the answer? Either works

**The Lesson:**

There's often a series of optimizations. Finding them requires understanding the algorithm deeply.

---

## 🎯 Part 8: The Kadane Algorithm (Final Form)

**Pseudocode:**

```
FUNCTION MaxSubarraySumKadane(A, n):
    IF n == 0:
        RETURN 0
    
    currentMax = A[0]
    globalMax = A[0]
    
    FOR i = 1 TO n-1:
        currentMax = max(A[i], currentMax + A[i])
        globalMax = max(globalMax, currentMax)
    
    RETURN globalMax
```

**Variables:**

- `currentMax`: Best subarray sum ending at current position
- `globalMax`: Best subarray sum found anywhere

**Loop Logic:**

1. At each position, decide: restart or extend
2. This decision is embedded in `max(A[i], currentMax + A[i])`
3. Update our "best seen so far" with `globalMax`

**Time:** O(n) — single pass
**Space:** O(1) — only two integers

---

## 💡 Part 9: Understanding the Mental Shift

### Before Kadane (DP Thinking)

You say: "I need a dp array to remember all best-ending values."

```c
dp[0] = -2    ← I need to remember this
dp[1] = 1     ← And this
dp[2] = -2    ← And this
...
```

Why? "Because I might need them later!"

### After Kadane (Optimization Insight)

You realize: "When computing position i, I only read dp[i-1]."

"I'll never read dp[i-2] or earlier again after position i."

"So I can just overwrite it!"

```c
currentMax = -2    → reading it
currentMax = 1     → overwrite, don't need first value anymore
currentMax = -2    → overwrite again
```

### The Philosophical Shift

❌ **Old thinking:** "Store everything because you might need it"

✅ **New thinking:** "Only store what you currently need"

This is the mindset of optimization:

- Understand dependencies
- Discard unused data immediately
- Minimize resource footprint

---

## 🔍 Part 10: Recognizing Kadane-Pattern Problems

### The Pattern

```
dp[i] = max(
    A[i],                  ← Start fresh at i
    dp[i-1] + A[i]         ← Extend from i-1
)
```

### Where This Appears

**✅ Problem 1: Maximum Subarray Sum**
```
dp[i] = max(A[i], dp[i-1] + A[i])
```

**✅ Problem 2: Maximum Product Subarray**
```
max_dp[i] = max(A[i], max_dp[i-1] * A[i], min_dp[i-1] * A[i])
min_dp[i] = min(A[i], max_dp[i-1] * A[i], min_dp[i-1] * A[i])
```
(Need both max and min because negatives flip signs)

**✅ Problem 3: Stock Buy/Sell (at most k transactions)**
```
dp[i] = max(
    dp[i-1],              ← Do nothing today
    A[i] - cost           ← Buy today (sell at future profit)
)
```

**✅ Problem 4: House Robber**
```
dp[i] = max(
    dp[i-1],              ← Skip house i
    A[i] + dp[i-2]        ← Rob house i, skip i-1
)
```

### The Recognition Framework

When you see a problem asking for:
- "Maximum sum/product of contiguous elements"
- "Best choice at each position (include or exclude)"
- "Optimal sequence of decisions"

Ask: **"Can I express dp[i] using only dp[i-1]?"**

If yes → Kadane pattern possible → O(1) space

---

## 📈 Part 11: Complexity Analysis

### Time Complexity: O(n)

**Why:**

- Single loop from 1 to n-1
- Constant work per iteration (two max operations)
- No nested loops

$$\text{Total operations} = 1 + 1 + ... + 1 \text{ (n-1 times)} = O(n)$$

### Space Complexity: O(1)

**Why:**

- No array allocation
- Only two integer variables: `currentMax`, `globalMax`
- Input array doesn't count as "extra space"

$$\text{Extra memory} = \text{sizeof(int)} \times 2 = O(1)$$

### Comparison Table

| Algorithm | Time | Space | Why Space is Better |
|-----------|------|-------|-------------------|
| Brute Force | O(n²) | O(1) | Two nested loops |
| DP (Full Array) | O(n) | O(n) | Need dp[0..n-1] |
| **Kadane** | **O(n)** | **O(1)** | **Only need previous** |

---

## 🎓 Part 12: Code Review — Kadane Implementation

### Version 1: Textbook Kadane

```c
int maxSubarraySum(int A[], int n) {
    int currentMax = A[0];
    int globalMax = A[0];
    
    for(int i = 1; i < n; i++) {
        currentMax = max(A[i], currentMax + A[i]);
        globalMax = max(globalMax, currentMax);
    }
    
    return globalMax;
}
```

**Clarity:** 4/5 (Simple but variables names could be clearer)

### Version 2: More Descriptive

```c
int maxSubarraySum(int A[], int n) {
    int best_ending_here = A[0];
    int best_so_far = A[0];
    
    for(int i = 1; i < n; i++) {
        // At position i: restart or extend?
        best_ending_here = max(A[i], best_ending_here + A[i]);
        
        // Update best seen globally
        best_so_far = max(best_so_far, best_ending_here);
    }
    
    return best_so_far;
}
```

**Clarity:** 5/5 (Variable names explain what they track)

### Version 3: With Comments for Interview

```c
int maxSubarraySum(int A[], int n) {
    int current = A[0];  // Best subarray sum ENDING at current position
    int global = A[0];   // Best subarray sum found ANYWHERE
    
    for(int i = 1; i < n; i++) {
        // Decision: Carry negative prefix forward, or start fresh?
        // If current < 0, starting fresh (A[i]) is better
        // If current >= 0, extending (current + A[i]) is better
        current = (A[i] > current + A[i]) ? A[i] : (current + A[i]);
        
        // Update global maximum
        global = (current > global) ? current : global;
    }
    
    return global;
}
```

**Clarity:** 5/5 (Comments explain the decision logic)

---

## 🔥 Part 13: Why This Algorithm Gets Its Name

**History:**

Kadane's algorithm is named after **Jay Kadane**, who discovered it in 1984.

**Why "Kadane"?**

Before Kadane:
- Best known algorithm was O(n²) brute force
- Some attempts at O(n log n) divide-and-conquer

Kadane's insight:
- **O(n) time** with **O(1) space**
- Elegantly simple recurrence
- Immediately became the standard

**Why It Matters:**

Kadane showed that understanding the problem structure (dependencies) can lead to dramatic optimization.

Not through advanced math, but through **careful state analysis**.

---

## 🎯 Part 14: What You're Really Learning

This is more than an algorithm. It's a mindset:

### Mindset 1: Dependency Analysis

> **"What does my current state actually depend on?"**

Many problems maintain unnecessary state because of lazy thinking.

Kadane teaches: Strip away everything except true dependencies.

### Mindset 2: Sequential Processing

> **"Can I process elements left-to-right, updating in place?"**

Many problems don't need bidirectional data or lookahead.

Kadane teaches: Process sequentially, each decision is final.

### Mindset 3: Recognizing Patterns

> **"Have I seen this recurrence structure before?"**

Once you solve Kadane, similar problems become obvious.

Kadane teaches: Pattern recognition is more valuable than memorization.

### Mindset 4: Space-Time Consciousness

> **"Do I need extra space for clarity, or can I trade clarity for efficiency?"**

Interview trade-offs often involve this choice.

Kadane teaches: Both solutions (DP array and Kadane) are valid, context matters.

---

## 📋 Part 15: Edge Cases and Tricky Inputs

### Case 1: All Negative

**Input:** `[-5, -3, -8, -1, -4]`

**Computation:**
```
i=0: current = -5, global = -5
i=1: current = max(-3, -5 + (-3)) = -3, global = -3
i=2: current = max(-8, -3 + (-8)) = -8, global = -3
i=3: current = max(-1, -8 + (-1)) = -1, global = -1
i=4: current = max(-4, -1 + (-4)) = -4, global = -1
```

**Answer:** -1 ✅ (correctly returns largest single element)

### Case 2: Single Element

**Input:** `[7]`

**Computation:** Returns 7 immediately ✅

### Case 3: Mix of Positive/Negative

**Input:** `[1, -2, 3, -4, 5]`

```
i=0: current = 1, global = 1
i=1: current = max(-2, 1 - 2) = -1, global = 1
i=2: current = max(3, -1 + 3) = 3, global = 3
i=3: current = max(-4, 3 - 4) = -1, global = 3
i=4: current = max(5, -1 + 5) = 5, global = 5
```

**Answer:** 5 ✅ (correctly identifies single element as best)

### Case 4: Entire Array is Best

**Input:** `[2, 3, 5, 1, 4]`

```
i=0: current = 2, global = 2
i=1: current = max(3, 2 + 3) = 5, global = 5
i=2: current = max(5, 5 + 5) = 10, global = 10
i=3: current = max(1, 10 + 1) = 11, global = 11
i=4: current = max(4, 11 + 4) = 15, global = 15
```

**Answer:** 15 ✅ (correctly extends all the way)

---

## 🎬 Part 16: Following the Algorithm on Different Inputs

### Test Input: `[-2, 1, -3, 4, -1, 2, 1, -5, 4]`

**Processing Flow:**

```
Position 0: ["Set baseline"]
  current = -2
  global = -2

Position 1: ["Restart with 1"]
  current = max(1, -2 + 1) = 1
  global = 1

Position 2: ["Extend but go negative"]
  current = max(-3, 1 - 3) = -2
  global = 1 (no update)

Position 3: ["Fresh restart with 4"]
  current = max(4, -2 + 4) = 4 ← This is a RESTART
  global = 4

Positions 4-6: ["Keep extending"]
  current grows to 6 via [4, -1, 2, 1]
  global updates to 6 ← **ANSWER FOUND HERE**

Positions 7-8: ["Can't beat 6"]
  Attempts to extend fail to exceed 6
  global remains 6
```

**Key Learning:** The algorithm doesn't look ahead. It makes the locally optimal decision (extend or restart) and this builds the globally optimal answer.

---

## ✨ Part 17: Interview Wisdom

### What Interviewers Test

1. **Can you recognize when O(1) space is possible?**
   - Many candidates implement DP array unnecessarily
   - Recognizing "previous state only" shows deep understanding

2. **Can you explain the trade-off?**
   - DP Array: Better visibility, clearer logic, O(n) space
   - Kadane: More optimized, O(1) space, requires careful variable usage

3. **Can you implement correctly?**
   - Off-by-one errors are common
   - Edge cases (all negative, single element) trip many up

4. **Can you recognize the pattern elsewhere?**
   - House Robber, Stock Trading, etc. use the same idea
   - This shows you understand structure, not just memorization

### The Common Mistake

```c
// ❌ WRONG
currentMax = max(A[i], currentMax + A[i]);
globalMax = currentMax;  // Updates EVERY iteration!
```

Problem: `globalMax` should be `max(globalMax, currentMax)`, not just assignment.

**Why it matters:** If there's an earlier peak, this loses it.

### The Follow-Up Question

**"Can you modify the algorithm to return the actual subarray, not just the sum?"**

Answer:
- Track `start` and `end` indices
- When `currentMax` resets (restart decision), update `start`
- When `globalMax` updates, record the current `start` and current position as `end`

This adds O(1) space for indices, but no additional traversal needed.

---

## 🌟 Part 18: Beyond MSS — Pattern Recognition

### This Pattern Unlocks

When you master Kadane, you unlock solutions to:

**✅ Maximum Product Subarray**
- Needs two states: `maxDp` and `minDp` (for negative flips)
- Otherwise identical logic

**✅ House Robber (1D)**
```
dp[i] = max(dp[i-1], A[i] + dp[i-2])
```
- Dependency on i-2 instead of i-1, but still O(1) space possible

**✅ Best Time to Buy and Sell Stock**
```
max_profit = current_price - min_price_so_far
```
- Similar "track state and optimize in one pass" thinking

**✅ Longest Arithmetic Subarray**
```
dp[i] = 1 + dp[i-1] if A[i] - A[i-1] == constant_difference
```
- Same sequential processing, same O(1) space

### The Universal Template

```
For each position i:
    1. Decide what to compute based on current and previous state
    2. Compare with global optimum
    3. Move to next position
```

Once you see this, you see it everywhere.

---

## 🎯 Part 19: The Final Insight

### Kadane's Algorithm Is A Teacher

It's not just "the solution to MSS."

It's a **lesson in system thinking**:

1. **Understand the problem deeply**
   - What does each state represent?
   - What does each state depend on?

2. **Eliminate redundancy**
   - Do I really need to store x? Or just remember y?
   - Can I process sequentially, updating in place?

3. **Recognize patterns**
   - This structure appears in many problems
   - Pattern recognition > memorization

4. **Optimize consciously**
   - O(n) time is often "good enough"
   - O(1) space shows deep understanding
   - But clarity sometimes matters more than optimization

### The Meta-Lesson

You're not learning "an algorithm."

You're learning **how to think like an engineer**.

---

## ✅ Part 20: Mastery Checklist

By the end of this section, you should:

✅ Understand why O(1) space is possible for Kadane
✅ Explain the "restart vs extend" decision at each position
✅ Implement Kadane cleanly without the dp array
✅ Recognize when problems follow the Kadane pattern
✅ Explain the trade-off: DP array (clarity) vs Kadane (space efficiency)
✅ Handle edge cases: all negative, single element, entire array
✅ Modify the algorithm to track start/end indices of optimal subarray
✅ See the pattern in House Robber, Stock Trading, etc.
✅ Explain to an interviewer why Kadane is optimal
✅ Recognize this is about mindset, not just an algorithm

---

## 🔥 The Final Truth

Kadane's algorithm is brilliant not because it's hard.

It's brilliant because it's **simple once you see the right structure**.

And seeing the right structure is everything in computer science.

**Master Kadane, and you master the art of algorithm optimization.**

