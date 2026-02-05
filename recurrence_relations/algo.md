# Recurrence Relations - Abdo's Approach

## What Abdo means by a recurrence relation

A recurrence relation is just a way to describe running time by relating a problem to smaller versions of the same problem.

Think like Abdo does on the whiteboard:

> **"If I know how much time a smaller input takes, I can express the time for a bigger input."**

So instead of guessing time complexity directly, we define it recursively, exactly how the algorithm works.

## Core idea Abdo repeats again and again

Every recurrence has two parts:

```
T(n) = cost to solve smaller problem
     + cost of work done at current step
```

That's it. Everything else is just patterns.

---

## 1️⃣ Decreasing function

### T(n) = T(n - 1) + 1

**What Abdo is saying:**
- Problem size reduces by 1 each step
- Each step does constant work (1)
```c
fun(n) {
    if (n == 0) return;
    fun(n-1);
}
```

**Whiteboard thinking:**
```
T(n) = T(n-1) + 1
T(n-1) = T(n-2) + 1
...
T(1) = T(0) + 1

Add them up:
T(n) = 1 + 1 + 1 + ... (n times)
```

**Final result:**
👉 **T(n) = Θ(n)**

$$1 + 2 + 4 + \dots + 2^n \approx 2^n$$
> "If you reduce by 1 every time, you'll run n times."

---


### T(n) = T(n - 1) + n


**What changes?**
- Still reducing by 1
- But work at each step grows: + n

**Example:**
```c
fun(n) {
    for (i = 0; i < n; i++) { /* work */ }
    fun(n-1);
}
```

**Expansion:**
```
T(n) = n + (n-1) + (n-2) + ... + 1

Sum of first n numbers:
n(n+1)/2
```

**Final result:**
👉 **T(n) = Θ(n²)**

💡 **Abdo's message:**
> "Even if recursion is simple, heavy work inside can kill performance."

---

## 3️⃣ Recursive tree explosion

- Binary search
- Finding MSB (most significant bit)
- Loop like: `while (n > 1) n = n / 2;`
### T(n) = 2T(n - 1) + 1

This is where Abdo starts waving hands dramatically on the board 😅

**Meaning:**
- One call becomes two recursive calls
- Size reduces slowly (n-1)

**Call tree:**
```
Level 0:      1 call
Level 1:      2 calls
Level 2:      4 calls
...

Total calls:
1 + 2 + 4 + ... ≈ 2ⁿ
```

**Final result:**
👉 **T(n) = Θ(2ⁿ)**

💡 **Abdo's warning:**
> "Never write recursion like this unless you want exponential time."

**Classic example:** naive Fibonacci

---

## 4️⃣ Dividing function (VERY IMPORTANT)

### T(n) = T(n / 2) + 1

Now Abdo smiles 😌 because this is efficient.

**Meaning:**
- Problem size halves each time
- Constant work per step

**Example:**
```c
binarySearch(arr, n)
```

**Expansion:**
```
n → n/2 → n/4 → n/8 → ...

How many steps until n = 1?
log₂ n
```

**Final result:**
👉 **T(n) = Θ(log n)**

💡 **Abdo's core lesson:**
> "Dividing is always better than decreasing."

---

## 5️⃣ Divide + linear work

### T(n) = T(n / 2) + n

This shows up in Merge Sort–like thinking.

**At each level:**
- Work = n
- Depth = log n

**So:**
```
n + n + n + ... (log n times)
```

**Final result:**
👉 **T(n) = Θ(n log n)**

💡 **Abdo's mantra:**
> "n log n is the best you can usually hope for in sorting."

---

## How Abdo wants YOU to think in exams

When you see a recurrence, immediately ask:

1. **Is it decreasing or dividing?**
2. **How many recursive calls?**
3. **How much work outside recursion?**

### Quick Reference Table

