# Binary Search (Divide and Conquer) - Educational Reference

## 1. Core Idea

Binary search is not just a faster linear search. It is a clean example of the
divide-and-conquer strategy applied to a searching problem.

Key takeaway:

> Binary search works because the input is structured and we can discard half
> the search space at every step.

---

## 2. Problem Definition

**Goal:** Find a key in a **sorted** list or array.

Why sorted matters:
- Divide and conquer needs structure.
- Without order, you cannot eliminate half the input safely.

---

## 3. Divide and Conquer Mapping

Binary search follows the three-step pattern:

### Divide
Pick the middle element and split the array into two halves.

### Conquer
Decide which half can contain the key.

- If `key < mid`, search left half.
- If `key > mid`, search right half.

### Combine
There is nothing to combine. Many divide-and-conquer algorithms skip this step.

---

## 4. Why It Is Efficient

Every comparison cuts the problem size in half:

```
n -> n/2 -> n/4 -> n/8 -> ...
```

This is why binary search is fast even for large inputs.

---

## 5. Recursion Fits Naturally

Binary search repeatedly solves the same problem on a smaller input, and stops
when the subarray is empty or has one element.

You can implement it:
- Recursively (matches the divide-and-conquer idea)
- Iteratively (same logic, no call stack)

---

## 6. The Hidden Math Lesson

Each step halves the input size, so the number of steps is:

```
log2(n)
```

This is the first major example of **logarithmic time** complexity.

---

## 7. Time Complexity Insight

Compare:
- Linear search: `O(n)`
- Binary search: `O(log n)`

Reason:
Halving beats scanning, always.

---

## 8. Why Binary Search Is a Model Algorithm

Binary search teaches:
- Divide-and-conquer thinking
- Recursive structure
- Logarithmic complexity
- Dependence on input constraints (sorted data)

This mindset carries into:
- Merge sort
- Quick sort
- Recurrence relations

---

## 9. The Mental Checklist

When you see a problem, ask:
- Can I discard a large part of the input at each step?
- Is the input structured enough to allow that?
- Does the subproblem look like the original problem?

If yes, binary-search-like thinking may apply.

---

## 10. Final Message

Binary search is not about searching. It is about **eliminating unnecessary
work** using structure and halving.

If you understand why it is fast, you are ready for more advanced algorithms.

---

## Algorithm: Binary Search (Divide and Conquer)

**Input:**

- A sorted array `A[0 ... n-1]`
- A key value `key` to search

**Output:**

- Index of `key` if found
- Otherwise `-1`

---

### Step 1: Initialize

- Set `low = 0`
- Set `high = n - 1`

---

### Step 2: Repeat While `low <= high`

1. Compute middle index
	 `mid = (low + high) / 2`

2. Compare `A[mid]` with `key`

	 - If `A[mid] == key`
		 -> **Return `mid`** (element found)

	 - If `key < A[mid]`
		 -> Search left half
		 -> `high = mid - 1`

	 - If `key > A[mid]`
		 -> Search right half
		 -> `low = mid + 1`

---

### Step 3: Not Found Case

- If loop ends
	-> **Return `-1`**

---

### Key Notes (What Abdo Expects You to Say)

- Array **must be sorted**
- Each step eliminates **half of the array**
- Time Complexity: **O(log n)**
- Strategy Used: **Divide and Conquer**

---

## Recurrence Relation for Binary Search

### Step 1: Define the Problem Size

Let:

- `T(n)` = time taken to search in an array of size `n`

---

### Step 2: Observe What the Algorithm Does

At each step:

- One comparison is done → **constant time**
- The array size is reduced to **n / 2**

---

### Step 3: Write the Recurrence

$$T(n) = T(n/2) + c$$

Where:

- `T(n/2)` → recursive call on half the array
- `c` → constant time for comparison

---

### Step 4: Define the Base Case

When only one element is left:

$$T(1) = c$$

---

### Step 5: Expand the Recurrence

$$\begin{aligned}
T(n) &= T(n/2) + c \\
&= T(n/4) + c + c \\
&= T(n/8) + 3c \\
&\vdots
\end{aligned}$$

---

### Step 6: Find When Recursion Stops

Recursion stops when:

$$n / 2^k = 1$$

Solving:

$$k = \log_2 n$$

---

### Step 7: Final Result

$$T(n) = c \log_2 n + c$$

Ignoring constants:

$$\boxed{T(n) = O(\log n)}$$

---

### Key Sentence to Say (Very Important)

> "Since the problem size is halved at every step, the time complexity is logarithmic."

---

# Merge Sort - What Abdo Is Really Teaching

## 1. Why Simple Sorting Ideas Are Not Enough

Abdo starts by reminding you:

- Bubble Sort, Selection Sort, Insertion Sort -> **O(n^2)**
- They work, but they do not scale

Main lesson:

> For large data, naive algorithms completely break down.

So we need a **strategy**, not tricks.

---

## 2. Merge Sort Is a Divide and Conquer Solution

Abdo wants you to see Merge Sort as:
- Not just another sorting algorithm
- A clean Divide and Conquer model

He maps it clearly:

- **Divide** -> split array into halves
- **Conquer** -> sort each half recursively
- **Combine** -> merge two sorted halves

Unlike binary search, **Merge Sort needs the combine step**.

---

## 3. Why Dividing Helps in Sorting

Key insight Abdo stresses:

> Sorting small lists is easy.

So instead of sorting `n` elements:

- Sort two lists of `n/2`
- Merge them efficiently

This reduces complexity dramatically.

---

## 4. The Real Star: The Merge Step

Abdo emphasizes:

- Merging **two sorted arrays** can be done in **O(n)** time
- This is the secret weapon of Merge Sort

Without efficient merge, Divide and Conquer fails.

This prepares you mentally for:

- K-way merging
- External sorting

---

## 5. The Hidden Mathematical Lesson

Abdo wants you to notice the pattern:

- Divide -> log n levels
- Merge at each level -> n work

So total work becomes:

```
n * log n
```

That is how we escape **O(n^2)**.

---

## 6. Recursion Is Not Optional Here

Merge Sort:

- Cannot be written cleanly without recursion
- Naturally forms a recursion tree

This lecture connects directly to:

- Recurrence relations
- Master Theorem

---

## 7. Stability and Predictability

Abdo highlights:

- Merge Sort is **stable**
- Time complexity is **always O(n log n)**
	(best, average, worst - same)

This predictability is important in real systems.

---

## 8. What Abdo Is Training You For

This lecture is preparation for:

- Writing recurrence relations
- Understanding recursion trees
- Advanced algorithms (Quick Sort, DP, External Sorting)

He wants you to **trust strategy over brute force**.

---

## 9. Abdo's Silent Message

> "First divide the problem correctly - the solution will become simple."

Merge Sort teaches **discipline in algorithm design**.
