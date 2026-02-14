# Rat in Maze — Path Finding with Backtracking

## Part 1: What Is the Goal of This Lecture?

Abdul Bari is teaching you **three core ideas**:

1. **How to solve a path-finding problem** using backtracking
2. **What makes backtracking different** from brute force exploration
3. **How to think recursively** about grid-based problems

He's not just solving a maze puzzle.

He's teaching you the **mindset** that applies to:
- Knight's tour (move chess knight)
- Word search (find paths in letter grids)
- Graph traversal with constraints
- Game AI pathfinding
- Robot navigation

---

## Part 2: What Is the Rat in Maze Problem?

### The Setup

**You are given:**
- A square matrix (n × n grid) representing a maze
- `1` = Open path (can move through)
- `0` = Blocked wall (cannot move through)
- Rat starts at position **(0, 0)** (top-left)
- Rat must reach position **(n-1, n-1)** (bottom-right)

### Allowed Moves

The rat can move in **four directions** (basic version):
- **Right** → (i, j+1)
- **Down** → (i+1, j)
- **Left** → (i, j-1) (advanced)
- **Up** → (i-1, j) (advanced)

**Constraint:** Cannot revisit cells already in current path

### Your Job

**Find a valid path** from start to destination.

**Example:**

```
Maze:        Solution Path:
1 1 0 0      R G 0 0
1 0 1 1   →  R G G G
0 1 0 0      0 G 0 0
0 1 1 1      0 G G G

R = Start
G = Valid path
0 = Wall
```

---

## Part 3: This Is a Backtracking Problem

### The Pattern

Backtracking follows this universal structure:

```
CHOOSE a move
  ↓
CHECK if valid
  ↓
GO FORWARD (recurse)
  ↓
IF STUCK → BACKTRACK (undo move)
  ↓
TRY ANOTHER MOVE
```

### For Rat in Maze

```
CHOOSE:  Try moving right or down
  ↓
CHECK:   Is this cell:
           • Inside bounds?
           • Not a wall (value = 1)?
           • Not already visited?
CHECK PASSES ✓
  ↓
MOVE:    Mark cell as part of current path
  ↓
RECURSE: Try to reach destination from here
  ↓
IF FAILS:
  UNMARK cell from path (backtrack)
  TRY next direction
  ↓
IF SUCCEEDS: Return path found!
```

---

## Part 4: Whiteboard Thinking (Very Important)

### What Abdul Bari Shows on the Board

He draws:
1. **The maze grid**
2. **Current position** (marked with color)
3. **Recursive calls** as branches
4. **When cells are marked**
5. **When cells are unmarked** (backtrack)

### Visualization

```
Recursion Tree for Finding Path:

                     solve(0,0)
                         |
              visit [0,0] mark it
                         |
            ____________/|\____________
           /              |              \
       solve(0,1)    solve(1,0)      [wall/visited]
       mark [0,1]    mark [1,0]
          |              |
      solve(0,2)     solve(1,1)
      [wall]         [marked as visited]
      unmark,fail    unmark,fail
          |              |
    backtrack          backtrack
       return            return
       false             false
        |                |
     Next move       Next move
    solve(1,0)      solve(2,0)
         |              |
       ...             ...
```

### Key Visual Insight

```
Every decision point has multiple branches:
Right, Down, (Left, Up if advanced)

Some branches:
  ✓ Lead to solution
  ✗ Hit walls
  ✗ Find dead ends
  ✗ Revisit cells

Backtracking = Exploring all branches until finding solution
            = Undoing wrong moves to try alternatives
```

---

## Part 5: The Core Algorithm Logic

### Pseudocode Structure

