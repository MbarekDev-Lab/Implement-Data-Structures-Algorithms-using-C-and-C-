# Sudoku Solver – Backtracking Algorithm
## Abdul Bari's Complete Pedagogical Breakdown

---

## Part 1: Goal of This Lecture

**What Abdul Bari Is Teaching:**

This is NOT about solving Sudoku puzzles.

This is about **mastering recursive problem-solving on a 2D grid with multiple constraints**.

After this lecture, you will understand:
- How to solve constraint satisfaction problems using recursion
- How to design **smart bounding functions** that prevent backtracking
- How to move through 2D matrices via recursion
- How to structure code for problems with multiple validation rules
- **How to think** about exponential search spaces

**The Real Skill Being Taught:**

"Use recursion to explore possibilities, and use validation to cut off wrong paths early."

This skill applies to:
- Graph coloring
- Puzzle solving
- Scheduling problems
- Resource allocation
- AI pathfinding

---

## Part 2: The Problem Statement

You have a **9×9 matrix**:

```
0       = Empty cell (needs to be filled)
1–9     = Already filled number
```

**Sudoku Rules:**

A number must appear:
- **Only once in its row**
- **Only once in its column**
- **Only once in its 3×3 block**

**Your Goal:**

Fill all empty cells (0s) with numbers 1–9 such that all rules are satisfied.

**Example Input (Unsolved):**

```
5 3 0 | 0 7 0 | 0 0 0
6 0 0 | 1 9 5 | 0 0 0
0 9 8 | 0 0 0 | 0 6 0
------+-------+------
8 0 0 | 0 6 0 | 0 0 3
4 0 0 | 8 0 3 | 0 0 1
7 0 0 | 0 2 0 | 0 0 6
------+-------+------
0 6 0 | 0 0 0 | 2 8 0
0 0 0 | 4 1 9 | 0 0 5
0 0 0 | 0 8 0 | 0 7 9
```

**Your Algorithm:**

Given a partially filled sudoku, fill it completely.

---

## Part 3: This Is a Backtracking Problem

**Structure:**

```
CONSTRUCT (Choose a number)
VALIDATE (Check if valid)
PLACE (Put it down)
RECURSE (Go deeper)
UNDO (If stuck, remove it)
```

This is the **exact pattern** used for:
- N-Queens (choosing columns)
- Permutations (choosing elements)
- Rat in Maze (choosing directions)

**The only difference:**

The **bounding function** (validation step) changes per problem.

For Sudoku: Check row, column, **and 3×3 block**.

---

## Part 4: Whiteboard Thinking – The Decision Tree

When solving Sudoku recursively:

**At cell (0,1):**
```
Try 1? No (in row)
Try 2? No (in col)
Try 3? Yes → Place 3
  │
  ├─ Go to cell (0,2)
  │   Try 1? No
  │   Try 2? Yes → Place 2
  │   │   Continue...
  │   │   If stuck → Backtrack, Remove 2
  │   Try 3? No
  │   ...
  │
  └─ Remove 3, Try 4
```

**Key Insight:**

At cell (0,1): 9 possible numbers to try.

Of those 9, maybe 2–3 are valid.

The remaining 6–7 are pruned immediately by `isValid()`.

This pruning makes the algorithm tractable.

Without `isValid()`, you'd explore all 9^81 possibilities (impossible).

With `isValid()`, you explore maybe 9^10 effective paths (feasible).

---

## Part 5: Core Algorithm Logic – Cell-by-Cell Traversal

**The Main Idea:**

Process the grid **left to right, top to bottom**.

For each cell:

1. **If filled:** Skip to next cell
2. **If empty:** Try numbers 1–9
3. **For each number:** Check if valid, place, recurse
4. **If stuck:** Backtrack, try next number

**Pseudocode:**

