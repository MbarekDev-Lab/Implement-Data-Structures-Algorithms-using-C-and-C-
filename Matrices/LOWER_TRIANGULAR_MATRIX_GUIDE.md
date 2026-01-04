# Lower Triangular Matrix - Complete Reference Guide

**Source:** Abdul Bari's Data Structures and Algorithms Course  
**Topic:** Lower Triangular Matrix with Row-Major and Column-Major Mapping  
**Author's Notes:** Complete theoretical and practical guide

---

## Table of Contents

1. [What is a Lower Triangular Matrix?](#1-what-is-a-lower-triangular-matrix)
2. [Why Use 1D Array Representation?](#2-why-use-1d-array-representation)
3. [Row-Major Mapping (Core Concept)](#3-row-major-mapping-core-concept)
4. [Column-Major Mapping](#4-column-major-mapping)
5. [Complete C++ Implementation](#5-complete-c-implementation)
6. [Memory Layout Comparison](#6-memory-layout-comparison)
7. [Practice Problems & Solutions](#7-practice-problems--solutions)
8. [Interview & Exam Gold Points](#8-interview--exam-gold-points)

---

## 1. What is a Lower Triangular Matrix?

### Definition

A **Lower Triangular Matrix** is an **n × n** square matrix where **all elements above the main diagonal are zero**.

Mathematically:
```
A[i][j] = 0  for all i < j
A[i][j] ≠ 0  for all i ≥ j (potentially)
```

### Visual Example (4×4)

```
i\j   1   2   3   4
1     1   0   0   0     ← Row 1: 1 element
2     2   3   0   0     ← Row 2: 2 elements
3     4   5   6   0     ← Row 3: 3 elements
4     7   8   9   10    ← Row 4: 4 elements
```

### Storage Optimization

**Traditional 2D Array:**
- Stores n² elements
- For n=4: 16 elements (including zeros)

**Optimized 1D Array:**
- Stores only non-zero elements
- Formula: **n(n+1)/2** elements
- For n=4: **10 elements** (60% space reduction!)

```
Elements needed = 1 + 2 + 3 + ... + n = n(n+1)/2
```

---

## 2. Why Use 1D Array Representation?

### Memory Efficiency

| Matrix Size | 2D Storage | 1D Storage | Space Saved |
|-------------|-----------|------------|-------------|
| 4×4         | 16        | 10         | 37.5%       |
| 10×10       | 100       | 55         | 45%         |
| 100×100     | 10,000    | 5,050      | 49.5%       |
| 1000×1000   | 1,000,000 | 500,500    | ~50%        |

### Implementation Advantage

```cpp
// Wasteful 2D array
int A[1000][1000];  // 1,000,000 integers = 4 MB

// Efficient 1D array
int A[500500];      // 500,500 integers = ~2 MB
```

### The Challenge

**Problem:** How do we map 2D coordinates `(i, j)` to a 1D array index?

**Solution:** Mathematical mapping formulas!

---

## 3. Row-Major Mapping (Core Concept)

### The Idea

**Row-Major:** Store elements **row by row** in sequential memory.

```
Row 1: a
Row 2: b c
Row 3: d e f
Row 4: g h i j

1D Array: [a, b, c, d, e, f, g, h, i, j]
           0  1  2  3  4  5  6  7  8  9  ← indices (0-based)
```

### Formula Derivation

To find the 1D index of element `A[i][j]`:

**Step 1:** Count elements in rows before row `i`
```
Row 1 has: 1 element
Row 2 has: 2 elements
Row 3 has: 3 elements
...
Row (i-1) has: (i-1) elements

Total = 1 + 2 + 3 + ... + (i-1) = (i-1) × i / 2
```

**Step 2:** Add offset within row `i`
```
Position of column j in row i = (j - 1)
```

**Step 3:** Combine
```
index(i, j) = (i-1)×i/2 + (j-1)
```

### ✅ Final Row-Major Formula (1-based indexing)

```cpp
index = (i × (i - 1)) / 2 + (j - 1)
```

**Condition:** Valid only when **i ≥ j** (lower triangle)

### Example Calculation

Find index of element at position (3, 2):

```
i = 3, j = 2

Elements before row 3:
= (3-1) × 3 / 2
= 2 × 3 / 2
= 3

Offset in row 3:
= j - 1
= 2 - 1
= 1

Final index = 3 + 1 = 4
```

Verify:
```
Index: 0  1  2  3  4  5  6  7  8  9
Value: a  b  c  d  e  f  g  h  i  j
                      ↑
                    position 4 ✓
```

---

## 4. Column-Major Mapping

### The Idea

**Column-Major:** Store elements **column by column** in sequential memory.

```
Col 1: a b d g
Col 2: c e h
Col 3: f i
Col 4: j

1D Array: [a, b, d, g, c, e, h, f, i, j]
           0  1  2  3  4  5  6  7  8  9  ← indices
```

### Why Different Formula?

The **number of elements per column decreases** as we move right:
- Column 1: n elements
- Column 2: n-1 elements
- Column 3: n-2 elements
- Column j: (n - j + 1) elements

### Formula Derivation

**Step 1:** Count elements in columns before column `j`
```
Col 1: n elements
Col 2: (n-1) elements
Col 3: (n-2) elements
...
Col (j-1): (n-j+2) elements

Total = n + (n-1) + (n-2) + ... + (n-j+2)
      = n×(j-1) - [1 + 2 + ... + (j-2)]
      = n×(j-1) - (j-2)×(j-1)/2
```

**Step 2:** Add offset within column `j`
```
Position of row i in column j = (i - j)
```

**Step 3:** Combine

### ✅ Final Column-Major Formula (1-based indexing)

```cpp
index = n×(j-1) - (j-2)×(j-1)/2 + (i-j)
```

**Condition:** Valid only when **i ≥ j** (lower triangle)

### Example Calculation

For n=4, find index of element at position (3, 2):

```
n = 4, i = 3, j = 2

Elements before column 2:
= 4×(2-1) - (2-2)×(2-1)/2
= 4×1 - 0×1/2
= 4 - 0
= 4

Offset in column 2:
= i - j
= 3 - 2
= 1

Final index = 4 + 1 = 5
```

---

## 5. Complete C++ Implementation

### Class Structure

```cpp
#include <iostream>
using namespace std;
 
class LTMatrix {
private:
    int n;     // Matrix dimension (n×n)
    int* A;    // 1D dynamic array for storage

public:
    // Constructor: Allocate memory
    LTMatrix(int n) {
        this->n = n;
        A = new int[n * (n + 1) / 2];  // Exact space needed
    }

    // Destructor: Free memory
    ~LTMatrix() {
        delete[] A;
    }
    
    // Row-Major Operations
    void setRowMajor(int i, int j, int x);
    int getRowMajor(int i, int j);

    // Column-Major Operations
    void setColMajor(int i, int j, int x);
    int getColMajor(int i, int j);

    // Utility
    void Display(bool row = true);
    int getN() { return n; }
};
```

### Row-Major Set/Get

```cpp
void LTMatrix::setRowMajor(int i, int j, int x) {
    if (i >= j) {  // Only lower triangle
        int index = ((i * (i - 1)) / 2) + j - 1;
        A[index] = x;
    }
}

int LTMatrix::getRowMajor(int i, int j) {
    if (i >= j) {  // Lower triangle
        int index = ((i * (i - 1)) / 2) + j - 1;
        return A[index];
    } else {  // Upper triangle
        return 0;  // Always zero
    }
}
```

**Key Points:**
- `if (i >= j)` ensures we only store lower triangle
- Upper triangle elements return `0` automatically
- Uses 1-based indexing (matches mathematical convention)

### Column-Major Set/Get

```cpp
void LTMatrix::setColMajor(int i, int j, int x) {
    if (i >= j) {
        int index = (n * (j-1) - (((j-2) * (j-1)) / 2)) + (i-j);
        A[index] = x;
    }
}

int LTMatrix::getColMajor(int i, int j) {
    if (i >= j) {
        int index = (n * (j-1) - (((j-2) * (j-1)) / 2)) + (i-j);
        return A[index];
    } else {
        return 0;
    }
}
```

### Display Function

```cpp
void LTMatrix::Display(bool row) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i >= j) {
                if (row) {
                    cout << getRowMajor(i, j) << " ";
                } else {
                    cout << getColMajor(i, j) << " ";
                }
            } else {
                cout << 0 << " ";  // Upper triangle
            }
        }
        cout << endl;
    }
}
```

**Magic:** Reconstructs 2D matrix illusion from 1D array!

### Usage Example

```cpp
int main() {
    // Row-major storage
    LTMatrix rm(4);
    rm.setRowMajor(1, 1, 1);
    rm.setRowMajor(2, 1, 2);
    rm.setRowMajor(2, 2, 3);
    rm.setRowMajor(3, 1, 4);
    rm.setRowMajor(3, 2, 5);
    rm.setRowMajor(3, 3, 6);
    rm.setRowMajor(4, 1, 7);
    rm.setRowMajor(4, 2, 8);
    rm.setRowMajor(4, 3, 9);
    rm.setRowMajor(4, 4, 10);
    
    cout << "Row-Major Matrix:\n";
    rm.Display();
    
    // Column-major storage
    LTMatrix cm(4);
    cm.setColMajor(1, 1, 1);
    cm.setColMajor(2, 1, 2);
    // ... (same values)
    
    cout << "\nColumn-Major Matrix:\n";
    cm.Display(false);
    
    return 0;
}
```

**Output (both are identical):**
```
1 0 0 0
2 3 0 0
4 5 6 0
7 8 9 10
```

---

## 6. Memory Layout Comparison

### Row-Major Memory Layout

```
2D View:          1D Array Memory:
1 0 0 0          [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
2 3 0 0           │  └─┐ └──┐  └───┐  └────┐
4 5 6 0           │    │    │      │       │
7 8 9 10          row1 row2 row3   row4    
```

**Access Pattern:**
- Sequential row reading is fast
- Used when you process row by row

### Column-Major Memory Layout

```
2D View:          1D Array Memory:
1 0 0 0          [1, 2, 4, 7, 3, 5, 8, 6, 9, 10]
2 3 0 0           │  └────┐ └──┐ └──┐ └─┐
4 5 6 0           │       │    │    │   │
7 8 9 10          col1    col2 col3 col4
```

**Access Pattern:**
- Sequential column reading is fast
- Used when you process column by column

### Performance Comparison

| Operation | Row-Major | Column-Major |
|-----------|-----------|--------------|
| Row traversal | ✅ Fast (sequential) | ❌ Scattered access |
| Column traversal | ❌ Scattered access | ✅ Fast (sequential) |
| Matrix × Vector | ✅ Better | ❌ Slower |
| Vector × Matrix | ❌ Slower | ✅ Better |

---

## 7. Practice Problems & Solutions

### Problem 1: Index Formula Derivation

**Question:** In a compact 1D array representation for lower triangular matrices (n×n), where non-zero elements of each row are stored one after another starting from the first row, what is the index of the (i,j)th element?

**Given Options:**
- a) `i + j`
- b) `i + j - 1`
- c) `j - 1 + i(i + 1)/2`
- d) `(j - 1) + i(i - 1)/2` ✅

**Solution:**

Elements before row i:
```
1 + 2 + 3 + ... + (i-1) = (i-1)×i/2
```

Offset in row i:
```
j - 1
```

**Total index:**
```
(j - 1) + i(i - 1)/2
```

**✅ Answer: (d)**

---

### Problem 2: Array Sum

**Question:** An n×n array v is defined as follows:
```
v[i,j] = i - j  for all 1 ≤ i ≤ n, 1 ≤ j ≤ n
```
What is the sum of all elements?

**Solution:**

Total sum:
```
Sum = Σ(i=1 to n) Σ(j=1 to n) (i - j)
    = Σ(i=1 to n) Σ(j=1 to n) i  -  Σ(i=1 to n) Σ(j=1 to n) j
```

First part:
```
Σ(i=1 to n) Σ(j=1 to n) i = Σ(i=1 to n) n×i = n × n(n+1)/2
```

Second part:
```
Σ(i=1 to n) Σ(j=1 to n) j = Σ(j=1 to n) n×j = n × n(n+1)/2
```

Result:
```
Sum = n×n(n+1)/2 - n×n(n+1)/2 = 0
```

**Intuition:** For every element (i,j) = i-j, there exists (j,i) = j-i. They cancel out!

**✅ Answer: 0**

---

### Problem 3: Matrix Transpose Algorithm

**Question:** Consider this pseudocode:
```
C = 100
for i = 1 to n do
    for j = 1 to n do
        Temp = A[i][j] + C
        A[i][j] = A[j][i]
        A[j][i] = Temp - C
        
for i = 1 to n do
    for j = 1 to n do
        print(A[i][j])
```
What is the output?

**Options:**
- a) Transpose of A
- b) A itself ✅
- c) Symmetric matrix
- d) Zero matrix

