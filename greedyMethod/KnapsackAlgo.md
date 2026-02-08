# Fractional Knapsack — Why Greedy Works Here (And Where It Fails)

## Abdo's Core Message

> "Take the item with **maximum profit per unit weight** first."

**If you understand why that works, you understood the lecture.**

This single lesson teaches the difference between **greedy algorithms that are provably optimal** and **greedy that fails catastrophically.**

---

## Part 1: The Problem Statement — Optimization Under Constraint

### What Is the Knapsack Problem?

You have:
- **n objects** (items)
- Each object **i** has:
  - **Profit (value):** `p[i]`
  - **Weight:** `w[i]`
- **Knapsack capacity:** `M` (weight limit)

**Goal:** Maximize total profit while staying within weight limit M.

### Real-World Examples

```
1. BACKPACKING TRIP
   - Knapsack capacity: 15 kg
   - Items: tent (2kg, value 50), sleeping bag (3kg, value 80), 
            food (5kg, value 40), water (2kg, value 30)
   - Problem: What should you pack to maximize value?

2. CARGO PLANE
   - Capacity: 5000 kg
   - Cargo items of different weights and values
   - Load to maximize profit

3. DATA CENTER MIGRATION
   - Server capacity: 32 GB RAM
   - Processes with different memory and priority
   - Schedule to maximize performance

4. INVESTMENT PORTFOLIO
   - Budget: $10,000
   - Stocks with different prices and expected returns
   - Buy to maximize returns
```

### The Constraint Is Critical

```
❌ WITHOUT constraint (unlimited capacity):
   Just take everything → Easy, not interesting

✅ WITH constraint (limited capacity):
   Must choose WHICH items → Optimization problem
```

The constraint transforms this from trivial to interesting.

---

## Part 2: Why This Is an Optimization Problem (Not Just Search)

### Three Types of Knapsack Problems

| Type | Constraint | Question | Difficulty |
|------|-----------|----------|-----------|
| **Fractional** | Can take fractions | What's the max any profit? | Easy (Greedy works) |
| **0/1** | Take whole or nothing | What's the max profit? | Hard (Need DP) |
| **Unbounded** | Can take multiple copies | What's the max profit? | Hard (Need DP) |

### Why "Optimization"?

```
DECISION PROBLEM:
  "Can we achieve profit ≥ 100?"
  Answer: YES or NO

SEARCH PROBLEM:
  "Find any set of items worth $100"
  Answer: Some set of items

OPTIMIZATION PROBLEM:
  "Find the MAXIMUM possible profit"
  Answer: Specific best solution + value

Optimization is HARDEST of the three.
```

---

## Part 3: The Greedy Strategy — Fractional Knapsack

### Understanding "Fractional"

**Key allowance:** You can take **partial items**.

```
Example:
  Item A weighs 10 kg, worth $100
  Remaining capacity: 3 kg
  
  Fractional knapsack: Take 3/10 of item A
                      Weight: 3 kg ✓
                      Profit: (3/10) × $100 = $30

  0/1 Knapsack: Can't take it (must take whole or nothing)
                Skip item A
```

This small difference changes EVERYTHING about the algorithm.

### The Greedy Approach

```
STRATEGY: Always take the item with HIGHEST profit per unit weight.

Steps:

1. Calculate ratio for each item:
   ratio[i] = p[i] / w[i]

2. Sort items by ratio (descending)

3. Greedily take items in order:
   - If item fits completely → take all of it
   - If item partially fits → take the fraction that fits
   - If no space left → stop
```

### Why This Strategy?

**Intuition:**
```
If items with higher profit/weight ratio are available,
taking them first maximizes bang-for-buck.

Fractions allow perfect packing.
```

**Mathematical insight:**
```
You want to maximize:
  profit = Σ (fraction[i] × p[i])

Subject to:
  Σ (fraction[i] × w[i]) ≤ M
  0 ≤ fraction[i] ≤ 1

Greedy solution: Take items in order of p[i]/w[i] until full.
```

---

## Part 4: Algorithm Walkthrough — Step by Step

### Step 1: Calculate Profit/Weight Ratios

```
For each object i:
  ratio[i] = p[i] / w[i]
```

**Example:**

```
Objects:
  Item A: p=60,  w=10  → ratio = 60/10  = 6.0
  Item B: p=100, w=20  → ratio = 100/20 = 5.0
  Item C: p=120, w=30  → ratio = 120/30 = 4.0

Knapsack capacity: M = 50
```

### Step 2: Sort by Ratio (Descending)

