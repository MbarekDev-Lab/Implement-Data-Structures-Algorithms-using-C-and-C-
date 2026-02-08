# Kruskal's Algorithm Implementation — Abdo's Whiteboard Breakdown

## Abdo's Core Message

> "Kruskal = Sort edges + Pick minimum + Avoid cycles using Disjoint Set"

**Everything on the board serves this idea.**

This lecture shows exactly **how to implement Kruskal efficiently** using real data structures (priority queue/sorting and Union-Find).

---

## Part 1: The Input — The Graph You're Given

### What You Start With

On the right side of the board:

```
Vertices: 1, 2, 3, 4, 5, 6, 7  (7 nodes, n = 7)

Edges: Each with a GIVEN cost
  1-2: 28
  1-6: 10
  2-3: 16
  2-7: 14
  3-4: 12
  4-5: 22
  4-7: 18
  5-6: 25
  5-7: 24
  (and possibly more...)
```

**Critical:** These numbers are INPUTS, not calculated by Kruskal.

They represent real quantities:
- Distance between cities
- Cost of laying cable
- Time to connect nodes
- Any optimization metric you're minimizing

### The Optimization Problem (What Abdo Writes)

**Constraints:**
```
✓ Create a Spanning Tree
✓ Graph must be connected
✓ No cycles
✓ Exactly (n - 1) edges

For n = 7 vertices:
  → MST must have exactly 6 edges
```

**Objective:**
```
Minimize total cost (sum of edge weights in the tree)
```

### Why Greedy Works Here

Abdo emphasizes:

```
Local minimum edge choices (greedy)
  ↓
Lead to global minimum (MST property)

This property is PROVABLE (by exchange argument).
It's rare. Most problems don't have it.
```

---

## Part 2: The Algorithm Structure (Left Side of Board)

### The Function Signature

```
Algorithm Kruskal(int edges[][], int n):
    INPUT:
      edges[][] → adjacency list of all edges
                  Each edge: (u, v, cost)
      n → number of vertices (7 in this example)
    
    OUTPUT:
      minCost → total weight of MST
```

### Key Variables Initialization

```c
selected[] = array of size |E| (number of edges)
            Initially all FALSE
            Marks which edges have been processed

minCost = 0
            Total cost of MST (accumulates)

edgeCount = 0
            Number of edges selected so far
            Stop when edgeCount == n - 1

Disjoint ds = new Disjoint(n)
            Creates n disjoint sets initially
            One vertex per set
            For n = 7:
              parent = [-1, -1, -1, -1, -1, -1, -1]
              (Each vertex is root of its own set)
```

### The Disjoint Set (Union-Find) Creation

**Why this is critical:**

```
Disjoint Set Purpose:
  - Track which vertices are connected
  - Detect when adding an edge would create a cycle
  - Efficiently merge two components

Initially (before any edges):
  Vertices: 1 2 3 4 5 6 7
  Sets:     {1}{2}{3}{4}{5}{6}{7}
  
  Each vertex is isolated (its own component)
```

This is the **foundation for cycle detection**.

---

## Part 3: The Main Loop (Center Logic)

### Loop Control

```c
while (edgeCount < n - 1):
    // Keep adding edges until we have n-1
```

**Why this constraint?**

A spanning tree with V vertices must have exactly **V - 1 edges**.

For 7 vertices: exactly 6 edges in MST.

### Step 1: Find Minimum Unused Edge

Abdo shows brute force (for clarity, not efficiency):

```c
min = MAX_INT
index = -1

for i = 0 to edges.length:
    if selected[i] == false and edges[i][2] < min:
        min = edges[i][2]
        index = i
```

**What this does:**
- Scan all edges
- Find the cheapest edge that hasn't been processed yet
- Remember its index

**In production:** Use a priority queue (min-heap) for O(log E) instead of O(E).

### Step 2: Extract the Edge

```c
u = edges[index][0]      // First vertex
v = edges[index][1]      // Second vertex
cost = edges[index][2]   // Weight
```

Now we have the cheapest edge: `(u, v, cost)`

### Step 3: THE CRITICAL LINE — Cycle Detection

```c
if (ds.find(u) != ds.find(v)):
```

**This single line is where Abdo emphasizes everything:**

```
Find(u) → Which set does u belong to?
Find(v) → Which set does v belong to?

If different sets → u and v are not yet connected
                   Adding this edge won't create a cycle
                   ✅ SAFE TO ADD

If same set → u and v already connected (by some path)
             Adding this edge creates a cycle
             ❌ REJECT THIS EDGE
```

This is **the entire reason Disjoint Set exists**.

### Step 4A: Accept the Edge (If Safe)

