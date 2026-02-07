# Greedy Method & Optimization Problems — When Fast Isn't Always Right

## Abdo's Core Message

> "Fast algorithms are useless if they are wrong."

**Greedy algorithms are fast because they don't look back — and dangerous for the same reason.**

This lecture teaches **when to trust greedy thinking and when to reject it.**

---

## Part 1: Optimization Problems — The Real Starting Point

### What Abdo Starts With (Not Algorithms)

Abdo does **NOT** introduce greedy algorithms first.

He starts by defining a **type of problem**:

```
An OPTIMIZATION PROBLEM is one where:
  - You have MANY possible solutions
  - Each solution has a VALUE (cost, profit, distance, time, etc.)
  - You want the BEST possible solution
```

### Why Start Here?

Many students conflate:
- **Decision problems:** "Is there a solution?" (Yes/No)
- **Search problems:** "Find any solution" (Any works)
- **Optimization problems:** "Find the BEST solution" (Specific)

These are fundamentally different:

| Problem Type | Question | Example | Difficulty |
|--------------|----------|---------|-----------|
| **Decision** | Does a solution exist? | "Can we visit all cities?" | Often NP-complete |
| **Search** | Find any solution | "Find any path from A to B" | Usually easier |
| **Optimization** | Find the BEST solution | "Find SHORTEST path from A to B" | Usually hardest |

**Abdo's point:** Optimization problems are fundamentally harder because you can't just find *any* solution—you need the *best* one.

### Real-World Examples

```
Minimize cost / time:
  - Route trucks most efficiently (delivery optimization)
  - Schedule employees with minimum payroll
  - Pack items in fewest boxes
  - Choose smallest subset of items with required properties

Maximize profit / utility:
  - Maximize value of items in knapsack
  - Maximize coverage with minimum transmitters
  - Maximize customer satisfaction within budget
  - Select stocks to maximize return
```

All are **optimization problems.**

---

## Part 2: The Two Fundamental Approaches

### Abdo's Classification

When faced with an optimization problem, there are fundamentally two strategies:

### Strategy 1️⃣: Exhaustive / Brute Force

```
"Try EVERYTHING and pick the best."
```

**How it works:**
```python
best_solution = None
best_value = infinity

for each possible solution:
    calculate its value
    if value is better:
        best_solution = this solution
        best_value = value

return best_solution
```

**Guarantees:**
- ✅ Always optimal
- ✅ Always correct
- ✅ Works for ANY problem

**Reality:**
- ❌ Exponential time (usually)
- ❌ Impossible for realistic input sizes
- ❌ 2^n or n! possibilities

**When this is viable:**
- Very small inputs (n < 20)
- Proof-of-concept
- When optimality is critical and speed doesn't matter

### Strategy 2️⃣: Smart Strategies (Greedy, DP, Backtracking)

```
"Use problem structure to skip most solutions."
```

**Examples:**
- **Greedy:** Make the locally best choice each step
- **Dynamic Programming:** Build solutions bottom-up, remembering past decisions
- **Backtracking:** Explore smartly, prune dead-ends

**Guarantees:**
- ✅ Usually fast (polynomial time)
- ✅ Practical for real inputs
- ❌ Optimal? **DEPENDS on the problem**

**The Trade-off:**

```
SPEED vs. OPTIMALITY

Exhaustive:   Slow but always optimal
Greedy:       Fast but sometimes wrong
DP:           Medium speed, often optimal
Backtracking: Medium speed, optimal but slow on hard cases
```

---

## Part 3: What "Greedy" Really Means

### Not What You Think

Greedy does **NOT** mean:

```
❌ Careless
❌ Lazy
❌ Random
❌ "Just pick anything"
```

### What It Actually Means

```
Greedy Algorithm:

At EVERY STEP:
  1. Look at available IMMEDIATE choices
  2. Pick the BEST one by some criterion
  3. Commit to that choice
  4. Move to next step
  5. Repeat
```

**Key insight:** "Best by some criterion" is explicitly defined and systematic.

### Example: Greedy for Minimum Coins

