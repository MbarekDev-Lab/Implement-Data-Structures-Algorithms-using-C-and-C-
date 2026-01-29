#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * MaxHeap Class
 *
 * A Max Heap is a complete binary tree where every parent node has a value
 * greater than or equal to its children. It's stored as an array/vector.
 *
 * Array Representation:
 *   - Parent of index i: (i-1)/2
 *   - Left child of i:   2*i + 1
 *   - Right child of i:  2*i + 2
 *
 * Example:      50
 *              /  \
 *            35    40
 *           / \    /
 *         20  30  25
 *
 * Array: [50, 35, 40, 20, 30, 25]
 * Index:  0   1   2   3   4   5
 */
class MaxHeap
{
private:
    vector<int> heap;

    // Helper function to get parent index
    int parent(int i) { return (i - 1) / 2; }

    // Helper function to get left child index
    int leftChild(int i) { return 2 * i + 1; }

    // Helper function to get right child index
    int rightChild(int i) { return 2 * i + 2; }

    /**
     * Heapify Up (Bubble Up)
     * Moves element at index i upward to maintain heap property
     * Time Complexity: O(log n)
     */
    void heapifyUp(int i)
    {
        while (i > 0 && heap[i] > heap[parent(i)])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    /**
     * Heapify Down (Bubble Down)
     * Moves element at index i downward to maintain heap property
     * Time Complexity: O(log n)
     */
    void heapifyDown(int i)
    {
        int maxIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);

        // Find largest among node, left child, and right child
        if (left < static_cast<int>(heap.size()) && heap[left] > heap[maxIndex])
        {
            maxIndex = left;
        }
        if (right < static_cast<int>(heap.size()) && heap[right] > heap[maxIndex])
        {
            maxIndex = right;
        }

        // If largest is not the current node, swap and continue
        if (i != maxIndex)
        {
            swap(heap[i], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    MaxHeap() {}

    /**
     * Constructor from array
     * Builds heap from existing array
     * Time Complexity: O(n log n) using repeated insert
     */
    MaxHeap(const vector<int> &arr)
    {
        for (int val : arr)
        {
            insert(val);
        }
    }

    /**
     * Insert a new element into the heap
     * Time Complexity: O(log n)
     *
     * Process:
     * 1. Add element at the end
     * 2. Bubble up to maintain heap property
     */
    void insert(int key)
    {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    /**
     * Extract (remove and return) the maximum element
     * Time Complexity: O(log n)
     *
     * Process:
     * 1. Store the root (maximum element)
     * 2. Move last element to root
     * 3. Bubble down to maintain heap property
     */
    int extractMax()
    {
        if (heap.empty())
        {
            throw runtime_error("Heap is empty!");
        }

        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
        {
            heapifyDown(0);
        }

        return maxVal;
    }

    /**
     * Peek at the maximum element without removing it
     * Time Complexity: O(1)
     */
    int getMax() const
    {
        if (heap.empty())
        {
            throw runtime_error("Heap is empty!");
        }
        return heap[0];
    }

    /**
     * Get the size of the heap
     */
    int size() const
    {
        return heap.size();
    }

    /**
     * Check if heap is empty
     */
    bool isEmpty() const
    {
        return heap.empty();
    }

    /**
     * Print heap as array
     */
    void print() const
    {
        cout << "Heap: [";
        for (size_t i = 0; i < heap.size(); i++)
        {
            cout << heap[i];
            if (i < heap.size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }

    /**
     * Print heap as tree (simple representation)
     */
    void printTree() const
    {
        if (heap.empty())
        {
            cout << "Empty heap" << endl;
            return;
        }

        int level = 0;
        int levelSize = 1;
        size_t idx = 0;

        while (idx < heap.size())
        {
            // Print spaces for indentation
            for (int i = 0; i < (1 << (3 - level)); i++)
                cout << " ";

            // Print elements at this level
            for (int i = 0; i < levelSize && idx < heap.size(); i++)
            {
                cout << heap[idx++] << " ";
            }
            cout << endl;

            level++;
            levelSize *= 2;
        }
    }

    /**
     * Get underlying vector (for testing)
     */
    const vector<int> &getHeap() const
    {
        return heap;
    }
};

/**
 * Heap Sort
 * Sorts array in ascending order using Max Heap
 * Time Complexity: O(n log n)
 * Space Complexity: O(1) in-place
 */
void heapSort(vector<int> &arr)
{
    MaxHeap heap(arr);
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        arr[i] = heap.extractMax();
    }
}

// ==================== DEMONSTRATION ====================

int main()
{
    cout << "===========================================" << endl;
    cout << "   MAX HEAP IMPLEMENTATION DEMO" << endl;
    cout << "===========================================" << endl
         << endl;

    // Test 1: Basic Insert Operations
    cout << "Test 1: Building Heap with Insertions" << endl;
    cout << "---------------------------------------" << endl;
    MaxHeap heap1;
    int values[] = {10, 20, 30, 25, 5, 40, 35};

    cout << "Inserting: ";
    for (int val : values)
    {
        cout << val << " ";
        heap1.insert(val);
    }
    cout << endl;
    heap1.print();
    cout << "Max element: " << heap1.getMax() << endl;
    cout << "Heap size: " << heap1.size() << endl
         << endl;

    // Test 2: Constructor from Array
    cout << "Test 2: Building Heap from Array" << endl;
    cout << "---------------------------------------" << endl;
    vector<int> arr = {45, 35, 15, 30, 10, 12, 6, 5, 20};
    cout << "Original array: [";
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i];
        if (i < arr.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    MaxHeap heap2(arr);
    heap2.print();
    cout << "Max element: " << heap2.getMax() << endl
         << endl;

    // Test 3: Extract Max Operations
    cout << "Test 3: Extracting Maximum Elements" << endl;
    cout << "---------------------------------------" << endl;
    MaxHeap heap3({50, 30, 40, 10, 20, 35, 25});
    cout << "Initial heap: ";
    heap3.print();

    cout << "\nExtracting elements in descending order:" << endl;
    while (!heap3.isEmpty())
    {
        cout << heap3.extractMax() << " ";
    }
    cout << endl
         << endl;

    // Test 4: Heap Sort
    cout << "Test 4: Heap Sort" << endl;
    cout << "---------------------------------------" << endl;
    vector<int> unsorted = {64, 34, 25, 12, 22, 11, 90};
    cout << "Before sorting: [";
    for (size_t i = 0; i < unsorted.size(); i++)
    {
        cout << unsorted[i];
        if (i < unsorted.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    heapSort(unsorted);

    cout << "After sorting:  [";
    for (size_t i = 0; i < unsorted.size(); i++)
    {
        cout << unsorted[i];
        if (i < unsorted.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl
         << endl;

    // Test 5: Priority Queue Simulation
    cout << "Test 5: Priority Queue Simulation" << endl;
    cout << "---------------------------------------" << endl;
    MaxHeap pq;
    cout << "Adding tasks with priorities..." << endl;
    pq.insert(5);
    cout << "  Task priority 5 added" << endl;
    pq.insert(3);
    cout << "  Task priority 3 added" << endl;
    pq.insert(8);
    cout << "  Task priority 8 added" << endl;
    pq.insert(1);
    cout << "  Task priority 1 added" << endl;
    pq.insert(10);
    cout << "  Task priority 10 added" << endl;

    cout << "\nProcessing tasks by priority:" << endl;
    while (!pq.isEmpty())
    {
        cout << "  Processing task with priority: " << pq.extractMax() << endl;
    }

    cout << "\n===========================================" << endl;
    cout << "   DEMO COMPLETED SUCCESSFULLY!" << endl;
    cout << "===========================================" << endl;

    return 0;
}

/*

    benraiss@Mbareks-MacBook-Air heap % clang++ -std=c++17 -Wall -Wextra -o _treeheap Heap.cpp
    benraiss@Mbareks-MacBook-Air heap % _treeheap
    zsh: command not found: _treeheap
    benraiss@Mbareks-MacBook-Air heap % ./_treeheap
    ===========================================
    MAX HEAP IMPLEMENTATION DEMO
    ===========================================

    Test 1: Building Heap with Insertions
    ---------------------------------------
    Inserting: 10 20 30 25 5 40 35
    Heap: [40, 25, 35, 10, 5, 20, 30]
    Max element: 40
    Heap size: 7

    Test 2: Building Heap from Array
    ---------------------------------------
    Original array: [45, 35, 15, 30, 10, 12, 6, 5, 20]
    Heap: [45, 35, 15, 30, 10, 12, 6, 5, 20]
    Max element: 45

    Test 3: Extracting Maximum Elements
    ---------------------------------------
    Initial heap: Heap: [50, 30, 40, 10, 20, 35, 25]

    Extracting elements in descending order:
    50 40 35 30 25 20 10

    Test 4: Heap Sort
    ---------------------------------------
    Before sorting: [64, 34, 25, 12, 22, 11, 90]
    After sorting:  [11, 12, 22, 25, 34, 64, 90]

    Test 5: Priority Queue Simulation
    ---------------------------------------
    Adding tasks with priorities...
    Task priority 5 added
    Task priority 3 added
    Task priority 8 added
    Task priority 1 added
    Task priority 10 added

    Processing tasks by priority:
    Processing task with priority: 10
    Processing task with priority: 8
    Processing task with priority: 5
    Processing task with priority: 3
    Processing task with priority: 1

    ===========================================
    DEMO COMPLETED SUCCESSFULLY!
    ===========================================
    benraiss@Mbareks-MacBook-Air heap %

*/