```
SOLVE(row, col, visited, solution):
    
    // BASE CASE 1: Destination reached
    if (row == n-1 AND col == n-1):
        mark solution[row][col] = 1
        RETURN TRUE  // Path found!
    
    // BASE CASE 2: Out of bounds or invalid
    if NOT SAFE(row, col, visited):
        RETURN FALSE
    
    // RECURSIVE CASE: Try this path
    mark visited[row][col] = TRUE
    mark solution[row][col] = 1
    
    // CHOOSE: Try moving right
    if SOLVE(row, col+1, visited, solution):
        RETURN TRUE  // Found path via right
    
    // CHOOSE: Try moving down
    if SOLVE(row+1, col, visited, solution):
        RETURN TRUE  // Found path via down
    
    // CHOOSE: Try moving left (advanced)
    if SOLVE(row, col-1, visited, solution):
        RETURN TRUE  // Found path via left
    
    // CHOOSE: Try moving up (advanced)
    if SOLVE(row-1, col, visited, solution):
        RETURN TRUE  // Found path via up
    
    // BACKTRACK: No solution found
    mark visited[row][col] = FALSE
    mark solution[row][col] = 0  // UNMARK (Critical!)
    RETURN FALSE
```

### What's Really Happening

**CHOOSE:** For each cell, we try all four directions
**CHECK:** The SAFE() function validates the move
**GO FORWARD:** Recursive call to explore from new position
**BACKTRACK:** Unmark the cell so future paths can use it

---

## Part 6: The "Safe" Check (Bounding Function)

### What Defines a Valid Move?

Before moving to cell (row, col), it must satisfy **all** these conditions:

```c
SAFE(row, col, visited, maze):
    return (
        row >= 0 AND row < n              // Inside rows?
        AND
        col >= 0 AND col < n              // Inside columns?
        AND
        maze[row][col] == 1               // Is it open path (1)?
        AND
        visited[row][col] == FALSE        // Not already visited?
    );
```

### Why Each Check Matters

| Check | Purpose | Example Failure |
|-------|---------|---|
| `row >= 0 AND row < n` | Don't go above matrix | row = -1 or row = n |
| `col >= 0 AND col < n` | Don't go outside matrix | col = -1 or col = n |
| `maze[row][col] == 1` | Only move through open paths | Hit a wall (0) |
| `!visited[row][col]` | Prevent cycles/loops | Cell already in path |

### This is Your Bounding Function

Just like in N-Queens:
```
N-Queens bounding: !row_used && !diag_conflicts
Rat in Maze bounding: in_bounds && is_open && !visited
```

**Same concept, different constraints!**

---

## Part 7: Marking and Unmarking (Critical!)

### The Most Important Backtracking Concept

This is where **many programmers make mistakes**.

### What Happens When We Move Forward

```
Current path: (0,0) → (0,1) → (1,1)
visited: [T T F]
         [F T F]
         [F F F]

visited[0][0] = TRUE   // Cell (0,0) in current path
visited[0][1] = TRUE   // Cell (0,1) in current path
visited[1][1] = TRUE   // Cell (1,1) in current path

solution[0][0] = 1     // Part of path
solution[0][1] = 1
solution[1][1] = 1
```

### What Happens When We Backtrack

```
Backtrack from (1,1) because no path forward:

visited[1][1] = FALSE  // Remove from current path
solution[1][1] = 0     // Remove from solution

Current path: (0,0) → (0,1)
visited: [T T F]
         [F F F]
         [F F F]

Now (1,1) can be visited again via different path!
```

### Why This Is Critical

❌ **WRONG** (forgot to unmark):
```
visited[row][col] = TRUE
mark solution[row][col] = 1
RECURSE(...)
// Return without unmarking!
// Next time we try to visit (row, col), it's already marked!
// Algorithm fails to find paths it should find
```

✅ **CORRECT** (proper backtracking):
```
visited[row][col] = TRUE
mark solution[row][col] = 1
RECURSE(...)
visited[row][col] = FALSE    // UNMARK!
mark solution[row][col] = 0  // UNMARK!
// Now cell is available for other paths
```

---