```
After sorting by profit/weight ratio (highest first):

  Position 1: Item A (ratio = 6.0)
  Position 2: Item B (ratio = 5.0)
  Position 3: Item C (ratio = 4.0)
```

The item with BEST bang-for-buck comes first.

### Step 3: Initialize Variables

```
total_profit = 0
remaining_capacity = M = 50
```

### Step 4: Greedily Pick Objects

```
Iteration 1: Process Item A
  Weight of A: 10 kg
  Check: Can Item A fit?
    10 ≤ 50?  YES ✓
  Action: Take ENTIRE item
    total_profit = 0 + 60 = 60
    remaining_capacity = 50 - 10 = 40

Iteration 2: Process Item B
  Weight of B: 20 kg
  Check: Can Item B fit?
    20 ≤ 40?  YES ✓
  Action: Take ENTIRE item
    total_profit = 60 + 100 = 160
    remaining_capacity = 40 - 20 = 20

Iteration 3: Process Item C
  Weight of C: 30 kg
  Check: Can Item C fit?
    30 ≤ 20?  NO ✗
  Action: Take FRACTION
    Fraction to take: 20/30 = 0.667 (two-thirds)
    Profit from fraction: 0.667 × 120 = 80
    total_profit = 160 + 80 = 240
    remaining_capacity = 20 - 20 = 0

Iteration 4: No capacity left
  STOP
```

### Step 5: Output Result

```
Final Answer:
  Maximum profit = 240
  
  Selection:
    - All of Item A (weight 10, profit 60)
    - All of Item B (weight 20, profit 100)
    - 2/3 of Item C (weight 20, profit 80)
  
  Total weight: 10 + 20 + 20 = 50 ✓ (exactly at capacity)
  Total profit: 60 + 100 + 80 = 240
```

---

## Part 5: Pseudocode Implementation

### Algorithm

```
algorithm FractionalKnapsack(items, capacity):
    
    INPUT:
      items: array of [profit, weight]
      capacity: knapsack capacity M
    
    OUTPUT:
      maximum_profit
    
    // STEP 1: Calculate ratios
    for i = 0 to n-1:
        ratio[i] = profit[i] / weight[i]
    
    // STEP 2: Create array of (ratio, profit, weight, index)
    items_with_ratio = []
    for i = 0 to n-1:
        items_with_ratio.append((ratio[i], profit[i], weight[i]))
    
    // STEP 3: Sort by ratio descending
    sort(items_with_ratio) by ratio descending
    
    // STEP 4: Greedy selection
    total_profit = 0
    remaining_capacity = capacity
    
    for each item in items_with_ratio:
        ratio, profit, weight = item
        
        if weight <= remaining_capacity:
            // Item fits completely
            total_profit += profit
            remaining_capacity -= weight
        else:
            // Item partially fits
            fraction = remaining_capacity / weight
            total_profit += profit * fraction
            remaining_capacity = 0
            break  // Knapsack is full
    
    // STEP 5: Return result
    return total_profit


-------------
algo_knapsack(double obj[][] , int n, int m){
sort(obj, n)
double profit = 0
for(int i = 0 ; i < n ; i++){
    if(obj[][] <= m){
        profit += obj[][]
        m=m-obj[][]
    } else{
        profit += obj[][] * m/obj[][]
        break
    }
}
return profit
}

--------------

```

### C Implementation

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float profit;
    float weight;
    float ratio;
} Item;

// Comparator for sorting (descending by ratio)
int compare(const void *a, const void *b) {
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    if (item1->ratio < item2->ratio) return 1;   // descending
    if (item1->ratio > item2->ratio) return -1;
    return 0;
}

float FractionalKnapsack(Item *items, int n, float capacity) {
    // Calculate ratios
    for (int i = 0; i < n; i++) {
        items[i].ratio = items[i].profit / items[i].weight;
    }
    
    // Sort by ratio (descending)
    qsort(items, n, sizeof(Item), compare);
    
    // Greedy selection
    float total_profit = 0.0;
    float remaining = capacity;
    
    for (int i = 0; i < n && remaining > 0; i++) {
        if (items[i].weight <= remaining) {
            // Take entire item
            total_profit += items[i].profit;
            remaining -= items[i].weight;
            printf("Take all of item %d: profit=%f\n", i, items[i].profit);
        } else {
            // Take fraction
            float fraction = remaining / items[i].weight;
            total_profit += items[i].profit * fraction;
            printf("Take %.2f of item %d: profit=%f\n", 
                   fraction, i, items[i].profit * fraction);
            remaining = 0;
        }
    }
    
    return total_profit;
}