**Solution:**

Analyze the inner operations:
```
Temp = A[i][j] + C
A[i][j] = A[j][i]
A[j][i] = Temp - C = (A[i][j] + C) - C = A[i][j]
```

**This swaps A[i][j] and A[j][i]**

But the loop runs for **all i and j**, not just i < j:
- When (i,j) is processed → swap happens
- When (j,i) is processed → swap happens again (reverses!)

**Result:** Every swap is undone → matrix remains unchanged

**✅ Answer: (b) A itself**

**Key Insight:** C is just a temporary storage trick; it doesn't modify values.

---

## 8. Interview & Exam Gold Points

### Critical Concepts

✅ **Space Optimization:**
- Lower triangular stores `n(n+1)/2` instead of `n²`
- Saves ~50% memory for large matrices

✅ **Index Mapping Formulas:**
- **Row-major:** `(i×(i-1))/2 + (j-1)`
- **Column-major:** `n×(j-1) - (j-2)×(j-1)/2 + (i-j)`

✅ **Condition:**
- Both valid only when `i ≥ j`

✅ **Upper Triangle:**
- Always returns `0` (definition of lower triangular)

### Common Interview Questions

**Q1:** "Why not just store as 2D array?"  
**A:** Memory waste. For 1000×1000 matrix, wastes 500K elements (50%).