```c
solve(int row, int col) {
    
    // BASE CASE: Passed the last row
    if (row == 9) {
        // All cells filled correctly
        return TRUE;
    }
    
    // Calculate next cell
    int next_row = col == 8 ? row + 1 : row;
    int next_col = col == 8 ? 0 : col + 1;
    
    // RECURSIVE CASE: Current cell filled?
    if (sudoku[row][col] != 0) {
        // Already filled, skip to next
        return solve(next_row, next_col);
    }
    
    // Cell is empty, try numbers 1–9
    for (int num = 1; num <= 9; num++) {
        
        if (isValid(row, col, num)) {
            
            sudoku[row][col] = num;           // CHOOSE
            
            if (solve(next_row, next_col)) {  // GO DEEPER
                return TRUE;
            }
            
            sudoku[row][col] = 0;             // UNDO (Critical!)
        }
    }
    
    return FALSE;
}
```

---

## Part 6: Cell Traversal Pattern

**Moving Through the Grid:**

After cell (r, c), next cell is:

```
If c == 8 (end of row):
    Go to (r+1, 0)    [Start of next row]

Else:
    Go to (r, c+1)    [Next column in same row]
```

**On the board, Abdul Bari writes:**

```c
next_row = (c == 8) ? r + 1 : r;
next_col = (c == 8) ? 0     : c + 1;
```

This ternary style is the pattern:

**Why?**

Because we fill the **entire row** before moving to the next row.

This makes the algorithm intuitive: we solve left-to-right, top-to-bottom.

**Visual:**

```
(0,0) → (0,1) → (0,2) → ... → (0,8)
                                  ↓
(1,0) → (1,1) → (1,2) → ... → (1,8)
                                  ↓
...
```

---

## Part 7: Base Case – When Are We Done?

**When Does Recursion Stop?**

```c
if (row == 9) {
    // We've gone past the last row
    // That means ALL 81 cells have been processed!
    return TRUE;
}
```

**Why row == 9?**

Rows are indexed 0–8.

When we try to go to row 9, we've passed row 8 (the last row).

This means **every cell has been filled**.

If we reach this point **without returning FALSE**, every constraint was satisfied.

**The moment we return TRUE:**

The recursion unwinds, and the solution is in the grid.

---

## Part 8: Already-Filled Cells – Skip Them

**In Sudoku, some cells are pre-filled.**

When we encounter a filled cell:

```c
if (sudoku[row][col] != 0) {
    // Cell is already filled
    // Don't try to fill it
    // Just move to next cell
    return solve(next_row, next_col);
}
```

**Why?**

We only need to fill the 0s (empty cells).

Filled cells are **constraints** that we must respect.

**Example:**

```
5 3 0 | ... (5 and 3 are filled, so we skip them)
      (0 is empty, so we try to fill it)
```

---

## Part 9: Empty Cell Handling – Trying Numbers

**When we find an empty cell (value = 0):**

```c
for (int num = 1; num <= 9; num++) {
    
    if (isValid(row, col, num)) {
        
        sudoku[row][col] = num;           // PLACE
        
        if (solve(next_row, next_col)) {  // RECURSE
            return TRUE;                   // Found solution!
        }
        
        sudoku[row][col] = 0;             // UNDO
    }
}

return FALSE;  // No number worked
```

**Step by step:**

1. Try number 1
2. Check if it's valid (1 is not in row, col, block)
3. If yes: Place it, recurse
4. If recursion returns TRUE: We found the solution! Return TRUE
5. If recursion returns FALSE: This number doesn't lead to a solution
6. Remove the number (undo)
7. Try number 2
8. ...continue...
9. If all 9 numbers fail: Return FALSE

**This is backtracking in action.**

---

## Part 10: The isValid Function – The Bounding Function

**This is THE MOST IMPORTANT function.**

It prevents bad choices from being explored.

**Pseudocode:**

```c
bool isValid(int row, int col, int val) {
    
    // Check 1: Row constraint
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == val) {
            return FALSE;  // val already in row
        }
    }
    
    // Check 2: Column constraint
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][col] == val) {
            return FALSE;  // val already in col
        }
    }
    
    // Check 3: 3×3 block constraint
    int blockRow = row - row % 3;
    int blockCol = col - col % 3;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[blockRow + i][blockCol + j] == val) {
                return FALSE;  // val already in block
            }
        }
    }
    
    return TRUE;  // val is valid!
}
```