```c
if (ds.find(u) != ds.find(v)):
    minCost += edges[index][2]   // Add cost
    edgeCount++                   // Count it
    selected[index] = true        // Mark processed
    ds.union(u, v)                // Merge components
```

**What happens:**
- Edge is added to MST
- Total cost increases
- The two components are merged (now connected via this edge)

### Step 4B: Reject the Edge (If Unsafe)

```c
else:
    selected[index] = true    // Mark processed
    // Do NOT add to MST
    // Do NOT increment edgeCount
    // Do NOT merge components
```

**What happens:**
- Edge is skipped
- No cost added
- Edge is marked "processed" so we don't reconsider it

---

## Part 4: The Input Representation (The Edge Table)

### Abdo Shows the Edge Table

On the board, edges are represented as data:

```
Index   u   v   cost    selected(before)?
0       1   2   28      F
1       1   6   10      F
2       2   3   16      F
3       2   7   14      F
4       3   4   12      F
5       4   5   22      F
6       4   7   18      F
7       5   6   25      F
8       5   7   24      F
```

**Abdo's Key Point:**

```
"Graphs are NOT pictures — they are arrays."

When you code, you don't draw pictures.
You represent graphs as:
  - Edge lists (u, v, cost)
  - Adjacency matrices
  - Adjacency lists

This table shows edge list representation.
```

### Selected[] Array Updates

As Kruskal runs, the `selected[]` column changes:

```
After processing some edges:

Index   selected?   Reason
0       T           Processed (accepted or rejected)
1       T           Processed (accepted)
2       T           Processed (accepted)
3       T           Processed (accepted)
4       T           Processed (accepted)
5       F           Not yet considered
6       F           Not yet considered
7       F           Not yet considered
8       F           Not yet considered
```

The `F` entries mean "haven't examined this edge yet" (still in priority queue).

---

## Part 5: Disjoint Set State Evolution

### Initial State

```
Vertices: 1   2   3   4   5   6   7
Parent:  -1  -1  -1  -1  -1  -1  -1

Meaning: Each vertex is its own component (root of its own set)
```

### After Each Union

As edges are accepted, components merge:

```
After edge (1,6, cost=10):
  Union(1, 6) → Merge components
  Now: {1,6} {2} {3} {4} {5} {7}
  
  Parent might be: [-1, 1, -1, -1, -1, -1, -1]
  (1 is root, 6 is child of 1, others unchanged)

After edge (1,2, cost=28):
  Union(2, 1) → Merge {2} with {1,6}
  Now: {1,2,6} {3} {4} {5} {7}
  
  Parent might be: [-1, 1, 1, -1, -1, -1, -1]
  (1 is root, 2 and 6 are children)

... continue until all vertices are in one component ...

After 6 edges selected:
  Parent: [root, root, root, root, root, root, root]
  (All vertices connected, all paths lead to roots)
```

**On the board, Abdo shows the final parent array:**

```
Index:     1  2  3  4  5  6  7
Parent:   -1 -1 -1  3 -1  1  2
```

This encodes the tree structure numerically.

---

## Part 6: The Decision Flow (Why Edges Are Accepted/Rejected)

### Example Walkthrough

Starting with empty MST:

```
SIMULATION OF KRUSKAL:

Initial: edgeCount = 0, minCost = 0
All vertices isolated: {1}{2}{3}{4}{5}{6}{7}

Iteration 1: Find min edge
  Minimum unused edge: (1,6, cost=10)
  Find(1)=1, Find(6)=6 → Different ✓
  Accept edge (1,6, cost=10)
  minCost = 10, edgeCount = 1
  Union: {1,6}{2}{3}{4}{5}{7}

Iteration 2: Find min edge
  Minimum unused edge: (2,7, cost=14)
  Find(2)=2, Find(7)=7 → Different ✓
  Accept edge (2,7, cost=14)
  minCost = 24, edgeCount = 2
  Union: {1,6}{2,7}{3}{4}{5}

Iteration 3: Find min edge
  Minimum unused edge: (3,4, cost=12)
  Find(3)=3, Find(4)=4 → Different ✓
  Accept edge (3,4, cost=12)
  minCost = 36, edgeCount = 3
  Union: {1,6}{2,7}{3,4}{5}

Iteration 4: Find min edge
  Minimum unused edge: (2,3, cost=16)
  Find(2)=2, Find(3)=3 → Different ✓
  Accept edge (2,3, cost=16)
  minCost = 52, edgeCount = 4
  Union: {1,6}{2,3,4,7}{5}

Iteration 5: Find min edge
  Minimum unused edge: (4,7, cost=18)
  Find(4)={2,3,4,7}, Find(7)={2,3,4,7}
  SAME! ✗
  Reject edge (creates cycle in component)

Iteration 6: Find min edge
  Minimum unused edge: (4,5, cost=22)
  Find(4)={2,3,4,7}, Find(5)=5 → Different ✓
  Accept edge (4,5, cost=22)
  minCost = 74, edgeCount = 5
  Union: {1,2,3,4,5,7,6}

Iteration 7: Find min edge
  Minimum unused edge: (5,6, cost=25)
  Find(5)={1,2,3,4,5,6,7}, Find(6)={1,2,3,4,5,6,7}
  SAME! ✗
  Reject (all vertices already connected)

Iteration 8: edgeCount = 6 = n-1
  STOP (we have a spanning tree)
```