| Pattern | Time Complexity |
|---------|----------------|
| T(n) = T(n-1) + 1 | Θ(n) |
| T(n) = T(n-1) + n | Θ(n²) |
| T(n) = 2T(n-1) + 1 | Θ(2ⁿ) |
| T(n) = T(n/2) + 1 | Θ(log n) |
| T(n) = T(n/2) + n | Θ(n log n) |

---

## Lecture 385 focus: T(n) = 2T(n − 1) + 1

**Plain-English reading:**
> “To solve size $n$, solve **two** problems of size $n-1$, then do constant extra work.”

That single change (two calls instead of one) makes the time explode.

**Recursion tree intuition:**
- Level 0: $1$ call
- Level 1: $2$ calls
- Level 2: $4$ calls
- Level 3: $8$ calls

Total calls form a geometric series:
$$1 + 2 + 4 + \dots + 2^n \approx 2^n$$

**Final result:**
👉 **$T(n) = \Theta(2^n)$**

**Key takeaway (Abdo-style):**
> “Branching recursion with slow size decrease is always exponential.”

---

## Decreasing recurrences by the value of $a$

General form:
$$T(n) = aT(n-1) + f(n)$$

### Case A: $a = 1$
One recursive call. No branching.

- If $f(n)=1$, then $T(n)=\Theta(n)$
- If $f(n)=n$, then $T(n)=\Theta(n^2)$

**Rule:** total time is the sum of $f(n)$ along the chain.

### Case B: $a > 1$
Multiple recursive calls. Branching tree.

- Even with small $f(n)$, total nodes grow like $a^n$
- Polynomial $f(n)$ does **not** beat exponential growth

**Rule:** if $a>1$ and the size decreases by $1$, the time is exponential.

### Case C: $a < 1$ (theoretical only)
Mathematically, something like:
$$T(n) = 0.5T(n-1) + 1$$
converges to a constant, so $T(n)=\Theta(1)$.

**But in real algorithms, this doesn't happen** because you can't make half a recursive call. The number of calls is always an integer.

---

## Lecture 387 focus: T(n) = T(n/2) + 1

**Plain-English reading:**
> “To solve size $n$, solve **one** problem of size $n/2$, then do constant extra work.”

This is a dividing recurrence, not decreasing-by-1.

**Recursion chain:**
$$n \to n/2 \to n/4 \to n/8 \to \dots \to 1$$