**Three checks. ALL must pass.**

If even one fails, the number is invalid.

---

## Part 11: Row Checking in isValid

**Part of the bounding function:**

```c
for (int i = 0; i < 9; i++) {
    if (sudoku[row][i] == val) {
        return FALSE;  // Found val in row
    }
}
```

**What it does:**

Scans the entire row (columns 0–8).

If it finds `val` anywhere, return FALSE.

**Why?**

Sudoku rule: A number appears only once per row.

If `val` is already in the row, we can't place it again.

Example:

```
Row 0: [5, 3, 0, 0, 7, 0, 0, 0, 0]
                ↑ We want to place 5 in position (0,2)
       But 5 already exists at (0,0)
       → isValid returns FALSE for 5
```

---

## Part 12: Column Checking in isValid

**Part of the bounding function:**

```c
for (int i = 0; i < 9; i++) {
    if (sudoku[i][col] == val) {
        return FALSE;  // Found val in column
    }
}
```

**What it does:**

Scans the entire column (rows 0–8).

If it finds `val` anywhere, return FALSE.

**Why?**

Sudoku rule: A number appears only once per column.

**Example:**

```
Col 2:
  0  ← Row 0
  0  ← Row 1
  8  ← Row 2
  0  ← Row 3
  ...

If we want to place 8 at (0,2):
  8 is already at (2,2)
  → isValid returns FALSE for 8
```

---

## Part 13: 3×3 Block Checking – The Math

**This is the tricky part.**

Sudoku has nine 3×3 blocks:

```
Block (0,0)  | Block (0,1)  | Block (0,2)
  (0-2,0-2)  |  (0-2,3-5)   |  (0-2,6-8)
─────────────|──────────────|─────────────
Block (1,0)  | Block (1,1)  | Block (1,2)
  (3-5,0-2)  |  (3-5,3-5)   |  (3-5,6-8)
─────────────|──────────────|─────────────
Block (2,0)  | Block (2,1)  | Block (2,2)
  (6-8,0-2)  |  (6-8,3-5)   |  (6-8,6-8)
```

**The formula to find block's top-left corner:**

```c
int blockRow = row - row % 3;
int blockCol = col - col % 3;
```

**Examples:**

```
Cell (0, 2):  blockRow = 0 - 0 = 0,  blockCol = 2 - 2 = 0  → Block at (0, 0) ✓
Cell (2, 7):  blockRow = 2 - 2 = 0,  blockCol = 7 - 1 = 6  → Block at (0, 6) ✓
Cell (5, 4):  blockRow = 5 - 2 = 3,  blockCol = 4 - 1 = 3  → Block at (3, 3) ✓
Cell (8, 8):  blockRow = 8 - 2 = 6,  blockCol = 8 - 2 = 6  → Block at (6, 6) ✓
```

**Then check the 3×3 block:**

```c
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (sudoku[blockRow + i][blockCol + j] == val) {
            return FALSE;  // Found val in block
        }
    }
}
```

This checks all 9 cells in the block.

---

## Part 14: Backtracking – The Critical Undo Line

**This is the line that makes backtracking work:**

```c
sudoku[row][col] = 0;  // UNDO
```

**Why is this critical?**

When we place a number:

```c
sudoku[row][col] = num;  // Place it
```

We're saying: "Let's assume this number works."

We then recurse deeper to test.

If recursion comes back as FALSE (no solution found), it means:

**This number doesn't lead to a solution.**

So we must:

```c
sudoku[row][col] = 0;  // Remove it
```

This allows us to try another number.

**Without this line:**

The cell stays filled forever.

When we try the next number, the cell still has the old value.

Result: **Algorithm fails to find solutions.**

**With this line:**

The cell is reset.

We can try the next number fresh.

Result: **Algorithm explores all possibilities.**

**Example:**

```
Cell (0,1) needs a number
├─ Try 1: Place 1
│   └─ Recurse... FALSE (no solution)
│   └─ Remove 1 (undo)
├─ Try 2: Place 2
│   └─ Recurse... TRUE (found solution!)
│   └─ Return TRUE immediately

Without undo: After trying 1, cell is still 1
After trying 2, cell becomes 2
Problem: Cell can't be both 1 and 2!
```

