#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// MERGE SORT: Divide & Conquer Approach
// ============================================================================
// Time Complexity: O(n log n) - best, average, worst case
// Space Complexity: O(n) - temporary array for merging
// Stability: Yes - maintains relative order of equal elements
// ============================================================================

// Function to merge two sorted subarrays in-place using a temporary buffer
// Uses the O(n) merge step that is the "secret weapon" of Merge Sort
void Merge(int *arr, int left, int mid, int right)
{
    // Calculate sizes of the two subarrays
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    // Create temporary arrays
    int *leftArr = (int *)malloc(leftSize * sizeof(int));
    int *rightArr = (int *)malloc(rightSize * sizeof(int));

    if (!leftArr || !rightArr)
    {
        perror("malloc");
        free(leftArr);
        free(rightArr);
        return;
    }

    // Copy data to temporary arrays
    memcpy(leftArr, &arr[left], leftSize * sizeof(int));
    memcpy(rightArr, &arr[mid + 1], rightSize * sizeof(int));

    // Merge the two temporary arrays back into arr[left..right]
    int i = 0;    // Initial index of left subarray
    int j = 0;    // Initial index of right subarray
    int k = left; // Initial index of merged subarray

    // Compare elements and merge smallest first (Conquer step)
    while (i < leftSize && j < rightSize)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k++] = leftArr[i++];
        }
        else
        {
            arr[k++] = rightArr[j++];
        }
    }

    // Copy remaining elements from left subarray
    while (i < leftSize)
    {
        arr[k++] = leftArr[i++];
    }

    // Copy remaining elements from right subarray
    while (j < rightSize)
    {
        arr[k++] = rightArr[j++];
    }

    // Free temporary arrays
    free(leftArr);
    free(rightArr);
}

// Recursive merge sort function
// Implements the Divide & Conquer strategy:
// DIVIDE: split array into two halves
// CONQUER: recursively sort each half
// COMBINE: merge two sorted halves
void MergeSortHelper(int *arr, int left, int right)
{
    if (left < right)
    {
        // DIVIDE: find the middle point
        int mid = left + (right - left) / 2;

        // CONQUER: recursively sort first half
        MergeSortHelper(arr, left, mid);

        // CONQUER: recursively sort second half
        MergeSortHelper(arr, mid + 1, right);

        // COMBINE: merge the sorted halves
        Merge(arr, left, mid, right);
    }
}

// Public interface for Merge Sort
void MergeSort(int *arr, int n)
{
    if (n <= 1)
        return;

    MergeSortHelper(arr, 0, n - 1);
}