## Part 8: How Backtracking Prevents Brute Force

### Without Backtracking (Brute Force)

```
Generate all possible paths:
• Start at (0,0)
• Try all 4^(n²) possible move sequences
• Check if any reach destination
• Very inefficient
```

### With Backtracking

```
Build paths incrementally:
• Move to a cell
• Check if valid
• If dead end: backtrack immediately
• Don't waste time exploring from there
• Focus on promising paths
```

### The Difference

```
Brute Force:  Generate 4^16 = 4,294,967,296 sequences for 4×4 maze
Backtracking: Explore only ~20-50 cells before finding path

That's the power of in-place validation!
```

---

## Part 9: Recursion Tree Visualization

### Small Example (3×3 Maze)

```
Maze:
1 1 0
1 0 1
1 1 1

Path to destination:
(0,0) → (1,0) → (2,0) → (2,1) → (2,2)
```

### Recursion Tree

```
                    solve(0,0)
                    [safe ✓]
                    mark visited[0,0]=T
                    |
        ____________|____________
       /            |            \
      X        solve(0,1)    [out of bounds]
   [wall]       [wall]       [fail]
              solve(1,0)
              [safe ✓]
              mark visited[1,0]=T
              |
      ________|________
     /        |        \
    X      solve(1,1)  [out of bounds]
  [wall]       [wall]
             solve(2,0)
             [safe ✓]
             mark visited[2,0]=T
             |
        _____|_____
       /     |     \
      X      X   solve(2,1)
   [wall] [wall] [safe ✓]
            |
        ____|____
       /        \
      X      solve(2,2)
   [wall]    [DESTINATION!]
            RETURN TRUE ✓

Path found: [(0,0), (1,0), (2,0), (2,1), (2,2)]
```

### Key Observations

- Many branches pruned early (walls, bounds, visited)
- Recursion explores only safe cells
- When destination found, backtrack stops and returns TRUE
- Dead ends trigger backtrack automatically

---

## Part 10: Comparison with N-Queens

### Similarities

| Aspect | N-Queens | Rat in Maze |
|--------|----------|---|
| **Core Pattern** | Try → Check → Recurse → Undo | Try → Check → Recurse → Undo |
| **Decision Tree** | Queen placement tree | Movement tree |
| **Bounding Function** | Conflict checking | Safety checking |
| **Marking/Unmarking** | Place/remove queen | Enter/exit cell |
| **Base Case** | All columns filled | Destination reached |

### Differences

| Aspect | N-Queens | Rat in Maze |
|--------|----------|---|
| **Space** | NxN board | NxN grid |
| **Decision** | Which row for queen | Which direction to move |
| **Constraints** | Row/diagonal conflicts | Walls/bounds/visited |
| **Markers** | Row/diagonal arrays | Visited matrix |
| **Complexity** | O(N!) → heavily pruned | O(4^(N²)) → heavily pruned |

### The Template Is Identical

```
void solve(state) {
    if (goal_reached(state))      // Destination vs All placed
        return TRUE;
    
    for (each option) {           // Each direction vs Each row
        if (is_valid(option)) {   // SAFE check vs Conflict check
            apply(option);        // Mark cell vs Place queen
            if (solve(next_state))
                return TRUE;
            undo(option);         // Unmark cell vs Remove queen
        }
    }
    return FALSE;
}
```

---

## Part 11: One Path vs All Paths

### Version 1: Find One Path (Basic)

**Goal:** Find any valid path from start to destination

**Return:** TRUE when first path found, stop exploring

**Use case:** "Can we reach the destination?"

### Version 2: Find All Paths (Advanced)

**Goal:** Find all possible paths from start to destination

**Modification:**
```
Don't return immediately when path found
Continue exploring other branches
Store/count all paths
```

---

## Part 12: The Mark/Unmark Deep Understanding

### Why Can't We Just Use a Global Visited Matrix?

