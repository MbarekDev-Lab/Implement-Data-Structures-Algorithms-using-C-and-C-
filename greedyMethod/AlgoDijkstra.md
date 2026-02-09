# Dijkstra's Algorithm — Abdo's Shortest Path Lecture

## Part 1: The Problem — What Is Dijkstra Solving?

### The Core Question

**Given:**
```
A weighted graph (undirected or directed)
One source vertex s
All edge weights are non-negative
```

**Find:**
```
Shortest distance from s to every other vertex
(i.e., shortest path cost, not the path itself)
```

### What Dijkstra Is NOT

❌ **Not MST.** Prim and Kruskal build trees connecting all vertices cheaply.
Dijkstra builds **distance records** from one source.

❌ **Not all pairs.** Something like Floyd-Warshall does that.
Dijkstra is **single source**.

❌ **Not negative weights.** Dijkstra assumes all edges ≥ 0.
With negative edges → use Bellman-Ford instead.

### Example Problem

**The Graph:**
```
        1 ─── 4 ─── 2
       /│      \    /
      /3│       \1 /
     α  │        \/
    /   │        /\
   0    │       /  \
    \   │      /5   2
     \2 │     /
      \ │    /
       \│   /
        3──

Vertices: 0, 1, 2, 3
Source: 0
Weights: (0,1)=1, (0,3)=2, (1,2)=4, (1,3)=3, (3,2)=5
```

**Dijkstra's Answer:**
```
From vertex 0:
  Distance to 0: 0 (itself)
  Distance to 1: 1 (direct: 0→1)
  Distance to 2: 5 (via 1: 0→1→2)
  Distance to 3: 2 (direct: 0→3)
```

Abdo emphasizes:

```
"The distance is the SUM of edges along the shortest path.
 Not just the nearest neighbor."
```

---

## Part 2: The Big Idea — Abdo's Intuition

### Greedy Philosophy

Abdo teaches Dijkstra like this:

```
You're at the source, exploring outward.

At each step, ask:
"Which unvisited node am I closest to right now?"

Visit that node (lock its distance).

Then ask:
"Maybe I can reach other nodes cheaper through this new node?"

Update neighbors.

Repeat.
```

### The Key Insight

```
Once a node's distance is selected/finalized:
  ✓ It will never be improved again
  ✓ No future path can be shorter
  ✓ This distance is locked forever

Why? Because:
  - All edges are non-negative
  - We always pick the minimum unvisited distance
  - Adding any positive edge makes paths longer
```

This is the **greedy magic.**

### The Contract

```
Dijkstra says:
"Pick the smallest distance.
 Lock it.
 Use it to improve neighbors.
 Never look back."

This works ONLY if:
✔ No negative edges
✔ We always pick the minimum
✔ We relax before locking the next one
```

---

## Part 3: Whiteboard Tables — What You See on the Board

### Table A: The Cost Matrix (Input)

The graph itself, as a matrix:

```
Cost Matrix (from example above)
     0   1   2   3
0    0   1   ∞   2
1    1   0   4   3
2    ∞   4   0   5
3    2   3   5   0

Meaning:
cost[i][j] = weight of edge from i to j
0 = no self-edge weight shown (or 0)
∞ = no direct edge
```

**Abdo's point:**

```
"This is just the graph representation.
 It's the INPUT to Dijkstra."
```

### Table B: The Distance Array (THE HEART)

This is what Dijkstra computes:

```
dist[] array
(after each iteration, it evolves)

Initially:
dist[0] = 0    (source)
dist[1] = ∞
dist[2] = ∞
dist[3] = ∞

Meaning:
dist[v] = shortest known distance from source to v
```

**Evolution during algorithm:**