### Why Some Edges Are Rejected

**Edge (4,7, cost=18):**
```
At this point:
  Component A: {2,3,4,7}
  Component B: {1,6}
  Singleton: {5}

Edge (4,7) would connect 4 and 7 (already in same component A)
Result: Would create a cycle within A
Rejection is CORRECT
```

**Edge (5,6, cost=25):**
```
At this point:
  After previous accepts: {1,2,3,4,5,6,7} (all connected)

Edge (5,6) would connect 5 and 6 (already in same component)
Result: Would create a cycle
Plus: We already have 6 edges (=n-1), don't need more anyway
```

---

## Part 7: The Final Result (What Abdo Underlines)

### Selected Edges

```
Accepted edges in MST:
  (1,6) cost=10
  (2,7) cost=14
  (3,4) cost=12
  (2,3) cost=16
  (4,5) cost=22
  (1,2) cost=28
  
Total: 6 edges (= n-1 for n=7) ✓

Total cost: 10+14+12+16+22+28 = 102

(Note: Abdo's board might show different order
 but same total — MST weight is unique even if
 edges are not)
```

### Why Abdo Underlines the Cost

```
minCost = 102
```

This is the **answer to the optimization problem:**

```
"What is the minimum total cost to connect all 7 vertices?"

Answer: 102

(This is the only value that matters for evaluation.)
```

---

## Part 8: Why Find() and Union() Are Essential

### What Abdo Writes at Bottom

```
Find(x):
  Purpose: Determine which component x belongs to
  Returns: Root representative of x's component
  Cost: Nearly O(1) with path compression
  
Union(u, v):
  Purpose: Merge the component containing u 
           with the component containing v
  Effect: After union, Find(u) == Find(v)
  Cost: Nearly O(1) with union by rank
```

### Why This Matters

**Without Union-Find:**

```
Cycle detection would require:
  - DFS: O(V+E) per edge check
  - Total: O(E·(V+E)) — way too slow

With Union-Find:
  - Find: O(α(V)) ≈ O(1)
  - Union: O(α(V)) ≈ O(1)
  - Total: O(E·α(V)) ≈ O(E) — much faster
```

Abdo is silently saying:

```
"Kruskal is theoretically simple.
 But it only works efficiently WITH Union-Find."
```

---

## Part 9: Complete Pseudocode (What Abdo Is Showing)

### Full Implementation

```
algorithm Kruskal(Edge edges[], int n):
    
    // Initialize
    selected[] = array[edges.length] = {false}
    minCost = 0
    edgeCount = 0
    
    // Create disjoint set for all vertices
    UnionFind ds = new UnionFind(n)
    
    // Main loop: keep adding edges until spanning tree is complete
    while (edgeCount < n - 1):
        
        // Find minimum cost unused edge
        min_edge = find_minimum_unused_edge(edges, selected)
        
        if min_edge == null:
            break  // No more edges (should only happen on error)
        
        u = min_edge.u
        v = min_edge.v
        cost = min_edge.cost
        
        // Check if adding this edge would create a cycle
        if ds.find(u) != ds.find(v):
            // SAFE: u and v in different components
            minCost += cost
            edgeCount++
            selected[min_edge.index] = true
            ds.union(u, v)
        else:
            // CYCLE: u and v already in same component
            selected[min_edge.index] = true
            // Do NOT add this edge
    
    return minCost
```

---

## Part 10: The Teaching Progression (What Abdo Expects)

### What You Should Understand After This Board

| Concept | Should Understand |
|---------|-------------------|
| **Input graph** | Edges with costs are GIVEN |
| **Optimization** | Minimize total edge weight subject to spanning tree constraints |
| **Greedy strategy** | Always pick cheapest safe edge |
| **Cycle avoidance** | Use Union-Find's Find/Union operations |
| **Loop invariant** | After iteration k, have k edges forming k components merged together |
| **Termination** | Stop when edgeCount = n-1 (spanning tree guaranteed) |
| **Correctness** | Provable by exchange argument (greedy choice property) |
| **Complexity** | O(E log E) if using sorted edges, O(E α(V)) for Union-Find ops |
| **Data structures** | Priority queue/sorting + Union-Find |

