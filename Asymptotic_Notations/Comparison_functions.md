## Asymptotic Notations — Complete Summary (DSA)

### 1. What is Asymptotic Analysis?

Asymptotic analysis is a method to evaluate an algorithm’s **efficiency based on input size (n)**, ignoring:

* Machine speed
* Programming language
* Compiler
* Hardware

The goal is to study **how an algorithm grows when n becomes very large**.

---

### 2. Why Asymptotic Notations Are Needed

Exact execution time depends on environment, so it is unreliable.

Asymptotic notations provide:

* Machine-independent analysis
* Fair comparison between algorithms
* Focus on growth rate, not exact time

Key idea:

> Performance matters most when **n → ∞**

---

### 3. Comparison of Functions (Growth Rates)

Common time complexities ordered from **best to worst**:

1 < log n < n < n log n < n² < n³ < 2ⁿ < n!

Rules:

* Lower growth rate = better scalability
* Constants do not matter for large n
* Polynomial time is better than exponential time

Example:

* O(n) is always better than O(n²) for large input sizes

---

### 4. Big-O Notation — O(f(n))

Represents the **upper bound** (worst-case complexity).

Meaning:

> The algorithm will **not take more time than this**.

Example:
f(n) = 3n² + 5n + 10
Big-O → **O(n²)**

Used for:

* Worst-case analysis
* Guaranteeing performance limits

---

### 5. Omega Notation — Ω(f(n))

Represents the **lower bound** (best-case complexity).

Meaning:

> The algorithm will **not take less time than this**.

Example:

* Linear Search best case → Ω(1)

Used for:

* Best-case analysis
* Theoretical minimum work

---

### 6. Theta Notation — Θ(f(n))

Represents the **tight bound** (exact growth rate).

Meaning:

> The algorithm grows **exactly at this rate**.

Example:
f(n) = 3n² + 5n + 10
Theta → **Θ(n²)**

Theta is used when:

* Upper bound and lower bound are the same

---

### 7. Rules for Using Asymptotic Notations

#### Rule 1: Ignore Constants

O(2n) → O(n)
O(100) → O(1)

#### Rule 2: Ignore Lower-Order Terms

O(n² + n) → O(n²)
O(n + log n) → O(n)

#### Rule 3: Loops

* Single loop → O(n)
* Nested loop → O(n²)
* Triple nested loop → O(n³)

#### Rule 4: Sequential Statements

O(n) + O(n²) → **O(n²)**
(Take the maximum)

#### Rule 5: Conditionals

Worst-case branch decides the complexity

---

### 8. Best, Worst, and Average Case Analysis

* **Best Case**: Minimum time required
* **Worst Case**: Maximum time required
* **Average Case**: Expected time over all inputs

Example (Linear Search):

| Case    | Time |
| ------- | ---- |
| Best    | O(1) |
| Worst   | O(n) |
| Average | O(n) |

Important exam rule:

> If not specified, **assume worst case (Big-O)**

---

### 9. Key Takeaways

* Asymptotic analysis focuses on **growth**, not exact time
* Big-O is the most commonly used notation
* Theta gives the exact complexity
* Omega gives the minimum complexity
* Worst case is the default unless stated otherwise
* This section is foundational for:

  * Divide & Conquer
  * Greedy Algorithms
  * Dynamic Programming
  * Recurrence Relations
  * Sorting and Searching Algorithms