```
After selecting vertex 0:
dist[0] = 0    ← locked
dist[1] = 1    ← updated through 0
dist[2] = ∞    ← unreachable yet
dist[3] = 2    ← updated through 0

After selecting vertex 3:
dist[0] = 0    ← locked
dist[1] = 1    ← locked (still 1)
dist[2] = 7    ← updated: 0→3→2 costs 2+5=7
dist[3] = 2    ← locked

After selecting vertex 1:
dist[0] = 0    ← locked
dist[1] = 1    ← locked
dist[2] = 5    ← updated: 0→1→2 costs 1+4=5 (better than 7)
dist[3] = 2    ← locked

After selecting vertex 2:
dist[0] = 0    ← locked
dist[1] = 1    ← locked
dist[2] = 5    ← locked
dist[3] = 2    ← locked
```

**Abdo stresses:**

```
"Distance is NOT the edge weight.
 It's the cumulative cost from source."
```

### Table C: The Selected Array

```
selected[] array (tracks which distances are locked)

Initially:
selected[0] = F
selected[1] = F
selected[2] = F
selected[3] = F

After iteration 1 (pick vertex 0):
selected[0] = T    ← locked, never changes
selected[1] = F
selected[2] = F
selected[3] = F

After iteration 2 (pick vertex 3):
selected[0] = T    ← locked
selected[1] = F
selected[2] = F
selected[3] = T    ← locked

After iteration 3 (pick vertex 1):
selected[0] = T    ← locked
selected[1] = T    ← locked
selected[2] = F
selected[3] = T    ← locked

After iteration 4 (pick vertex 2):
selected[0] = T    ← locked
selected[1] = T    ← locked
selected[2] = T    ← locked
selected[3] = T    ← locked
```

**Meaning:**

```
selected[v] = T → dist[v] is final
selected[v] = F → dist[v] might improve

Once T → never goes back to F
```

---

## Part 4: Step-by-Step Walkthrough

### Initialization Phase

```
Graph setup (4 vertices, source = 0):
Edges: (0,1)=1, (0,3)=2, (1,2)=4, (1,3)=3, (3,2)=5

Initialize:
dist[] = {0, ∞, ∞, ∞}
selected[] = {F, F, F, F}

Abdo says:
"We start knowing the source is distance 0 from itself.
 Everything else is unknown (∞)."
```

### Iteration 1: Pick Minimum Unselected Distance

```
Unselected vertices: 0, 1, 2, 3
Their distances: dist[0]=0, dist[1]=∞, dist[2]=∞, dist[3]=∞

Minimum: dist[0] = 0

Pick vertex 0
selected[0] = true

Abdo says:
"Vertex 0 is closest (it's the source).
 Its distance is FINAL.
 Lock it."
```

### Iteration 1: Relax Adjacent Vertices

```
Neighbors of vertex 0:
  - Vertex 1: cost[0][1] = 1
  - Vertex 3: cost[0][3] = 2

Relaxation step (check if we can improve neighbors through 0):

For vertex 1:
  Is selected[1] == false? YES
  Is dist[0] + cost[0][1] < dist[1]?
  Is 0 + 1 < ∞? YES
  Update: dist[1] = 0 + 1 = 1

For vertex 3:
  Is selected[3] == false? YES
  Is dist[0] + cost[0][3] < dist[3]?
  Is 0 + 2 < ∞? YES
  Update: dist[3] = 0 + 2 = 2

For vertex 2:
  Is it adjacent to 0? NO (cost[0][2] = ∞)
  Skip

State after iteration 1:
dist[] = {0, 1, ∞, 2}
selected[] = {T, F, F, F}
```

### Iteration 2: Pick Minimum Unselected

```
Unselected vertices: 1, 2, 3
Their distances: dist[1]=1, dist[2]=∞, dist[3]=2

Minimum: dist[1] = 1

Pick vertex 1
selected[1] = true

Abdo says:
"Vertex 1 is next closest (distance 1).
 This cannot be improved:
 We already explored vertex 0 (distance 0).
 Any path through other nodes would be longer.
 Lock it."
```

### Iteration 2: Relax Adjacent Vertices