**Q2:** "What about cache performance?"  
**A:** Row-major better for row operations; column-major better for column ops.

**Q3:** "How would you implement upper triangular?"  
**A:** Flip condition to `i ≤ j`, adjust formulas.

**Q4:** "Can you do matrix multiplication with this representation?"  
**A:** Yes, but need to handle the mapping properly. More complex than 2D arrays.

**Q5:** "What's the time complexity of accessing element (i,j)?"  
**A:** O(1) - formula is constant time arithmetic.

### Related Data Structures

This concept extends to:
- **Upper Triangular Matrix** (mirror image)
- **Diagonal Matrix** (only n elements)
- **Symmetric Matrix** (stores only lower triangle, rest is mirror)
- **Tri-diagonal Matrix** (3 diagonals)
- **Sparse Matrix** (compressed storage for mostly zeros)
- **Toeplitz Matrix** (constant diagonals)

---

## 9. Key Takeaways

### 🎯 Core Understanding

1. **Definition:** Lower triangular = all elements above diagonal are zero
2. **Optimization:** Store only `n(n+1)/2` non-zero elements
3. **Mapping:** Use mathematical formula to convert (i,j) → 1D index
4. **Choice:** Row-major vs column-major depends on access pattern

### 🧠 Mental Model

**Think of it as:**
> Compressing a matrix by removing all the zeros, then using math to remember where everything was.

