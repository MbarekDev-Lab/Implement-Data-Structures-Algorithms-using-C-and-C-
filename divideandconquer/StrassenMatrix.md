# Strassen's Matrix Multiplication — Beyond Divide & Conquer

## Abdo's Core Message

> "Think differently about the problem, **not harder**."

**Strassen's algorithm proves that fewer multiplications can beat simpler logic.**

This lecture teaches a crucial lesson: **optimization often comes from reformulation, not brute force.**

---

## Part 1: The Problem — Is Classical Matrix Multiplication Optimal?

### The Question Abdo Starts With

Before introducing algorithms, Abdo asks:

```
❓ "Is O(n³) the best we can do for matrix multiplication?"
```

This question is **the heart of the lecture**.

### Classical Matrix Multiplication

```c
// Standard O(n³) approach
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}
```

**Analysis:**
- Three nested loops of size n each
- Time Complexity: **O(n³)**
- Space Complexity: **O(n²)** (for result matrix)

### Why This Matters

For real-world matrices:

| Size | Operations |
|------|------------|
| 100 × 100 | 1,000,000 ops |
| 1,000 × 1,000 | 1,000,000,000 ops |
| 10,000 × 10,000 | 1,000,000,000,000 ops (1 trillion) |

**The problem scales terribly.** Applications demanding fast matrix multiplication:

- **Machine learning** (neural networks, matrix operations)
- **Graphics rendering** (transformation matrices)
- **Scientific computing** (simulations)
- **Cryptography** (large matrix operations)

### Abdo's Challenge

> Can **Divide & Conquer reduce this cost?**

This is what the entire lecture answers.

---

## Part 2: The Naive Divide & Conquer Approach

### How to Apply Divide & Conquer to Matrices

Divide each `n × n` matrix into four `(n/2) × (n/2)` submatrices:

```
A = | A11  A12 |      B = | B11  B12 |
    | A21  A22 |          | B21  B22 |

Result:
C = | C11  C12 |
    | C21  C22 |
```

### The Block Multiplication Formula

Using block matrix multiplication rules:

```
C11 = A11·B11 + A12·B21
C12 = A11·B12 + A12·B22
C21 = A21·B11 + A22·B21
C22 = A21·B12 + A22·B22
```

This requires **8 matrix multiplications** of size `(n/2) × (n/2)`.

### The Recurrence

```
T(n) = 8·T(n/2) + O(n²)
```

**Explanation:**
- 8 recursive multiplications: `8·T(n/2)`
- Adding/combining subresults: `O(n²)`

### Solving the Recurrence (Master Theorem)

Using Master Theorem with `a = 8`, `b = 2`, `f(n) = n²`:

```
log_b(a) = log₂(8) = 3

f(n) = n² = o(n³)

Therefore: T(n) = Θ(n³)
```

### The Disappointing Truth

```
❌ 8 multiplications of (n/2 × n/2) = O(n³)
✓ Same complexity as classical approach!
```

**Abdo's key point:**
> "Divide & Conquer alone is not enough.  
> We're just rearranging the work, not reducing it."

---

## Part 3: The Crucial Insight — Reduce Multiplications

### Strassen's Breakthrough

Volker Strassen (1969) made a **counterintuitive discovery:**

> "You don't need 8 multiplications.  
> **7 are sufficient.**"

This seems impossible because the formulas for C11, C12, C21, C22 **require** 8 products...

...unless you **reformulate** the computation.

### The Key Principle

```
FACT: Multiplication is more expensive than addition.

Cost estimate:
  - Multiplication: ~10 CPU cycles
  - Addition: ~1 CPU cycle

Therefore:
  - Reducing multiplications by 1 saves ~10 cycles
  - Adding extra additions costs ~few cycles
  - Net gain: HUGE
```

This is why Strassen trades multiplications for additions.

### The Reformulation Idea

Instead of directly computing C using the block formula, Strassen:

1. Computes **7 temporary products** M1 to M7
2. These products are cleverly chosen using **linear combinations**
3. The products can then be **recombined differently** to produce the same result

**This is algebraic manipulation, not algorithmic improvement.**

---

## Part 4: The 7 Magic Multiplications (The Core Algorithm)

### The Seven Products

Strassen defined these 7 products:

```
M1 = (A11 + A22) · (B11 + B22)
M2 = (A21 + A22) · B11
M3 = A11 · (B12 - B22)
M4 = A22 · (B21 - B11)
M5 = (A11 + A12) · B22
M6 = (A21 - A11) · (B11 + B12)
M7 = (A12 - A22) · (B21 + B22)
```

**Notice:**
- M1, M6, M7 use additions before multiplication (leverages distributive property)
- M2-M5 use subtraction before multiplication
- Total: **7 multiplications** of `(n/2) × (n/2)` matrices

### Reconstructing the Result

From these 7 products, reconstruct C using **additions/subtractions only**:

```
C11 = M1 + M4 - M5 + M7
C12 = M3 + M5
C21 = M2 + M4
C22 = M1 - M2 + M3 + M6
```

**Verification (for 2×2 case):**

Let's verify C11 = M1 + M4 - M5 + M7:

```
M1 + M4 - M5 + M7
= (A11 + A22)(B11 + B22) + A22(B21 - B11)
  - (A11 + A12)B22 + (A12 - A22)(B21 + B22)

[After expanding and collecting terms]
= A11·B11 + A12·B21

This equals the classical C11 formula! ✓
```

### Why This Works

This is **pure algebra**:

1. The classical formulas for C11, C12, C21, C22 are correct
2. Strassen rearranges these formulas to extract common subexpressions
3. Those common subexpressions become M1-M7
4. The reconstruction formulas recover the original result
5. Net result: **fewer multiplications, more additions**

---

## Part 5: Time Complexity Analysis

### The New Recurrence

With 7 multiplications instead of 8:

```
T(n) = 7·T(n/2) + O(n²)
```

### Solving with Master Theorem

```
a = 7  (number of subproblems)
b = 2  (reduction factor)
f(n) = n² (combining work)

log_b(a) = log₂(7) ≈ 2.807

Since n² = o(n^2.807), we're in case 1:

T(n) = Θ(n^log₂(7)) ≈ Θ(n^2.807)
```

### The Improvement

| Approach | Complexity | For n = 1000 |
|----------|-----------|--------------|
| Classical | O(n³) = n³ | 10⁹ ops |
| Divide & Conquer (8 mult) | O(n³) | 10⁹ ops |
| Strassen (7 mult) | O(n^2.81) | ~10⁸·⁷ ops |
| **Improvement** | **12% faster** per dimension | **≈ 2x faster** |

**For large matrices, Strassen is asymptotically faster.**

### Visual Recursion Tree Comparison

```
CLASSICAL (8 multiplications):
                    n³
        _____|_______|_______|_______|_______|_______|_______|_____
       /     |      |      |      |      |      |      |      \
     8 nodes of (n/2)³ each
      |
     64 nodes of (n/4)³ each
      |
    512 nodes of (n/8)³ each
     ...
   Total levels: log₂(n)
   Nodes at level k: 8^k
   Total work: 8^(log₂(n)) · (n/something) = n³

STRASSEN (7 multiplications):
                    n³
        _____|_______|_______|_______|_______|_______|______
       /     |      |      |      |      |      |      \
     7 nodes of something
      |
     49 nodes of smaller problem
      |
    343 nodes
     ...
   Total levels: log₂(n)
   Nodes at level k: 7^k
   Total work: 7^(log₂(n)) · n² = n^log₂(7) · n² = n^(2.81)
```

---

## Part 6: Why Strassen Isn't Used for Small Matrices

### The Hidden Constants

Strassen's analysis shows **asymptotic** improvement, but:

```
T_Strassen(n) = 7·T(n/2) + 18·(n/2)²
              = 7·T(n/2) + 4.5·n²    [CONSTANT = 4.5]

T_Classical(n) = 8·T(n/2) + O(n²)
              = 8·T(n/2) + c·n²      [CONSTANT = c]
```

**For small n, constants dominate.**

### Crossover Point

| n | Classical | Strassen | Winner |
|---|-----------|----------|--------|
| 2 | ~8 | ~50 | Classical |
| 8 | ~512 | ~400 | Strassen |
| 32 | ~32K | ~15K | Strassen |
| 128 | ~2M | ~500K | Strassen |
| 512 | ~134M | ~10M | Strassen |

**Breakeven: roughly n ≈ 32-64.**

### Practical Trade-offs

| Factor | Impact |
|--------|--------|
| **Memory overhead** | Strassen requires temporary matrices for each recursion level |
| **Cache efficiency** | Classical method has better cache locality |
| **Numerical stability** | More floating-point operations = more rounding error |
| **Implementation complexity** | Strassen is much harder to code correctly |
| **Practical speed** | Hybrid (switch to classical at small n) is fastest |

### Why Abdo Emphasizes This

> "Asymptotic analysis is not the whole story.  
> Constants, implementation, and practical constraints matter."

---

## Part 7: Deeper Mathematical Insight

### The Magic Behind M1-M7

How did Strassen discover these formulas?

He used **polynomial optimization** and **linear algebra**:

```
The classical formula for C can be written as a 
polynomial in the matrix entries of A and B.

The question becomes:
"What is the minimum number of multiplications 
needed to compute this polynomial?"

This is a non-trivial problem in algebraic complexity theory.

Answer: 7 (proved via computer search in the 1960s)
```

### Implications

This raises questions Abdo wants you to consider:

1. **Is 7 optimal?** Could we do better with a different decomposition?
2. **How to find such algorithms?** Is there a systematic method?
3. **Where else do such insights apply?** (FFT, polynomial multiplication...)

### The Deeper Principle

> "The way you **structure** a problem affects  
> the **inherent complexity** of solving it."

This is why reformulation matters more than optimization.

---

## Part 8: Why It's Not Used Everywhere

### The Honest Assessment

Abdo is very clear: **Strassen is rarely used in practice.**

**Reasons:**

1. **Memory overhead**
   - Multiplying 2 large matrices requires many temporary matrices
   - For n=1000, this becomes prohibitive

2. **Numerical instability**
   - More arithmetic operations = more accumulated floating-point errors
   - For practical applications (graphics, ML), this is unacceptable

3. **Cache misses**
   - Classical method has sequential access patterns
   - Strassen causes scattered memory access

4. **Already solved better**
   - **BLAS libraries** (Level 3) use highly optimized classical multiplication
   - Years of engineering beats algorithmic theory

5. **Asymptotic doesn't mean practical**
   ```
   Strassen: O(n^2.81) with huge constants
   BLAS: O(n^3) with tiny optimized constants
   
   For n < 10,000: BLAS wins
   For n = 1,000,000: Strassen might win
   But nobody multiplies 1M × 1M dense matrices!
   ```

### Where Strassen IS Used

- **Symbolic computation** (exact arithmetic, not floats)
- **Theoretical computer science** (studying lower bounds)
- **GPU implementations** (different memory hierarchy)
- **Very specialized cases** (extremely large dense matrices)

---

## Part 9: What Abdo Is REALLY Training Your Brain For

### Immediate Connections

1. **Recurrence Relations**
   - Write T(n) = 7T(n/2) + O(n²)
   - Solve using Master Theorem
   - Understanding exponents in complexity

2. **Advanced Divide & Conquer**
   - When simple division isn't enough
   - Reformulate to reduce subproblems
   - Think algebraically about problems

3. **Polynomial Multiplication**
   - Karatsuba's algorithm (similar idea, reduces multiplications)
   - Fast Fourier Transform (FFT - reduces from O(n²) to O(n log n))

### Long-Term Insights

This lecture teaches that:

- **Complexity is not fixed** — it depends on how you structure the problem
- **Multiplication is expensive** — whether it's arithmetic or algorithmic work
- **Asymptotic analysis has limits** — constants and implementation matter
- **Theory and practice differ** — algorithms that are "better" might not be practical

### Advanced Topics This Prepares You For

| Topic | Connection |
|-------|-----------|
| **Fast Fourier Transform** | Reduces polynomial multiplication from O(n²) to O(n log n) |
| **Algebraic Complexity** | Studies minimum operations needed for any computation |
| **Parallel Algorithms** | Strassen's 7 multiplications can be done in parallel |
| **Computational Geometry** | Similar ideas for closest-pair, convex-hull problems |
| **Cryptography** | Matrix operations appear in many cryptographic protocols |

---

## Part 10: The Silent Message of This Lecture

### Abdo's Hidden Teaching

> "Optimization is not about working harder.  
> It's about thinking about the problem differently."

This is the difference between:
- **Hacking:** Do the same thing faster with code tricks
- **Algorithm design:** Solve the fundamentally different problem

Strassen teaches **algorithm design.**

### The Principle

```
PRINCIPLE: Before optimizing code, ask:
  "Am I solving the right subproblem?"
  "Can I reformulate to reduce expensive operations?"
  "What if I rearrange the structure?"

Often, architectural changes beat micro-optimizations 100:1.
```

### Why This Changes How You Think

- Instead of: "How do I speed up multiplication?"
- Think: "What if I don't multiply these terms at all?"
- Now ask: "Can I compute the result with fewer multiplications?"

This is **lateral thinking applied to algorithms.**

---

## Part 11: One Sentence Summary (Exam Gold)

Pick your level:

**Elementary:**
> "Strassen multiplies two matrices faster by using 7 multiplications instead of 8."

**Intermediate:**
> "Strassen's algorithm reduces matrix multiplication from O(n³) to O(n^2.81) by reformulating the computation."

**Expert:**
> "Strassen proves that asymptotically faster algorithms exist for dense matrix multiplication, though practical implementations favor BLAS due to constants and numerical stability."

**Abdo's preferred answer:**
> "Strassen's algorithm proves that fewer multiplications can beat simpler logic."

If you can explain **why that statement is true**, you've mastered the lecture.

---

## Part 12: Understanding Progression (Surface to Mastery)

| Level | Can Do |
|-------|--------|
| **Surface** | Write down the 7 products M1-M7 |
| **Deeper** | Verify one reconstruction formula (like C11) algebraically |
| **Deep** | Explain why 7 < 8 reduces complexity from O(n³) to O(n^2.81) |
| **Mastery** | Discuss tradeoffs between Strassen and BLAS, when each is appropriate |
| **Expert** | Understand how algebraic complexity analysis finds optimal algorithms |

---

## Part 13: Interview Approach

### What To Say

✓ "Strassen is a divide & conquer approach that uses 7 matrix multiplications instead of 8"

✓ "This reduces complexity from O(n³) to O(n^log₂7) ≈ O(n^2.81)"

✓ "In practice, classical multiplication is faster for most matrix sizes due to constants and numerical stability"

✓ "The real lesson is that reformulation can improve asymptotic complexity"

### What NOT To Say

✗ "Strassen is faster for matrices"

✗ "All O(n^2.81) algorithms are better than O(n³)"

✗ "I memorized the 7 formulas but don't understand why they work"

✗ "My code would just use numpy.dot()"

### How To Distinguish Yourself

Ask yourself in the interview:

> "Can I explain why fewer multiplications matter asymptotically?"

> "What practical problems does conventional wisdom solve better?"

> "How would I decide between two asymptotically different algorithms?"

Asking these shows **algorithmic maturity.**

---

## Part 14: Deep Dive: Why These Specific 7 Products?

### The Intuition

The 7 products encode **clever algebraic identities**:

```
Notice M1: (A11 + A22)(B11 + B22)
    = A11·B11 + A11·B22 + A22·B11 + A22·B22
    
This appears in multiple output formulas!

M1 contributes to: C11 and C22

The choice of M1 means we compute this sum 
ONCE (not twice), saving a multiplication.

Same principle for M2-M7: each is chosen to appear 
in multiple output formulas.
```

### The Discovery Process

Strassen didn't hand-derive these formulas. Instead:

1. **Algebraic analysis:** Express Cij as polynomials in A and B entries
2. **Common subexpression elimination:** Find minimal set of products
3. **Computer search:** Try combinations systematically
4. **Verification:** Check that any set of 7 products works

This is **algorithmic research**, not classical problem-solving.

---

## Part 15: Connection to Other Fast Algorithms

### The Pattern Strassen Revealed

Strassen taught us: **Reduce the "inner" recursive multiplications.**

This pattern appears elsewhere:

| Algorithm | Problem | Improvement |
|-----------|---------|-------------|
| **Strassen** | Matrix mult | 8 → 7 products: O(n³) → O(n^2.81) |
| **Karatsuba** | Integer mult | 4 → 3 multiplies: O(n²) → O(n^1.585) |
| **FFT** | Polynomial mult | O(n²) → O(n log n) using frequency domain |
| **Schönhage-Strassen** | Large integer mult | O(n log n log log n) |

All follow the same principle: **Reformulate to reduce expensive operations.**

---

## Part 16: Practice Questions

### Understanding Questions

1. **Why is Strassen faster asymptotically?**
   - Answer: Reduces multiplications from 8 to 7; log₂(7) ≈ 2.81 < 3

2. **Can Strassen be slower than classical for some inputs?**
   - Answer: Yes, for small n where constant factors dominate

3. **What is the breakeven point (roughly)?**
   - Answer: Around n = 32-64, depends on implementation

4. **Why not use Strassen everywhere in practice?**
   - Answer: Constants, numerical stability, memory overhead, cache efficiency

5. **How did Strassen discover these specific 7 formulas?**
   - Answer: Algebraic analysis + computer search for minimal product set

### Application Questions

6. **If you had to implement matrix multiplication for a GPU, would you use Strassen? Why?**
   - Consider: memory bandwidth, parallel structure, numerical precision

7. **How would you modify Strassen for single-precision floats vs. exact arithmetic?**
   - Exact: Strassen is viable (no rounding error)
   - Float: Numerical stability is critical

8. **What's the space complexity of Strassen?**
   - Answer: O(n²) for recursion depth, plus temporary matrices

---

## Part 17: Key Takeaways for Study

| Concept | Remember |
|---------|----------|
| **7 Products** | M1-M7 are algebraically equivalent to the 8 classical products |
| **Recursion** | T(n) = 7T(n/2) + O(n²) |
| **Complexity** | O(n^log₂7) ≈ O(n^2.81) |
| **Practical** | BLAS beats Strassen for most applications |
| **Lesson** | Reformulation beats micro-optimization |
| **When to use** | Symbolic computation, theoretical CS, extreme scales |
| **Theory vs. Practice** | Asymptotic doesn't always mean practical |

---

## Part 18: Final Wisdom from Abdo

The point of Strassen is **not to teach you matrix multiplication.**

The point is to teach you:

1. **Problems can be reformulated** — The way you structure a computation affects its complexity
2. **Multiplication is expensive** — Whether algorithmic multiplications or arithmetic ones
3. **Asymptotic theory has limits** — Constants and implementation details matter enormously
4. **Think algebraically** — Use properties of your problem domain to simplify structure
5. **Long-term thinking** — Learn the principle, not just the algorithm

### The Deeper Pattern

Strassen shows that **truly fast algorithms come from deep insight, not surface optimization.**

Every great algorithm follows this pattern:
- Naive approach: O(something slow)
- Question assumptions: "Is this structure necessary?"
- Reformulation: "What if we structure it this other way?"
- Breakthrough: New complexity class