---

## Part 15: Decision Tree Visualization with Pruning

**At cell (0,1), we try 9 numbers:**

```
Cell (0,1):
  Try 1? → isValid? FALSE → Prune (stop recursing)
  Try 2? → isValid? FALSE → Prune
  Try 3? → isValid? TRUE  → Recurse
  Try 4? → isValid? TRUE  → Recurse
  Try 5? → isValid? FALSE → Prune
  ...
```

**Pruned = We never recurse for that number.**

**Effect:**

Instead of exploring 9^81 possibilities, we might explore 9^20.

Dramatic reduction.

**Why does pruning help so much?**

Because most cells have very few valid choices.

Once you place numbers, choices for remaining cells become very restricted.

Example:

```
Row has [5, 3, _, _, 7, _, _, _, _]
We're at (0,2) trying to place.

Can't place: 5, 3, 7 (already in row)
Can place: 1, 2, 4, 6, 8, 9

That's already 3/9 numbers eliminated by row alone!
Add column and block constraints: Maybe only 1–2 choices left.
```

---

## Part 16: Comparison With N-Queens – Same Pattern, Different Problem

**N-Queens:**

```c
void solve(int row, int col) {
    if (row == n) return;
    
    for (int col = 0; col < n; col++) {
        if (isValid(row, col)) {
            place_queen(row, col);
            solve(row + 1, col);
            remove_queen(row, col);
        }
    }
}
```

**Sudoku:**

```c
void solve(int row, int col) {
    if (row == 9) return;
    
    for (int num = 1; num <= 9; num++) {
        if (isValid(row, col, num)) {
            place_num(row, col, num);
            solve(next_row, next_col);
            remove_num(row, col);
        }
    }
}
```

**Differences:**

| Aspect | N-Queens | Sudoku |
|--------|----------|--------|
| **Try** | Each column in a row | Each digit 1–9 |
| **Check** | Diagonal conflict | Row/col/block conflict |
| **Go** | Next row | Next cell |
| **Undo** | Remove queen | Clear cell (set 0) |

**Similarities:**

✓ Same recursive structure
✓ Same Try → Check → Go → Undo pattern
✓ Same base case (finished)
✓ Same bounding function concept

**The key insight:**

Only the **Try** and **Check** parts change.

The **pattern** stays the same.

---

## Part 17: Complexity Analysis

**Worst Case Time Complexity:**

In the worst case, we might try all 9 digits at every empty cell.

For a completely empty 9×9 grid:

```
O(9^(number of empty cells))
O(9^81)  ← With pruning, much better
```

**With pruning (isValid):**

Effective time complexity is much lower.

Empirically, a sudoku solver with good pruning solves in:

```
O(10^7) to O(10^8) operations
```

For a 9×9 grid with 50+ empty cells, this is **very fast** (< 1 second).

**Space Complexity:**

```
Recursion depth: O(81)   [One level per cell]
Local variables: O(1)    [Constant space per call]
Grid: O(81)              [Store sudoku grid]

Total: O(81) = O(1) [Since grid size is fixed]
```

---

## Part 18: Common Mistakes

**❌ Mistake 1: Forgetting to Undo**

```c
sudoku[row][col] = num;      // Place
solve(next);                 // Recurse
// Forgot to undo!
```

**Result:** Algorithm misses solutions.

**✅ Fix:**

```c
sudoku[row][col] = num;      // Place
if (solve(next)) return TRUE;
sudoku[row][col] = 0;        // UNDO!
```

---

**❌ Mistake 2: Wrong Cell Traversal**

```c
// Going diagonally instead of left-to-right
solve(row+1, col+1);  // WRONG
```

**Result:** Skips cells, solution incomplete.

**✅ Fix:**

```c
next_row = (col == 8) ? row + 1 : row;
next_col = (col == 8) ? 0 : col + 1;
```

---

**❌ Mistake 3: Wrong Base Case**