**Problem:** Make $0.41 using fewest coins
- Available: 25¢, 10¢, 5¢, 1¢

**Greedy approach:**
```
Step 1: What's the biggest coin that fits? 25¢
        Take 1 × 25¢  (Remaining: 16¢)

Step 2: What's the biggest coin that fits? 10¢
        Take 1 × 10¢  (Remaining: 6¢)

Step 3: What's the biggest coin that fits? 5¢
        Take 1 × 5¢   (Remaining: 1¢)

Step 4: What's the biggest coin that fits? 1¢
        Take 1 × 1¢   (Remaining: 0¢)

Result: 4 coins (25+10+5+1)
Optimal: 4 coins ✓ (CORRECT in this case)
```

**But what if coins were {25, 10, 1}?**

```
Greedy:     25 + 10 + 1 + 1 + 1 + 1 + 1 + 1 + 1 = 9 coins ❌
Optimal:    10 + 10 + 10 + 10 + 1 = 5 coins ✓
```

**The lesson:** Greedy feels smart but **guarantees nothing.**

---

## Part 4: The Whiteboard Rule — Greedy Never Changes Its Mind

### The Core Principle

Abdo repeatedly emphasizes (even if implicitly):

```
A greedy algorithm IS COMMITTED to its choices.

Once made:
  ✅ FINAL
  ✅ NEVER RECONSIDERED
  ✅ NO BACKTRACKING
```

This is why greedy is fast AND why it fails.

### Visual Comparison

```
EXHAUSTIVE (Backtracking):
  Step 1: Try choice A
    Step 2: Try choice X
      Step 3: Try choice 1
        Dead end? BACKTRACK
      Step 3: Try choice 2
        Dead end? BACKTRACK
    Step 2: Try choice Y
  Step 1: Try choice B
  ... explore ALL branches

GREEDY:
  Step 1: Pick BEST local choice (say A)
    Step 2: Pick BEST local choice (say X)
      Step 3: Pick BEST local choice (say 1)
        Not optimal? TOO BAD, committed!
  Done. (1 path explored)
```

### Why This Matters

```
≠ Greedy is FAST (single path, no backtracking)
✓ Greedy can be WRONG (might miss better path)
```

Example: Navigation in maze
```
GREEDY:    "Always move closer to exit"
           → Might hit dead end (committed!)

BACKTRACKING: "Try paths, backtrack if stuck"
              → Always finds exit
```

---

## Part 5: Why Greedy Feels So Attractive

### The Seduction of Speed

Greedy algorithms typically have:
- **Time:** O(n log n) or O(n)
- **Logic:** Very clean and intuitive
- **Implementation:** Short code, few bugs
- **Explanation:** Easy to understand ("pick the best locally")

### Why Engineers Love It

In industry:
- Code that works quickly wins
- Time-to-market matters
- Greedy is easy to code and explain

**The danger:** Engineers might deploy greedy solutions that **look right but are subtly wrong.**

### Real Examples of Hidden Greedy Failures

```
1. NETWORK ROUTING
   Greedy: Always use fastest link
   Problem: Network congestion → slower overall
   Solution: Load balancing (non-greedy)

2. CACHING
   Greedy: Remove least-recently-used
   Problem: Not always optimal
   Solution: Offline algorithms (see future)

3. SCHEDULING
   Greedy: Schedule shortest jobs first
   Problem: Works for some metrics, fails for others
   Solution: Check the specific problem

4. RESOURCE ALLOCATION
   Greedy: Give to whoever needs most
   Problem: Might starve other processes
   Solution: Fairness constraints
```

---

## Part 6: The Critical Question — When Does Greedy Work?

### Abdo's Core Teaching

Every time you consider greedy, ask:

```
❓ "Is the greedy choice guaranteed to lead 
    to the OPTIMAL solution?"
```

**Answer: YES?**  → Greedy is SAFE ✅

**Answer: NO?**   → Greedy is DANGEROUS ❌

**Answer: MAYBE?** → Need to PROVE it ⚠️

### Examples

#### Example 1: Fractional Knapsack ✅