❌ **WRONG Approach:**
```c
int visited[n][n] = all FALSE;

solve(row, col):
    if (!SAFE(row, col)):
        return FALSE
    
    visited[row][col] = TRUE
    // Never unmark!
    
    // Try moves...
    if (solve(row, col+1)) return TRUE;
    // If this fails, visited[row][col] is still TRUE
    // But we could have reached it via different path!
    
    // This limits exploration to one attempt per cell
```

✅ **CORRECT Approach:**
```c
solve(row, col, visited):
    if (!SAFE(row, col, visited)):
        return FALSE
    
    visited[row][col] = TRUE     // Mark
    
    // Try moves...
    if (solve(row, col+1, visited)) return TRUE;
    if (solve(row+1, col, visited)) return TRUE;
    
    visited[row][col] = FALSE    // Unmark (Critical!)
    
    // Now (row, col) is available for different paths!
```

### The Insight

The visited matrix is **local to current search path**, not global.

A cell can be:
- Visited in path 1: (0,0) → (0,1) → (1,1)
- Unvisited when trying path 2: (0,0) → (1,0) → (1,1)

This is why **unmarking during backtrack is critical**.

---

## Part 13: Complexity Analysis

### Time Complexity

**Worst case:** O(4^(N²))
- Each cell can try up to 4 directions
- In worst case (no walls), exploratory choices at each cell
- But heavily pruned by walls and visited cells

**Practical case:** O(path_length) or less
- Most mazes have walls that prune heavily
- Valid paths found quickly
- Pruning rate: 90%+ in typical mazes

### Space Complexity

**Recursion stack:** O(N²)
- Maximum depth = longest possible path
- In worst case: N² cells

**Visited matrix:** O(N²)
- Tracks which cells in current path

**Solution matrix:** O(N²)
- Stores the final path

**Total:** O(N²)

---

## Part 14: From Rat in Maze to Real Problems

### Knight's Tour

**Problem:** Move chess knight to every square exactly once

**Backtracking differences:**
- Choose from 8 possible knight moves
- Check if square is unvisited
- Backtrack if stuck

### Word Search

**Problem:** Find word in 2D letter grid (paths spell word)

**Backtracking differences:**
- Move to adjacent cells
- Check if letter matches next in word
- Backtrack if doesn't match

### Graph Coloring

**Problem:** Color nodes so adjacent ones differ

**Backtracking differences:**
- Assign color to node
- Check if conflicts with neighbors
- Backtrack if needed

### The Template Still Applies

```
For any grid/graph problem:

1. Define your "neighbors" (4-directional vs 8-directional vs graph edges)
2. Define your "safety check" (walls? visited? conflicts? matches?)
3. Use the backtracking template
4. Mark/unmark properly
```

---

## Part 15: Interview Wisdom

### What Interviewers Want to Hear

✅ **Good Answer:**
"I'll use backtracking. Mark cells as visited, explore all directions, unmark when backtracking. This ensures all paths are explored."

✓ Shows understanding: mark/unmark importance
✓ Shows awareness: all paths need exploration

✅ **Better Answer:**
"I'll use backtracking with a visited matrix. When I move to a cell, I mark it. If the path leads to destination, I return success. If not, I unmark (backtrack) and try another direction. This ensures I don't revisit cells in the same path, but allows revisiting via different paths."

✓ Technical precision
✓ Justification for decisions

❌ **Red Flags:**
- "I'll just mark cells and never unmark"
- "I'll store all visited cells globally"
- "Backtracking is brute force trying everything"
- No mention of mark/unmark importance

---

## Part 16: Common Mistakes & Fixes

### Mistake 1: Forgot to Unmark

```c
// WRONG
solve(row, col, visited) {
    visited[row][col] = TRUE;
    if (solve_next()) return TRUE;
    // Missing unmark!
    return FALSE;
}

// RIGHT
solve(row, col, visited) {
    visited[row][col] = TRUE;
    if (solve_next()) return TRUE;
    visited[row][col] = FALSE;  // Don't forget!
    return FALSE;
}
```