```
Neighbors of vertex 1:
  - Vertex 0: cost[1][0] = 1 (but selected[0] = T, skip)
  - Vertex 2: cost[1][2] = 4
  - Vertex 3: cost[1][3] = 3

Relaxation:

For vertex 0:
  Is selected[0] == false? NO
  Skip (already locked)

For vertex 2:
  Is selected[2] == false? YES
  Is dist[1] + cost[1][2] < dist[2]?
  Is 1 + 4 < ∞? YES
  Update: dist[2] = 1 + 4 = 5

For vertex 3:
  Is selected[3] == false? YES
  Is dist[1] + cost[1][3] < dist[3]?
  Is 1 + 3 < 2? NO (3 is not less than 2)
  Don't update

State after iteration 2:
dist[] = {0, 1, 5, 2}
selected[] = {T, T, F, F}
```

### Iteration 3: Pick Minimum Unselected

```
Unselected vertices: 2, 3
Their distances: dist[2]=5, dist[3]=2

Minimum: dist[3] = 2

Pick vertex 3
selected[3] = true

Abdo says:
"Vertex 3 is now the closest unvisited (distance 2).
 Lock it."
```

### Iteration 3: Relax Adjacent Vertices

```
Neighbors of vertex 3:
  - Vertex 0: cost[3][0] = 2 (but selected[0] = T, skip)
  - Vertex 1: cost[3][1] = 3 (but selected[1] = T, skip)
  - Vertex 2: cost[3][2] = 5

Relaxation:

For vertex 2:
  Is selected[2] == false? YES
  Is dist[3] + cost[3][2] < dist[2]?
  Is 2 + 5 < 5? Is 7 < 5? NO
  Don't update

State after iteration 3:
dist[] = {0, 1, 5, 2}
selected[] = {T, T, F, T}
```

### Iteration 4: Pick Minimum Unselected

```
Unselected vertices: 2
Their distances: dist[2]=5

Minimum: dist[2] = 5

Pick vertex 2
selected[2] = true

Abdo says:
"Only vertex 2 left.
 Lock it.
 Done."
```

### Iteration 4: Relax Adjacent Vertices

```
Neighbors of vertex 2:
  - Vertex 0: selected[0] = T (skip)
  - Vertex 1: selected[1] = T (skip)
  - Vertex 3: selected[3] = T (skip)

All neighbors are locked. No updates.

Final state:
dist[] = {0, 1, 5, 2}
selected[] = {T, T, T, T}
```

### ALGORITHM COMPLETE

```
Shortest distances from vertex 0:
  0 → 0: distance 0
  0 → 1: distance 1
  0 → 2: distance 5
  0 → 3: distance 2
```

---

## Part 5: Why Dijkstra Works (The Proof Idea)

### The Guarantee

**Claim:** After selecting vertex u, dist[u] is the final shortest distance.

**Why?**

```
Proof sketch:

1. We always select the minimum unselected distance

2. All edges are non-negative

3. Therefore:
   - Any unselected vertex v has dist[v] ≥ dist[u]
   - To reach v through any unselected vertex would cost
     at least dist[u] + (positive edge weight)
   - Which is > dist[u]
   - So it cannot be better than what we already know

4. Conclusion:
   - dist[u] cannot improve
   - Lock it
```

### The Condition: Non-Negative Edges

**What breaks with negative edges:**

```
Example with negative edge:

    0 ──2→ 1
     \
      \─1→ 2 ──-5→ 1

Dijkstra:
  Picks vertex 0 (dist=0), locks it
  Updates vertex 1: dist[1] = 2, locks it
  But then: 0→2→1 costs 1 + (-5) = -4
  Which is better than 2!
  But 1 is already locked. Can't fix it.

Dijkstra fails!
```

**Solution:** Use Bellman-Ford for negative edges.

---

## Part 6: Dijkstra vs. Prim — Pattern Recognition

### Side-by-Side Comparison

```
                    Prim                Dijkstra
────────────────────────────────────────────────────
Problem             MST                 Shortest paths
What it finds       Min tree cost       Min distances
Perspective         Growing tree        Growing paths
Source?             None (any start)    One fixed source
Selects by          Edge weight         Path distance
Output              Edges               Distance array
Can use edges?      Yes                 Not typically (edges not needed)
Use case            Connect all cheap   Find closest nodes
────────────────────────────────────────────────────
```

### Structural Similarity

Both algorithms:

```
1. Initialize: start = best known value

2. Loop n times:
   a. Pick minimum unselected value
   b. Lock it (selected = true)
   c. Update neighbors through this node

3. Return: array of final values
```

**Different wording, same skeleton:**

| Step | Prim | Dijkstra |
|------|------|----------|
| **Initialize** | visited[start]=T, near[]=start, key[]=cost[start][] | dist[start]=0, all others=∞, selected[]=F |
| **Pick minimum** | Find vertex v with min key[v] where visited[v]=F | Find vertex v with min dist[v] where selected[v]=F |
| **Lock it** | visited[v] = T | selected[v] = T |
| **Update neighbors** | For each neighbor k: if cost[v][k] < key[k], update | For each neighbor k: if dist[v]+cost[v][k] < dist[k], update |

**Abdo's lesson:**

```
"Recognize the pattern. The algorithm shape matters more than the problem.
 Once you understand the structure, variations become obvious."
```

---

## Part 7: What You Must Remember for Exams & Coding

### The One-Liner (Gold for Exams)

**If someone asks: "What is Dijkstra?"**

Answer:
> "Dijkstra's algorithm finds the shortest path from a single source vertex to all other vertices in a weighted graph with non-negative edges by repeatedly selecting the unvisited vertex with minimum distance and relaxing its adjacent edges."

### The Three Core Ideas

```
1. GREEDY CHOICE
   "Pick the closest unvisited vertex"

2. RELAXATION
   "Check if going through this vertex improves neighbors"

3. NON-NEGATIVE EDGES
   "If negative edges exist, use Bellman-Ford instead"
```

### The Pseudocode (Whiteboard Format)

```
DIJKSTRA(G, source)

// Initialize
For each vertex v in G:
    dist[v] ← ∞
    selected[v] ← false

dist[source] ← 0

// Main loop
Repeat |V| − 1 times:
    
    // Greedy choice: pick closest unvisited
    Pick vertex u such that:
        selected[u] = false AND dist[u] is minimum
    
    selected[u] ← true
    
    // Relax neighbors
    For each vertex v adjacent to u:
        If selected[v] = false AND
           dist[u] + cost[u][v] < dist[v]:
            dist[v] ← dist[u] + cost[u][v]

Return dist[]
```

### Implementation Checklist

When coding Dijkstra:

```
✓ Initialize dist[source] = 0, all others = ∞
✓ Initialize selected[] = all false
✓ Loop n-1 times (or until all selected)
✓ Find minimum unselected distance
✓ Mark as selected (never change again)
✓ For each neighbor of selected vertex:
  ✓ Check if going through selected vertex is better
  ✓ Update distance if yes
✓ Return distance array
```

### Common Errors to Avoid

```
❌ Forgetting to check selected[v] before relaxation
❌ Not checking if dist[v] is actually better
❌ Updating distance after selecting (it's locked!)
❌ Using ∞ without proper handling (INT_MAX causes overflow)
❌ Assuming negative edges work (they don't)
```

---

## Part 8: Mental Picture — Abdo's Water Analogy

### The Visualization

```
Think of Dijkstra like water spreading from the source:

Step 1: Water pours out at source (distance 0)

Step 2: Water spreads to nearest neighbors
        (They get wet first, at distance 1 and 2)

Step 3: From those neighbors, water continues spreading
        (Reaches farther vertices)

Step 4: Water eventually reaches everywhere
        (Or stops if graph is disconnected)

The distance each vertex gets wet at:
= The shortest path distance
```

### Why This Works

```
Water always:
  - Spreads from the closest point
  - Never flows backward
  - Reaches each place exactly once
  - At the minimum distance possible
```

---

## Part 9: Time Complexity

### With Simple Array Scanning

```
Finding minimum:  O(V) per iteration
Vertices:        V iterations
Relaxation:      O(E) total across all iterations

Total: O(V²)
```

**When to use:**
```
✓ Dense graphs
✓ Small V
✓ Teaching/interviews
```

### With Binary Heap (Priority Queue)

