# Backtracking Algorithm for String Permutation - Deep Dive

## Table of Contents

1. [Introduction](#introduction)
2. [Core Concept](#core-concept)
3. [Algorithm Implementation](#algorithm-implementation)
4. [Step-by-Step Execution](#step-by-step-execution)
5. [Visual Decision Tree](#visual-decision-tree)
6. [Why Backtracking is Necessary](#why-backtracking-is-necessary)
7. [Complete Execution Trace](#complete-execution-trace)
8. [Time and Space Complexity](#time-and-space-complexity)
9. [Comparison with Other Methods](#comparison-with-other-methods)
10. [Practice Exercises](#practice-exercises)

---

## Introduction

**Backtracking** is a powerful algorithmic technique for solving problems by exploring all possible solutions. For string permutation, it systematically generates all possible arrangements of characters by:

1. Making a choice (swap characters)
2. Exploring that choice recursively
3. Undoing the choice (backtracking) to try other possibilities

**Problem Statement:** Given a string, generate all possible permutations of its characters.

**Example:**

```
Input:  "ABC"
Output: ABC, ACB, BAC, BCA, CAB, CBA (6 permutations)
```

---

## Core Concept

### What is Backtracking?

Think of backtracking as exploring all paths in a decision tree, then **going back** to try alternative paths when you reach a dead end.

**Real-world analogy:** Solving a maze

- Try a path
- If it leads to a dead end, go back
- Try a different path
- Repeat until you find the exit (or explore all paths)

### Key Principles

1. **Choice:** At each step, make a decision (which character to fix)
2. **Constraint:** Ensure no duplicate characters at the same position
3. **Goal:** Generate all valid permutations
4. **Backtrack:** Undo choices to explore alternatives

---

## Algorithm Implementation

### 1. Helper Function: Character Swap

```c
void swap_chars(char *a, char *b)
{
    char temp = *a;  // Store first character
    *a = *b;         // Copy second to first
    *b = temp;       // Copy stored value to second
}
```

**Purpose:** Exchanges two characters in the string.

**Example:**

```c
char str[] = "ABC";
swap_chars(&str[0], &str[2]);  // Swap 'A' and 'C'
// Result: "CBA"
```

---

### 2. Core Recursive Function

```c
void permute_recursive(char str[], int left, int right, int *count)
{
    // Base case: reached the end of string
    if (left == right)
    {
        printf("%d: %s\n", ++(*count), str);  // Print permutation
    }
    else
    {
        // Try each character at position 'left'
        for (int i = left; i <= right; i++)
        {
            // Step 1: Swap current character with position 'left'
            swap_chars(&str[left], &str[i]);

            // Step 2: Recursively permute remaining substring
            permute_recursive(str, left + 1, right, count);

            // Step 3: Backtrack - restore original string
            swap_chars(&str[left], &str[i]);
        }
    }
}
```

**Parameters:**

- `str[]`: The string being permuted
- `left`: Current position being fixed (starts at 0)
- `right`: Last position in the string (always `length - 1`)
- `count`: Pointer to track permutation number

---

### 3. Wrapper Function

```c
void permutation_backtracking()
{
    char str[] = "ABC";
    int len = strlen(str);
    int count = 0;

    printf("\n=== Permutations Using Backtracking (Recursive) ===\n");
    printf("String: \"%s\" (length = %d)\n", str, len);

    // Calculate factorial
    int factorial = 1;
    for (int i = 2; i <= len; i++)
        factorial *= i;
    printf("Total permutations: %d! = %d\n\n", len, factorial);

    permute_recursive(str, 0, len - 1, &count);

    printf("\nThis method works for ANY string length!\n");
}
```

---

## Step-by-Step Execution

Let's trace the algorithm execution for string **"ABC"**:

### Initial Call

```c
permute_recursive("ABC", 0, 2, &count)
//                 str   left right
```

### Level 0: Fixing Position 0

```
Current string: "ABC"
left = 0, right = 2

Loop iterations (i = 0 to 2):
```

#### Iteration 1: i=0 (Fix 'A' at position 0)

```c
// Step 1: Swap str[0] with str[0] (no change)
swap_chars(&str[0], &str[0]);  // "ABC" → "ABC"

// Step 2: Recurse with left=1
permute_recursive("ABC", 1, 2, &count);
    // ↓ This explores all permutations starting with 'A'

// Step 3: Backtrack (swap back)
swap_chars(&str[0], &str[0]);  // "ABC" → "ABC"
```

**Inside recursion (left=1):**

```
Level 1: Fixing Position 1 (string = "ABC")
left = 1, right = 2

Loop iterations (i = 1 to 2):

  i=1: Swap str[1] with str[1] → "ABC"
       Recurse with left=2
       ↓ Base case! Print "1: ABC"
       Backtrack → "ABC"

  i=2: Swap str[1] with str[2] → "ACB"
       Recurse with left=2
       ↓ Base case! Print "2: ACB"
       Backtrack → "ABC"
```

#### Iteration 2: i=1 (Fix 'B' at position 0)

```c
// Step 1: Swap str[0] with str[1]
swap_chars(&str[0], &str[1]);  // "ABC" → "BAC"

// Step 2: Recurse with left=1
permute_recursive("BAC", 1, 2, &count);
    // ↓ This explores all permutations starting with 'B'

// Step 3: Backtrack
swap_chars(&str[0], &str[1]);  // "BAC" → "ABC"
```

**Inside recursion:**

```
Level 1: "BAC", left=1, right=2

  i=1: "BAC" → Recurse → Print "3: BAC"
  i=2: "BAC" → "BCA" → Recurse → Print "4: BCA" → Backtrack to "BAC"
```

#### Iteration 3: i=2 (Fix 'C' at position 0)

```c
// Step 1: Swap str[0] with str[2]
swap_chars(&str[0], &str[2]);  // "ABC" → "CBA"

// Step 2: Recurse with left=1
permute_recursive("CBA", 1, 2, &count);

// Step 3: Backtrack
swap_chars(&str[0], &str[2]);  // "CBA" → "ABC"
```

**Inside recursion:**

```
Level 1: "CBA", left=1, right=2

  i=1: "CBA" → Recurse → Print "5: CBA"
  i=2: "CBA" → "CAB" → Recurse → Print "6: CAB" → Backtrack to "CBA"
```

---

## Visual Decision Tree

```
                        ABC (start)
                         |
            ┌────────────┼────────────┐
            ↓            ↓            ↓
           ABC          BAC          CBA
        (fix A)      (fix B)      (fix C)
            |            |            |
        ┌───┴───┐    ┌───┴───┐    ┌───┴───┐
        ↓       ↓    ↓       ↓    ↓       ↓
       ABC     ACB  BAC     BCA  CBA     CAB
       (1)     (2)  (3)     (4)  (5)     (6)
```

**Key Insight:** Each branch represents fixing one character at the current position, then recursively permuting the remaining characters.

### State Transition Diagram

```
ABC (initial)
 ↓ swap(0,0)
ABC ──→ recurse(1) ──→ ABC, ACB
 ↓ backtrack
ABC
 ↓ swap(0,1)
BAC ──→ recurse(1) ──→ BAC, BCA
 ↓ backtrack
ABC
 ↓ swap(0,2)
CBA ──→ recurse(1) ──→ CBA, CAB
 ↓ backtrack
ABC (restored)
```

---

## Why Backtracking is Necessary

### Without Backtracking (WRONG)

```c
// WITHOUT backtracking:
permute_recursive("ABC", 0, 2, &count);
  swap to "BAC"
  permute_recursive("BAC", 1, 2, &count);  // ✓ Works
  // But now we're stuck with "BAC" for next iteration!

  swap to "CAC" (wrong!) // ❌ Should be "CBA"
```

**Result:** Generates incorrect permutations because the string state is corrupted.

### With Backtracking (CORRECT)

```c
// WITH backtracking:
permute_recursive("ABC", 0, 2, &count);
  swap to "BAC"
  permute_recursive("BAC", 1, 2, &count);
  swap back to "ABC"  // ← BACKTRACK restores original state

  swap to "CBA"  // ✓ Correct!
```

**Result:** All permutations generated correctly because the string is restored after each recursive call.

---

## Complete Execution Trace

### Detailed Call Stack for "ABC"

```
Call Stack                    String State    Action
===============================================================================
permute(ABC, 0, 2)            ABC             Start
  i=0: swap(0,0)              ABC             No change
  ├─ permute(ABC, 1, 2)       ABC             Recurse
  │    i=1: swap(1,1)         ABC             No change
  │    ├─ permute(ABC, 2, 2)  ABC             Base case
  │    │   → Print "1: ABC"
  │    │
  │    │   swap back(1,1)     ABC             Backtrack
  │    │
  │    i=2: swap(1,2)         ACB             Swap B↔C
  │    ├─ permute(ACB, 2, 2)  ACB             Base case
  │    │   → Print "2: ACB"
  │    │
  │    │   swap back(1,2)     ABC             Backtrack
  │
  │   swap back(0,0)          ABC             Backtrack
  │
  i=1: swap(0,1)              BAC             Swap A↔B
  ├─ permute(BAC, 1, 2)       BAC             Recurse
  │    i=1: swap(1,1)         BAC             No change
  │    ├─ permute(BAC, 2, 2)  BAC             Base case
  │    │   → Print "3: BAC"
  │    │
  │    │   swap back(1,1)     BAC             Backtrack
  │    │
  │    i=2: swap(1,2)         BCA             Swap A↔C
  │    ├─ permute(BCA, 2, 2)  BCA             Base case
  │    │   → Print "4: BCA"
  │    │
  │    │   swap back(1,2)     BAC             Backtrack
  │
  │   swap back(0,1)          ABC             Backtrack
  │
  i=2: swap(0,2)              CBA             Swap A↔C
  ├─ permute(CBA, 1, 2)       CBA             Recurse
       i=1: swap(1,1)         CBA             No change
       ├─ permute(CBA, 2, 2)  CBA             Base case
       │   → Print "5: CBA"
       │
       │   swap back(1,1)     CBA             Backtrack
       │
       i=2: swap(1,2)         CAB             Swap B↔A
       ├─ permute(CAB, 2, 2)  CAB             Base case
       │   → Print "6: CAB"
       │
       │   swap back(1,2)     CBA             Backtrack

       swap back(0,2)         ABC             Backtrack to original
```

### Memory Stack Visualization

```
Recursion Level 0 (left=0):
┌────────────────────┐
│  str = "ABC"       │
│  left = 0          │  Try: i=0, i=1, i=2
│  right = 2         │
└────────────────────┘
         │
         ├─ Recursion Level 1 (left=1):
         │  ┌────────────────────┐
         │  │  str = "ABC"       │
         │  │  left = 1          │  Try: i=1, i=2
         │  │  right = 2         │
         │  └────────────────────┘
         │           │
         │           └─ Recursion Level 2 (left=2):
         │              ┌────────────────────┐
         │              │  str = "ABC"       │
         │              │  left = 2          │  Base case!
         │              │  right = 2         │
         │              └────────────────────┘
         │                       │
         │                       └─ Print "ABC"
```

---

## Time and Space Complexity

### Time Complexity: **O(n! × n)**

**Breakdown:**

- **n!** permutations to generate (factorial)
- **n** operations per permutation (swaps + print + string operations)

**For "ABC":**

- n = 3
- Permutations: 3! = 6
- Total operations: 6 × 3 = 18

**Growth:**

```
n=3  → 6 permutations
n=4  → 24 permutations
n=5  → 120 permutations
n=10 → 3,628,800 permutations (impractical!)
```

### Space Complexity: **O(n)**

**Breakdown:**

- **Recursion depth:** n levels (one per character)
- **String storage:** O(n) for the input string
- **No additional data structures** needed

**Call stack for "ABC":**

```
permute(ABC, 0, 2)        ← Level 0
  permute(ABC, 1, 2)      ← Level 1
    permute(ABC, 2, 2)    ← Level 2 (base case)
```

Maximum depth = 3 = n

---

## Comparison with Other Methods

| Method                | Time Complexity | Space Complexity | Works for any n? | Notes                                      |
| --------------------- | --------------- | ---------------- | ---------------- | ------------------------------------------ |
| **Backtracking**      | O(n! × n)       | O(n)             | ✅ YES           | Educational, recursive                     |
| Brute Force (3 loops) | O(n³)           | O(1)             | ❌ Only n=3      | Limited, not scalable                      |
| Heap's Algorithm      | O(n!)           | O(n)             | ✅ YES           | Faster, generates each permutation in O(1) |
| Iterative (Narayana)  | O(n!)           | O(1)             | ✅ YES           | Lexicographic order                        |
| STL next_permutation  | O(n!)           | O(1)             | ✅ YES           | C++ only, built-in                         |

### Performance Comparison

```
Input Size    Backtracking    Heap's    Brute Force
─────────────────────────────────────────────────────
n=3           6 perms         6 perms   6 perms     ✓
n=4           24 perms        24 perms  N/A         ✓
n=5           120 perms       120 perms N/A         ✓
n=10          3.6M perms      3.6M perms N/A        ⚠️ Slow
n=15          1.3T perms      1.3T perms N/A        ❌ Impractical
```

---

## Practice Exercises

### Exercise 1: Trace "AB"

**Task:** Manually trace the execution for string "AB".

**Expected Output:**

```
1: AB
2: BA
```

**Hint:** Only 2 levels of recursion needed!

<details>
<summary>Solution</summary>

```
permute("AB", 0, 1, &count)
  i=0: swap(0,0) → "AB"
       ├─ permute("AB", 1, 1) → Base case → Print "1: AB"
       swap back(0,0) → "AB"

  i=1: swap(0,1) → "BA"
       ├─ permute("BA", 1, 1) → Base case → Print "2: BA"
       swap back(0,1) → "AB"
```

</details>

---

### Exercise 2: Count Recursive Calls

**Task:** How many times is `permute_recursive()` called for "ABC"?

**Options:**

- A) 6
- B) 9
- C) 15
- D) 16

<details>
<summary>Solution</summary>

**Answer: C) 15**

**Calculation:**

```
Level 0: 1 call
Level 1: 3 calls (one for each i=0,1,2)
Level 2: 3×3 = 9 calls (base cases + recursive)
         But only 6 reach base case

Total: 1 + 3 + 6 + 3 + 2 = 15 calls
```

**General formula:** For n characters: (n+1)! / 2 - 1 calls

</details>

---

### Exercise 3: Modify for Unique Permutations

**Task:** Modify the algorithm to handle duplicate characters.

**Example:**

```
Input:  "AAB"
Output: AAB, ABA, BAA (3 unique permutations, not 6)
```

<details>
<summary>Hint</summary>

Add a check before swapping to skip duplicate characters:

```c
bool shouldSwap(char str[], int start, int current)
{
    for (int i = start; i < current; i++)
    {
        if (str[i] == str[current])
            return false;  // Duplicate found
    }
    return true;
}

// In permute_recursive():
for (int i = left; i <= right; i++)
{
    if (shouldSwap(str, left, i))  // Add this check
    {
        swap_chars(&str[left], &str[i]);
        permute_recursive(str, left + 1, right, count);
        swap_chars(&str[left], &str[i]);
    }
}
```

</details>

---

### Exercise 4: Iterative Version

**Challenge:** Implement permutation generation without recursion.

**Hint:** Use a stack to simulate the call stack and maintain state explicitly.

---

### Exercise 5: Lexicographic Order

**Task:** Modify to generate permutations in lexicographic (dictionary) order.

**Example:**

```
Input:  "ABC"
Output: ABC, ACB, BAC, BCA, CAB, CBA (same as current)

Input:  "CBA"
Output: ABC, ACB, BAC, BCA, CAB, CBA (sorted first)
```

<details>
<summary>Hint</summary>

Sort the string before calling `permute_recursive()`:

```c
void permutation_lexicographic()
{
    char str[] = "CBA";
    // Sort first
    qsort(str, strlen(str), sizeof(char), compare_char);

    int count = 0;
    permute_recursive(str, 0, strlen(str) - 1, &count);
}
```

</details>

---

## Advanced Topics

### 1. Handling Duplicate Characters

When the input string contains duplicate characters, the basic algorithm generates duplicate permutations. To fix this:

```c
bool shouldSwap(char str[], int start, int current)
{
    // Check if str[current] already appeared between start and current-1
    for (int i = start; i < current; i++)
    {
        if (str[i] == str[current])
            return false;
    }
    return true;
}
```

### 2. Generating k-Permutations

Modify the algorithm to generate permutations of length k from n characters:

```c
void permute_k(char str[], int left, int k, int *count)
{
    if (left == k)  // Changed from: if (left == right)
    {
        // Print only first k characters
        for (int i = 0; i < k; i++)
            printf("%c", str[i]);
        printf("\n");
        return;
    }

    // Rest of the algorithm remains the same
    for (int i = left; i <= strlen(str) - 1; i++)
    {
        swap_chars(&str[left], &str[i]);
        permute_k(str, left + 1, k, count);
        swap_chars(&str[left], &str[i]);
    }
}
```

### 3. Memory Optimization

For very large strings, consider using bit manipulation to track used characters instead of swapping:

```c
void permute_bits(char str[], int mask, char result[], int pos, int n)
{
    if (pos == n)
    {
        result[pos] = '\0';
        printf("%s\n", result);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if ((mask & (1 << i)) == 0)  // Character not used
        {
            result[pos] = str[i];
            permute_bits(str, mask | (1 << i), result, pos + 1, n);
        }
    }
}
```

---

## Common Pitfalls and Debugging Tips

### Pitfall 1: Forgetting to Backtrack

```c
// ❌ WRONG
for (int i = left; i <= right; i++)
{
    swap_chars(&str[left], &str[i]);
    permute_recursive(str, left + 1, right, count);
    // Missing backtrack!
}

// ✅ CORRECT
for (int i = left; i <= right; i++)
{
    swap_chars(&str[left], &str[i]);
    permute_recursive(str, left + 1, right, count);
    swap_chars(&str[left], &str[i]);  // Must restore!
}
```

### Pitfall 2: Off-by-One Errors

```c
// ❌ WRONG: Using length instead of length-1
permute_recursive(str, 0, strlen(str), &count);  // Goes out of bounds!

// ✅ CORRECT
permute_recursive(str, 0, strlen(str) - 1, &count);
```

### Pitfall 3: Modifying const Strings

```c
// ❌ WRONG
const char *str = "ABC";
permute_recursive(str, 0, 2, &count);  // Can't modify const!

// ✅ CORRECT
char str[] = "ABC";  // Mutable array
permute_recursive(str, 0, 2, &count);
```

### Debugging Tips

1. **Add print statements:**

```c
void permute_recursive(char str[], int left, int right, int *count)
{
    printf("Called with: \"%s\", left=%d, right=%d\n", str, left, right);
    // ... rest of code
}
```

2. **Visualize the recursion tree:**

```c
void print_indent(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("  ");
}

void permute_debug(char str[], int left, int right, int *count, int depth)
{
    print_indent(depth);
    printf("permute(\"%s\", %d, %d)\n", str, left, right);

    if (left == right)
    {
        print_indent(depth);
        printf("→ Found: %s\n", str);
        return;
    }

    for (int i = left; i <= right; i++)
    {
        print_indent(depth);
        printf("Swap %c ↔ %c\n", str[left], str[i]);

        swap_chars(&str[left], &str[i]);
        permute_debug(str, left + 1, right, count, depth + 1);
        swap_chars(&str[left], &str[i]);
    }
}
```

---

## When to Use Backtracking

### ✅ Best Use Cases

1. **Small input sizes** (n ≤ 10)
2. **Learning recursion** and backtracking concepts
3. **Educational purposes** - understanding algorithm design
4. **Generating all solutions** when all are needed
5. **Problems with constraints** (e.g., only valid permutations)

### ❌ Not Recommended For

1. **Large strings** (n > 15) - exponential time complexity
2. **Real-time applications** - too slow for production
3. **Single permutation needed** - use Heap's or iterative methods
4. **Memory-constrained systems** - recursion depth can be large

### Alternatives to Consider

- **Heap's Algorithm:** Faster, generates each permutation in O(1) amortized time
- **Iterative methods:** No recursion overhead, constant space
- **next_permutation (C++):** Built-in, lexicographic order
- **Narayana's algorithm:** Generates next permutation efficiently

---

## Summary

### Key Takeaways

1. **Backtracking explores all possibilities** by making choices and undoing them
2. **Swapping + Recursion + Backtracking** form the core of the algorithm
3. **Time complexity is O(n! × n)** - factorial growth
4. **Space complexity is O(n)** - recursion depth
5. **Always restore state** after recursive calls (backtrack!)

### Algorithm Pattern

```
1. Base case: If reached the end, print/store result
2. Recursive case:
   For each possible choice:
     - Make the choice (swap)
     - Recurse on remaining problem
     - Undo the choice (backtrack)
```

### Mental Model

Think of permutation generation as:

- **Filling positions** from left to right
- **Trying every character** at each position
- **Recursively filling** the remaining positions
- **Backtracking** to try different combinations

---

## Further Reading

### Books

- **"Introduction to Algorithms"** by CLRS - Chapter on Backtracking
- **"Algorithm Design Manual"** by Skiena - Combinatorial Search section
- **"Programming Pearls"** by Bentley - Permutation generation

### Online Resources

- [GeeksforGeeks - Permutations of a String](https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/)
- [Visualgo - Recursion Tree Visualization](https://visualgo.net/en/recursion)
- [Wikipedia - Permutation Algorithm](https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order)

### Related Algorithms

- **Heap's Algorithm** - More efficient permutation generation
- **N-Queens Problem** - Classic backtracking problem
- **Sudoku Solver** - Constraint satisfaction with backtracking
- **Subset Sum** - Decision problem using backtracking

---

## License

This documentation is part of the **Data Structures and Algorithms in C/C++** repository.

**Repository:** [Implement-Data-Structures-Algorithms-using-C-and-C-](https://github.com/MbarekDev-Lab/Implement-Data-Structures-Algorithms-using-C-and-C-)  
**Author:** MbarekDev-Lab  
**Date:** December 2025

---

## Contributing

Found an error or want to add more examples? Feel free to:

1. Open an issue
2. Submit a pull request
3. Share your learning experience

Happy Learning! 🚀