// Utility function to print an array
void PrintArray(const int *arr, int n, const char *label)
{
    printf("%s: ", label);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// ============================================================================
// DEMONSTRATION: Merge of Two Sorted Arrays (Building block of Merge Sort)
// ============================================================================
void AlgoMerge(const int *A, const int *B, int m, int n)
{
    int i = 0, j = 0, k = 0;
    int *C = (int *)malloc((m + n) * sizeof(int));
    if (!C)
    {
        perror("malloc");
        return;
    }

    while (i < m && j < n)
    {
        if (A[i] < B[j])
        {
            C[k++] = A[i++];
        }
        else
        {
            C[k++] = B[j++];
        }
    }
    for (; i < m; i++)
    {
        C[k++] = A[i];
    }
    for (; j < n; j++)
    {
        C[k++] = B[j];
    }

    for (i = 0; i < m + n; i++)
    {
        printf("%d ", C[i]);
    }
    printf("\n");

    free(C);
}

int main(int argc, char const *argv[])
{
    printf("=== MERGE SORT DEMONSTRATION ===\n\n");

    // Test 1: Merge two sorted arrays (the O(n) building block)
    printf("--- Test 1: Merge Two Sorted Arrays ---\n");
    printf("Array A: ");
    AlgoMerge((int[]){1, 3, 5}, (int[]){2, 4, 6}, 3, 3);

    // Test 2: Full Merge Sort with unsorted array
    printf("\n--- Test 2: Full Merge Sort ---\n");
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    PrintArray(arr1, n1, "BEFORE");
    MergeSort(arr1, n1);
    PrintArray(arr1, n1, "AFTER");

    // Test 3: Already sorted array
    printf("\n--- Test 3: Already Sorted Array ---\n");
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    PrintArray(arr2, n2, "BEFORE");
    MergeSort(arr2, n2);
    PrintArray(arr2, n2, "AFTER");

    // Test 4: Reverse sorted array (worst case for some, not Merge Sort)
    printf("\n--- Test 4: Reverse Sorted Array ---\n");
    int arr3[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    PrintArray(arr3, n3, "BEFORE");
    MergeSort(arr3, n3);
    PrintArray(arr3, n3, "AFTER");

    // Test 5: Single element (trivial case)
    printf("\n--- Test 5: Single Element ---\n");
    int arr4[] = {42};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    PrintArray(arr4, n4, "BEFORE");
    MergeSort(arr4, n4);
    PrintArray(arr4, n4, "AFTER");

    // Test 6: Duplicate elements (tests stability)
    printf("\n--- Test 6: Array with Duplicates ---\n");
    int arr5[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);

    PrintArray(arr5, n5, "BEFORE");
    MergeSort(arr5, n5);
    PrintArray(arr5, n5, "AFTER");

    return 0;
}

/*
### 1. Why Simple Sorting Ideas Are Not Enough

* Bubble Sort, Selection Sort, Insertion Sort → **O(n²)**
* They work, but they **don’t scale**

Main lesson:

> For large data, naïve algorithms completely break down.

So we need a **strategy**, not tricks.

---

### 2. Merge Sort Is a Divide & Conquer Solution

Abdo wants you to see Merge Sort as:
“just another sorting algorithm”
“a perfect Divide & Conquer model”

maps it clearly:

* **Divide** → split array into halves
* **Conquer** → sort each half recursively
* **Combine** → merge two sorted halves

maps it clearly:

* **Divide** → split array into halves
* **Conquer** → sort each half recursively
* **Combine** → merge two sorted halves

 Unlike Binary Search, **Merge Sort NEEDS the combine step**.

---

### 3. Why Dividing Helps in Sorting

Key insight Abdo stresses:

> Sorting small lists is easy.

So instead of sorting `n` elements:

* Sort two lists of `n/2`
* Then merge them efficiently

This reduces complexity dramatically.

---

### 4. The Real Star: The Merge Step

Abdo emphasizes:

* Merging **two sorted arrays** can be done in **O(n)** time
* This is the *secret weapon* of Merge Sort

Without efficient merge:

* Divide & Conquer fails

This prepares you mentally for:

* K-way merging
* External sorting

---

### 5. The Hidden Mathematical Lesson

Abdo wants you to notice the pattern:

* Divide → log n levels
* Merge at each level → n work

So total work becomes:

```
n × log n
```

That’s how we escape **O(n²)**.

---

### 6. Recursion Is Not Optional Here

Merge Sort:

* Cannot be written cleanly without recursion
* Naturally forms a **recursion tree**

This lecture connects directly to:

* Recurrence relations
* Master Theorem

---

### 7. Stability and Predictability

Abdo highlights:

* Merge Sort is **stable**
* Time complexity is **always O(n log n)**
  (best, average, worst — same)

This predictability is extremely important in real systems.

---

### 8. What Abdo Is Training You For

This lecture is preparation for:

* Writing recurrence relations
* Understanding recursion trees
* Advanced algorithms (Quick Sort, DP, External Sorting)

He wants you to **trust strategy over brute force**.

---

### 9. Abdo’s Silent Message

> “First divide the problem correctly —
> the solution will become simple.”

Merge Sort teaches **discipline in algorithm design**

*/