```
Finding minimum:    O(log V) per iteration
Vertices:          V iterations
Relaxations:       O((V+E) log V) with decrease-key

Total: O((V + E) log V)
```

**Much better for sparse graphs.**

---

## Part 10: Complete Pseudocode (Detailed)

```
DIJKSTRA_DETAILED(cost[][], source, n)

// Input: cost[n][n] = adjacency matrix with weights
//        source = source vertex (0-indexed)
//        n = number of vertices
// Output: dist[n] = shortest distances

// Step 1: Initialize
dist[0...n-1] = ∞
dist[source] = 0
selected[0...n-1] = false

edgeCount = 0

// Step 2: Main algorithm
While edgeCount < n:
    
    // Find minimum distance unselected vertex
    minDist = ∞
    u = -1
    
    For v = 0 to n-1:
        If selected[v] = false AND dist[v] < minDist:
            minDist = dist[v]
            u = v
    
    If u == -1:
        break  // Disconnected graph
    
    // Lock this distance
    selected[u] = true
    edgeCount = edgeCount + 1
    
    // Relax all neighbors
    For v = 0 to n-1:
        If selected[v] = false AND
           cost[u][v] != ∞ AND
           dist[u] + cost[u][v] < dist[v]:
            dist[v] = dist[u] + cost[u][v]

Return dist[]
```

---

## Part 11: Example with Larger Graph

### The Graph (6 vertices)

```
Edges and weights:
0-1: 4
0-2: 2
1-2: 1
1-3: 5
2-3: 8
2-4: 10
3-4: 2
3-5: 6
4-5: 3

Source: 0
```

### Step-By-Step Execution

```
INITIALIZATION:
dist[] = {0, ∞, ∞, ∞, ∞, ∞}
selected[] = {F, F, F, F, F, F}

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ITERATION 1:
Pick vertex 0 (dist=0, minimum)
selected[0] = T

Relax neighbors of 0:
  0→1: 0+4=4 < ∞ → dist[1]=4
  0→2: 0+2=2 < ∞ → dist[2]=2

dist[] = {0, 4, 2, ∞, ∞, ∞}
selected[] = {T, F, F, F, F, F}

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ITERATION 2:
Pick vertex 2 (dist=2, minimum of unselected)
selected[2] = T

Relax neighbors of 2:
  2→1: 2+1=3 < 4 → dist[1]=3
  2→3: 2+8=10 < ∞ → dist[3]=10
  2→4: 2+10=12 < ∞ → dist[4]=12

dist[] = {0, 3, 2, 10, 12, ∞}
selected[] = {T, F, T, F, F, F}

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ITERATION 3:
Pick vertex 1 (dist=3, minimum of unselected)
selected[1] = T

Relax neighbors of 1:
  1→3: 3+5=8 < 10 → dist[3]=8

dist[] = {0, 3, 2, 8, 12, ∞}
selected[] = {T, T, T, F, F, F}

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ITERATION 4:
Pick vertex 3 (dist=8, minimum of unselected)
selected[3] = T

Relax neighbors of 3:
  3→4: 8+2=10 < 12 → dist[4]=10
  3→5: 8+6=14 < ∞ → dist[5]=14

dist[] = {0, 3, 2, 8, 10, 14}
selected[] = {T, T, T, T, F, F}

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ITERATION 5:
Pick vertex 4 (dist=10, minimum of unselected)
selected[4] = T

Relax neighbors of 4:
  4→5: 10+3=13 < 14 → dist[5]=13

dist[] = {0, 3, 2, 8, 10, 13}
selected[] = {T, T, T, T, T, F}

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ITERATION 6:
Pick vertex 5 (dist=13, only unselected)
selected[5] = T

No outgoing edges from 5.

dist[] = {0, 3, 2, 8, 10, 13}
selected[] = {T, T, T, T, T, T}

COMPLETE!
```

### Final Distances from Vertex 0

```
0 → 0: 0
0 → 1: 3 (path: 0→2→1)
0 → 2: 2 (path: 0→2)
0 → 3: 8 (path: 0→2→1→3)
0 → 4: 10 (path: 0→2→1→3→4)
0 → 5: 13 (path: 0→2→1→3→4→5)
```