// Driver
int main() {
    Item items[] = {
        {60, 10, 0},   // profit=60, weight=10
        {100, 20, 0},  // profit=100, weight=20
        {120, 30, 0}   // profit=120, weight=30
    };
    int n = 3;
    float capacity = 50;
    
    float max_profit = FractionalKnapsack(items, n, capacity);
    printf("Maximum profit: %f\n", max_profit);
    
    return 0;
}
```





---

## Part 6: Complexity Analysis

### Time Complexity

```
Step 1: Calculate ratios
  → O(n)

Step 2: Sort by ratios
  → O(n log n)

Step 3: Greedy selection
  → O(n)

Total: O(n log n)
  (dominated by sorting)
```

**Practical implication:**
- For 1 million items: ~20 million operations (very fast)
- Sorting is the bottleneck, not the greedy selection

### Space Complexity

```
Storage:
  - items array: O(n)
  - ratio array: O(n)
  - Temporary variables: O(1)

Total: O(n)
```

---

## Part 7: Why Greedy Works Here — The Proof

### The Key Question

> "Is the greedy choice property satisfied?"
> (Does taking highest ratio item guarantee optimality?)

### Proof by Exchange Argument

**Claim:** The greedy solution is optimal.

**Proof:**

Suppose the greedy solution is NOT optimal.

Then there exists an optimal solution OPT where:
- OPT does NOT include the item with highest ratio
- OPT includes some item with lower ratio instead

**Construct a better solution:**

Since fractional knapsack allows fractions:
1. Remove the lower-ratio item from OPT
2. Add the highest-ratio item instead (in the same weight amount)
3. This increases profit (higher ratio = more profit per weight)
4. So OPT was not actually optimal — contradiction!

**Therefore:** Greedy must be optimal. QED.

### Why Fractions Are Essential

```
This proof ONLY works because we can take fractions.

If we couldn't take fractions (0/1 knapsack):
  - We couldn't make the exchange above
  - The proof breaks down
  - Greedy fails!
```

---

## Part 8: Why Greedy FAILS for 0/1 Knapsack

### The Critical Difference

```
FRACTIONAL: "Your knapsack is like a liquid — 
             you can pour in any amount."
             → Greedy works ✓

0/1:         "Your knapsack holds whole items only — 
             take it or leave it."
             → Greedy FAILS ✗
```

### Counterexample

```
Items:
  A: profit=6,  weight=3,  ratio=2.0
  B: profit=5,  weight=2,  ratio=2.5 ← Higher ratio!
  C: profit=5,  weight=2,  ratio=2.5 ← Same ratio!
  
Capacity: 5 kg

GREEDY (by ratio):
  1. Take B (ratio 2.5): profit=5, weight=2, remaining=3
  2. Try A (ratio 2.0): weight=3, fits!
     Take A: profit+=6, weight=3, total_profit=11, remaining=0
  3. Try C: doesn't fit
  
  Greedy result: profit = 11

OPTIMAL:
  Take B+C (both ratio 2.5): 
    profit = 5+5 = 10
    weight = 2+2 = 4
    remaining = 1
  Can't fit A (weight 3)
  
  vs. Greedy's 11?
  
  Let me try different example...

ACTUAL COUNTEREXAMPLE:

Items:
  A: profit=10, weight=6,   ratio=1.67
  B: profit=9,  weight=5,   ratio=1.8  ← Higher ratio
  C: profit=8,  weight=5,   ratio=1.6
  
Capacity: 11

GREEDY (by ratio):
  1. Take B (ratio 1.8): profit=9, weight=5, remaining=6
  2. Try A (ratio 1.67): weight=6, fits!
     Take A: profit+=10, total=19, weight=11, remaining=0
  
  Greedy result: profit = 19, weight = 11 ✓

ALTERNATIVE:
  Take C+B: profit=8+9=17, weight=5+5=10 ✓
  
Greedy still wins...

Let me use the CLASSIC 0/1 counterexample:

Items:
  A: profit=11, weight=5,  ratio=2.2
  B: profit=9,  weight=4,  ratio=2.25 ← Higher ratio!
  C: profit=9,  weight=4,  ratio=2.25
  
Capacity: 8

GREEDY (by ratio B):
  1. Take B (ratio 2.25): profit=9, weight=4, remaining=4
  2. Take C (ratio 2.25): profit+=9, total=18, weight=8, remaining=0
  
  Greedy result: profit = 18

ALTERNATIVE:
  Take A: profit=11, weight=5, remaining=3
  Take nothing else that fits
  
  Alternative: profit = 11 (worse than 18)

Hmm, still greedy wins.

ACTUALLY WORKING COUNTEREXAMPLE:

Items:
  A: profit=50, weight=10, ratio=5.0   ← HIGHEST ratio
  B: profit=40, weight=9,  ratio=4.44
  C: profit=40, weight=9,  ratio=4.44
  
Capacity: 18

GREEDY (by ratio A):
  1. Take A (ratio 5.0): profit=50, weight=10, remaining=8
  2. Try B (ratio 4.44): weight=9, doesn't fit remaining 8
  3. Try C (ratio 4.44): weight=9, doesn't fit remaining 8
  
  Greedy result: profit = 50, weight = 10

OPTIMAL:
  Take B+C: profit=40+40=80, weight=9+9=18 ✓
  
Greedy: 50
Optimal: 80 ✓✓✓ GREEDY IS WRONG BY FACTOR OF 1.6!
```

### Why This Happens

```
The greedy choice (take A because of highest ratio)
BLOCKS the better choice (take B+C combination).

With fractions, we can take partial C to fill remaining space.
Without fractions (0/1), we're stuck with wasted capacity.

This is why 0/1 knapsack REQUIRES DYNAMIC PROGRAMMING.
```

---

## Part 9: Time Complexity Comparison

### Comparison: Fractional vs. 0/1

| Aspect | Fractional | 0/1 |
|--------|-----------|-----|
| **Algorithm** | Greedy | Dynamic Programming |
| **Time** | O(n log n) | O(n·M) |
| **Space** | O(n) | O(n·M) |
| **Implementation** | Easy | Medium |
| **Correctness** | Provably optimal | Provably optimal |
| **Speed** | Very fast | Much slower |

For capacity M = 1000, n = 100:
- Fractional: ~700 operations (fast!)
- DP: ~100,000 operations (slower)

But DP gives optimal answer for 0/1, greedy doesn't.

---

## Part 10: Why This Matters — Real Applications

### Where Fractional Knapsack Applies

```
1. LIQUID CARGO (oil, water, chemicals)
   - Can load partial containers
   - Goal: Maximize value with truck capacity
   - Greedy works!

2. MINING RESOURCE EXTRACTION
   - Can process partial ore batches
   - Different ores, different profits/weight
   - Choose ores by profit/weight ratio

3. CAPITAL ALLOCATION (stocks)
   - Can buy partial shares
   - Different expected returns per dollar
   - Allocate budget to maximize return

4. BANDWIDTH ALLOCATION
   - Can allocate partial bandwidth to streams
   - Different priority per unit bandwidth
   - Stream by priority ratio
```

### Where 0/1 Knapsack Applies

```
1. BACKPACKING: Can't take "half a tent"
2. JOB SCHEDULING: Can't do "half a job"
3. EQUIPMENT SELECTION: Can't take "half a computer"
4. COMMITTEE SELECTION: Can't hire "half a person"
```

Functionally important distinction!

---

## Part 11: Understanding Progression

| Level | Can Do |
|-------|--------|
| **Surface** | Describe greedy strategy (highest ratio first) |
| **Deeper** | Implement algorithm with code |
| **Deep** | Trace example and compute answer |
| **Mastery** | Explain why greedy works (exchange argument) |
| **Expert** | Construct counterexample for 0/1 knapsack |

---

## Part 12: Interview Approach

### What To Say

✓ "This is a fractional knapsack problem where greedy works"

✓ "I'll sort by profit/weight ratio and greedily pick items"

✓ "Time complexity is O(n log n) due to sorting"

✓ "For 0/1 variant, greedy fails — need dynamic programming"

✓ "I can prove greedy is optimal using exchange argument"

### What NOT To Say

✗ "I'll just pick high-profit items"

✗ "Greedy always works for knapsack"

✗ "I don't know why it's optimal, it just is"

✗ "My solution runs in O(n) with no sorting"

### How To Distinguish Yourself

In an interview:

1. **Clarify the problem** — "Is this fractional or 0/1?"
2. **Choose algorithm** — "Greedy for fractional, DP for 0/1"
3. **Explain reasoning** — "Because fractional allows fractions"
4. **Prove optimality** — "By exchange argument..."
5. **Discuss complexity** — "Sorting dominates: O(n log n)"

This shows **deep algorithmic thinking.**

---

## Part 13: Connection to Larger Ideas

### What This Teaches Beyond Knapsack

#### 1. **Greedy Choice Property**
- Not all problems benefit from greedy
- Must prove property holds
- Fractional knapsack has it ✓
- 0/1 knapsack doesn't ✗

#### 2. **Optimal Substructure**
- After taking first item, remaining problem is still knapsack
- Greedy choice leaves subproblem solvable
- Both properties needed!

#### 3. **Algorithm Distinction** 
- Same problem with small variation (fraction allowed)
- One has simple greedy solution
- One requires complex DP solution
- Shows importance of problem specifics

#### 4. **Why DP Exists**
- When greedy fails (0/1), use DP
- This is next chapter—learn DP as greedy's "fix"
- DP is slower but more general

---

## Part 14: Practice Problems

### Compute These Examples

**Example 1: Simple**
```
Items:  (profit, weight)
  A: (12, 2)
  B: (10, 3)
  C: (20, 4)
  