**Problem:** Pack a knapsack (capacity W) with items of different weights/values. Can take fractions of items. Maximize total value.

**Greedy approach:** Sort items by value/weight ratio, take as much as possible of best ratio.

```
Items:    value/weight
  A:      10/2 = 5.0
  B:      6/3  = 2.0
  C:      8/4  = 2.0
Capacity: 7

Greedy: Take all of A (2 weight, 10 value)
        Take 5 of B (5 weight, 10 value)
        Total: 7 weight, 20 value ✓

Why optimal? Because fractions allow us to always fill
remaining capacity with item with best ratio. Proved.
```

**Greedy works here:** ✅

#### Example 2: 0/1 Knapsack ❌

**Problem:** Pack a knapsack with items. Can take WHOLE item or nothing (no fractions). Maximize total value.

**Greedy attempt:** Sort by value/weight ratio.

```
Items:      value/weight
  A:        10/5 = 2.0
  B:        6/1  = 6.0
  C:        8/5  = 1.6
Capacity:   6

Greedy: Take all of B (1 weight, 6 value)
        Can't take A (5 weight, total would be 6)
        Can take C (5 weight, total 6)
        Total: 6 weight, 14 value

Optimal: Take A (5 weight, 10 value)
         Can't fit B or C
         Total: 5 weight, 10 value

Wait, greedy gives 14 > 10... Is it correct here?

Let me retry with different example:

Items:      A(v=100, w=50), B(v=90, w=45), C(v=1, w=1)
Capacity:   50

Greedy (by ratio):
  A: 100/50 = 2.0  → Take A
  Result: 50 weight, 100 value

Optimal:
  B+C: 45+1=46 weight, 90+1=91 value ✗
  Actually A is better here...

Better counterexample:
Items:      A(v=10, w=6), B(v=9, w=5), C(v=8, w=5)
Capacity:   10

Greedy (by ratio):
  A: 10/6 = 1.67
  B: 9/5  = 1.8  ← Take B first
  C: 8/5  = 1.6
  Take B (5 weight, 9 value)
  Take C (5 weight, 8 value)
  Total: 10 weight, 17 value

Optimal:
  Take A+C: 6+5=11 weight > 10 ✗
  Take B+C: 5+5=10 weight, 9+8=17 value
  
Hmm, still same...

ACTUAL bad example:
Items:      A(v=100, w=99), B(v=50, w=50), C(v=50, w=50)
Capacity:   100

Greedy (by ratio):
  A: 100/99 = 1.01
  Take A (99 weight, 100 value)
  Remaining: 1 weight (can't fit B or C)
  Total: 100 value

Optimal:
  B+C: 50+50=100 weight, 50+50=100 value
  
Greedy wins here too! But...

ACTUAL working counterexample:
Items:      A(v=50, w=10), B(v=60, w=11), C(v=70, w=12)
Capacity:   12

Greedy (by ratio):
  A: 50/10 = 5.0  ← Take A first
  B: 60/11 ≈ 5.45
  C: 70/12 ≈ 5.83
  Take C: 12 weight, 70 value

Optimal:
  Take C: 12 weight, 70 value ✓

This example doesn't work either. Let me use the CLASSIC one:

Items:      A(v=12, w=4), B(v=30, w=10), C(v=20, w=9)
Capacity:   13

Greedy (by ratio):
  A: 12/4 = 3.0
  B: 30/10 = 3.0
  C: 20/9 ≈ 2.22
  Take A and B: 14 weight > 13 ✗
  Take A: 4 weight, 12 value
  Take C: 9 weight, 20 value
  Total: 13 weight, 32 value

Optimal:
  Take B and C: 10+9=19 > 13 ✗
  Take B: 10 weight, 30 value
  Remaining: 3 weight (nothing fits)
  Take just B: 10 weight, 30 value
  
  Take A and C: 4+9=13 weight, 12+20=32 value ✓
  
So Greedy = 32, Optimal = 32... They're the same.

The CLASSIC counterexample that actually works:
Items:      A(v=11, w=5), B(v=9, w=4), C(v=9, w=4)
Capacity:   8

Greedy (by value desc):
  A: 11/5 = 2.2
  B: 9/4  = 2.25 ← Take B
  C: 9/4  = 2.25 ← Take C
  Take B and C: 4+4=8 weight, 9+9=18 value ✓

Optimal:
  Take A+B: 5+4=9 > 8 ✗
  Take A: 5 weight, 11 value
  Remaining: 3 weight (nothing fits)
  Take just A and something that fit: A+? = 5+ < 8
  Best is A alone: 5 weight, 11 value
  
Greedy wins (18 > 11). 

OK let me use the ACTUAL classic one taught in textbooks:

Items:      A(v=60, w=10), B(v=100, w=20), C(v=120, w=30)
Capacity:   30

Greedy (by ratio):
  A: 60/10 = 6.0   ← BEST ratio
  B: 100/20 = 5.0
  C: 120/30 = 4.0
  Take A: 10 weight, 60 value
  Take B: 20 weight, 100 value
  Total: 30 weight, 160 value ✓

Optimal:
  Take B+C: 20+30=50 > 30 ✗
  Take B alone: 20 weight, 100 value
  Can't fit C
  Take B: 20 weight, 100 value
  Remaining: 10 weight
  Take A: 10 weight, 60 value
  Total: 120+100=100? NO wait...
  B+A = 20+10=30 weight, 100+60=160 value ✓
  
Still the same!

Actually this is hard to construct because greedy often works well in practice. Let me use a PROVEN counterexample:

Items: A(v=6, w=3), B(v=5, w=2), C(v=5, w=2)
Capacity: 5

Greedy (by ratio):
  A: 6/3 = 2.0
  B: 5/2 = 2.5
  C: 5/2 = 2.5
  Take B (2 weight, 5 value)
  Take C (2 weight, 5 value)
  Total: 4 weight, 10 value
  Remaining: 1 weight (can't fit A)

Optimal:
  Take A + something: A is 3, remaining 2
  Take A+B: 3+2=5, value=6+5=11 ✓

Greedy: 10
Optimal: 11

NOW we have a counterexample! Greedy is WRONG for 0/1 Knapsack.
```