---

## Part 12: Key Takeaways (Reference Table)

| Concept | Understand |
|---------|-----------|
| **Problem** | Single source shortest paths to all vertices |
| **Input** | Weighted graph with non-negative edges |
| **Output** | Distance array (distances from source) |
| **Greedy strategy** | Always pick closest unvisited vertex |
| **Relaxation** | Try to improve neighbor distances through current vertex |
| **Why it works** | Non-negative edges guarantee no improvement after selection |
| **Time complexity** | O(V²) with array, O((V+E)logV) with heap |
| **Space complexity** | O(V) for dist and selected arrays |
| **Key arrays** | dist[] (distances), selected[] (finalized) |
| **When to use** | Finding shortest distances from one source |
| **When NOT to use** | Negative edges (use Bellman-Ford), all pairs (use Floyd-Warshall) |
| **Compared to Prim** | Same structure, but distances instead of spanning tree |
| **Compared to BFS** | BFS for unweighted, Dijkstra for weighted |
| **Most common error** | Updating distance after selecting it (it's locked!) |

---

## Part 13: Practice Questions

### Can You Answer These?

1. **Why does Dijkstra require non-negative edges?**
   - Because the greedy choice (minimum distance so far) is only guaranteed optimal with non-negative edges

2. **What does "relaxation" mean?**
   - Checking if going through a vertex improves the distance to a neighbor

3. **Why do we never change selected[u] back to false?**
   - Once dist[u] is finalized, no future path can be shorter (all edges non-negative)

4. **If you pick vertex u and set selected[u] = true, is dist[u] guaranteed to be final?**
   - Yes, because u has the minimum distance, and all edges are non-negative

5. **Why update vertex 2 only if dist[1] + cost[1][2] < dist[2]?**
   - Because we only change distance if we find a better (shorter) path

6. **What's the difference between Dijkstra and Prim's algorithm?**
   - Dijkstra finds shortest paths from one source; Prim builds a minimum spanning tree

7. **What would happen if you picked ANY unvisited vertex instead of the minimum?**
   - The algorithm would not guarantee shortest paths

---

## Part 14: Common Coding Pitfalls

### Pitfall 1: Updating After Selection

```
❌ WRONG:
selected[u] = true
dist[u] = dist[v] + cost[v][u]  // TOO LATE!

✓ CORRECT:
// Update dist[u] BEFORE marking selected
// Once selected[u] = true, dist[u] is fixed
```

### Pitfall 2: Checking Adjacent Vertices

```
❌ WRONG:
For all vertices:
    if dist[u] + cost[u][v] < dist[v]:
        update

(This tries to relax even non-adjacent vertices!)

✓ CORRECT:
For neighbors of u only:
    if dist[u] + cost[u][v] < dist[v]:
        update

(Or check if cost[u][v] != ∞)
```

### Pitfall 3: Infinity Handling

```
❌ WRONG:
dist[v] = ∞
dist[u] + 10 + ... might overflow

✓ CORRECT:
Use INT_MAX carefully, or
Initialize to large number instead of ∞
Or check if dist[u] != ∞ before adding
```

### Pitfall 4: Not Checking Selected

```
❌ WRONG:
For each neighbor v:
    if dist[u] + cost[u][v] < dist[v]:
        dist[v] = ...

(This might re-update a locked vertex!)

✓ CORRECT:
For each neighbor v:
    if selected[v] == false AND
       dist[u] + cost[u][v] < dist[v]:
        dist[v] = ...
```

---

## Part 15: Interview Answer Format

### "Explain Dijkstra's Algorithm"

**Structure (30 seconds):**

```
"Dijkstra finds the shortest path from a single source 
to all other vertices in a weighted graph with non-negative weights.

It uses a greedy strategy: repeatedly select the unvisited vertex 
with minimum distance, finalize it, and use it to relax neighbors."
```

**More detail (1 minute):**

```
"Here's how it works:

1. Initialize: source distance = 0, all others = ∞
2. Repeat:
   - Pick the minimum distance unvisited vertex
   - Lock its distance (it won't change)
   - For each neighbor, check if going through this vertex is cheaper
   - Update their distances if a better path is found
3. Continue until all vertices are processed"
```

**Why it works (30 seconds):**

```
"Because all edges are non-negative, once we pick the minimum 
distance vertex, no future path through other vertices can 
improve it. So we can safely lock that distance and move on."
```

---

## Part 16: The Meta-Lesson

Abdo is teaching you beyond just this algorithm:

### Pattern Recognition

```
Problem: Distance from one source
Solution: Dijkstra (greedy)

Pattern:
  Initialize: start = 0, others = ∞
  Loop: pick min → lock → relax neighbors
  Output: distance array
```

### Why This Matters

```
Once you understand this pattern:
- Prim becomes obvious (same pattern, different meaning)
- Bellman-Ford becomes obvious (relaxation without greedy pick)
- A* becomes obvious (Dijkstra + heuristic)
```

### Algorithm Engineering

```
Same idea + different data structure = different complexity

Array:    O(V²)
Heap:     O((V+E) log V)
Fibonacci: O(V log V + E)

These differences matter in practice.
```

---

## Part 17: Connection to Other Algorithms

Dijkstra is a gateway to:

```
1. Bellman-Ford
   "What if edges can be negative?"
   → Relax all edges n-1 times instead of greedy pick

2. A* Search
   "What if we have a target?"
   → Dijkstra + heuristic toward target

3. Floyd-Warshall
   "What if we need all-pairs shortest paths?"
   → Run Dijkstra from each source

4. Minimum Spanning Tree
   "How is this different from Prim?"
   → Different objective, same structure
```

---

## Part 18: One-Line Memory Aids (Exam Gold)

```
"Pick nearest unvisited, lock it, relax neighbors."

OR

"Always expand from the closest frontier."

OR

"Non-negative edges with greedy distance picks."
```

If you can explain one of these sentences precisely, you understand Dijkstra.

---

## Part 19: When NOT to Use Dijkstra

| Scenario | Why Not | Use Instead |
|----------|---------|-------------|
| **Negative edges** | Greedy fails | Bellman-Ford |
| **All pairs** | Inefficient to repeat n times | Floyd-Warshall |
| **Unweighted graph** | Overkill | BFS |
| **Multiple sources** | Not designed for it | Modify or run multiple |
| **With negative cycles** | Undefined shortest path | Detect and report error |

---

## Part 20: Final Abdo Wisdom

> "Dijkstra teaches you the power of greedy plus non-negative constraints. Memorize the algorithm. But more importantly, understand WHY it works and WHEN it fails. That's what separates the prepared from the truly educated."

---

## Summary Card (For Your Notebook)

```
╔════════════════════════════════════════════════════════════╗
║           DIJKSTRA'S SHORTEST PATH ALGORITHM              ║
╠════════════════════════════════════════════════════════════╣
║                                                            ║
║  Problem:  Shortest distances from source to all vertices  ║
║  Input:    Weighted graph, non-negative edges, source     ║
║  Output:   dist[] array of shortest distances             ║
║                                                            ║
║  Algorithm:                                                ║
║    1. dist[source] = 0, others = ∞, selected[] = false   ║
║    2. While unvisited remain:                              ║
║       a. Pick u with min unvisited dist[u]                 ║
║       b. Mark selected[u] = true (LOCKED)                  ║
║       c. For each neighbor v of u:                         ║
║          if dist[u] + cost[u][v] < dist[v]:              ║
║             dist[v] = dist[u] + cost[u][v]               ║
║                                                            ║
║  Complexity:  O(V²) with array, O((V+E)logV) with heap   ║
║  Space:       O(V) for dist and selected arrays            ║
║  Greedy:      Always pick closest unvisited vertex        ║
║                                                            ║
║  Key Insight:                                              ║
║    Non-negative edges → once selected, dist never changes  ║
║                                                            ║
║  When:  Single-source shortest paths, non-negative edges   ║
║  NOT:   Negative edges (Bellman-Ford), all pairs (Floyd)  ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝
```