### 📚 Study Strategy

1. ✅ Understand **why** optimization matters (space)
2. ✅ Derive formulas from scratch (count elements)
3. ✅ Practice with small examples (n=3, n=4)
4. ✅ Code it yourself in C++ and C
5. ✅ Solve practice problems (timing access, memory calc)

---

## 10. References & Resources

### Primary Source
- **Abdul Bari** - Data Structures Course
  - Lower Triangular Matrix Lecture
  - Matrix Representation Section
  - YouTube: Abdul Bari Algorithm Channel

### Implementation Files
- `LTMatrix.cpp` - Full C++ implementation with both mappings
- `LowerTriangularMatrix.c` - C version (row-major only)
- `LowerTriangularMatrix.cpp` - C++ version with detailed comments

### Related Topics to Study Next
1. Upper Triangular Matrix
2. Symmetric Matrix Representation
3. Sparse Matrix (3-tuple representation)
4. Matrix Chain Multiplication
5. Strassen's Matrix Multiplication

---

## 11. Quick Reference Cheat Sheet

### Formulas (1-based indexing)

```cpp
// Row-Major
index = (i * (i - 1)) / 2 + (j - 1)     // where i ≥ j

// Column-Major  
index = n * (j - 1) - ((j - 2) * (j - 1)) / 2 + (i - j)  // where i ≥ j
```

### Memory Requirements

```cpp
elements = n * (n + 1) / 2
```

### Implementation Template

```cpp
class LowerTriangularMatrix {
private:
    int n;
    int* A;
public:
    LowerTriangularMatrix(int n) {
        this->n = n;
        A = new int[n * (n + 1) / 2];
    }
    ~LowerTriangularMatrix() { delete[] A; }
    
    void Set(int i, int j, int x) {
        if (i >= j) 
            A[rowMajorIndex(i, j)] = x;
    }
    
    int Get(int i, int j) {
        return (i >= j) ? A[rowMajorIndex(i, j)] : 0;
    }
};
```

---

**Last Updated:** January 4, 2026  
**Status:** Complete Reference Guide  
**Level:** Intermediate to Advanced Data Structures

---

*This guide is designed for students learning from Abdul Bari's lectures and preparing for technical interviews or exams. Practice the problems, understand the derivations, and implement the code yourself for maximum retention.*