---

## Part 11: Why Each Part of the Board Matters

### Right Side: The Problem

```
Graph visual + optimization statement

Why Abdo includes it:
  - Shows the concrete problem
  - Makes inputs concrete (specific vertices/edges/costs)
  - Frames as optimization (minimize cost)
```

### Left Side: The Algorithm

```
Pseudocode + variable initialization

Why Abdo includes it:
  - Shows systematic approach
  - Emphasizes Union-Find from the start
  - Makes loop structure visible
```

### Center: The Simulation

```
Edge table + component evolution

Why Abdo includes it:
  - Shows what happens step-by-step
  - Demonstrates cycle rejection
  - Shows Union-Find in action
```

### Bottom: The Data Structure Operations

```
Find() and Union() highlighted

Why Abdo includes it:
  - Emphasizes they're the KEY operations
  - Links algorithm to data structure
  - Explains why Union-Find is necessary
```

---

## Part 12: The Meta-Lesson (What Abdo Really Wants)

Abdo is teaching three things simultaneously:

### Lesson 1: Greedy Algorithm Design

```
Kruskal exemplifies greedy:
  - Make locally optimal choice (cheapest edge)
  - Constraints ensure global optimality (no cycles)
  - This is RARE (most problems need DP instead)
```

### Lesson 2: Data Structure Integration

```
Algorithm efficiency depends on data structures:
  - Sorting edges: O(E log E)
  - Union-Find: O(E α(V))
  - Without Union-Find, cycle check alone is O(E·(V+E))
  
Total: O(E log E) with good structures vs. O(E²) otherwise
```

### Lesson 3: Algorithm Implementation

```
From pseudocode to code:
  - Variables: selected[], minCost, edgeCount
  - Loop conditions: while (edgeCount < n-1)
  - The critical line: if (find(u) != find(v))
  - State evolution: Disjoint Set parent array changes
```

---

## Part 13: Connection to Next Topics

### Leads Directly To

1. **Union-Find Implementation**
   - Path compression and union by rank
   - Why O(α(V)) is nearly constant

2. **Prim's Algorithm**
   - Alternative MST (vertex-based vs. edge-based)
   - When to use Prim vs. Kruskal

3. **Detecting Cycles in General Graphs**
   - Union-Find applies beyond MST
   - Useful for many graph problems

4. **Advanced Greedy Algorithms**
   - When greedy works (like MST)
   - When greedy fails (0/1 Knapsack, TSP)

---

## Part 14: Key Takeaways

| Item | Understand |
|------|-----------|
| **Input** | Edges with costs (given, not calculated) |
| **Objective** | Minimize sum of selected edge costs |
| **Constraint** | Must form spanning tree (V-1 edges, connected, no cycles) |
| **Greedy Strategy** | Pick cheapest edge that doesn't create cycle |
| **Cycle Detection** | Use Union-Find: find(u) != find(v) means safe |
| **Loop Control** | Continue while edgeCount < n-1 |
| **Accepted Edge** | Cost added, components merged |
| **Rejected Edge** | Would create cycle, skipped |
| **Final Answer** | Sum of accepted edge costs = MST weight |
| **Complexity** | O(E log E) with sorting |
| **Data Structures** | Sorted edges (or heap) + Union-Find |

---

## Part 15: One-Line Summary (Exam Gold)

> "Kruskal repeatedly selects the cheapest edge that doesn't form a cycle (detected via Union-Find), stopping at n-1 edges."

OR even tighter:

> "Sort edges by cost, greedily pick those that unite different components."

If you can explain the word "components," you've mastered this whiteboard.

---

## Part 16: Practice Questions

### Can You Answer These?

1. **Why do we start with each vertex in its own set?**
   - To detect when an edge would merge components vs. create a cycle

2. **What does find(u) != find(v) mean?**
   - u and v are currently in different components, so the edge is safe

3. **Why stop at exactly n-1 edges?**
   - That's how many edges a spanning tree on n vertices has

4. **What if we picked n edges instead of n-1?**
   - Would create a cycle (violated tree structure)

5. **Why not just pick the n-1 cheapest edges?**
   - Might create cycles; must check connectivity

6. **How does Union-Find prevent checking each edge twice?**
   - selected[] array marks processed edges, Find()/Union() track components

---

## References & Next Steps

- **Prerequisite:** Understand graphs, spanning trees, optimization
- **During:** Union-Find (Disjoint Set) data structure
- **Immediate Next:** Implement Kruskal with Union-Find code
- **Compare:** Prim's algorithm (alternative MST)
- **Apply:** Cycle detection in general graphs, other greedy algorithms