**Greedy fails here:** ❌ (Needs Dynamic Programming)

### The Pattern

| Problem | Greedy Works? | Why? |
|---------|---------------|------|
| **Fractional Knapsack** | ✅ YES | Fractions allow filling gaps optimally |
| **0/1 Knapsack** | ❌ NO | Discrete choices create conflicts |
| **Coin Change (some sets)** | ✅ YES (with proof) | Greedy choice property holds |
| **Coin Change (other sets)** | ❌ NO | Counterexamples exist |
| **Activity Selection** | ✅ YES | Earliest finish is always safe |
| **Huffman Coding** | ✅ YES | Merge smallest frequencies |
| **MST (Kruskal)** | ✅ YES | Cycle property guarantees optimality |

---

## Part 7: The Greedy Choice Property & Optimal Substructure

### Two Required Properties

For a problem to be solvable optimally by greedy, it must have BOTH:

### Property 1️⃣: Greedy Choice Property

```
DEFINITION: A locally optimal (greedy) choice can lead 
to a globally optimal solution.

In other words:
  "Making the best choice NOW doesn't prevent 
   finding the optimal solution LATER."
```

**Example: Activity Selection**
- Problem: Select maximum non-overlapping activities
- Greedy choice: Always pick activity ending soonest
- Property holds: This leaves most room for future activities
- Proves globally optimal

**Counterexample: 0/1 Knapsack**
- Problem: Maximize value with weight limit
- Greedy choice: Pick item with best value/weight
- Property FAILS: Picking best ratio can block better combinations

### Property 2️⃣: Optimal Substructure

```
DEFINITION: An optimal solution contains optimal solutions 
to subproblems.

In other words:
  "If I make the greedy choice now,
   the remaining problem is still an optimization 
   problem that can be solved optimally."
```

**Example: Merge Sort (Divide & Conquer)**
- Divide: Split array into two halves
- Conquer: Sort each half optimally
- Combine: Merge sorted halves
- Substructure: If halves are sorted optimally, merge produces optimal result