Capacity: 7

Task: 
  1. Compute ratios
  2. Sort
  3. Apply greedy
  4. Find maximum profit
```

**Example 2: Tricky Ratios**
```
Items:  (profit, weight)
  A: (30, 5)
  B: (28, 4)
  C: (50, 10)
  
Capacity: 9

Task:
  1. Which item has highest ratio?
  2. In what order will greedy pick?
  3. Will any items be fractional?
```

**Example 3: Fractional Necessity**
```
Items:  (profit, weight)
  A: (10, 3)
  B: (20, 6)
  
Capacity: 5

Task:
  1. Can you take both whole items? (3+6=9 > 5)
  2. What fraction of B can you take?
  3. Final profit?
```

---

## Part 15: Proof Techniques

### Exchange Argument (How to Prove Greedy)

**General approach:**

```
Theorem: Greedy algorithm produces optimal solution.

Proof by contradiction:

1. Assume greedy solution G is NOT optimal
2. Let O be an optimal solution different from G
3. Find first position where G and O differ
4. Show that swapping at this position improves O
   (or at least doesn't hurt it)
5. Repeat until O becomes G
6. Therefore G must be optimal

Contradiction! QED.
```

### For Fractional Knapsack Specifically

```
1. Assume greedy picks items in order of ratio p/w
2. Assume there's a better solution OPT
3. OPT must include some item with lower ratio
4. But we can replace that item with one with higher ratio
5. This increases profit (same weight, more value)
6. So OPT wasn't actually optimal

Therefore greedy IS optimal.
```

---

## Part 16: Key Takeaways

| Concept | Remember |
|---------|----------|
| **Fractional Knapsack** | Can take partial items |
| **0/1 Knapsack** | Take whole or nothing |
| **Greedy Strategy** | Highest profit/weight ratio first |
| **Greedy Works** | For fractional (provably optimal) |
| **Greedy Fails** | For 0/1 (needs DP instead) |
| **Proof** | By exchange argument |
| **Time** | O(n log n) for sorting |
| **When To Use** | Only when greedy property holds |

---

## Part 17: Real-World Impact

### Where This Reasoning Matters

**Fractional Knapsack teaches:**
1. **Resource allocation** — How to distribute when partial allocation is possible
2. **Prioritization** — Ratio-based approach generalizes widely
3. **Optimality proofs** — Why some greedy strategies work

**0/1 Knapsack teaches:**
1. **Discrete optimization** — Harder than continuous
2. **Need for DP** — When greedy fails
3. **Problem structure matters** — Small change, big difference

### Where Companies Use This

- **Hadoop/Spark:** Data allocation to resources
- **Databases:** Query optimization (choosing which indexes)
- **Load balancers:** Request routing (highest priority first)
- **Airlines:** Overbooking optimization (fractional seats)

All use ratio-based greedy thinking when conditions allow.

---

## Part 18: Final Wisdom from Abdo

### The Real Lesson

This isn't really about "packing a knapsack."

This is about:**understanding when a simple greedy strategy works.**

### Two Principles

1. **Greedy is tempting because it's fast**
   - Always think: "Is this provably optimal?"
   - Many problems look solvable by greedy but aren't

2. **One constraint change changes everything**
   - Fractional vs. 0/1: same goal, different solution
   - This is why problem definition is critical

### The Meta-Lesson

> "Before coding, ask: **Does this problem have the greedy choice property?**"

This separates:
- **Practitioners** — Code first, optimize later
- **Engineers** — Think first, code once

---

## References & Next Reading

- **Prerequisite:** Understand Big-O, ratios, sorting
- **Next:** 0/1 Knapsack with Dynamic Programming (see DP section)
- **Related:** Other greedy problems (Huffman, MST, Dijkstra)
- **Advanced:** Approximation algorithms (when even DP is too slow)

---

## One-Line Summary (Exam Gold)

> "Fractional knapsack: sort by profit/weight ratio, greedily pick items — greedy works because fractions let us perfectly fill capacity."

OR more concisely:

> "Take items by ratio, fractions = optimal."

If you can explain the word "fractions" is critical, you've mastered this lecture.