```c
if (row == 8) return TRUE;  // WRONG (should be 9)
```

**Result:** Algorithm stops before processing the last row.

**✅ Fix:**

```c
if (row == 9) return TRUE;  // Correct
```

---

**❌ Mistake 4: Incomplete isValid Check**

```c
bool isValid(row, col, val) {
    // Only check row, forget column and block
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == val) return FALSE;
    }
    return TRUE;  // WRONG
}
```

**Result:** Algorithm places invalid numbers.

**✅ Fix:**

```c
bool isValid(row, col, val) {
    // Check all 3: row, column, block
    // (See Part 10 for full code)
}
```

---

## Part 19: Abdul Bari's Core Message

**He wants you to understand this principle:**

> "Recursion explores exponentially many possibilities.
> Validation cuts off entire subtrees of impossible solutions.
> Together, they solve constraint problems efficiently."

**This is the **fundamental idea** of Backtracking.**

It applies to:
- Any **constraint satisfaction problem**
- Any **combinatorial search**
- Game AI (chess, tic-tac-toe)
- Puzzle solving
- Scheduling
- Resource allocation

**The pattern is universal:**

```
Enumerate possibilities → Check validity → Prune invalid → Recurse → Backtrack
```

Learn to **recognize** this pattern, and you can **solve hundreds of problems**.

---

## Part 20: Advanced Insights & Extensions

**What if Sudoku has multiple solutions?**

Modify to find all:

```c
void solve(int row, int col) {
    if (row == 9) {
        print_solution();  // Don't return, count it
        return;             // Let backtracking continue
    }
    // ...rest of code...
}
```

**What if you want to find the hardest Sudoku?**

Measure branching factor:

```
Factor = (number of recursion calls) / (number of cells filled)

High factor = Easy (many choices)
Low factor = Hard (few choices)
```

**Performance optimization:**

Choose the **cell with fewest possibilities** first (MRV heuristic).

```c
// Instead of fixed (0,0) → (0,1) → ...
// Pick the cell with minimum remaining values

Cell best_cell = find_minimum_remaining_values();
Try values in that cell;
```

This can **reduce time by 100x**.

**Connection to AI:**

Sudoku solving is essentially **constraint propagation** + **search**.

This is used in:
- SAT solvers
- AI planning
- Knowledge representation

---

## Part 21: Final Interview Wisdom

**How to explain this in an interview:**

1. "It's a constraint satisfaction problem."
2. "I'll use recursion to explore possibilities."
3. "I'll validate each placement with a bounding function."
4. "I'll backtrack when stuck."
5. "The key is pruning: isValid prevents exploring impossible branches."

**Code structure to show:**

```
Main solve() function
  ↓
For each cell
  ↓
For each possible value
  ↓
If valid (bounding function)
  ↓
Place and recurse
  ↓
Backtrack

This demonstrates:
✓ Recursion
✓ Backtracking
✓ Algorithm design
✓ Constraint satisfaction
```

**Time estimate to implement:**

"20–30 minutes for a working version.
Add pruning optimizations: another 20–30 minutes."

**Why this problem is important:**

"It teaches the core pattern of **exponential search with pruning**.
This pattern applies to 100+ interview problems."

---

## Summary: The Complete Picture

| Concept | Understanding |
|---------|---|
| **Recursion** | Process cells one by one, leading to next cell |
| **Try** | For each empty cell, try digits 1–9 |
| **Check** | isValid ensures row/col/block constraints |
| **Go** | Recurse to next cell with sudo[r][c] = num |
| **Undo** | Backtrack with sudo[r][c] = 0 |
| **Base Case** | row == 9 means all cells filled |
| **Pruning** | isValid eliminates invalid branches early |
| **Complexity** | O(9^n) worst case, much better with pruning |

---

**Abdul Bari's Final Insight:**

The specific problem (Sudoku) is not important.

What matters is **recognizing the pattern**:

✓ Decision tree exploration
✓ Smart pruning
✓ Proper backtracking

Master this, and you can solve **any constraint satisfaction problem**.

This is **algorithmic thinking** at its essence.