### Why Both Are Needed

```
WITHOUT Greedy Choice Property:
  → Greedy choice might block future options
  → Leads to suboptimal solutions

WITHOUT Optimal Substructure:
  → After greedy choice, remaining problem isn't solvable optimally
  → Can't guarantee final result is optimal
```

### Abdo's Teaching Point

Abdo is quietly preparing you to:

1. **Recognize** when problems have these properties
2. **Prove** that a greedy algorithm is correct by showing both properties
3. **Know** when DP is needed (when properties don't hold)

This distinction is **critical** for algorithm design interviews.

---

## Part 8: Why Greedy Algorithms Are Gateway to Advanced Topics

### The Learning Progression

```
Greedy Algorithms
    ↓ (When greedy fails)
Dynamic Programming
    ↓ (When DP becomes intractable)
Backtracking / Branch & Bound
    ↓ (When still too slow)
Approximation Algorithms / Heuristics
```

### Specifically, This Leads To

#### 1. **Fractional vs. 0/1 Knapsack**
- Greedy works for fractional
- Need DP for 0/1
- This teaches the importance of problem specifics

#### 2. **MST Algorithms: Kruskal vs. Prim**
- Both greedy
- Different implementations (Kruskal = sort edges, Prim = priority queue)
- Both provably optimal (Union-Find cycle property)

#### 3. **Shortest Path: Dijkstra**
- Greedy selection of nearest unvisited node
- Optimal only with non-negative weights
- Bellman-Ford (DP) needed for negative weights

#### 4. **Huffman Coding**
- Greedy: Merge two smallest frequency nodes
- Provably optimal prefix code
- Connection to information theory

#### 5. **Greedy Fails: Activity Selection Variants**
- Pure activity selection: Greedy works
- Weighted activity selection: Need DP

This progression teaches **when to apply each technique.**

---

## Part 9: The Silent Message — Understand Before Trusting

### Abdo's Core Philosophy

> "Fast algorithms are useless if they are wrong."

This message appears in every section:

```
✅ Understand WHY greedy works (if it does)
✅ Prove it works (don't just assert)
✅ Know counterexamples (if it doesn't)
✅ Choose the right algorithm for the problem
✅ Trust data, not intuition
```

### The Educational Goal

Abdo is NOT teaching you:
- ❌ "Here are some greedy algorithms, memorize them"

Abdo IS teaching you:
- ✅ "Here's how to think about when algorithms work"
- ✅ "Here's how to justify your choices"
- ✅ "Here's how to prove correctness"

This is **algorithmic maturity.**

---

## Part 10: The Dangerous Seduction — When Greedy SEEMS Right

### Why Engineers Deploy Wrong Algorithms

```
SCENARIO: You've written a greedy load-balancing algorithm.

TEST 1: Distribute 10 tasks across 3 servers
        → Greedy produces: (3, 3, 4)
        → Optimal: (3, 3, 4)
        → MATCH! ✓

TEST 2: Small random task sets
        → Greedy matches optimal
        → MATCH! ✓

TEST 3: Deploy to production
        → Works fine for months...
        → Until SPECIFIC task pattern hits
        → Suddenly inefficient
        → But code looked right!
```

**Why?** Tests aren't comprehensive. One lucky case doesn't mean algorithm is correct.

### The Lesson

```
PROOF vs. LUCK

Just because greedy works on:
  - All your test cases
  - All examples you tried
  - All cases you can imagine

Does NOT mean it works on:
  - Cases you didn't test
  - Adversarial inputs
  - Edge cases in production
```

**Need a PROOF, not just evidence.**

---

## Part 11: Understanding Progression

| Level | Can Do |
|-------|--------|
| **Surface** | Describe greedy algorithm in words |
| **Deeper** | Implement greedy algorithm |
| **Deep** | Explain why greedy works for this problem |
| **Mastery** | Prove greedy choice and optimal substructure properties |
| **Expert** | Construct counterexample proving greedy fails for variant |

---

## Part 12: Interview Approach

### What To Say

✓ "This problem has greedy choice property because..."

✓ "I can prove the greedy choice doesn't block optimal solutions by..."

✓ "Alternative: For variant of this problem, greedy fails when..."

✓ "So for this problem, we need DP instead because..."

### What NOT To Say

✗ "Greedy is fast so it must be optimal"

✗ "This looks like a greedy problem"

✗ "Greedy works because I tested it"

✗ "I don't know if it's proven, but it seems right"

### How To Distinguish Yourself

In an interview, prove understanding by:

1. **Proposing greedy** with a specific strategy
2. **Analyzing why it might work** (greedy choice property)
3. **Testing with counterexample** (to verify vs. disprove)
4. **Providing alternative** (DP if greedy fails)

This shows **depth of algorithmic thinking.**

---

## Part 13: Problems Where Greedy Works ✅

### Proven Optimal

These have been mathematically proven to have both required properties:

| Problem | Greedy Strategy | Why Works |
|---------|-----------------|-----------|
| **Activity Selection** | Earliest finish time | Leaves maximum room for future |
| **Fractional Knapsack** | Best value/weight ratio | Fractions fill gaps |
| **MST (Kruskal)** | Smallest edges | Cycle property |
| **MST (Prim)** | Nearest node | Cut property |
| **Huffman Coding** | Merge smallest frequency | Optimality of merge |
| **Dijkstra (non-negative)** | Nearest unvisited | Distance monotonicity |
| **Scheduling (SPT)** | Shortest processing time | Minimizes flow time |
| **Task Scheduling** | Deadline-first | Avoids violations |

---

## Part 14: Problems Where Greedy Fails ❌

### Requires Different Approach

| Problem | Why Greedy Fails | What Works |
|---------|-----------------|-----------|
| **0/1 Knapsack** | Discrete choices conflict | DP |
| **Weighted Activity** | Weights create conflicts | DP |
| **TSP (General)** | No greedy choice property | DP / Branch & Bound |
| **Longest Path** | Greedy misses better paths | DP / Backtracking |
| **Coin Change (some sets)** | Greedy fails for weird coins | DP |
| **Interval Scheduling (weighted)** | Weights override time | DP |

---

## Part 15: Practice Questions

### Understanding Questions

1. **What's the difference between greedy choice property and optimal substructure?**
   - Greedy: Local choice leads to global optimum
   - Substructure: Optimal solution contains optimal subproblems

2. **Why does greedy work for Huffman coding?**
   - Merging smallest frequencies minimizes tree depth
   - Shorter depth = shorter codes = smaller encoding

3. **Why does greedy fail for 0/1 knapsack?**
   - Picking best ratio item blocks better combinations
   - Discrete choices create unavoidable conflicts

4. **How would you prove greedy works for activity selection?**
   - Show earliest-finish leaves most room for future activities
   - Show no other choice leaves more room

5. **What's the counterexample for greedy coin change?**
   - Coins {1, 3, 4}, target 6
   - Greedy: 4+1+1 (3 coins)
   - Optimal: 3+3 (2 coins)

### Application Questions

6. **You're designing a scheduling algorithm. How do you know if greedy is safe?**
   - Test with various inputs and edge cases
   - Look for a mathematical proof of properties
   - Try to construct counterexample

7. **Your greedy algorithm passes all tests but fails in production. What went wrong?**
   - Tests weren't comprehensive
   - Specific input pattern exists that breaks it
   - Need rigorous proof, not just testing

8. **You have two algorithms: greedy O(n) and DP O(n²). When do you use greedy?**
   - Only if you've proven it's correct
   - If speed critical and correctness verified
   - Otherwise, use DP for safety

---

## Part 16: Deep Analysis: Why Greedy Sometimes Works

### The Mathematical Reason

Certain problem structures guarantee greedy works:

#### Exchange Argument

When you can prove that:
1. Greedy chooses X
2. Optimal chose something else
3. You can exchange them without hurting optimality
4. Repeat until greedy = optimal

#### Matroid Property

Some problems have "matroid" structure where:
- Independent sets can be built greedily
- Maximal greedy solution is maximum

**Examples:** MST edges form a matroid, activity selections do too

#### Exchange Property

When any "better" choice can be exchanged for greedy without loss:

```
If optimal solution O chose item Y at position i,
but greedy chose X:
  → If we replace Y with X in O
  → New solution O' is still optimal
  → Repeat until O' = greedy solution
```

These proofs are **rigorous** and require practice to develop.

---

## Part 17: Key Takeaways for Study

| Concept | Remember |
|---------|----------|
| **Optimization Problem** | Find BEST solution, not just any |
| **Greedy** | Make best LOCAL choice each step |
| **No Backtracking** | Once chosen, never reevaluated |
| **Greedy Choice Property** | Local optimum leads to global |
| **Optimal Substructure** | Subproblems remain optimization |
| **Proof Matters** | Testing doesn't prove correctness |
| **Counterexamples** | How to disprove greedy |
| **Greedy vs. DP** | Different trade-offs |

---

## Part 18: Real-World Impact

### Where Understanding This Matters

**Real company problems:**

1. **Google Maps Routing**
   - Not pure greedy (would suggest wrong paths)
   - Actually: Combination of heuristics + optimization

2. **Netflix Recommendation**
   - Couldn't just pick "most popular" (greedy)
   - Uses DP-like optimization + collaborative filtering

3. **Database Query Planning**
   - Join order optimization looks greedy but needs careful proof
   - Wrong order causes 100x slowdown

4. **Network Routing**
   - Dijkstra (greedy) works for hop count
   - But bandwidth-optimized routing is NOT greedy

All of these initially look like "pick the best locally" but require deeper analysis.

---

## Part 19: Final Wisdom from Abdo

The lesson isn't about learning specific greedy algorithms.

The lesson is about **thinking carefully** before trusting any algorithm:

### The Three Questions

Before implementing any algorithm, ask:

1. **Is it correct?**
   - Have I proven it? Or just tested?
   - What's the worst case input?

2. **When is it correct?**
   - What assumptions must hold?
   - What constraints guarantee optimality?

3. **When is it wrong?**
   - Can I construct a counterexample?
   - What would make it fail?

### The Meta-Lesson

> "Algorithm selection is a **conscious choice**, not a guess."

This applies far beyond greedy:
- Always ask WHY you chose this algorithm
- Always be ready to PROVE it's correct
- Always test EDGE CASES, not just happy paths

This is **professional software engineering**, not school projects.

---

## Part 20: Practice Problems

### Classic Greedy Problems (with proofs)

1. **Activity Selection**
   - Sort by finish time, greedily pick non-overlapping
   - Proof: Exchange argument + exchange property

2. **Huffman Coding**
   - Merge two smallest frequencies
   - Proof: Optimality of merge operation

3. **MST (Kruskal)**
   - Sort edges, add if doesn't create cycle
   - Proof: Cut property + cycle property

### Problems Where Greedy Fails

4. **0/1 Knapsack**
   - Greedy by value/weight fails
   - Use DP instead

5. **Weighted Activity Selection**
   - Greedy by finish time fails
   - Use DP (similar to 0/1 knapsack)

### Mix (Decide Greedy or DP)

6. **Coinotation Change**
   - For some coin sets: greedy works
   - For others: need DP
   - Depends on coin denominations!

7. **Interval Scheduling (Weighted)**
   - Simple intervals: greedy works
   - With weights: need DP

---

## References & Next Steps

- **Prerequisite:** Understand Big-O, basic algorithms
- **Immediate:** Learn specific greedy algorithms (Dijkstra, Kruskal, Huffman)
- **Next:** Master Dynamic Programming (when greedy fails)
- **Advanced:** Approximation algorithms (when even DP is too slow)
- **Theory:** NP-completeness (classify problems by hardness)

---

## One-Line Summary (Exam Gold)

> "Greedy algorithms are fast because they don't look back — and dangerous for the same reason."

OR

> "Choose greedy only when you can *prove* the greedy choice property holds."

If you can explain **why** either statement is true, you've mastered this section.