**Key question (Abdo's favorite):**
How many times can you divide $n$ by $2$ until it becomes $1$?

Solve:
$$\frac{n}{2^k} = 1 \Rightarrow k = \log_2 n$$

**Final result:**
👉 **$T(n) = \Theta(\log n)$**

**Quick comparison:**

| Recurrence | Time |
|---|---|
| $T(n)=T(n-1)+1$ | $\Theta(n)$ |
| $T(n)=T(n/2)+1$ | $\Theta(\log n)$ |

**Abdo's takeaway:**
> “Divide is always better than decrease.”

**Real-world examples:**
- Binary search
- Finding MSB (most significant bit)
- Loop like: `while (n > 1) n = n / 2;`

---

## Detailed Lecture: T(n) = 2T(n/2) + 1

This recurrence is common in **divide-and-conquer algorithms** like binary search trees, merge sort traversal, or recursive functions that split problems into halves.

### 1️⃣ Understanding the Recurrence

Breaking down **T(n) = 2T(n/2) + 1**:

- **T(n)** = time to solve a problem of size $n$
- **2T(n/2)** = problem splits into **2 subproblems**, each of size $n/2$
  - This happens when you recursively process left and right halves (like in binary trees)
- **+1** = work done outside the recursive calls (comparisons, additions, constant-time operations)

**Plain English:**
> "To solve a problem of size $n$, I solve two smaller problems of size $n/2$ each, and then do 1 extra operation."

### 2️⃣ Solution Method 1: Recursion Tree

Let's trace the tree level by level:

```
Level 0: 1 call    → work = 1 × 1 = 1
Level 1: 2 calls   → work = 2 × 1 = 2
Level 2: 4 calls   → work = 4 × 1 = 4
Level 3: 8 calls   → work = 8 × 1 = 8
...
Level k: 2^k calls → work = 2^k × 1 = 2^k
```

**Observation:**
- At each level: total work = (number of nodes) × (work per node) = $2^{\text{level}}$
- Number of levels = $\log_2 n$ (because we divide by 2 each time)
- At last level: $2^{\log_2 n} = n$ nodes

**Total Work:**
$$T(n) = 1 + 2 + 4 + 8 + \dots + n = 2n - 1$$

✅ **T(n) = Θ(n)**

### 3️⃣ Solution Method 2: Master Theorem

The Master Theorem formula:
$$T(n) = aT(n/b) + f(n)$$

**Identify parameters:**
- $a = 2$ (number of subproblems)
- $b = 2$ (size reduction factor)
- $f(n) = 1$ (extra work per call)

**Apply Master Theorem:**

Step 1: Calculate $\log_b a$:
$$\log_2 2 = 1$$

Step 2: Compare $f(n)$ with $n^{\log_b a} = n^1 = n$:
- $f(n) = 1 = O(n^0)$
- This is **smaller** than $n^1$

Step 3: **Case 1 applies:**
$$T(n) = \Theta(n^{\log_b a}) = \Theta(n^1) = \Theta(n)$$

### 4️⃣ Intuition

Even though there are **2 recursive calls**, each call is on a **smaller half**, and the extra work at each level is tiny (+1).

The key insight:
- Work doubles at each level (1 → 2 → 4 → 8...)
- But the number of levels is only $\log n$
- The last level dominates with $n$ operations

This leads to **linear overall time** O(n).

### 5️⃣ When is this Used?

**Practical applications:**
- Traversing a complete binary tree while doing a small operation at each node
- Calculating sums recursively in divide-and-conquer algorithms
- Any binary splitting scenario where extra work per split is constant
- Counting nodes in a binary tree
- Finding elements in a balanced tree structure

---

## Understanding "Dividing" Recurrences

A recurrence is called **dividing** when the problem size is reduced by a **factor**, not by a constant.

**General form:**
$$T(n) = aT(n/b) + f(n)$$

Where:
- $a$ = number of subproblems
- $n/b$ = size of each subproblem
- $f(n)$ = work done outside recursion

This is the backbone of **divide and conquer**.

### Why Dividing is Powerful

Compare:

| Type | Size change | Height |
|------|-------------|--------|
| Decreasing | $n \to n-1$ | $n$ |
| Dividing | $n \to n/2$ | $\log n$ |

👉 Cutting by half collapses the recursion tree very fast.

---

## Case 1: T(n) = T(n/2) + 1

**Meaning:**
- 1 recursive call
- Constant extra work
- Size halves each time

**Tree:**
```
T(n)
 |
T(n/2)
 |
T(n/4)
 |
...
 |
T(1)
```

**Height:**
Solve:
$$\frac{n}{2^k} = 1 \Rightarrow k = \log_2 n$$

**Work:**
- Work per level = 1
- Levels = $\log n$

✅ **$T(n) = \Theta(\log n)$**

---

## Case 2: T(n) = T(n/2) + n

Now this looks scary, but it's actually gentle.

**Expand:**
$$n + \frac{n}{2} + \frac{n}{4} + \frac{n}{8} + \dots$$

This is a geometric series.

**Sum:**
$$n\left(1 + \frac{1}{2} + \frac{1}{4} + \dots\right)$$

This converges to:
$$2n$$

✅ **$T(n) = \Theta(n)$**

💡 **Abdo's hidden message:**
> "Even if work decreases slowly, dividing keeps things linear."

---

## Case 3: T(n) = 2T(n/2) + 1

**Meaning:**
- 2 recursive calls
- Constant work
- Size halves

**Tree:**
```
Level 0: 1 node → 1
Level 1: 2 nodes → 2
Level 2: 4 nodes → 4
...
```

**Height** = $\log n$

**Total nodes:**
$$1 + 2 + 4 + \dots + n = 2n - 1$$

✅ **$T(n) = \Theta(n)$**

---

## Case 4: T(n) = 2T(n/2) + n

This is **Merge Sort** territory.

**Per level work:**
- Level 0: $n$
- Level 1: $n$
- Level 2: $n$
- ...

**Why?**
Each level has more nodes, but each node handles a smaller piece.

- Total work per level = $n$
- Levels = $\log n$

✅ **$T(n) = \Theta(n \log n)$**

---

## Case 5: T(n) = 2T(n/2) + n²

Now extra work dominates.

**Per level:**
$$n^2 + \left(\frac{n}{2}\right)^2 + \left(\frac{n}{4}\right)^2 + \dots$$

This converges to:
$$\approx n^2$$

Levels don't matter anymore.

✅ **$T(n) = \Theta(n^2)$**

---

## Detailed Lecture 391: T(n) = 2T(n/2) + n²

This lecture shows a **divide-and-conquer** scenario where the **combination step is expensive**. The key insight: when extra work dominates, it determines the final complexity.

### Context: Why this recurrence?

This recurrence appears in algorithms like:
- **Naive matrix multiplication** (combining $2 \times 2$ quadrant multiplications)
- **Solving 2D problems** using divide-and-conquer
- Any algorithm where combining subproblems requires quadratic work

### 1️⃣ Understanding the Recurrence

Breaking down **T(n) = 2T(n/2) + n²**:

- **T(n)** = total time to solve a problem of size $n$
- **2T(n/2)** = 2 recursive calls, each on size $n/2$
- **+n²** = extra work needed to combine the results (quadratic!)

**Plain English:**
> "To solve size $n$, make two recursive calls on half-size problems, then do $n^2$ extra work to combine results."

### 2️⃣ Recursion Tree Analysis

Let's see work distribution by level:

```
Level 0: 1 node work = n²           → total: n²
Level 1: 2 nodes work = (n/2)² each → total: 2·(n/2)² = n²/2
Level 2: 4 nodes work = (n/4)² each → total: 4·(n/4)² = n²/4
Level 3: 8 nodes work = (n/8)² each → total: 8·(n/8)² = n²/8
...
```

**Observation:**
- At each level $i$: Work = $2^i \cdot (n/2^i)^2 = n^2 / 2^i$
- Number of levels = $\log_2 n$
- **Work is NOT constant per level** — it decreases!

**Total work:**
$$T(n) = n^2 + \frac{n^2}{2} + \frac{n^2}{4} + \frac{n^2}{8} + \dots$$

This is a geometric series:
$$T(n) = n^2 \left(1 + \frac{1}{2} + \frac{1}{4} + \frac{1}{8} + \dots\right)$$

The sum converges to 2:
$$T(n) = n^2 \cdot 2 = 2n^2$$

✅ **T(n) = Θ(n²)**

**Key insight:** The **first level dominates** because it has the most work (n²). All other levels combined don't exceed n². So we just look at the top level.

### 3️⃣ Master Theorem Application

For:
$$T(n) = aT(n/b) + f(n)$$

**Identify parameters:**
- $a = 2$ (2 subproblems)
- $b = 2$ (size reduction factor)
- $f(n) = n^2$ (extra work)

**Step 1: Calculate $n^{\log_b a}$**
$$n^{\log_2 2} = n^1 = n$$

**Step 2: Compare $f(n)$ with $n^{\log_b a}$**
- $f(n) = n^2$
- $n^{\log_b a} = n^1$
- $\Rightarrow n^2 > n$ (f(n) **grows faster**)

**Step 3: Apply Case 3 (f(n) dominates)**

When $f(n)$ grows faster than $n^{\log_b a}$:
$$T(n) = \Theta(f(n)) = \Theta(n^2)$$

### 4️⃣ Why the Top Level Dominates

This is **Abdo's key message** in this lecture:

When combining work ($f(n)$) is **much larger** than the recursive structure ($n^{\log_b a}$), the combining work **dominates everything**.

Consider:
- Level 0 (top): $n^2$ work
- Level 1: $n^2/2$ work
- Levels 2 onwards: even less work
- **Total:** Less than $2n^2$

So the complexity is determined by the **most expensive level**, which is the top: **Θ(n²)**.

### 5️⃣ Intuition

| Aspect | Analysis |
|--------|----------|
| Number of levels | $\log n$ (tree is shallow) |
| Work at top level | $n^2$ (very expensive) |
| Work per doubling | Halves each level |
| Which level dominates? | **Top level** |
| Final complexity | $\Theta(n^2)$ |

**Abdo's takeaway:**
> "When combining is expensive, it doesn't matter how many levels you have. The top dominates."

### 6️⃣ Why this is Different from T(n) = 2T(n/2) + n

Compare these two:

| Recurrence | Extra Work | Work per Level | Dominates | Result |
|---|---|---|---|---|
| $T(n) = 2T(n/2) + n$ | $n$ | Constant across levels | **Stays same at each level, $\log n$ levels** | $\Theta(n \log n)$ |
| $T(n) = 2T(n/2) + n^2$ | $n^2$ | Decreases exponentially | **Top level only** | $\Theta(n^2)$ |

The **quadratic work** crushes the logarithmic growth!

### 7️⃣ Real-World Applications

This recurrence shows up in:
- **Matrix multiplication** (naive divide-and-conquer):
  - Split matrix into 4 quadrants
  - Do 8 multiplications
  - Combine results (expensive!)
- **2D range queries** with quadratic merging
- **Convolution** in signal processing with quadratic assembly

---

## Lecture 392: Master Theorem for Dividing Functions

This is the **crown jewel** of recurrence relation analysis. Abdul Bari teaches you a powerful formula that instantly gives time complexity for divide-and-conquer algorithms without expanding the recursion tree manually.

### Context: Why Master Theorem?

Dividing functions (divide-and-conquer) have the form:
$$T(n) = aT(n/b) + f(n)$$

This appears everywhere:
- **Merge Sort:** $T(n) = 2T(n/2) + n$ → $\Theta(n \log n)$
- **Binary Search:** $T(n) = T(n/2) + 1$ → $\Theta(\log n)$
- **Matrix Multiplication:** $T(n) = 2T(n/2) + n^2$ → $\Theta(n^2)$
- **Quick Sort:** $T(n) = 2T(n/2) + n$ → $\Theta(n \log n)$ (average case)

Instead of solving each one manually, **Master Theorem gives you a formula**.

### The Master Theorem Formula

For recurrence:
$$T(n) = aT(n/b) + f(n)$$

**Step 1: Identify parameters**
- $a$ = number of recursive subproblems
- $b$ = factor by which input size reduces
- $f(n)$ = non-recursive work (combination, merging, etc.)

**Step 2: Calculate the critical exponent**
$$n^{\log_b a}$$

This is the "balance point" — it compares recursive work with extra work.

**Step 3: Compare $f(n)$ with $n^{\log_b a}$**

### The Three Cases

#### Case 1: $f(n)$ is Polynomially Smaller

**Condition:**
$$f(n) = O(n^{\log_b a - \epsilon})$$

for some constant $\epsilon > 0$.

In plain English: *$f(n)$ grows slower than $n^{\log_b a}$ by a polynomial factor.*

**Result:**
$$T(n) = \Theta(n^{\log_b a})$$

**Intuition:** Recursive work dominates. Extra work is negligible.

**Example:** $T(n) = 2T(n/2) + 1$
- $\log_b a = \log_2 2 = 1$
- $f(n) = 1 = O(n^0)$, which is $O(n^{1-1}) = O(n^0)$ ✓
- $T(n) = \Theta(n)$

---

#### Case 2: $f(n)$ is Polynomially Equal

**Condition:**
$$f(n) = \Theta(n^{\log_b a})$$

In plain English: *$f(n)$ grows at the same rate as $n^{\log_b a}$.*

**Result:**
$$T(n) = \Theta(n^{\log_b a} \cdot \log n)$$

**Intuition:** Recursive work and extra work grow at the same rate. They add up logarithmically across levels.

**Example:** $T(n) = 2T(n/2) + n$
- $\log_b a = \log_2 2 = 1$
- $f(n) = n = \Theta(n^1)$ ✓
- Recursive and extra work both $\Theta(n)$ per level
- $\log_2 n$ levels
- $T(n) = \Theta(n \log n)$ ← **Merge Sort!**

---

#### Case 3: $f(n)$ is Polynomially Larger

**Condition:**
$$f(n) = \Omega(n^{\log_b a + \epsilon})$$

for some constant $\epsilon > 0$.

**Regularity Condition** (must also satisfy):
$$a \cdot f(n/b) \leq c \cdot f(n)$$

for some constant $c < 1$ and sufficiently large $n$.

In plain English: *$f(n)$ grows faster than $n^{\log_b a}$ by a polynomial factor, and satisfies regularity.*

**Result:**
$$T(n) = \Theta(f(n))$$

**Intuition:** Extra work dominates. Top level does most of the work.

**Example:** $T(n) = 2T(n/2) + n^2$
- $\log_b a = \log_2 2 = 1$
- $f(n) = n^2 = \Omega(n^{1+1})$ ✓
- Regularity: $2 \cdot (n/2)^2 = n^2/2 \leq c \cdot n^2$ for $c = 1/2$ ✓
- $T(n) = \Theta(n^2)$

---

### ⚠️ Important: Gaps Between Cases

Master Theorem **does NOT cover all cases**. There are gaps:

**Gap between Case 1 and 2:**
- If $f(n)$ is smaller than $n^{\log_b a}$ but **not polynomially** smaller
- Example: $f(n) = n^{\log_b a} / \log n$ → No case applies!

**Gap between Case 2 and 3:**
- If $f(n)$ is larger than $n^{\log_b a}$ but **not polynomially** larger
- Example: $f(n) = n^{\log_b a} \cdot \log n$ → No case applies!

**For gaps:** Use recursion tree method or recurrence relation expansion.

---

### 4️⃣ Step-by-Step Application

**General Approach:**

| Step | Action |
|------|--------|
| 1 | **Write the recurrence** in form $T(n) = aT(n/b) + f(n)$ |
| 2 | **Identify** $a$, $b$, and $f(n)$ |
| 3 | **Calculate** $\log_b a$ |
| 4 | **Compare** $f(n)$ with $n^{\log_b a}$ |
| 5 | **Choose case** (1, 2, or 3) and **apply the formula** |

**Let's work through an example:**

$T(n) = 3T(n/4) + n \log n$

| Step | Calculation |
|------|-------------|
| Identify | $a = 3$, $b = 4$, $f(n) = n \log n$ |
| Compare exponent | $\log_4 3 \approx 0.79$ |
|  | So $n^{\log_4 3} \approx n^{0.79}$ |
| Compare with $f(n)$ | $n \log n$ vs $n^{0.79}$ |
| | $n \log n$ is **larger** (polynomially) |
| Check regularity | $3 \cdot (n/4) \log(n/4) \leq c \cdot n \log n$ ✓ |
| Apply Case 3 | $T(n) = \Theta(n \log n)$ |

---

### 5️⃣ Quick Reference: Common Recurrences

| Recurrence | Parameters | $\log_b a$ | Case | Result |
|---|---|---|---|---|
| $T(n)=T(n/2)+1$ | $a=1, b=2$ | $0$ | 2 | $\Theta(\log n)$ |
| $T(n)=2T(n/2)+n$ | $a=2, b=2$ | $1$ | 2 | $\Theta(n \log n)$ |
| $T(n)=2T(n/2)+1$ | $a=2, b=2$ | $1$ | 1 | $\Theta(n)$ |
| $T(n)=2T(n/2)+n^2$ | $a=2, b=2$ | $1$ | 3 | $\Theta(n^2)$ |
| $T(n)=4T(n/2)+n$ | $a=4, b=2$ | $2$ | 1 | $\Theta(n^2)$ |
| $T(n)=4T(n/2)+n^2$ | $a=4, b=2$ | $2$ | 2 | $\Theta(n^2 \log n)$ |
| $T(n)=4T(n/2)+n^3$ | $a=4, b=2$ | $2$ | 3 | $\Theta(n^3)$ |

---

### 6️⃣ Why Master Theorem Works (Abdo's Wisdom)

The key insight is about **level dominance** in the recursion tree:

**Case 1 (Recursive dominates):**
- Work decreases as we go down levels
- Top level has most work: $a \cdot f(n/b) < f(n)$ at each level
- Base case level has $\Theta(n^{\log_b a})$ nodes
- Total: dominated by base level

**Case 2 (Balanced):**
- Work stays roughly the same across levels
- $\log n$ levels each doing $\Theta(n^{\log_b a})$ work
- Total: $\log n$ times $n^{\log_b a}$

**Case 3 (Extra work dominates):**
- Work decreases down the tree, but slowly
- Top level has most work: $f(n)$
- All other levels combined don't exceed top level
- Total: dominated by $f(n)$

---

### 7️⃣ Real-World Algorithm Examples

**Merge Sort: $T(n) = 2T(n/2) + n$**
- Case 2 → $\Theta(n \log n)$
- Balanced: doubling calls, but merging stays linear per level

**Binary Search: $T(n) = T(n/2) + 1$**
- Case 2 → $\Theta(\log n)$
- Only one call, constant work

**Naive Matrix Multiplication: $T(n) = 8T(n/2) + n^2$**
- $\log_2 8 = 3$
- $n^3$ vs $n^2$ → Case 1
- $T(n) = \Theta(n^3)$ (no improvement over naive!)

**Strassen's Algorithm: $T(n) = 7T(n/2) + n^2$**
- $\log_2 7 \approx 2.81$
- $n^{2.81}$ vs $n^2$ → Case 1
- $T(n) = \Theta(n^{2.81})$ (faster!)

---

## Quick Master Theorem Reference (Summary from Lecture 392)

For recurrence $T(n) = aT(n/b) + f(n)$, calculate $\log_b a$ and compare with $f(n)$:

| Case | Condition | Result |
|------|-----------|--------|
| Case 1 | $f(n) = O(n^{\log_b a - \epsilon})$ | $\Theta(n^{\log_b a})$ |
| Case 2 | $f(n) = \Theta(n^{\log_b a})$ | $\Theta(n^{\log_b a} \log n)$ |
| Case 3 | $f(n) = \Omega(n^{\log_b a + \epsilon})$ | $\Theta(f(n))$ |

**For the detailed explanation, see Lecture 392 above.**

---

## Abdul Bari's Core Intuition (THIS IS GOLD)

1. **Tree height** = $\log n$
2. **Count work per level**
3. **See which level dominates**

That's it. No magic.

---

## One table you should memorize

| Recurrence | Time |
|------------|------|
| $T(n)=T(n/2)+1$ | $\Theta(\log n)$ |
| $T(n)=T(n/2)+n$ | $\Theta(n)$ |
| $T(n)=2T(n/2)+1$ | $\Theta(n)$ |
| $T(n)=2T(n/2)+n$ | $\Theta(n \log n)$ |
| $T(n)=2T(n/2)+n^2$ | $\Theta(n^2)$ |

---

## Final brain-switch

When you see division:

1. **"How many levels? → $\log n$"**
2. **"What's the work per level?"**

Answer those two and the RR solves itself.