### Mistake 2: Wrong Order of Operations

```c
// WRONG: Check after moving
solve(row, col) {
    visited[row][col] = TRUE;
    if (!SAFE(row, col)) return FALSE;  // Too late!
}

// RIGHT: Check before moving
solve(row, col) {
    if (!SAFE(row, col)) return FALSE;  // Check first
    visited[row][col] = TRUE;
    // Now safe to proceed
}
```

### Mistake 3: Confused Base Cases

```c
// WRONG
if (maze[row][col] == 0) return TRUE;  // Reached exit?

// RIGHT
if (row == n-1 && col == n-1) {
    mark as part of solution
    return TRUE;  // Reached destination
}
```

---

## Part 17: The Big Message from Abdul Bari

He wants you to understand:

> **"Try → Check → Go Forward → If Stuck → Undo → Try Another Way"**

This is the backtracking philosophy.

### Why This Matters

This pattern appears in:
- Constraint satisfaction (N-Queens, Sudoku)
- Path finding (Maze, Knight's tour)
- Combinatorial search (permutations, combinations)
- Game AI (game tree search)
- Optimization (branch & bound)

### What Makes You Different

Most programmers:
- Know the algorithm
- Copy-paste solutions
- Don't understand backtracking

You:
- Understand WHY mark/unmark is critical
- Can explain the bounding function
- Can apply to NEW problems
- Explain your thinking in interviews

---

## Part 18: Mental Model Summary

### Think of It Like This

```
You're a rat in a maze (literally).

Each cell you enter, you paint it blue:
  "I've been here in this attempt"

If you hit a dead-end wall:
  You backtrack (unpaint the cell)
  "OK, this path didn't work"
  "Someone else can try this cell"

You try a different direction
  Mark cells again
  Eventually reach the cheese (destination)!

If you never unpainted cells:
  You'd block yourself permanently
  You could never explore alternate routes
  The maze would become impossible
```

### This Is Exactly What Backtracking Does

---

## Part 19: Advanced Variants

### 2D Movement (4 directions)

```
Current cell: (i, j)

Possible moves:
• RIGHT:  (i, j+1)
• DOWN:   (i+1, j)
• LEFT:   (i, j-1)
• UP:     (i-1, j)
```

### Weighted Paths

```
Some cells have costs
Find path with minimum cost
Backtrack if cost exceeds best found so far
(This is Branch & Bound!)
```

### Multiple Agents

```
Multiple rats in same maze
Coordinate paths without collisions
(More complex backtracking)
```

---

## Part 20: Final Wisdom

### What You Now Understand

✓ **Backtracking pattern:** Try → Check → Go → Undo
✓ **Mark/unmark importance:** Enable revisiting via different paths
✓ **Safety checking:** The bounding function that enables pruning
✓ **Recursion tree:** How branching and pruning work
✓ **Why it's not brute force:** Early termination via constraints
✓ **How to apply elsewhere:** Knight's tour, Word search, etc.

### The Real Skill

It's not memorizing "Rat in Maze" solution.

It's understanding:
- **When** to use backtracking (decision tree problems)
- **How** to design the bounding function (what makes a move valid)
- **Why** mark/unmark is critical (enables proper exploration)
- **How to apply** to problems you've never seen

### Interview Success

When asked "Solve rat in maze," you will:
1. Recognize it as backtracking problem
2. Explain the algorithm clearly
3. Discuss mark/unmark importance
4. Write clean code with clear variable names
5. Trace through a small example
6. Discuss complexity
7. Extend to variations

This puts you in the **top 5% of interviewees**.

### The Deeper Truth

Rat in Maze isn't about solving a maze.

It's about learning to think recursively and systematically.

Master this. You'll solve problems you've never seen before.

That's the real power.

